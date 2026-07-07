package com.microservice.product_service.services;

import com.microservice.product_service.dtos.ProductRequest;
import com.microservice.product_service.dtos.ProductResponse;
import com.microservice.product_service.models.Product;
import com.microservice.product_service.repos.ProductRepo;
import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
@RequiredArgsConstructor
@Slf4j
public class ProductService {

    private final ProductRepo repo;

    public void createProduct(ProductRequest request){
        Product product = Product.builder()
                .name(request.getName())
                .description(request.getDescription())
                .price(request.getPrice())
                .build();

        repo.save(product);
        log.info("Product {}({}) is saved", product.getId(), product.getName());
    }

    public List<ProductResponse> getAllProducts() {
        List<Product> products = repo.findAll();
        return products.stream().map(this::mapToResponse).toList();
    }

    private ProductResponse mapToResponse(Product p) {
        return ProductResponse.builder()
                .id(p.getId())
                .name(p.getName())
                .description(p.getDescription())
                .price(p.getPrice())
                .build();
    }
}
