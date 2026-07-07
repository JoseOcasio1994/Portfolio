package com.example.demo.services;

import java.util.Optional;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.userdetails.User;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.security.core.userdetails.UsernameNotFoundException;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.stereotype.Service;

import com.example.demo.models.dtos.UserDTO;
import com.example.demo.models.dtos.UserReadDTO;
import com.example.demo.models.entities.UserInfo;
import com.example.demo.repository.UserRepo;

@Service
public class UserInfoService implements UserDetailsService {

    @Autowired
    private UserRepo repo;

    @Autowired
    private PasswordEncoder encoder;

    // Method to load user details by username (email)
    @Override
    public UserDetails loadUserByUsername(String username) throws UsernameNotFoundException {
        // Fetch user from the database by email (username)
        Optional<UserInfo> userInfo = repo.findByEmail(username);

        if (userInfo.isEmpty()) {
            throw new UsernameNotFoundException("User not found with email: " + username);
        }

        // Convert User to UserDetails (UserInfoDetails)
        UserInfo user = userInfo.get();
        return new User(user.getEmail(), user.getPassword(), user.getAuthorities());
    }

    public UserInfo getUser(String email)
    {
        Optional<UserInfo> userInfo  = repo.findByEmail(email);
        
        if (userInfo.isEmpty()) {
            return null;
        }
        
        UserInfo user = userInfo.get();
        return user;
    }

    public UserReadDTO addUser(UserDTO dto) {
        dto.password = (encoder.encode(dto.password));
        UserInfo user = new UserInfo(dto);
        user.Now();
        var saved = repo.save(user);
        return new UserReadDTO(saved);
    }
}
