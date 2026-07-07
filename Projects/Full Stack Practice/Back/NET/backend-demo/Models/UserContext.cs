using Microsoft.EntityFrameworkCore;

namespace backend_demo.Models;

public class UserContext(DbContextOptions<UserContext> options) : DbContext(options)
{
    public DbSet<User> User { get; set; } = null!;

}
