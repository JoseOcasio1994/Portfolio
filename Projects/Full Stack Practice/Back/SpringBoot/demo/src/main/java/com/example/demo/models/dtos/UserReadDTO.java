package com.example.demo.models.dtos;

import com.example.demo.models.entities.UserInfo;
import com.fasterxml.jackson.annotation.JsonPropertyOrder;


@JsonPropertyOrder({"id", "name", "email", "role"})
public class UserReadDTO {

    public String name, email, role;
    public int id;

    public UserReadDTO(UserInfo other) {
        this.name = other.getName();
        this.email = other.getEmail();
        this.role = other.getRoles();
        this.id = other.getId();
    }
}
