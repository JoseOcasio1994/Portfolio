package com.example.demo.services;

import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import com.example.demo.models.dtos.CustomerReadDto;
import com.example.demo.models.dtos.CustomerDto;
import com.example.demo.models.entities.Customer;
import com.example.demo.repository.CustomerRepo;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

@Service
@RequiredArgsConstructor
@Slf4j
public class CustomerService {
    
    @Autowired
    private CustomerRepo repo;

    public List<CustomerReadDto> getAllCustomers() {
        List<Customer> customers = repo.findAll();
        return convertToDtoList(customers);
    }

    public CustomerReadDto getCustomerById(Integer id){
        Customer customer = repo.findById(id).orElse(null);
        return customer != null ? convertToDto(customer) : null;
    }

    public CustomerReadDto saveCustomer(CustomerDto dto) {
        Customer customer = convertToEntity(dto);
        customer.setCreatedAt(LocalDateTime.now());
        customer.setUpdatedAt(LocalDateTime.now());

        log.info("Customer with id: {} saved successfully", customer.getId());
        return convertToDto(repo.save(customer));
    }

    public CustomerReadDto updateCustomer(CustomerDto dto, Integer id) {

        Customer existingCustomer = repo.findById(id).orElse(null);
        
        if (existingCustomer == null) { return null; }
        
        Customer customer = convertToEntity(dto);
        customer.update(existingCustomer);

        log.info("Customer with id: {} updated successfully", id);
        return convertToDto(repo.save(customer));
    }

    public void deleteCustomerById (Integer id) {
        if(repo.existsById(id)) {
            repo.deleteById(id);
        }
    }

    public void deleteAll() {
        repo.deleteAll();
    }

    private List<CustomerReadDto> convertToDtoList(List<Customer> customers) {
        List<CustomerReadDto> dtos = new ArrayList<>();
        for (Customer c : customers) {
            dtos.add(convertToDto(c));
        }

        return dtos;
    }

    private CustomerReadDto convertToDto(Customer c) {
        return new CustomerReadDto(c);
    }

    private Customer convertToEntity(CustomerDto dto) {
        return new Customer(dto);
    }

}
