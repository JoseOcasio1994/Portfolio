package com.example.demo.models.entities;

import java.time.LocalDateTime;

import jakarta.persistence.GeneratedValue;
import jakarta.persistence.Id;
import jakarta.persistence.MappedSuperclass;
import lombok.Data;
import lombok.NoArgsConstructor;

@NoArgsConstructor
@Data
@MappedSuperclass
public class BaseModel {

    @Id
    @GeneratedValue
    protected Integer id;
    private LocalDateTime createdAt;
    private LocalDateTime updatedAt;

    public void update(BaseModel other) {
        this.setId(other.getId());
        this.setCreatedAt(other.getCreatedAt());
        this.setUpdatedAt(LocalDateTime.now());
    }

    public void Now() {
        this.setCreatedAt(LocalDateTime.now());
        this.setUpdatedAt(LocalDateTime.now());
    }
}

