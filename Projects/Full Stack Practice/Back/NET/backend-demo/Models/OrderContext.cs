using Microsoft.EntityFrameworkCore;

namespace backend_demo.Models;

public class OrderContext(DbContextOptions<OrderContext> options) : DbContext(options)
{
    public DbSet<Order> Orders { get; set; } = null!;
    public DbSet<OrderDetails> OrderDetails { get; set; } = null!;

    public DbSet<Customer> Customers { get; set; } = null!;
    public DbSet<Product> Products { get; set; } = null!;

    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        modelBuilder.Entity<Category>()
            .HasMany(e => e.Products)
            .WithOne(e => e.Category)
            .HasForeignKey(e => e.CategoryId);

        modelBuilder.Entity<Product>()
            .HasMany(e => e.Details)
            .WithOne(e => e.Product)
            .HasForeignKey(e => e.productId);

        modelBuilder.Entity<Order>()
            .HasMany(e => e.Details)
            .WithOne(e => e.Order)
            .HasForeignKey(e => e.orderId);

        modelBuilder.Entity<Customer>()
            .HasMany(e => e.Orders)
            .WithOne(e => e.Customer)
            .HasForeignKey(e => e.customerId);
    }
}
