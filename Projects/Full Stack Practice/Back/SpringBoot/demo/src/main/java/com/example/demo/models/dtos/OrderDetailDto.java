package com.example.demo.models.dtos;

import com.example.demo.models.entities.OrderDetails;

import jakarta.validation.constraints.Min;
import jakarta.validation.constraints.NotBlank;
import lombok.NoArgsConstructor;

@NoArgsConstructor
public class OrderDetailDto {

    @NotBlank(message = "quantity is required")
    @Min(value = 1, message = "Quantity must be greater than 0")
    public Integer quantity;

    @NotBlank(message = "productId is required")
    public Integer productId;

    public OrderDetailDto(OrderDetails other) {
        this.quantity = other.getQuantity();
        this.productId = other.getProduct().getId();
    }
}
