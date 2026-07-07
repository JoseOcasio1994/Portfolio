using Microsoft.Extensions.Hosting;
using Newtonsoft.Json;
using NuGet.Protocol;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Diagnostics.CodeAnalysis;

namespace backend_demo.Models;

[Table("Users")]
public class User
{
    [Key]
    [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
    public long Id { get; set; }

    [Required]
    [MaxLength(50)]
    public required string Name { get; set; } = String.Empty;

    [Required]
    [MaxLength(50)]
    [Index(IsUnique = true)]
    public required string Email { get; set; } = String.Empty;

    [Required]
    [MaxLength(50)]
    [Index(IsUnique = true)]
    public required string UserName { get; set; } = String.Empty;

    [Required]
    [MinLength(8)]
    public required string Password { get; set; } = String.Empty;

    [Required]
    [MaxLength(25)]
    public required string Role { get; set; } = "User";

    public required DateTime CreatedAt { get; set; }
    public required DateTime UpdatedAt { get; set; }

    [SetsRequiredMembers]
    public User() {
        this.CreatedAt = this.UpdatedAt = DateTime.UtcNow;
    }

    [SetsRequiredMembers]
    public User(RegisterRequest r) : this()
    {
        this.Name = r.Name;
        this.Email = r.Email;
        this.UserName = r.UserName;
        this.Password = r.Password;
        this.Role = r.Role;
    }

    public void Update(RegisterRequest r)
    {
        this.Name = r.Name;
        this.Email = r.Email;
        this.Password = r.Password;
        this.Role = r.Role;
        this.UpdatedAt = DateTime.UtcNow;
    }
}

public class LoginRequest
{
    public LoginRequest() { }

    [SetsRequiredMembers]
    public LoginRequest(LoginRequest l)
    {
        this.UserName = l.UserName;
        this.Password = l.Password;
    }

    public required String UserName { get; set; }
    public required String Password { get; set; }
}

public class LoginResponseDTO
{
    public LoginResponseDTO() { }

    [SetsRequiredMembers]
    public LoginResponseDTO(Boolean success, String msg, String? jwt)
    {
        this.Success = success;
        this.Message = msg;
        if (jwt != null)
        {
            this.Token = jwt!;
        }
        this.LoginTime = DateTime.Now;
    }

    public Boolean Success { get; set; }
    public String Message { get; set; } = String.Empty;
    public String Token { get; set; } = String.Empty;
    public DateTime LoginTime { get; set; }
}

public class RegisterRequest
{
    public RegisterRequest() { }

    [SetsRequiredMembers]
    public RegisterRequest(RegisterRequest r)
    {
        this.Name = r.Name;
        this.Email = r.Email;
        this.UserName = r.UserName;
        this.Password = r.Password;
        this.Role = r.Role;
    }

    public required string Name { get; set; } = String.Empty;
    public required string Email { get; set; } = String.Empty;
    public required string UserName { get; set; } = String.Empty;
    public required string Password { get; set; } = String.Empty;
    public required string Role { get; set; } = String.Empty;
}

public class RegisterResponse
{
    public RegisterResponse() { }

    [SetsRequiredMembers]
    public RegisterResponse(User u)
    {
        this.Id = u.Id;
        this.UserName = u.UserName;
        this.Role = u.Role;
        this.CreatedAt = DateTime.Now;
    }

    public long Id { get; set; }
    public required string UserName { get; set; } = String.Empty;
    public required string Role { get; set; } = String.Empty;
    public required DateTime CreatedAt { get; set; }
}