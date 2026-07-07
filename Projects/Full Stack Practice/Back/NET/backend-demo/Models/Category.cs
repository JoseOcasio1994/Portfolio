using Microsoft.Extensions.Hosting;
using NuGet.Protocol;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Diagnostics.CodeAnalysis;

namespace backend_demo.Models;

[Table("Categories")]
public class Category : CategoryDTO
{
    [Key]
    [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
    public long Id { get; set; }
    public required DateTime CreatedAt { get; set; }
    public required DateTime UpdatedAt { get; set; }

    public ICollection<Product> Products { get; set; } = [];

    public Category(): base() {
        this.CreatedAt = this.UpdatedAt = DateTime.UtcNow;
    }

    [SetsRequiredMembers]
    public Category(CategoryDTO c) : base(c)
    {
        this.CreatedAt = this.UpdatedAt = DateTime.UtcNow;
    }

    [SetsRequiredMembers]
    public Category(dynamic record)
    {
        this.CategoryName = record.category;
        this.Description = record.description;
        this.CreatedAt = this.UpdatedAt = DateTime.UtcNow;
    }

    public void Update(CategoryDTO dto)
    {
        this.CategoryName = dto.CategoryName;
        this.Description = dto.Description;
        this.UpdatedAt = DateTime.UtcNow;
    }
}

public class CategoryDTO
{
    public CategoryDTO() { }

    [SetsRequiredMembers]
    public CategoryDTO(CategoryDTO c)
    {
        this.CategoryName = c.CategoryName;
        this.Description = c.Description;
    }

    public required String CategoryName { get; set; }
    public String? Description { get; set; }
}

public class CategoryReadDTO:  CategoryDTO
{
    public CategoryReadDTO() { }

    [SetsRequiredMembers]
    public CategoryReadDTO(Category c): base(c)
    {
        this.Id = c.Id;
    }

    public long Id { get; set; }
}