package com.example.demo.repository;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

import com.example.demo.models.entities.Customer;

@Repository
public interface CustomerRepo extends JpaRepository<Customer, Integer> {}
