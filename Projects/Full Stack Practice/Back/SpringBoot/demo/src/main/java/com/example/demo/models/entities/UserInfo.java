package com.example.demo.models.entities;

import java.util.List;
import java.util.stream.Collectors;

import org.springframework.security.core.GrantedAuthority;
import org.springframework.security.core.authority.SimpleGrantedAuthority;

import com.example.demo.models.dtos.UserDTO;

import jakarta.persistence.Entity;
import jakarta.persistence.Table;
import lombok.Data;
import lombok.EqualsAndHashCode;
import lombok.NoArgsConstructor;

@NoArgsConstructor
@Data
@EqualsAndHashCode(callSuper = true)
@Entity
@Table(name = "users", schema = "public")
public class UserInfo extends BaseModel {

    private String name;
    private String email;
    private String password;
    private String roles;
    
    public UserInfo(UserDTO other) {
        this.name = other.name;
        this.email = other.email;
        this.password = other.password;
        this.roles = other.role;
    }

    @Override
    public String toString() {
        return "User [id=" + id + ", name=" + name + "]";
    }

    public List<GrantedAuthority> getAuthorities() {
        return List.of(roles.split(","))
            .stream()
            .map(SimpleGrantedAuthority::new)
            .collect(Collectors.toList());
    }

}

