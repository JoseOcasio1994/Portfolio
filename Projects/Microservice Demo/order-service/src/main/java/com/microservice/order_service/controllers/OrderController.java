package com.microservice.order_service.controllers;

import com.microservice.order_service.dtos.OrderRequest;
import com.microservice.order_service.services.OrderService;
import io.github.resilience4j.circuitbreaker.annotation.CircuitBreaker;
import io.github.resilience4j.retry.annotation.Retry;
import io.github.resilience4j.timelimiter.annotation.TimeLimiter;
import lombok.RequiredArgsConstructor;
import org.apache.hc.core5.concurrent.CompletedFuture;
import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.*;

import java.util.concurrent.CompletableFuture;

@RestController
@RequestMapping("/api/order")
@RequiredArgsConstructor
public class OrderController {

    private final OrderService service;

    @PostMapping()
    @ResponseStatus(HttpStatus.CREATED)
    @CircuitBreaker(name="inventory", fallbackMethod = "inventoryFallback")
    @TimeLimiter(name="inventory")
    @Retry(name="inventory")
    public CompletableFuture<String> placeOrder(@RequestBody OrderRequest request){
        return CompletableFuture.supplyAsync(() -> service.placeOrder(request));
    }

    public CompletableFuture<String> inventoryFallback(OrderRequest request, RuntimeException ex) {
        return CompletableFuture.supplyAsync(() -> "Oops! Something went wrong. Please order after some time.");
    }
}
