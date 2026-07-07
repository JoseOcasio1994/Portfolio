package com.microservice.order_service.models;

import com.microservice.order_service.dtos.OrderLineItemsDto;
import jakarta.persistence.*;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

import java.math.BigDecimal;

@Entity
@Table(name = "order_line_items")
@AllArgsConstructor
@NoArgsConstructor
@Getter
@Setter
public class OrderLineItem {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;
    private String skuCode;
    private BigDecimal price;
    private Integer quantity;

    public OrderLineItem(OrderLineItemsDto dto) {
        setSkuCode(dto.getSkuCode());
        setPrice(dto.getPrice());
        setQuantity(dto.getQuantity());
    }
}
