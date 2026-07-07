using Microsoft.EntityFrameworkCore;
using System.Reflection.Metadata;

namespace backend_demo.Models;

public class ProductContext(DbContextOptions<ProductContext> options) : DbContext(options)
{
    public DbSet<Product> Product { get; set; } = null!;
    public DbSet<Category> Category { get; set; } = null!;

    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        modelBuilder.Entity<Category>()
            .HasMany(e => e.Products) 
            .WithOne(e => e.Category) 
            .HasForeignKey(e => e.CategoryId);
    }
}
