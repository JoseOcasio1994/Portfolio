package com.example.demo.models.dtos;

import com.example.demo.models.entities.OrderDetails;
import com.fasterxml.jackson.annotation.JsonPropertyOrder;

import lombok.EqualsAndHashCode;

@EqualsAndHashCode(callSuper = true)
@JsonPropertyOrder({"id", "productId", "productName", "quantity"})
public class OrderDetailReadDto extends OrderDetailDto {
    
    public int id;
    public String product;

    public OrderDetailReadDto(OrderDetails other) {
        super(other);
        this.id = other.getId();
        this.product = other.getProduct().getProductName();
    }
}
