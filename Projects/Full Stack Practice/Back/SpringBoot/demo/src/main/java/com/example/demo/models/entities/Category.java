package com.example.demo.models.entities;

import jakarta.persistence.CascadeType;
import jakarta.persistence.Entity;
import jakarta.persistence.OneToMany;
import jakarta.persistence.Table;
import lombok.Data;
import lombok.EqualsAndHashCode;
import lombok.NoArgsConstructor;

import java.util.HashSet;
import java.util.Set;

import com.example.demo.models.dtos.CategoryDto;

@NoArgsConstructor
@Data
@EqualsAndHashCode(callSuper = true)
@Entity
@Table(name = "categories", schema = "public")
public class Category extends BaseModel {

    private String categoryName;
    private String description;
    
    @OneToMany(mappedBy = "category", cascade = CascadeType.ALL, orphanRemoval = true)
    private Set<Product> product = new HashSet<>();

    public Category(CategoryDto dto) {
        this.categoryName = dto.categoryName;
        this.description = dto.description;
    }

    @Override
    public String toString() {
        return "Category [id=" + id + ", name=" + categoryName + "]";
    }

}

