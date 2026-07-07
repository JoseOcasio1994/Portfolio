package com.microservice.order_service.services;

import com.microservice.order_service.dtos.InventoryResponse;
import com.microservice.order_service.dtos.OrderLineItemsDto;
import com.microservice.order_service.dtos.OrderRequest;
import com.microservice.order_service.events.OrderPlacedEvent;
import com.microservice.order_service.models.Order;
import com.microservice.order_service.models.OrderLineItem;
import com.microservice.order_service.repos.OrderRepo;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.kafka.core.KafkaTemplate;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.web.reactive.function.client.WebClient;

import java.util.Arrays;
import java.util.List;
import java.util.UUID;

@Service
@RequiredArgsConstructor
@Transactional
@Slf4j
public class OrderService {

    private final OrderRepo repo;
    private final WebClient.Builder webClientBuilder;
    private final KafkaTemplate<String, OrderPlacedEvent> kafkaTemplate;
    public String placeOrder(OrderRequest request){
        Order order = new Order();
        order.setOrderNumber(UUID.randomUUID().toString());
        
        var items = request.getItems().stream().map(this::mapToDto).toList();
        order.setItems(items);

        List<String> skuCodes = order.getItems().stream()
                .map(OrderLineItem::getSkuCode)
                .toList();

        InventoryResponse[] result = webClientBuilder.build().get()
                .uri("http://inventory-service/api/inventory",
                        uriBuilder -> uriBuilder.queryParam("skuCode", skuCodes).build())
                .retrieve()
                .bodyToMono(InventoryResponse[].class)
                .block();

        boolean allProductsInStock = Arrays.stream(result).allMatch(InventoryResponse::isInStock);

        if (allProductsInStock) {
            repo.save(order);
            try {
                kafkaTemplate.send("notificationTopic", new OrderPlacedEvent(order.getOrderNumber()));
            } catch (Exception e) {
                log.error(e.getStackTrace().toString());
                throw new RuntimeException(e);
            }
            return "Order Placed Successfully";
        } else {
            throw new IllegalArgumentException("Product Is Not In Stock.");
        }
    }

    private OrderLineItem mapToDto(OrderLineItemsDto dto) {
        return new OrderLineItem(dto);
    }

}
