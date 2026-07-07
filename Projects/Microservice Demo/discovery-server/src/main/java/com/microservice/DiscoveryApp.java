package com.microservice;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.cloud.netflix.eureka.server.EnableEurekaServer;
import reactor.core.publisher.Hooks;

@SpringBootApplication
@EnableEurekaServer
public class DiscoveryApp
{
    public static void main( String[] args )
    {
        Hooks.enableAutomaticContextPropagation();
        SpringApplication.run(DiscoveryApp.class, args);
    }
}
