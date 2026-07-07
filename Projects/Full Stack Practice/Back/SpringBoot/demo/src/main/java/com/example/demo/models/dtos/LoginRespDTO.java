package com.example.demo.models.dtos;

import com.fasterxml.jackson.annotation.JsonPropertyOrder;

@JsonPropertyOrder({"token", "user"})
public class LoginRespDTO {

    public String token;
    public Object user;

    public LoginRespDTO(Object other, String token) {
        this.token = token;
        this.user = other;
    }
}
