package com.example.demo.controllers;

import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;

import org.springframework.http.ResponseEntity;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;
import org.springframework.beans.factory.annotation.Autowired;

import com.example.demo.services.OrderService;

import io.swagger.v3.oas.annotations.tags.Tag;
import javassist.NotFoundException;

import com.example.demo.models.dtos.OrderDetailDto;
import com.example.demo.models.dtos.OrderDetailFullDto;
import com.example.demo.models.dtos.OrderDetailReadDto;
import com.example.demo.models.dtos.OrderDto;
import com.example.demo.models.dtos.OrderReadDto;
import com.example.demo.services.OrderDetailService;

import java.net.URISyntaxException;
import java.util.List;

@Slf4j
@RestController
@RequestMapping("/api/order")
@RequiredArgsConstructor
@Validated
@Tag(name = "Order", description = "Provides APIs for managing Orders") 
public class OrderController {
    @Autowired
    private OrderService orderService;
    @Autowired
    private OrderDetailService orderDetailService;

    /**
     * This method is called when a GET request is made
     * URL: localhost:8080/order/
     * Purpose: Fetches all the orders in the order table
     * @return List of Orders
     */
    @GetMapping("/")
    public ResponseEntity<List<OrderReadDto>> getAllOrdersEntity() {
        return ResponseEntity.ok().body(orderService.getAllOrders());
    }
    
     /**
     * This method is called when a GET request is made
     * URL: localhost:8080/order/{id}
     * Purpose: Fetches order with the given id
     * @param id - order id
     * @return Order with the given id
     */
    @GetMapping("/{id}")
    public ResponseEntity getOrderById(@PathVariable Integer id)
    {
        try {
            OrderReadDto dto = orderService.getOrderById(id);

            if (dto == null) {
                return ResponseEntity.notFound().build();
            }

            return ResponseEntity.ok().body(dto);
        } 
        catch (Exception e) {
            log.error(e.getMessage());
            return ResponseEntity.internalServerError().build();
        }
    }

    /**
     * This method is called when a GET request is made
     * URL: localhost:8080/order/details/{id}
     * Purpose: Fetches all the order details in the order_details table
     * @return List of Orders
     */
    @GetMapping("/details/{id}")
    public ResponseEntity<OrderDetailFullDto> getFullOrderDetailsEntity(@PathVariable Integer id) {
        OrderDetailFullDto dto = orderDetailService.getFullOrderDetailById(id);
        
        if (dto == null) {
            return ResponseEntity.notFound().build();
        }

        return ResponseEntity.ok().body(dto);
    }

    /**
     * This method is called when a POST request is made
     * URL: localhost:8080/order/
     * Purpose: Save an Order entity
     * @param order - Request body is an Order entity
     * @return Saved Order entity
     */
    @PostMapping("/")
    public ResponseEntity saveOrder(@RequestBody OrderDto orderDto)
            throws URISyntaxException {
        try {
            OrderDto dto = orderService.saveOrder(orderDto);
            return ResponseEntity.ok().body(dto);
        }
        catch (NotFoundException e) {
            return ResponseEntity.badRequest().body(e.getMessage());
        } 
        catch (Exception e) {
            return ResponseEntity.internalServerError().body(e.getMessage());
        } 
    }

    /**
     * This method is called when a PUT request is made
     * URL: localhost:8080/order/{id}
     * Purpose: Update an Order entity
     * @param order - Order entity to be updated
     * @param id - order id
     * @return Updated Order
     */
    //@PutMapping("/{id}")
    public ResponseEntity updateOrder(@RequestBody OrderDto order, @PathVariable Integer id)
    {
        try {
            OrderDto dto = orderService.updateOrder(order, id);
            return ResponseEntity.ok().body(dto);
        }
        catch (NotFoundException e) {
            return ResponseEntity.badRequest().body(e.getMessage());
        } 
        catch (Exception e) {
            return ResponseEntity.internalServerError().body(e.getMessage());
        } 
    }

    /**
     * This method is called when a PUT request is made
     * URL: localhost:8080/order/details/{id}
     * Purpose: Update an Order entity
     * @param order - Order entity to be updated
     * @param id - order id
     * @return Updated Order
     */
    @PutMapping("/details/{id}")
    public ResponseEntity updateOrderDetails(@RequestBody OrderDetailDto detail, @PathVariable Integer id)
    {
        try {
            OrderDetailReadDto dto = orderDetailService.updateOrderDetails(detail, id, null);
            
            if (dto == null) {
                return ResponseEntity.notFound().build();
            }

            return ResponseEntity.ok().body(dto);
        }
        catch (NotFoundException e) {
            return ResponseEntity.badRequest().body(e.getMessage());
        } 
        catch (Exception e) {
            return ResponseEntity.internalServerError().body(e.getMessage());
        } 
    }

    /**
     * This method is called when a DELETE request is made
     * URL: localhost:8080/order/{id}
     * Purpose: Delete an Order entity
     * @param id - order's id to be deleted
     * @return a String message indicating order record has been deleted successfully
     */
    @DeleteMapping("/{id}")
    public ResponseEntity<String> deleteOrderById(@PathVariable Integer id)
    {
        orderService.deleteOrderById(id);
        orderDetailService.deleteOrderDetailById(id);
        return ResponseEntity.ok().body("Deleted order successfully");
    }

}
