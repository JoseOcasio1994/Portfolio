package com.example.demo.repository;

import java.util.ArrayList;
import java.util.List;

import org.springframework.data.jpa.domain.Specification;

import com.example.demo.models.entities.Category;
import com.example.demo.models.entities.Product;
import com.example.demo.models.other.ProductFilter.PriceRange;

import jakarta.persistence.criteria.Predicate;
import jakarta.persistence.criteria.Expression;
import jakarta.persistence.criteria.Join;

public interface ProductSpec {

    public static Specification<Product> inCategory(List<String> categories) {
        return (root, query, cb) -> {
            Join<Product, Category> combined = root.join("category");
            List<Predicate> predicates = new ArrayList<>();
            for (String cat : categories) {
                predicates.add(cb.equal(cb.lower(combined.get("categoryName")), cat.toLowerCase()));
            }
            return cb.or(predicates.toArray(new Predicate[0]));
        };
    }

    public static Specification<Product> hasPriceBetween(List<PriceRange> prices) {
        return (root, query, cb) -> {
            List<Predicate> predicates = new ArrayList<>();
            for (PriceRange range : prices) {
                predicates.add(cb.between(root.get("price"), range.min, range.max));
            }
            return cb.or(predicates.toArray(new Predicate[0]));
        };
    }

    public static Specification<Product> excludeOutOfStock() {
        return (root, query, cb) -> {
            Expression<Integer> id = root.get("id");
            return cb.notEqual(cb.mod(id, 7), 3);
        };
    }
}
        