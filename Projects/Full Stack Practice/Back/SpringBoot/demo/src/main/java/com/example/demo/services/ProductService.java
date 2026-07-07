package com.example.demo.services;

import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.domain.Specification;
import org.springframework.stereotype.Service;

import com.example.demo.models.dtos.ProductReadDto;
import com.example.demo.models.dtos.ProductDto;
import com.example.demo.models.entities.Category;
import com.example.demo.models.entities.Product;
import com.example.demo.models.other.ProductFilter;
import com.example.demo.models.other.ProductFilter.PriceRange;
import com.example.demo.repository.CategoryRepo;
import com.example.demo.repository.ProductRepo;
import com.example.demo.repository.ProductSpec;

import javassist.NotFoundException;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

@Service
@RequiredArgsConstructor
@Slf4j
public class ProductService {

    @Autowired
    private ProductRepo repo;
    @Autowired
    private CategoryRepo catRepo;

    public Page<ProductReadDto> getAllProducts(ProductFilter filter, Pageable pageable) {
        Specification<Product> spec = Specification.unrestricted();

        List<String> categories = filter.getCategory();
        List<String> prices = filter.getPrice();
        boolean exclude = filter.isExcludeOutOfStock() || false;

        List<PriceRange> priceRanges = new ArrayList<>();

        if (prices != null ) {
            for (String s : prices) {
                priceRanges.add(filter.toRange(s));
            }
        }

        if (categories != null && !categories.isEmpty()) {
            spec = spec.and(ProductSpec.inCategory(categories));
        }

        if (prices != null && !prices.isEmpty()) {
            spec = spec.and(ProductSpec.hasPriceBetween(priceRanges));
        }

        if (exclude) {
            spec = spec.and(ProductSpec.excludeOutOfStock());
        }

        var products = repo.findAll(spec, pageable);
        return convertToDtoList(products);
    }

    public ProductReadDto getProductById(Integer id){
        Product product = repo.findById(id).orElse(null);
        return product != null ? convertToDto(product) : null;
    }

    public ProductReadDto saveProduct(ProductDto dto) throws NotFoundException {
        Category category = catRepo.findById(dto.categoryId).orElse(null);

        if (category == null) {
            throw new NotFoundException("Category With Id: " + dto.categoryId + " not found");
        }

        Product product = convertToEntity(dto);
        product.setCategory(category);
        product.setCreatedAt(LocalDateTime.now());
        product.setUpdatedAt(LocalDateTime.now());

        log.info("Product with id: {} saved successfully", product.getId());
        return convertToDto(repo.save(product));
    }

    public ProductReadDto updateProduct(ProductDto dto, Integer id) throws NotFoundException {
        Category category = catRepo.findById(dto.categoryId).orElse(null);

        if (category == null) {
            throw new NotFoundException("Category With Id: " + dto.categoryId + " not found");
        }
        
        Product existingProduct = repo.findById(id).orElse(null);
        
        if (existingProduct == null) { return null; }
        
        Product product = convertToEntity(dto);
        product.setCategory(category);
        product.update(existingProduct);

        log.info("Product with id: {} updated successfully", id);
        return new ProductReadDto(repo.save(product));
    }

    public void deleteProductById (Integer id) {
        if(repo.existsById(id)) {
            repo.deleteById(id);
        }
    }

    public void deleteAll() {
        repo.deleteAll();
    }

    private Page<ProductReadDto> convertToDtoList(Page<Product> products) {
        Page<ProductReadDto> pageDto = products.map(x -> convertToDto(x));
       
        return pageDto;
    }

    private ProductReadDto convertToDto(Product p) {
        return new ProductReadDto(p);
    }

    public Product convertToEntity(ProductDto dto) {
        return new Product(dto);
    }

}
