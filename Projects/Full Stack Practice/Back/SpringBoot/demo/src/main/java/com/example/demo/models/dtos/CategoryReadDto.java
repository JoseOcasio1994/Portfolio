package com.example.demo.models.dtos;

import com.example.demo.models.entities.Category;
import com.fasterxml.jackson.annotation.JsonPropertyOrder;

import lombok.EqualsAndHashCode;

@EqualsAndHashCode(callSuper = true)
@JsonPropertyOrder({"id", "categoryName", "description"})
public class CategoryReadDto extends CategoryDto {
    public int id;

    public CategoryReadDto(Category other) {
        super(other);
        this.id = other.getId();
    }

    @Override
    public String toString() {
        return "CategoryReadDto(name=" + categoryName + ")";
    }

}
