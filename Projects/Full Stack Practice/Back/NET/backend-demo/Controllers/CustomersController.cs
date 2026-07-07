using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using backend_demo.Models;

namespace backend_demo.Controllers;

[Route("api/[controller]")]
[ApiController]
public class CustomersController(CustomerContext context) : ControllerBase
{
    private readonly CustomerContext _context = context;

    // GET: api/Customers
    [HttpGet]
    public async Task<ActionResult<IEnumerable<CustomerReadDTO>>> GetCustomer()
    {
        return await _context.Customer
            .Select(c => new CustomerReadDTO(c))
            .ToListAsync();
    }

    // GET: api/Customers/5
    [HttpGet("{id}")]
    public async Task<ActionResult<CustomerReadDTO>> GetCustomer(long id)
    {
        var customer = await _context.Customer.FindAsync(id);

        if (customer == null)
        {
            return NotFound();
        }

        return new CustomerReadDTO(customer);
    }

    // PUT: api/Customers/5
    // To protect from overposting attacks, see https://go.microsoft.com/fwlink/?linkid=2123754
    [HttpPut("{id}")]
    public async Task<ActionResult<CustomerReadDTO>> PutCustomer(long id, CustomerDTO dto)
    {
        var customer = await _context.Customer.FindAsync(id);

        if (customer == null)
        {
            return NotFound();
        }

        customer.Update(dto);
        _context.Entry(customer).State = EntityState.Modified;

        try
        {
            await _context.SaveChangesAsync();
        }
        catch (DbUpdateConcurrencyException e)
        {
            return BadRequest(e.Message);
        }

        return new CustomerReadDTO(customer);
    }

    // POST: api/Customers
    // To protect from overposting attacks, see https://go.microsoft.com/fwlink/?linkid=2123754
    [HttpPost]
    public async Task<ActionResult<CustomerReadDTO>> PostCustomer(CustomerDTO dto)
    {
        Customer customer = new(dto);
        _context.Customer.Add(customer);
        await _context.SaveChangesAsync();

        CustomerReadDTO resp = new(customer);
        return CreatedAtAction(nameof(GetCustomer), new { id = resp.Id }, resp);
    }

    // DELETE: api/Customers/5
    [HttpDelete("{id}")]
    public async Task<IActionResult> DeleteCustomer(long id)
    {
        var customer = await _context.Customer.FindAsync(id);
        if (customer == null)
        {
            return NotFound();
        }

        _context.Customer.Remove(customer);
        await _context.SaveChangesAsync();

        return NoContent();
    }

    private bool CustomerExists(long id)
    {
        return _context.Customer.Any(e => e.Id == id);
    }
}
