using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using backend_demo.Models;

namespace backend_demo.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class OrdersController(OrderContext context) : ControllerBase
    {
        private readonly OrderContext _context = context;

        // GET: api/Orders
        [HttpGet]
        public async Task<ActionResult<IEnumerable<OrderReadDTO>>> GetOrder()
        {
            return await _context.Orders
                .Include(o => o.Customer)
                .Include(o => o.Details)
                .ThenInclude(o => o.Product)
                .Select(o => new OrderReadDTO(o))
                .ToListAsync();
        }

        // GET: api/Orders/5
        [HttpGet("{id}")]
        public async Task<ActionResult<OrderReadDTO>> GetOrder(long id)
        {
            var order = await _context.Orders
                .Include(o => o.Customer)
                .Include(o => o.Details)
                .ThenInclude(o => o.Product)
                .FirstAsync(o => o.Id == id);

            if (order == null)
            {
                return NotFound();
            }

            return new OrderReadDTO(order);
        }

        // GET: api/Orders/details
        [HttpGet("details")]
        public async Task<ActionResult<List<OrderDetailsReadDTO>>> GetOrderDetails()
        {
            return await _context.OrderDetails
                .Include(o => o.Order)
                .Include(o => o.Product)
                .Select(o => new OrderDetailsReadDTO(o))
                .ToListAsync();
        }

        // GET: api/Orders/details/{id}
        [HttpGet("details/{id}")]
        public async Task<ActionResult<OrderDetailsReadDTO>> GetOrderDetails(long id)
        {
            var detail = await _context.OrderDetails
                .Include(o => o.Order)
                .Include(o => o.Product)
                .FirstAsync(o => o.Id == id);

            if (detail == null)
            {
                return NotFound();
            }

            return new OrderDetailsReadDTO(detail);
        }

        // PUT: api/Orders/5
        [HttpPut("{id}")]
        public async Task<ActionResult<OrderReadDTO>> PutOrder(long id, List<OrderDetailsPutDTO> dtos)
        {
            var order = await _context.Orders
                .Include(o => o.Customer)
                .Include(o => o.Details)
                .FirstAsync(o => o.Id == id);

            if (order == null)
            {
                return NotFound("Order Not Found");
            }

            foreach (OrderDetailsPutDTO d in dtos)
            {
                var detail = order.Details.Where(x => x.Id == d.Id).FirstOrDefault();

                if (detail == null)
                {
                    return BadRequest("Order Detail ID not found or does not belong to this Order");
                }

                var p = await _context.Products.FindAsync(d.ProductId);

                if (p == null)
                {
                    return NotFound("Product " + d.ProductId + " Not Found");
                }

                detail.Update(d, p);
                _context.Entry(detail).State = EntityState.Modified;
            }

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException e)
            {
                return BadRequest(e.Message);
            }

            return new OrderReadDTO(order);
        }

        // PUT: api/Orders/details/5
        [HttpPut("details/{id}")]
        public async Task<ActionResult<OrderDetailsReadDTO>> PutOrderDetail(long id, OrderDetailsDTO dto)
        {
            var detail = await _context.OrderDetails
                .Include(o => o.Order)
                .Include(o => o.Product)
                .FirstAsync(o => o.Id == id); ;

            if (detail == null)
            {
                return NotFound("Order Detail Not Found");
            }

            var p = await _context.Products.FindAsync(dto.ProductId);

            if (p == null)
            {
                return NotFound("Product " + dto.ProductId + " Not Found");
            }

            detail.Update(dto, p);
            _context.Entry(detail).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException e)
            {
                return BadRequest(e.Message);
            }

            return new OrderDetailsReadDTO(detail);
        }

        // POST: api/Orders
        [HttpPost]
        public async Task<ActionResult<OrderReadDTO>> PostOrder(OrderDTO dto)
        {
            var customers = _context.Customers;
            var products = _context.Products;

            var c = await customers.FindAsync(dto.CustomerId);

            if (c == null)
            {
                return NotFound("Customer Not Found");
            }

            foreach (OrderDetailsDTO d in dto.Details)
            {
                var p = await products.FindAsync(d.ProductId);

                if (p == null)
                {
                    return NotFound("Product " + d.ProductId + " Not Found");
                }
            }

            Order order = new(dto, c);
             _context.Orders.Add(order);
            await _context.SaveChangesAsync();

            List<OrderDetails> details = [];
            dto.Details.ForEach(d => details.Add(new OrderDetails(d, order, null)));
            _context.OrderDetails.AddRange(details);

            await _context.SaveChangesAsync();
            order.Details = details;
            OrderReadDTO resp = new(order);
            return CreatedAtAction(nameof(GetOrder), new { id = resp.Id }, resp);
        }

        // DELETE: api/Orders/5
        [HttpDelete("{id}")]
        public async Task<IActionResult> DeleteOrder(long id)
        {
            var order = await _context.Orders.FindAsync(id);
            if (order == null)
            {
                return NotFound();
            }

            _context.Orders.Remove(order);

            IQueryable<OrderDetails> orders = _context.OrderDetails;
            var foundOrders = orders.Where(o => o.Order.Id == id);

            if (foundOrders != null && foundOrders.Any())
            {
                _context.OrderDetails.RemoveRange(foundOrders);
            }

            await _context.SaveChangesAsync();

            return NoContent();
        }

        // DELETE: api/Orders/details/5
        [HttpDelete("details/{id}")]
        public async Task<IActionResult> DeleteOrderDetail(long id)
        {
            var detail = await _context.OrderDetails.FindAsync(id);
            if (detail == null)
            {
                return NotFound();
            }

            _context.OrderDetails.Remove(detail);

            await _context.SaveChangesAsync();

            return NoContent();
        }

        private bool OrderExists(long id)
        {
            return _context.Orders.Any(e => e.Id == id);
        }
    }
}
