package com.example.demo.models.dtos;

import com.example.demo.models.entities.OrderDetails;
import com.fasterxml.jackson.annotation.JsonPropertyOrder;

import jakarta.validation.constraints.NotBlank;
import lombok.EqualsAndHashCode;

@EqualsAndHashCode(callSuper = true)
@JsonPropertyOrder({"id", "orderId", "productId", "product", "quantity"})
public class OrderDetailFullDto extends OrderDetailReadDto {
    
    @NotBlank(message = "orderId is required")
    public int orderId;

    public OrderDetailFullDto(OrderDetails other) {
        super(other);
        this.orderId = other.getOrder().getId();
    }
}
