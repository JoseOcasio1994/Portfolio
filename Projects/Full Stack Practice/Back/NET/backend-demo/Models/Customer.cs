using Humanizer;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Diagnostics.CodeAnalysis;

namespace backend_demo.Models;

[Table("Customers")]
public class Customer : CustomerDTO
{
    [Key]
    [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
    public long Id { get; set; }
    public required DateTime CreatedAt { get; set; }
    public required DateTime UpdatedAt { get; set; }

    public ICollection<Order> Orders { get; set; } = [];

    public Customer(): base() {
        this.CreatedAt = this.UpdatedAt = DateTime.UtcNow;
    }

    [SetsRequiredMembers]
    public Customer(CustomerDTO dto) : base(dto)
    {
        this.CreatedAt = this.UpdatedAt = DateTime.UtcNow;
    }

    [SetsRequiredMembers]
    public Customer(dynamic record)
    {
        this.CustomerName = record.name;
        this.Country = record.country;
        this.City = record.city;
        this.Address = record.address;
        this.PostalCode = record.postal;
        this.ContactName = record.contact;
        this.CreatedAt = this.UpdatedAt = DateTime.UtcNow;
    }

    public void Update(CustomerDTO dto)
    {
        this.CustomerName = dto.CustomerName;
        this.Country = dto.Country;
        this.City = dto.City;
        this.Address = dto.Address;
        this.PostalCode = dto.PostalCode;
        this.ContactName = dto.ContactName;
        this.UpdatedAt = DateTime.UtcNow;
    }

}

public class CustomerDTO
{
    public CustomerDTO() { }

    [SetsRequiredMembers]
    public CustomerDTO(CustomerDTO c) 
    { 
        this.CustomerName = c.CustomerName;
        this.Country = c.Country;
        this.City = c.City;
        this.Address = c.Address;
        this.PostalCode = c.PostalCode;
        this.ContactName = c.ContactName;
    }

    public required String CustomerName { get; set; }
    public required String Country { get; set; }
    public required String City { get; set; }
    public required String Address { get; set; }
    public required String PostalCode { get; set; }
    public String? ContactName { get; set; }
}

public class CustomerReadDTO : CustomerDTO
{
    public CustomerReadDTO() { }

    [SetsRequiredMembers]
    public CustomerReadDTO(Customer c) : base(c)
    {
        this.Id = c.Id;
    }

    public long Id { get; set; }
}