package com.example.demo.repository;

import java.util.List;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.stereotype.Repository;

import com.example.demo.models.entities.OrderDetails;

@Repository
public interface OrderDetailRepo extends JpaRepository<OrderDetails, Integer> {
    
    @Query(value = "select * from order_details od where od.orderId = :id", nativeQuery = true)
    List<OrderDetails> findByOrderId(Integer id);

    @Query(value = "select new java.lang.Boolean(count(*) > 0) from order_details where orderId = :id", nativeQuery = true)
    boolean existsByOrderId(Integer id);

    @Query(value = "delete from order_details od where od.orderId = :id", nativeQuery = true)
    void deleteByOrderId(Integer id);
}
