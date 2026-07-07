package com.microservice.product_service;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import reactor.core.publisher.Hooks;

@SpringBootApplication
public class ProductServiceApplication {

	public static void main(String[] args)
	{
		Hooks.enableAutomaticContextPropagation();
		SpringApplication.run(ProductServiceApplication.class, args);
	}

}
