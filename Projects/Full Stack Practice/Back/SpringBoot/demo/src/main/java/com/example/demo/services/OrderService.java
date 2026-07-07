package com.example.demo.services;

import lombok.RequiredArgsConstructor;
import lombok.extern.slf4j.Slf4j;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import com.example.demo.models.dtos.OrderDetailDto;
import com.example.demo.models.dtos.OrderDto;
import com.example.demo.models.dtos.OrderReadDto;
import com.example.demo.models.entities.Customer;
import com.example.demo.models.entities.Order;
import com.example.demo.models.entities.OrderDetails;
import com.example.demo.repository.CustomerRepo;
import com.example.demo.repository.OrderRepo;

import jakarta.transaction.Transactional;
import javassist.NotFoundException;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

@Service
@RequiredArgsConstructor
@Slf4j
public class OrderService {

    @Autowired
    private OrderRepo repo;
    @Autowired
    private CustomerRepo customerRepo;
    @Autowired
    private OrderDetailService detailService;

    public List<OrderReadDto> getAllOrders() {
        List<Order> orders = repo.findAll();
        return convertToDtoList(orders);
    }

    public OrderReadDto getOrderById(Integer id) {
        Order order = repo.findById(id).orElse(null);

        if (order == null) {
            return null;
        }

        return convertToDto(order);
    }

    @Transactional // This ensures the operations are atomic
    public OrderReadDto saveOrder(OrderDto dto) throws NotFoundException {

        Optional<Customer> c = customerRepo.findById(dto.customerId);
        if (c.isEmpty()) {
            throw new NotFoundException("Customer With ID " + dto.customerId + " not found.");
        }

        List<OrderDetailDto> detailDtos = dto.details;
        List<OrderDetails> details = new ArrayList<>();

        for (OrderDetailDto odto : detailDtos) {
            OrderDetails d = detailService.convertToEntity(odto);
            details.add(d);
        }

        Order order = convertToEntity(dto);
        order.Init(c.get(), details);

        Order saved = repo.save(order);
        log.info("Order with id: {} saved successfully", order.getId());

        List<OrderDetails> savedDetails = detailService.saveOrderDetails(detailDtos, order);
        saved.setDetails(savedDetails);
        saved = repo.save(saved);

        return convertToDto(saved);
    }

    @Transactional
    public OrderReadDto updateOrder (OrderDto dto, Integer id) throws NotFoundException {
        Order existingOrder = repo.findById(id).orElse(null);

        if (existingOrder == null) { return null; }

        Optional<Customer> c = customerRepo.findById(dto.customerId);
        if (c.isEmpty()) {
            throw new NotFoundException("Customer With ID " + dto.customerId + " not found.");
        }

        Order order = convertToEntity(dto);
        order.update(existingOrder);
        order.setOrderDate(existingOrder.getOrderDate());
        order.setCustomer(c.get());
        order.setDetails(existingOrder.getDetails());

        return convertToDto(repo.save(order));
    }

    public void deleteOrderById (Integer id) {
        if(repo.existsById(id)) {
            repo.deleteById(id);
        }
    }

    public void deleteAll() {
        repo.deleteAll();
    }

    private List<OrderReadDto> convertToDtoList(List<Order> orders) {
        List<OrderReadDto> dtos = new ArrayList<>();
        for (Order o : orders) {
            dtos.add(convertToDto(o));
        }

        return dtos;
    }

    private OrderReadDto convertToDto(Order o) {
        return new OrderReadDto(o);
    }

    public Order convertToEntity(OrderDto dto) {
        return new Order(dto);
    }

}
