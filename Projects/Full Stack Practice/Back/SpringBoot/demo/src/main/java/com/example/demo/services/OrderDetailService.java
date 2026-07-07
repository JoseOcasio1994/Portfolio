package com.example.demo.services;

import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import com.example.demo.models.dtos.OrderDetailReadDto;
import com.example.demo.models.dtos.OrderDetailFullDto;
import com.example.demo.models.dtos.OrderDetailDto;
import com.example.demo.models.entities.Order;
import com.example.demo.models.entities.OrderDetails;
import com.example.demo.models.entities.Product;
import com.example.demo.repository.OrderDetailRepo;
import com.example.demo.repository.ProductRepo;

import javassist.NotFoundException;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;
import java.util.concurrent.CopyOnWriteArrayList;

@Service
@RequiredArgsConstructor
@Slf4j
public class OrderDetailService {

    @Autowired
    private OrderDetailRepo repo;
    @Autowired
    private ProductRepo productRepo;

    public List<OrderDetailReadDto> getAllOrderDetails() {
        List<OrderDetails> details = repo.findAll();
        return convertToDtoList(details);
    }

    public List<OrderDetails> getDetailsByOrderId(int orderId) {
        List<OrderDetails> details = repo.findByOrderId(orderId);
        return details;
    }

    public OrderDetailReadDto getOrderDetailById(Integer id) {
        OrderDetails detail = repo.findById(id).orElse(null);
        return detail != null ? convertToDto(detail) : null;
    }

    public OrderDetailFullDto getFullOrderDetailById(Integer id) {
        OrderDetails detail = repo.findById(id).orElse(null);
        return detail != null ? new OrderDetailFullDto(detail) : null;
    }

    public List<OrderDetails> saveOrderDetails(List<OrderDetailDto> dtos, Order order) throws NotFoundException {
        List<OrderDetails> detailList = new CopyOnWriteArrayList<>();

        for (OrderDetailDto dto : dtos) {

            Optional<Product> product = productRepo.findById(dto.productId);
            if (product.isEmpty()) {
                throw new NotFoundException("Product With Id " + dto.productId + " not found.");
            }

            OrderDetails details = convertToEntity(dto);
            details.Init(order, product.get());

            detailList.add(details);
        }

        List<OrderDetails> saved = repo.saveAll(detailList);
        log.info("{} Order Details saved successfully", saved.size());

        return saved;
    }

    public OrderDetailReadDto updateOrderDetails(OrderDetailDto dto, Integer id, Order order) throws NotFoundException {

        OrderDetails existingOrderDetails = repo.findById(id).orElse(null);
        if (existingOrderDetails == null) {
            throw new NotFoundException("Order Detail With Id " + id + " not found.");
        }

        Optional<Product> product = productRepo.findById(dto.productId);
        if (product.isEmpty()) {
            throw new NotFoundException("Product With Id " + dto.productId + " not found.");
        }

        OrderDetails detail = convertToEntity(dto);

        detail.update(existingOrderDetails);
        detail.setProduct(product.get());

        if (order != null) {
            detail.setOrder(order);
        }
        else {
            detail.setOrder(existingOrderDetails.getOrder());
        }

        OrderDetails saved = repo.save(detail);
        log.info("OrderDetails with id: {} updated successfully", id);
        return new OrderDetailReadDto(saved);
    }

    public void deleteOrderDetailById(Integer id) {
        if (repo.existsById(id)) {
            repo.deleteById(id);
        }
    }

    public void deleteOrderDetailByOrderId (Integer id) {
        if(repo.existsByOrderId(id)) {
            repo.deleteByOrderId(id);
        }
    }

    public void deleteAll() {
        repo.deleteAll();
    }

    private List<OrderDetailReadDto> convertToDtoList(List<OrderDetails> details) {
        List<OrderDetailReadDto> dtos = new ArrayList<>();
        for (OrderDetails d : details) {
            dtos.add(convertToDto(d));
        }

        return dtos;
    }

    public OrderDetailReadDto convertToDto(OrderDetails d) {
        return new OrderDetailReadDto(d);
    }

    public OrderDetails convertToEntity(OrderDetailDto dto) {
        return new OrderDetails(dto);
    }

}
