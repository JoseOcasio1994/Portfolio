package com.example.demo.controllers;

import lombok.RequiredArgsConstructor;
import org.springframework.http.ResponseEntity;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;
import org.springdoc.core.annotations.ParameterObject;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.web.PageableDefault;

import com.example.demo.models.dtos.ProductReadDto;
import com.example.demo.models.other.ProductFilter;
import com.example.demo.models.dtos.ProductDto;
import com.example.demo.services.ProductService;

import io.swagger.v3.oas.annotations.tags.Tag;
import jakarta.validation.Valid;
import javassist.NotFoundException;

import java.net.URISyntaxException;

@RestController
@RequestMapping("/api/product")
@RequiredArgsConstructor
@Tag(name = "Product", description = "Provides APIs for managing Products") 
public class ProductController {
    @Autowired
    private ProductService productService;

    /**
     * This method is called when a GET request is made
     * URL: localhost:8080/product/
     * Purpose: Fetches all the products in the product table
     * @return List of Products
     */
    @GetMapping("/")
    public ResponseEntity<Page<ProductReadDto>> getAllProducts(
            @ParameterObject ProductFilter filter,
            @ParameterObject @PageableDefault(size = 10, page = 0) Pageable pageable
    ) {
            Page<ProductReadDto> page = productService.getAllProducts(filter, pageable);
            return ResponseEntity.ok(page);
    }

    /**
     * This method is called when a GET request is made
     * URL: localhost:8080/product/{id}
     * Purpose: Fetches product with the given id
     * @param id - product id
     * @return Product with the given id
     */
    @GetMapping("/{id}")
    public ResponseEntity<ProductReadDto> getProductById(@PathVariable Integer id)
    {
        ProductReadDto dto = productService.getProductById(id);
        
        if (dto == null) {
            return ResponseEntity.notFound().build();
        }

        return ResponseEntity.ok().body(dto);
    }

    /**
     * This method is called when a POST request is made
     * URL: localhost:8080/product/
     * Purpose: Save an Product entity
     * @param product - Request body is an Product entity
     * @return Saved Product entity
     */
    @Validated
    @PostMapping("/")
    public ResponseEntity saveProduct(@Valid @RequestBody ProductDto product)
            throws URISyntaxException {
        try {
            ProductReadDto dto = productService.saveProduct(product);

            if (dto == null) {
                return ResponseEntity.notFound().build();
            }

            return ResponseEntity.ok().body(dto);
        } 
        catch (NotFoundException e) {
            return ResponseEntity.badRequest().body(e.getMessage());
        } 
        catch (Exception e) {
            return ResponseEntity.internalServerError().body(e.getMessage());
        } 
    }

    /**
     * This method is called when a PUT request is made
     * URL: localhost:8080/product/{id}
     * Purpose: Update an Product entity
     * @param product - Product entity to be updated
     * @param id - product id
     * @return Updated Product
     */
    @Validated
    @PutMapping("/{id}")
    public ResponseEntity updateProduct(@Valid @RequestBody ProductDto product, @PathVariable Integer id)
    {
        try {
            ProductReadDto dto = productService.updateProduct(product, id);

            if (dto == null) {
                return ResponseEntity.notFound().build();
            }

            return ResponseEntity.ok().body(dto);
        } 
        catch (NotFoundException e) {
            return ResponseEntity.badRequest().body(e.getMessage());
        } 
        catch (Exception e) {
            return ResponseEntity.internalServerError().body(e.getMessage());
        } 

    }

    /**
     * This method is called when a DELETE request is made
     * URL: localhost:8080/product/{id}
     * Purpose: Delete an Product entity
     * @param id - product's id to be deleted
     * @return a String message indicating product record has been deleted successfully
     */
    @Validated
    @DeleteMapping("/{id}")
    public ResponseEntity<String> deleteProductById(@PathVariable Integer id)
    {
        productService.deleteProductById(id);
        return ResponseEntity.ok().body("Deleted product successfully");
    }

}
