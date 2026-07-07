package com.example.demo.models.dtos;

import com.example.demo.models.entities.Category;

import jakarta.validation.constraints.NotBlank;
import jakarta.validation.constraints.Size;

public class CategoryDto {

    @NotBlank(message = "categoryName is required")
    @Size(min = 3, max = 50, message = "categoryName must be between 3 and 50 characters")
    public String categoryName;

    @NotBlank(message = "description is required")
    @Size(min = 3, max = 50, message = "description must be between 3 and 50 characters")
    public String description;

    public CategoryDto() {
    }

    public CategoryDto(String name, String descr) {
        this.categoryName = name;
        this.description = descr;
    }

    public CategoryDto(Category other) {
        this.categoryName = other.getCategoryName();
        this.description = other.getDescription();
    }
}
