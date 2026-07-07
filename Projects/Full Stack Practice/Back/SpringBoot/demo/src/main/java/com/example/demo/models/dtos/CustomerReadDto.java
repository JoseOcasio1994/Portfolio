package com.example.demo.models.dtos;

import com.example.demo.models.entities.Customer;
import com.fasterxml.jackson.annotation.JsonPropertyOrder;

import lombok.EqualsAndHashCode;

@EqualsAndHashCode(callSuper = true)
@JsonPropertyOrder({"id", "customerName", "contactName", "country", "city", "address", "postalCode"})
public class CustomerReadDto extends CustomerDto {
    public int id;

    public CustomerReadDto(Customer other) {
        super(other);
        this.id = other.getId();
    }
}
