using Microsoft.EntityFrameworkCore;

namespace backend_demo.Models;

public class CategoryContext : DbContext
{
    public CategoryContext(DbContextOptions<CategoryContext> options) : base(options) {}

    public DbSet<Category> Category { get; set; } = null!;

}
