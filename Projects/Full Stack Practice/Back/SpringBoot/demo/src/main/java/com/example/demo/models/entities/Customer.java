package com.example.demo.models.entities;

import jakarta.persistence.CascadeType;
import jakarta.persistence.Entity;
import jakarta.persistence.OneToMany;
import jakarta.persistence.Table;
import lombok.Data;
import lombok.EqualsAndHashCode;
import lombok.NoArgsConstructor;

import java.util.HashSet;
import java.util.Set;

import com.example.demo.models.dtos.CustomerDto;
import com.fasterxml.jackson.annotation.JsonInclude;
import com.fasterxml.jackson.annotation.JsonInclude.Include;

@JsonInclude(Include.NON_NULL)
@NoArgsConstructor
@Data
@EqualsAndHashCode(callSuper = true)
@Entity
@Table(name = "customers", schema = "public")
public class Customer extends BaseModel {

    private String customerName;
    private String contactName;
    private String country;
    private String city;
    private String address;
    private String postalCode;

    @OneToMany(mappedBy = "customer", cascade = CascadeType.ALL, orphanRemoval = true)
    private Set<Order> order = new HashSet<>();

    public Customer(CustomerDto dto) {
        this.customerName = dto.customerName;
        this.contactName = dto.contactName;
        this.country = dto.country;
        this.city = dto.city;
        this.address = dto.address;
        this.postalCode = dto.postalCode;
    }

    @Override
    public String toString() {
        return "Customer [id=" + id + ", name=" + customerName + "]";
    }

}

