package com.example.demo.models.dtos;

import com.example.demo.models.entities.Product;

import jakarta.validation.constraints.Digits;
import jakarta.validation.constraints.NotBlank;
import jakarta.validation.constraints.NotNull;
import jakarta.validation.constraints.Size;

public class ProductDto {
    
    @NotBlank(message = "productName is required")
    @Size(min = 3, max = 50, message = "productName must be between 3 and 50 characters")
    public String productName;

    @NotNull(message = "categoryId is required")
    public int categoryId;

    @Size(min = 3, max = 50, message = "unit must be between 3 and 50 characters")
    public String unit;

    @NotNull(message = "price is required")
    @Digits(integer = 8, fraction = 3, message = "Value must have at most 8 integral digits and 3 fractional digits")
    public Float price;

    public ProductDto() {}

    public ProductDto(Product other) {
        this.productName = other.getProductName();
        this.unit = other.getUnit();
        this.price = other.getPrice();
        this.categoryId = other.getCategory().getId();
    }
}
