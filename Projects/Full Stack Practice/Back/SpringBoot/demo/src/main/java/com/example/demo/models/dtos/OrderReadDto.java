package com.example.demo.models.dtos;

import com.example.demo.models.entities.Order;
import com.fasterxml.jackson.annotation.JsonPropertyOrder;

import lombok.EqualsAndHashCode;

@EqualsAndHashCode(callSuper = true)
@JsonPropertyOrder({"id", "customerId", "customer", "orderDate", "details"})
public class OrderReadDto extends OrderDto {
    public int id;
    public String customer;

    public OrderReadDto(Order other) {
        super(other);
        this.id = other.getId();
        this.customer = other.getCustomer().getCustomerName();
    }
}
