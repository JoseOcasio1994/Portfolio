using Microsoft.EntityFrameworkCore;

namespace backend_demo.Models;

public class CustomerContext(DbContextOptions<CustomerContext> options) : DbContext(options)
{
    public DbSet<Customer> Customer { get; set; } = null!;

}
