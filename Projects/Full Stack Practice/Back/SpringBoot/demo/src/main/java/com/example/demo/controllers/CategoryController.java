package com.example.demo.controllers;

import lombok.RequiredArgsConstructor;

import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;
import org.springframework.beans.factory.annotation.Autowired;

import com.example.demo.models.dtos.CategoryDto;
import com.example.demo.models.dtos.CategoryReadDto;
import com.example.demo.services.CategoryService;

import io.swagger.v3.oas.annotations.tags.Tag;
import jakarta.validation.Valid;

import java.net.URISyntaxException;
import java.util.List;

@RestController
@RequestMapping("/api/category")
@RequiredArgsConstructor
@Validated
@Tag(name = "Category", description = "Provides APIs for managing categories") 
public class CategoryController {
    
    @Autowired
    private CategoryService categoryService;

    /**
     * This method is called when a GET request is made
     * URL: localhost:8080/category/
     * Purpose: Fetches all the categories in the category table
     * @return List of Categories
     */
    @GetMapping("/")
    public ResponseEntity<List<CategoryReadDto>> getAllCategories(){
        return ResponseEntity.ok().body(categoryService.getAllCategories());
    }

    /**
     * This method is called when a GET request is made
     * URL: localhost:8080/category/{id}
     * Purpose: Fetches category with the given id
     * @param id - category id
     * @return Category with the given id
     */
    @GetMapping("/{id}")
    public ResponseEntity<CategoryReadDto> getCategoryById(@PathVariable Integer id)
    {
        CategoryReadDto dto = categoryService.getCategoryById(id);
        
        if (dto == null) {
            return ResponseEntity.notFound().build();
        }

        return ResponseEntity.ok().body(dto);
    }

    /**
     * This method is called when a POST request is made
     * URL: localhost:8080/category/
     * Purpose: Save an Category entity
     * @param category - Request body is an Category entity
     * @return Saved Category entity
     */
    @PostMapping("/")
    public ResponseEntity<CategoryReadDto> saveCategory(@Valid @RequestBody CategoryDto category) throws URISyntaxException {
        return new ResponseEntity<CategoryReadDto>(categoryService.saveCategory(category), HttpStatus.CREATED);
    }

    /**
     * This method is called when a PUT request is made
     * URL: localhost:8080/category/{id}
     * Purpose: Update an Category entity
     * @param category - Category entity to be updated
     * @param id - category id
     * @return Updated Category
     */
    @PutMapping("/{id}")
    public ResponseEntity<CategoryReadDto> updateCategory(@Valid @RequestBody CategoryDto category, @PathVariable Integer id)
    {
        CategoryReadDto dto = categoryService.updateCategory(category, id);
        
        if (dto == null) {
            return ResponseEntity.notFound().build();
        }
        
        return ResponseEntity.ok().body(dto);
    }

    /**
     * This method is called when a DELETE request is made
     * URL: localhost:8080/category/{id}
     * Purpose: Delete an Category entity
     * @param id - category's id to be deleted
     * @return a String message indicating category record has been deleted successfully
     */
    @DeleteMapping("/{id}")
    public ResponseEntity<String> deleteCategoryById(@PathVariable Integer id)
    {
        categoryService.deleteCategoryById(id);
        return ResponseEntity.ok().body("Deleted category successfully");
    }

}
