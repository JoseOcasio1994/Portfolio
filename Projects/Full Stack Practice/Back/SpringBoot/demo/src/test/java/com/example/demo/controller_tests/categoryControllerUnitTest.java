package com.example.demo.controller_tests;

import static org.mockito.Mockito.doReturn;
import static org.mockito.Mockito.when;
import static org.springframework.test.web.servlet.request.MockMvcRequestB‌​uilders.get; 
import static org.springframework.test.web.servlet.result.MockMvcResultMat‌​chers.content; 
import static org.springframework.test.web.servlet.result.MockMvcResultMat‌​chers.status;

import java.util.Optional;

import org.junit.Test;
import org.junit.Before;
import org.junit.runner.RunWith;
import org.mockito.Mock;
import org.mockito.junit.MockitoJUnitRunner;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.reactive.AutoConfigureWebTestClient;
import org.springframework.boot.test.autoconfigure.web.reactive.WebFluxTest;
import org.springframework.boot.test.autoconfigure.web.servlet.WebMvcTest;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.boot.test.mock.mockito.MockBean;
import org.springframework.context.ApplicationContext;
import org.springframework.test.web.reactive.server.WebTestClient;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.setup.MockMvcBuilders;
import org.springframework.web.context.WebApplicationContext;

import com.example.demo.controllers.CategoryController;
import com.example.demo.models.dtos.CategoryDto;
import com.example.demo.models.dtos.CategoryReadDto;
import com.example.demo.models.entities.Category;
import com.example.demo.repository.CategoryRepo;
import com.example.demo.services.CategoryService;

@RunWith(MockitoJUnitRunner.class)
public class categoryControllerUnitTest {

    @Mock
    private CategoryRepo repo;

    @Mock
    private CategoryService service;

    @Autowired
    private WebApplicationContext wac;

    private MockMvc mockMvc;

    @Before
    public void setup() {
        this.mockMvc = MockMvcBuilders.standaloneSetup(new CategoryController()).build();
    }

    @Test
    public void shouldCreateCategory() throws Exception {

        // 1. Setup Mockito behavior
        int id = 1;
        CategoryDto dto = new CategoryDto("Beverages", "Sodas, Juices, etc.");
        Category category = new Category(dto);
        category.setId(id);
        CategoryReadDto readDto = new CategoryReadDto(category);

        when(repo.findById(id)).thenReturn(Optional.of(category));
        doReturn(readDto).when(service).getCategoryById(id);

        // 2. Perform request and verify results
        mockMvc.perform(get("/category/1"))
            .andExpect(status().isOk());
    }
}
