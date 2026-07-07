package com.example.demo.models.entities;

import com.example.demo.models.dtos.OrderDetailDto;

import jakarta.persistence.Entity;
import jakarta.persistence.JoinColumn;
import jakarta.persistence.ManyToOne;
import jakarta.persistence.Table;
import lombok.Data;
import lombok.EqualsAndHashCode;
import com.fasterxml.jackson.annotation.JsonInclude;
import com.fasterxml.jackson.annotation.JsonInclude.Include;

@JsonInclude(Include.NON_NULL)
@Data
@EqualsAndHashCode(callSuper = true)
@Entity
@Table(name = "order_details", schema = "public")
public class OrderDetails extends BaseModel {

    private Integer quantity;

    @ManyToOne()
    @JoinColumn(name = "orderId")
    private Order order;

    @ManyToOne()
    @JoinColumn(name = "productId")
    private Product product;

    public OrderDetails() {
        this.Now();
    }

    public OrderDetails(OrderDetailDto dto) {
        this.quantity = dto.quantity;
        this.Now();
    }

    public void Init(Order order, Product p) {
        this.Now();
        this.setOrder(order);
        this.setProduct(p);
    }

    @Override
    public String toString() {
        return "Id# " + id + "Order# " + order.getId() + "product " + product.getProductName();
    }

}
