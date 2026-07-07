package com.example.demo.controllers;

import com.example.demo.models.dtos.LoginRespDTO;
import com.example.demo.models.dtos.UserDTO;
import com.example.demo.models.dtos.UserReadDTO;
import com.example.demo.models.entities.AuthRequest;
import com.example.demo.models.entities.UserInfo;
import com.example.demo.services.JwtService;
import com.example.demo.services.UserInfoService;

import io.swagger.v3.oas.annotations.tags.Tag;
import lombok.RequiredArgsConstructor;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.dao.DataIntegrityViolationException;
import org.springframework.http.ResponseEntity;
import org.springframework.security.authentication.AuthenticationManager;
import org.springframework.security.authentication.UsernamePasswordAuthenticationToken;
import org.springframework.security.core.Authentication;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/api/auth")
@RequiredArgsConstructor
@Tag(name = "Users", description = "Provides APIs for managing Users")
public class UserController {

    @Autowired
    private UserInfoService service;
    @Autowired
    private JwtService jwtService;
    @Autowired
    private AuthenticationManager authenticationManager;
    @Autowired
    private PasswordEncoder encoder;

    @PostMapping("/addNewUser")
    public ResponseEntity addNewUser(@RequestBody UserDTO user) {
        try {
            AuthRequest req = new AuthRequest(user);
            
            UserReadDTO dto = service.addUser(user);
            LoginRespDTO resp = new LoginRespDTO(dto, generateToken(req));

            return ResponseEntity.ok().body(resp);
        }
        catch (DataIntegrityViolationException e) {
            if (e.getMessage().contains("duplicate key")) {
                return ResponseEntity.badRequest().body("Account already exists");
            }
            return ResponseEntity.badRequest().body(e.getMessage());
        }
        catch (Exception e) {
            return ResponseEntity.internalServerError().body(e.getMessage());
        } 
    }

    @PostMapping("/login")
    public ResponseEntity login(@RequestBody AuthRequest authRequest) {
        UserInfo user = service.getUser(authRequest.getUsername());
        
        if (user == null) {
            return ResponseEntity.notFound().build();
        }

        if (!encoder.matches(authRequest.getPassword(), user.getPassword())) {
            return ResponseEntity.badRequest().body("Incorrect Password");
        }

        UserReadDTO dto = new UserReadDTO(user);
        LoginRespDTO resp = new LoginRespDTO(dto, generateToken(authRequest));

        return ResponseEntity.ok().body(resp);
    }
    
    private String generateToken(AuthRequest authRequest) {
        Authentication authentication = authenticationManager
            .authenticate(
                new UsernamePasswordAuthenticationToken(authRequest.getUsername(), authRequest.getPassword())
            );
        if (authentication.isAuthenticated()) {
            return jwtService.generateToken(authRequest.getUsername());
        } else {
            return "Invalid user request!";
        }
    }

    @GetMapping("/user/userProfile")
    public String profile() {
        return "Welcome to User Profile";
    }
}