package com.example.demo.models.dtos;

import com.example.demo.models.entities.Customer;

import jakarta.validation.constraints.NotBlank;
import jakarta.validation.constraints.Size;

public class CustomerDto {

    @NotBlank(message = "customerName is required")
    @Size(min = 3, max = 50, message = "customerName must be between 3 and 50 characters")
    public String customerName;
    
    @Size(min = 3, max = 50, message = "contactName must be between 3 and 50 characters")
    public String contactName;
    
    @NotBlank(message = "country is required")
    @Size(min = 3, max = 50, message = "country must be between 3 and 50 characters")
    public String country;

    @NotBlank(message = "city is required")
    @Size(min = 3, max = 50, message = "city must be between 3 and 50 characters")
    public String city;

    @NotBlank(message = "address is required")
    @Size(min = 3, max = 50, message = "address must be between 3 and 50 characters")
    public String address;

    @NotBlank(message = "postalCode is required")
    @Size(min = 5, max = 10, message = "postalCode must be between 5 and 10 characters")
    public String postalCode;

    public CustomerDto() {}

    public CustomerDto(Customer other) {
        this.customerName = other.getCustomerName();
        this.contactName = other.getContactName();
        this.country = other.getCountry();
        this.city = other.getCity();
        this.address = other.getAddress();
        this.postalCode = other.getPostalCode();
    }
}
