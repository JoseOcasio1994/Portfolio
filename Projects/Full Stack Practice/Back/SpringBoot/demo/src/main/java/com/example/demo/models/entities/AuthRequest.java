package com.example.demo.models.entities;

import com.example.demo.models.dtos.UserDTO;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class AuthRequest {

    private String username;
    private String password;

    public AuthRequest(UserDTO dto) {
        this.username = dto.email;
        this.password = dto.password;
    }
}