package com.example.demo.models.dtos;

import java.time.LocalDate;
import java.util.List;
import java.util.concurrent.CopyOnWriteArrayList;

import com.example.demo.models.entities.Order;
import com.example.demo.models.entities.OrderDetails;
import com.fasterxml.jackson.annotation.JsonPropertyOrder;

import lombok.NoArgsConstructor;
import lombok.extern.slf4j.Slf4j;

@Slf4j
@NoArgsConstructor
@JsonPropertyOrder({"customerId", "orderDate", "details"})
public class OrderDto {
    public List<OrderDetailDto> details = new CopyOnWriteArrayList<>();
    public LocalDate orderDate;
    public int customerId;

    public OrderDto(Order other) {
        this.orderDate = other.getOrderDate();
        this.customerId = other.getCustomer().getId();
        for (OrderDetails d : other.getDetails()) {
            OrderDetailReadDto dto = new OrderDetailReadDto(d);
            details.add(dto);
        }
    }
}
