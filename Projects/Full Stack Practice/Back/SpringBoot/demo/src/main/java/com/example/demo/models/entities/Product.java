package com.example.demo.models.entities;

import jakarta.persistence.CascadeType;
import jakarta.persistence.Entity;
import jakarta.persistence.JoinColumn;
import jakarta.persistence.ManyToOne;
import jakarta.persistence.OneToMany;
import jakarta.persistence.Table;
import lombok.Data;
import lombok.EqualsAndHashCode;
import lombok.NoArgsConstructor;

import java.util.HashSet;
import java.util.Set;

import com.example.demo.models.dtos.ProductDto;

@NoArgsConstructor
@Data
@EqualsAndHashCode(callSuper = true)
@Entity
@Table(name = "products", schema = "public")
public class Product extends BaseModel {

    private String productName;
    private String unit;
    private Float price;

    @ManyToOne(cascade = CascadeType.PERSIST)
    @JoinColumn(name = "categoryId")
    private Category category;

    @OneToMany(mappedBy = "product", cascade = CascadeType.ALL, orphanRemoval = true)
    private Set<OrderDetails> detail = new HashSet<>();

    public Product(ProductDto dto) {
        this.productName = dto.productName;
        this.unit = dto.unit;
        this.price = dto.price;
    }

    @Override
    public String toString() {
        return "Product [id=" + id + ", name=" + productName + "]";
    }

}

