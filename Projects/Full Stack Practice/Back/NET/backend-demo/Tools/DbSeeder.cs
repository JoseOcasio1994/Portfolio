using backend_demo.Models;
using CsvHelper;
using CsvHelper.Configuration;
using NuGet.Versioning;
using System.Data;
using System.Globalization;

namespace backend_demo.Tools;

public class DbSeeder(SeedContext context)
{
    private readonly SeedContext _context = context;

    public void Seed()
    {
        var config = new CsvConfiguration(CultureInfo.InvariantCulture)
        {
            HasHeaderRecord = true,
            Mode = CsvMode.RFC4180,
            TrimOptions = TrimOptions.Trim
        };

        SeedCategories(config);
        SeedProducts(config);
        SeedCustomers(config);
        SeedOrders(config);
        SeedOrderDetails(config);
    }

    private void SeedCategories(CsvConfiguration config)
    {
        if (!_context.Categories.Any())
        {
            string filePath = "Data\\Categories.csv";
            List<Category> categories = [];
           
            using (var reader = new StreamReader(filePath))
            using (var csv = new CsvReader(reader, config))
            {
                var records = csv.GetRecords<dynamic>().ToList();

                foreach (var record in records)
                {
                    categories.Add(new Category(record));
                }
            }

            _context.Categories.AddRange(categories);
            _context.SaveChanges();
        }
    }

    private void SeedProducts(CsvConfiguration config)
    {
        if (!_context.Products.Any() )
        {
            string filePath = "Data\\Products.csv";
            List<Product> products = [];

            using (var reader = new StreamReader(filePath))
            using (var csv = new CsvReader(reader, config))
            {
                var records = csv.GetRecords<dynamic>().ToList();
                var categories = _context.Categories;

                foreach (var record in records)
                {
                    long catId = long.Parse(record.category);
                    Category cat = categories.Where(c => c.Id == catId).First();
                    products.Add(new Product(record, cat));
                }
            }

            _context.Products.AddRange(products);
            _context.SaveChanges();
        }
    }

    private void SeedCustomers(CsvConfiguration config)
    {
        if (!_context.Customers.Any())
        {
            string filePath = "Data\\Customers.csv";
            List<Customer> customers = [];

            using (var reader = new StreamReader(filePath))
            using (var csv = new CsvReader(reader, config))
            {
                var records = csv.GetRecords<dynamic>().ToList();

                foreach (var record in records)
                {
                    customers.Add(new Customer(record));
                }
            }

            _context.Customers.AddRange(customers);
            _context.SaveChanges();
        }
    }

    private void SeedOrders(CsvConfiguration config)
    {
        if (!_context.Orders.Any())
        {
            string filePath = "Data\\Orders.csv";
            List<Order> orders = [];
            var customers = _context.Customers;

            using (var reader = new StreamReader(filePath))
            using (var csv = new CsvReader(reader, config))
            {
                var records = csv.GetRecords<dynamic>().ToList();

                foreach (var record in records)
                {
                    long id = long.Parse(record.customer);
                    var customer = customers.Where(c => c.Id == id).First();
                    orders.Add(new Order(record, customer));
                }
            }

            _context.Orders.AddRange(orders);
            _context.SaveChanges();
        }
    }

    private void SeedOrderDetails(CsvConfiguration config)
    {
        if (!_context.OrderDetails.Any())
        {
            string filePath = "Data\\OrderDetails.csv";
            List<OrderDetails> details = [];
            var products = _context.Products;
            var orders = _context.Orders;

            using (var reader = new StreamReader(filePath))
            using (var csv = new CsvReader(reader, config))
            {
                var records = csv.GetRecords<dynamic>().ToList();

                foreach (var record in records)
                {
                    long oid = long.Parse(record.order);
                    var order = orders.Where(o => o.Id == oid).First();

                    long pid = long.Parse(record.product);
                    var product = products.Where(p => p.Id == pid).First();

                    details.Add(new OrderDetails(record, order, product));
                }
            }

            _context.OrderDetails.AddRange(details);
            _context.SaveChanges();
        }
    }
}
