using backend_demo.Models;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace backend_demo.Controllers;

[Route("api/[controller]")]
[ApiController]
public class ProductsController(ProductContext context) : ControllerBase
{
    private readonly ProductContext _context = context;

    // GET: api/Products
    [HttpGet]
    public async Task<ActionResult<SearchResults<ProductReadDTO>>> GetProduct([FromQuery] Search parameters)
    {
        Search finalParam = new(parameters);
        var products = await _context.Product.Include(p => p.Category).ToListAsync();

        var filtered = String.IsNullOrEmpty(finalParam.Filter) ? 
            products : 
            products.Where( x => x.ProductName.Contains(finalParam.Filter, StringComparison.CurrentCultureIgnoreCase));

        var ordered = finalParam.Sort == "Price" ? 
            filtered.OrderBy(x => x.Price) :
            filtered.OrderBy(x => x.ProductName);

        var curPage = finalParam.PageNumber ?? 1;
        var pageSize = finalParam.PageSize ?? 10;
        var paginated = ordered
            .Skip((curPage - 1) * pageSize)
            .Take(pageSize);

        var results = paginated
            .Select(p => new ProductReadDTO(p));

        int Pages = (int)Math.Ceiling((double)filtered.Count() / pageSize);
        return new SearchResults<ProductReadDTO>(
            results, 
            curPage, 
            Pages, // Total Pages
            filtered.Count() // Total Items
        );
    }

    // GET: api/Products/5
    [HttpGet("{id}")]
    public async Task<ActionResult<ProductReadDTO>> GetProduct(long id)
    {
        var product = await _context.Product
            .Include(p => p.Category)
            .FirstAsync(p => p.Id == id);

        if (product == null)
        {
            return NotFound();
        }

        return new ProductReadDTO(product);
    }

    // PUT: api/Products/5
    [HttpPut("{id}")]
    public async Task<ActionResult<ProductReadDTO>> PutProduct(long id, ProductWriteDTO dto)
    {
        var product = await _context.Product.FindAsync(id);

        if (product == null)
        {
            return NotFound("Product Not Found");
        }

        var cat = await _context.Category.FindAsync(dto.CategoryId);

        if (cat == null)
        {
            return NotFound("Category Not Found");
        }

        product.Update(dto, cat);
        _context.Entry(product).State = EntityState.Modified;

        try
        {
            await _context.SaveChangesAsync();
        }
        catch (DbUpdateConcurrencyException e)
        {
            return BadRequest(e.Message);
        }

        return new ProductReadDTO(product);
    }

    // POST: api/Products
    [HttpPost]
    public async Task<ActionResult<ProductReadDTO>> PostProduct(ProductWriteDTO dto)
    {
        var cat = await _context.Category.FindAsync(dto.CategoryId);

        if (cat == null)
        {
            return NotFound("Category Not Found");
        }

        Product product = new(dto, cat);
        _context.Product.Add(product);
        await _context.SaveChangesAsync();

        ProductReadDTO resp = new(product);
        return CreatedAtAction(nameof(GetProduct), new { id = resp.Id }, resp);
    }

    // DELETE: api/Products/5
    [HttpDelete("{id}")]
    public async Task<IActionResult> DeleteProduct(long id)
    {
        var product = await _context.Product.FindAsync(id);
        if (product == null)
        {
            return NotFound();
        }

        _context.Product.Remove(product);
        await _context.SaveChangesAsync();

        return NoContent();
    }

    private bool ProductExists(long id)
    {
        return _context.Product.Any(e => e.Id == id);
    }

}