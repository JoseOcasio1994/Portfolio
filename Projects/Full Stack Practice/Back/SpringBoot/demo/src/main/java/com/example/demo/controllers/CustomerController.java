package com.example.demo.controllers;

import lombok.RequiredArgsConstructor;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;
import org.springframework.beans.factory.annotation.Autowired;

import com.example.demo.models.dtos.CustomerDto;
import com.example.demo.models.dtos.CustomerReadDto;
import com.example.demo.services.CustomerService;

import io.swagger.v3.oas.annotations.tags.Tag;
import jakarta.validation.Valid;

import java.net.URISyntaxException;
import java.util.List;

@RestController
@RequestMapping("/api/customer")
@RequiredArgsConstructor
@Validated
@Tag(name = "Customer", description = "Provides APIs for managing Customers") 
public class CustomerController {
    @Autowired
    private CustomerService customerService;

    /**
     * This method is called when a GET request is made
     * URL: localhost:8080/customer/
     * Purpose: Fetches all the customers in the customer table
     * @return List of Customers
     */
    @GetMapping("/")
    public ResponseEntity<List<CustomerReadDto>> getAllCustomers(){
        return ResponseEntity.ok().body(customerService.getAllCustomers());
    }

    /**
     * This method is called when a GET request is made
     * URL: localhost:8080/customer/{id}
     * Purpose: Fetches customer with the given id
     * @param id - customer id
     * @return Customer with the given id
     */
    @GetMapping("/{id}")
    public ResponseEntity<CustomerReadDto> getCustomerById(@PathVariable Integer id)
    {
        CustomerReadDto dto = customerService.getCustomerById(id);
        
        if (dto == null) {
            return ResponseEntity.notFound().build();
        }

        return ResponseEntity.ok().body(dto);
    }

    /**
     * This method is called when a POST request is made
     * URL: localhost:8080/customer/
     * Purpose: Save an Customer entity
     * @param customer - Request body is an Customer entity
     * @return Saved Customer entity
     */
    @PostMapping("/")
    public ResponseEntity<CustomerReadDto> saveCustomer(@Valid @RequestBody CustomerDto customer) throws URISyntaxException {
        return new ResponseEntity<CustomerReadDto>(customerService.saveCustomer(customer), HttpStatus.CREATED);
    }

    /**
     * This method is called when a PUT request is made
     * URL: localhost:8080/customer/{id}
     * Purpose: Update an Customer entity
     * @param customer - Customer entity to be updated
     * @param id - customer id
     * @return Updated Customer
     */
    @PutMapping("/{id}")
    public ResponseEntity<CustomerReadDto> updateCustomer(@Valid @RequestBody CustomerDto customer, @PathVariable Integer id)
    {
        CustomerReadDto dto = customerService.updateCustomer(customer, id);
        
        if (dto == null) {
            return ResponseEntity.notFound().build();
        }

        return ResponseEntity.ok().body(dto);
    }

    /**
     * This method is called when a DELETE request is made
     * URL: localhost:8080/customer/{id}
     * Purpose: Delete an Customer entity
     * @param id - customer's id to be deleted
     * @return a String message indicating customer record has been deleted successfully
     */
    @DeleteMapping("/{id}")
    public ResponseEntity<String> deleteCustomerById(@PathVariable Integer id)
    {
        customerService.deleteCustomerById(id);
        return ResponseEntity.ok().body("Deleted customer successfully");
    }

}
