using Microsoft.CodeAnalysis.FlowAnalysis.DataFlow.CopyAnalysis;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Diagnostics.CodeAnalysis;

namespace backend_demo.Models;

[Table("Products")]
public class Product  : ProductDTO
{
    [Key]
    [DatabaseGenerated(DatabaseGeneratedOption.Identity)]
    public long Id { get; set; }
    public required DateTime CreatedAt { get; set; }
    public required DateTime UpdatedAt { get; set; }

    [ForeignKey("CategoryId")]
    public required Category Category { get; set; } = null!;
    public long CategoryId { get; set; }

    public ICollection<OrderDetails> Details { get; set; } = [];

    [SetsRequiredMembers]
    public Product() : base()
    {
        this.CreatedAt = this.UpdatedAt = DateTime.UtcNow;
    }

    [SetsRequiredMembers]
    public Product(ProductDTO dto, Category cat) : base(dto)
    {
        this.CategoryId = cat.Id;
        this.Category = cat;
        this.CreatedAt = this.UpdatedAt = DateTime.UtcNow;
    }

    [SetsRequiredMembers]
    public Product(dynamic record, Category cat)
    {
        this.ProductName = record.name;
        this.CategoryId = cat.Id;
        this.Category = cat;
        this.Unit = record.unit;
        this.Price = float.Parse(record.price);
        this.CreatedAt = this.UpdatedAt = DateTime.UtcNow;
    }

    public void Update(ProductDTO dto, Category cat)
    {
        this.ProductName = dto.ProductName;
        this.CategoryId = cat.Id;
        this.Category = cat;
        this.Unit = dto.Unit;
        this.Price = dto.Price;
        this.UpdatedAt = DateTime.UtcNow;
    }

}

public class ProductDTO
{
    [SetsRequiredMembers]
    public ProductDTO() { }

    [SetsRequiredMembers]
    public ProductDTO(ProductDTO p)
    {
        this.Copy(p);
    }

    protected void Copy(ProductDTO p)
    {
        this.ProductName = p.ProductName;
        this.Unit = p.Unit;
        this.Price = p.Price;
    }

    public required String ProductName { get; set; } = string.Empty;
    public required String Unit { get; set; } = string.Empty;
    public required float Price { get; set; }
}

public class ProductWriteDTO: ProductDTO
{
    [SetsRequiredMembers]
    public ProductWriteDTO(): base() { }

    [SetsRequiredMembers]
    public ProductWriteDTO(ProductWriteDTO p) : base()
    {
        this.Copy((ProductDTO)p);
        this.CategoryId = p.CategoryId;
    }

    public required long CategoryId { get; set; }
}

public class ProductReadDTO : ProductWriteDTO
{
    [SetsRequiredMembers]
    public ProductReadDTO(): base() { }

    [SetsRequiredMembers]
    public ProductReadDTO(Product p)
    {
        this.Copy((ProductDTO)p);
        this.Id = p.Id;
        this.CategoryId = p.Category.Id;
        this.CategoryName = p.Category.CategoryName;
    }

    public long Id { get; set; }
    public required String CategoryName { get; set; } = string.Empty;
}