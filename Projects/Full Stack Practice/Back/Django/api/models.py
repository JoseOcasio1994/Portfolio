
from django.db import models

class Category(models.Model):
    id = models.AutoField(primary_key=True)
    categoryName = models.CharField(max_length=100, unique=True, null=False)
    description = models.TextField(max_length=100, null=False)
    createdAt = models.DateTimeField(auto_now_add=True)
    updatedAt = models.DateTimeField(auto_now=True)

    def __str__(self):
        return self.categoryName + " " + self.description
    
    class Meta:
        db_table = 'categories'
    
class Customer(models.Model):
    id = models.AutoField(primary_key=True)
    customerName = models.CharField(max_length=100, null=False)
    contactName = models.TextField(max_length=100, null=True)
    address = models.TextField(max_length=100, null=False)
    city = models.TextField(max_length=100, null=False)
    country = models.TextField(max_length=100, null=False)
    postalCode = models.TextField(max_length=100, null=False)
    createdAt = models.DateTimeField(auto_now_add=True)
    updatedAt = models.DateTimeField(auto_now=True)

    def __str__(self):
        return self.customerName
    
    class Meta:
        db_table = 'customers'
    
class Product(models.Model):
    id = models.AutoField(primary_key=True)
    productName = models.CharField(max_length=100, null=False)
    categoryId = models.ForeignKey(Category, related_name='product', on_delete=models.CASCADE)
    unit = models.CharField(max_length=100, null=True)
    price = models.DecimalField(max_digits=9, decimal_places=2, null=False)
    createdAt = models.DateTimeField(auto_now_add=True)
    updatedAt = models.DateTimeField(auto_now=True)

    def __str__(self):
        return self.productName
    
    class Meta:
        db_table = 'products'
    
class Order(models.Model):
    id = models.BigIntegerField(primary_key=True)
    customerId = models.ForeignKey(Customer, related_name='order', on_delete=models.CASCADE)
    orderDate = models.DateField(null=False)
    createdAt = models.DateTimeField(auto_now_add=True)
    updatedAt = models.DateTimeField(auto_now=True)

    def __str__(self):
        return str(self.id)
    
    class Meta:
        db_table = 'orders'
    
class OrderDetail(models.Model):
    id = models.AutoField(primary_key=True)
    # Null Requirement Handled In View
    orderId = models.ForeignKey(Order, related_name='details', on_delete=models.CASCADE, null=True, blank=True)
    productId = models.ForeignKey(Product, related_name='orders', on_delete=models.CASCADE)
    quantity = models.IntegerField(null=False)
    createdAt = models.DateTimeField(auto_now_add=True)
    updatedAt = models.DateTimeField(auto_now=True)

    def __str__(self):
        return str(self.id)
    
    class Meta:
        db_table = 'order_details'
    