using Microsoft.EntityFrameworkCore.Update.Internal;
using Microsoft.Extensions.Hosting;
using System.Collections.ObjectModel;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Diagnostics.CodeAnalysis;
using System.Text.Json.Serialization;

namespace backend_demo.Models;

[Table("Orders")]
public class Order
{
    
    [Key]
    [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
    public long Id { get; set; }
    public required DateOnly OrderDate { get; set; }
    public required DateTime CreatedAt { get; set; }
    public required DateTime UpdatedAt { get; set; }

    [ForeignKey("customerId")]
    public required Customer Customer { get; set; }
    public long customerId { get; set; }

    public ICollection<OrderDetails> Details { get; set; } = [];

    public Order() { }

    [SetsRequiredMembers]
    public Order(OrderDTO o, Customer c)
    {
        this.OrderDate = o.OrderDate;
        this.Customer = c;
        this.customerId = c.Id;
        this.CreatedAt =  this.UpdatedAt = DateTime.UtcNow;
    }

    [SetsRequiredMembers]
    public Order(dynamic record, Customer c)
    {
        this.OrderDate = DateOnly.Parse(record.date);
        this.Customer = c;
        this.customerId = c.Id;
        this.CreatedAt = this.UpdatedAt = DateTime.UtcNow;
    }

    public void Update(OrderDTO dto)
    {
        this.OrderDate = dto.OrderDate;
        this.UpdatedAt = DateTime.UtcNow;
    }

}

[Table("OrderDetails")]
public class OrderDetails
{
    [Key]
    [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
    public long Id { get; set; }
    public required int Quantity { get; set; }
    public required DateTime CreatedAt { get; set; }
    public required DateTime UpdatedAt { get; set; }

    [ForeignKey("orderId")]
    public Order? Order { get; set; }
    public long orderId { get; set; }

    [ForeignKey("productId")]
    public Product? Product { get; set; }
    public long productId { get; set; }

    public OrderDetails() { }

    [SetsRequiredMembers]
    public OrderDetails(OrderDetailsDTO od, Order o, Product? p)
    {
        this.Order = o;
        this.orderId = o.Id;
        this.Product = p;
        this.productId = od.ProductId;
        this.Quantity = od.Quantity;
        this.CreatedAt = this.UpdatedAt = DateTime.UtcNow;
    }

    [SetsRequiredMembers]
    public OrderDetails(dynamic record, Order o, Product p)
    {
        this.Order = o;
        this.orderId = o.Id;
        this.Product = p;
        this.productId = p.Id;
        this.Quantity = int.Parse(record.quantity);
        this.CreatedAt = this.UpdatedAt = DateTime.UtcNow;
    }

    public void Update(OrderDetailsDTO dto, Product p)
    {
        this.Product = p;
        this.productId = p.Id;
        this.Quantity = dto.Quantity;
        this.UpdatedAt = DateTime.UtcNow;
    }

}

public class OrderDTO
{
    public OrderDTO() { }

    [SetsRequiredMembers]
    public OrderDTO(Order o)
    {
        this.OrderDate = o.OrderDate;
        this.CustomerId = o.Customer.Id;
        foreach(OrderDetails d in o.Details)
        {
            this.Details.Add(new OrderDetailsDTO(d));
        }
    }

    [Required(ErrorMessage = "OrderDate is required.")]
    public required DateOnly OrderDate { get; set; }

    [Required(ErrorMessage = "CustomerId is required.")]
    [Range(0, long.MaxValue, ErrorMessage = "The CustomerId field must be at least 0.")]
    public required long CustomerId { get; set; }

    [Required(ErrorMessage = "Details is required.")]
    public required List<OrderDetailsDTO> Details { get; set; } = [];
}

public class OrderReadDTO
{
    public OrderReadDTO() { }

    [SetsRequiredMembers]
    public OrderReadDTO(Order o)
    {
        this.Id = o.Id;
        this.Customer = o.Customer.CustomerName;
        this.OrderDate = o.OrderDate;
        this.CustomerId = o.Customer.Id;
        foreach (OrderDetails d in o.Details)
        {
            this.Details.Add(new OrderDetailsReadDTO(d));
        }
    }

    [JsonPropertyOrder(0)]
    public long Id { get; set; }
    [JsonPropertyOrder(1)]
    public long CustomerId { get; set; }
    [JsonPropertyOrder(2)]
    public String Customer { get; set; } = string.Empty;
    [JsonPropertyOrder(3)]
    public DateOnly OrderDate { get; set; }
    [JsonPropertyOrder(4)]
    public List<OrderDetailsReadDTO> Details { get; set; } = [];
    
    
}

public class OrderDetailsDTO
{
    public OrderDetailsDTO() { }

    [SetsRequiredMembers]
    public OrderDetailsDTO(OrderDetails od)
    {
        this.Quantity = od.Quantity;
        this.ProductId = od.Product!.Id;
    }

    [JsonPropertyOrder(2)]
    [Required(ErrorMessage = "ProductId is required.")]
    [Range(0, long.MaxValue, ErrorMessage = "The ProductId field must be at least 0.")]
    public required long ProductId { get; set; }

    [JsonPropertyOrder(4)]
    [Required(ErrorMessage = "Quantity is required.")]
    [Range(1, int.MaxValue, ErrorMessage = "The Quantity field must be greater than 0.")]
    public required int Quantity { get; set; } 
}

public class OrderDetailsPutDTO : OrderDetailsDTO
{
    public OrderDetailsPutDTO() { }

    [SetsRequiredMembers]
    public OrderDetailsPutDTO(OrderDetails od) : base(od)
    {
        this.Id = od.Id;
    }

    [JsonPropertyOrder(0)]
    [Required(ErrorMessage = "ID is required.")]
    [Range(0, long.MaxValue, ErrorMessage = "The ID field must be at least 0.")]
    public long Id { get; set; }
}

public class OrderDetailsReadDTO : OrderDetailsPutDTO
{
    public OrderDetailsReadDTO() { }

    [SetsRequiredMembers]
    public OrderDetailsReadDTO(OrderDetails od) : base(od)
    {
        this.OrderId = od.Order!.Id;
        this.Product = od.Product!.ProductName;
    }

    [JsonPropertyOrder(1)]
    public long OrderId { get; set; }

    [JsonPropertyOrder(3)]
    public required String Product { get; set; } = string.Empty;
}