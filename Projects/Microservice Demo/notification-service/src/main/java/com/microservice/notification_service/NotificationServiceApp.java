package com.microservice.notification_service;

import com.microservice.notification_service.events.OrderPlacedEvent;
import lombok.extern.slf4j.Slf4j;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.kafka.annotation.KafkaListener;

@SpringBootApplication
@Slf4j
public class NotificationServiceApp {

    public static void main(String[] args) {
        SpringApplication.run(NotificationServiceApp.class, args);
    }

    @KafkaListener(topics="notificationTopic")
    public void handleNotification(OrderPlacedEvent event){
        // Send Email Notification
        log.info("Received Notification For Order - {} ", event.getOrderNumber());
    }
}

