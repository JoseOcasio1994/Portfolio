package com.example.demo.service_tests;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.mockito.ArgumentMatchers.any;
import static org.mockito.Mockito.doNothing;
import static org.mockito.Mockito.times;
import static org.mockito.Mockito.verify;
import static org.mockito.Mockito.when;

import java.util.List;
import java.util.Optional;

import org.junit.Test;
import org.junit.jupiter.api.BeforeEach;
import org.junit.runner.RunWith;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;
import org.mockito.junit.MockitoJUnitRunner;

import com.example.demo.models.dtos.CategoryDto;
import com.example.demo.models.dtos.CategoryReadDto;
import com.example.demo.models.entities.Category;
import com.example.demo.repository.CategoryRepo;
import com.example.demo.services.CategoryService;

@RunWith(MockitoJUnitRunner.class)
public class categoryServiceUnitTest {

    @Mock
    private CategoryRepo repo;

    @InjectMocks
    private CategoryService service;

    @BeforeEach
    void setUp() {
        MockitoAnnotations.openMocks(this);
    }

    // ---------- Test 1: Create ----------
    @Test
    public void createCategory() {

        // Arrange: create a sample Category and mock repository behavior
        String name = "Beverages";
        String descr = "Sodas, Juices, etc.";
        CategoryDto dto = new CategoryDto(name, descr);
        Category category = new Category(dto);
        category.setId(1);
        when(repo.save(any(Category.class))).thenReturn(category);

        // Act: call the method
        CategoryReadDto created = service.saveCategory(dto);

        // Assert: check if returned object is correct
        assertNotNull(created);
        assertEquals(name, created.categoryName);
        assertEquals(descr, created.description);

        // verify repository interaction
        verify(repo, times(1)).save(any(Category.class));
    }
    
    // ---------- Test 2: Get All ----------
    @Test
    public void getAllCategories() {
        // Arrange
        CategoryDto dto1 = new CategoryDto("Category 1", "Description 1");
        CategoryDto dto2 = new CategoryDto("Category 2", "Description 2");
        Category category1 = new Category(dto1);
        Category category2 = new Category(dto2);
        category1.setId(1);
        category2.setId(2);
        when(repo.findAll()).thenReturn(List.of(category1, category2));

        // Act
        List<CategoryReadDto> todos = service.getAllCategories();

        // Assert
        assertEquals(2, todos.size());
        verify(repo, times(1)).findAll();
    }

    // ---------- Test 3: Get ID ----------
    @Test
    public void getCategoryById() {
        // Arrange
        int id = 1;
        CategoryDto dto = new CategoryDto("Beverages", "Sodas, Juices, etc.");
        Category category = new Category(dto);
        category.setId(1);
        when(repo.findById(id)).thenReturn(Optional.of(category));

        // Act
        CategoryReadDto found = service.getCategoryById(id);

        // Assert
        assertNotNull(found);
        assertEquals("Beverages", found.categoryName);
        verify(repo, times(1)).findById(id);
    }
    
    // ---------- Test 4: Update ----------
    @Test
    public void updateCategory() {
        // Arrange
        CategoryDto dto = new CategoryDto("Beverages", "Sodas, Juices, etc.");
        CategoryDto updatedDto = new CategoryDto("Seafood", "Sodas, Juices, etc.");
        Category existing = new Category(dto);
        Category updated = new Category(updatedDto);
        existing.setId(1);
        updated.setId(2);

        // Act
        when(repo.findById(1)).thenReturn(Optional.of(existing));
        when(repo.save(any(Category.class))).thenReturn(updated);
        CategoryReadDto result = service.updateCategory(updatedDto, 1);

        // Assert
        assertNotNull(result);
        assertEquals("Seafood", result.categoryName);
        verify(repo, times(1)).save(any(Category.class));
    }

    // ---------- Test 5: Delete ----------
    @Test
    public void deleteCategory() {
        // Arrange
        int id = 1;
        when(repo.existsById(1)).thenReturn(true);
        doNothing().when(repo).deleteById(id);

        // Act
        service.deleteCategoryById(id);

        // Assert
        verify(repo, times(1)).deleteById(id);
    }

}
