package com.microservice.inventory_service;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.cloud.client.discovery.EnableDiscoveryClient;
import reactor.core.publisher.Hooks;

@SpringBootApplication
@EnableDiscoveryClient
public class InventoryServiceApplication {

	public static void main(String[] args) {
		Hooks.enableAutomaticContextPropagation();
		SpringApplication.run(InventoryServiceApplication.class, args);
	}

	/*@Bean
	public CommandLineRunner loadData(InventoryRepo repo){
		return args -> {
			Inventory inventory = new Inventory();
			inventory.setSkuCode("ff15(ps5)");
			inventory.setQuantity(100);

			Inventory inventory2 = new Inventory();
			inventory2.setSkuCode("iphone_13");
			inventory2.setQuantity(35);

			repo.save(inventory);
			repo.save(inventory2);
		};
	}*/
}
