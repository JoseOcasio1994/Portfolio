package com.example.demo.services;

import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import com.example.demo.models.dtos.CategoryDto;
import com.example.demo.models.dtos.CategoryReadDto;
import com.example.demo.models.entities.Category;
import com.example.demo.repository.CategoryRepo;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

@Service
@RequiredArgsConstructor
@Slf4j
public class CategoryService {

    @Autowired
    private CategoryRepo repo;

    public CategoryService(CategoryRepo repo) {
        this.repo = repo;
    }

    public List<CategoryReadDto> getAllCategories() {
        List<Category> cats = repo.findAll();
        return convertToDtoList(cats);
    }

    public CategoryReadDto getCategoryById(Integer id){
        Category category = repo.findById(id).orElse(null);
        CategoryReadDto result = category != null ? convertToDto(category) : null;
        return result;
    }

    public CategoryReadDto saveCategory(CategoryDto dto) {
        
        Category category = convertToEntity(dto);
        category.setCreatedAt(LocalDateTime.now());
        category.setUpdatedAt(LocalDateTime.now());

        log.info("Category with id: {} saved successfully", category.getId());
        Category saved = repo.save(category);
        return convertToDto(saved);
    }

    public CategoryReadDto updateCategory(CategoryDto dto, Integer id) {

        Category existingCategory = repo.findById(id).orElse(null);
        
        if (existingCategory == null) { return null; }
        
        Category category = convertToEntity(dto);
        category.update(existingCategory);

        log.info("Category with id: {} updated successfully", id);
        return new CategoryReadDto(repo.save(category));
    }

    public void deleteCategoryById (Integer id) {
        if(repo.existsById(id)) {
            repo.deleteById(id);
        }
    }

    public void deleteAll() {
        repo.deleteAll();
    }

    private List<CategoryReadDto> convertToDtoList(List<Category> cats) {
        List<CategoryReadDto> dtos = new ArrayList<>();
        for (Category c : cats) {
            dtos.add(convertToDto(c));
        }

        return dtos;
    }

    private CategoryReadDto convertToDto(Category cat) {
        return new CategoryReadDto(cat);
    }

    private Category convertToEntity(CategoryDto dto) {
        return new Category(dto);
    }

}
