package com.example.demo.models.dtos;

import jakarta.validation.constraints.NotBlank;
import jakarta.validation.constraints.NotNull;
import jakarta.validation.constraints.Size;

public class UserDTO {
    
    @NotBlank(message = "name is required")
    @Size(min = 3, max = 50, message = "name must be between 3 and 50 characters")
    public String name;

    @NotNull(message = "email is required")
    public String email;

    @NotNull(message = "password is required")
    @Size(min = 8, max = 50, message = "password must be between 8 and 50 characters")
    public String password;

    @NotNull(message = "role is required")
    public String role;

    public UserDTO() {}

}
