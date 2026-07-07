using backend_demo.Models;
using Microsoft.EntityFrameworkCore;

namespace backend_demo.Tools;

public class SeedContext(DbContextOptions<SeedContext> options) : DbContext(options)
{
    public DbSet<Category> Categories { get; set; } = null!;
    public DbSet<Customer> Customers { get; set; } = null!;
    public DbSet<Order> Orders { get; set; } = null!;
    public DbSet<OrderDetails> OrderDetails { get; set; } = null!;
    public DbSet<Product> Products { get; set; } = null!;
}
