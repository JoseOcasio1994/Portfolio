package com.example.demo.models.dtos;

import com.example.demo.models.entities.Product;
import com.fasterxml.jackson.annotation.JsonPropertyOrder;

import lombok.EqualsAndHashCode;

@EqualsAndHashCode(callSuper = true)
@JsonPropertyOrder({"id", "productName", "category", "categoryId", "unit", "price", "stock"})
public class ProductReadDto extends ProductDto {

    public String category;
    public int id, stock;

    public ProductReadDto(Product other) {
        super(other);
        this.category = other.getCategory().getCategoryName();
        this.id = other.getId();
        if (id % 7 == 3) {
            this.stock = 0;
        }
        else {
            this.stock = (int) (Math.random() * 10) % 7 + 1;
        }
    }
}
