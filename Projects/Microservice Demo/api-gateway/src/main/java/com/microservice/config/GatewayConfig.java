package com.microservice.config;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.http.MediaType;
import org.springframework.web.reactive.function.client.WebClient;
import org.springframework.web.servlet.function.RouterFunction;
import org.springframework.web.servlet.function.RouterFunctions;
import org.springframework.web.servlet.function.ServerResponse;
import org.jetbrains.annotations.NotNull;

import static org.springframework.cloud.gateway.server.mvc.handler.GatewayRouterFunctions.route;
import static org.springframework.cloud.gateway.server.mvc.handler.HandlerFunctions.http;
import static org.springframework.cloud.gateway.server.mvc.filter.LoadBalancerFilterFunctions.lb;
import static org.springframework.web.servlet.function.RequestPredicates.GET;

@Configuration
public class GatewayConfig {

    private final WebClient webClient = WebClient.builder().build();
    private final String EUREKA_URL = "http://localhost:8761";

    // Eureka Dashboard Route
    @Bean
    public RouterFunction<@NotNull ServerResponse> eurekaDashboardRoute() {
        return RouterFunctions.route(GET("/eureka-dashboard"), request ->
                ServerResponse.ok()
                        .contentType(MediaType.TEXT_HTML)
                        .body(webClient.get().uri(EUREKA_URL)
                                .retrieve()
                                .bodyToMono(String.class))
        );
    }

    // Order Service Route
    @Bean
    public RouterFunction<@NotNull ServerResponse> orderServiceRoute() {
        return route("order-service")
                .GET("/api/order", http())
                .POST("/api/order", http())
                .filter(lb("ORDER-SERVICE"))
                .build();
    }

    // Product Service Route
    @Bean
    public RouterFunction<@NotNull ServerResponse> productServiceRoute() {
        return route("product-service")
                .GET("/api/product", http())
                .POST("/api/product", http())
                .filter(lb("PRODUCT-SERVICE"))
                .build();
    }

}
