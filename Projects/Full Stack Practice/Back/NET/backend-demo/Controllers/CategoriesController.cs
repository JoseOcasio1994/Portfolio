using backend_demo.Models;
using backend_demo.Tools;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Http.HttpResults;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace backend_demo.Controllers;

[Route("api/[controller]")]
[ApiController]
[Authorize]
public class CategoriesController(CategoryContext context) : ControllerBase
{
    private readonly CategoryContext _context = context;

    // GET: api/Categories
    [HttpGet]
    public async Task<ActionResult<IEnumerable<CategoryReadDTO>>> GetCategory()
    {
        return await _context.Category
            .Select(c => new CategoryReadDTO(c))
            .ToListAsync();
    }

    // GET: api/Categories/5
    [HttpGet("{id}")]
    public async Task<ActionResult<CategoryReadDTO>> GetCategory(long id)
    {
        var category = await _context.Category.FindAsync(id);

        if (category == null)
        {
            return NotFound();
        }

        return new CategoryReadDTO(category);
    }

    // PUT: api/Categories/5
    // To protect from overposting attacks, see https://go.microsoft.com/fwlink/?linkid=2123754
    [HttpPut("{id}")]
    public async Task<ActionResult<CategoryReadDTO>> PutCategory(long id, CategoryDTO dto)
    {
        var category = await _context.Category.FindAsync(id);

        if (category == null)
        {
            return NotFound();
        }

        category.Update(dto);
        _context.Entry(category).State = EntityState.Modified;

        try
        {
            await _context.SaveChangesAsync();
        }
        catch (DbUpdateConcurrencyException e)
        {
            return BadRequest(e.Message);
        }

        return new CategoryReadDTO(category);
    }

    // POST: api/Categories
    [HttpPost]
    public async Task<ActionResult<CategoryReadDTO>> PostCategory(CategoryDTO dto)
    {
        Category category = new(dto);
        _context.Category.Add(category);
        await _context.SaveChangesAsync();

        CategoryReadDTO resp = new(category);
        return CreatedAtAction(nameof(GetCategory), new { id = resp.Id }, resp);
    }

    // DELETE: api/Categories/5
    [HttpDelete("{id}")]
    public async Task<IActionResult> DeleteCategory(long id)
    {
        var category = await _context.Category.FindAsync(id);
        if (category == null)
        {
            return NotFound();
        }

        _context.Category.Remove(category);
        await _context.SaveChangesAsync();

        return Ok();
    }

    private bool CategoryExists(long id)
    {
        return _context.Category.Any(e => e.Id == id);
    }
}
