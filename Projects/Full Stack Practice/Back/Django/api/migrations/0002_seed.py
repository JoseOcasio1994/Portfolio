import os
import pandas as pd
from django.db import migrations

migration_dir = os.path.dirname(__file__)
path = migration_dir + '\\..\\data\\'

def seedCategory(apps, schema_editor):
    data = pd.read_csv(path + 'Categories.csv', skipinitialspace=True)
    Category = apps.get_model('api', 'Category')
    for i in range(0, len(data)):
        Category.objects.create(
            id=i+1,
            categoryName=data['category'][i], 
            description=data['description'][i]
        )
        
    print("Categories created successfully")
        
def deleteCategory(apps, schema_editor):
    data = pd.read_csv(path + 'Categories.csv', skipinitialspace=True)
    Category = apps.get_model('api', 'Category')
    
    for i in range(0, len(data)):
        Category.objects.filter(id=i+1).delete()
        
    print("Categories deleted successfully")
        
def seedCustomer(apps, schema_editor):
    data = pd.read_csv(path + 'Customers.csv', skipinitialspace=True)
    Customer = apps.get_model('api', 'Customer')
    
    for i in range(0, len(data)):
        Customer.objects.create(
            id=i+1,
            customerName=data['name'][i], 
            contactName=data['contact'][i],
            address=data['address'][i], 
            city=data['city'][i],
            postalCode=data['postal'][i], 
            country=data['country'][i]
        )
        
    print("Customers created successfully")
    
def deleteCustomer(apps, schema_editor):
    data = pd.read_csv(path + 'Customers.csv', skipinitialspace=True)
    Customer = apps.get_model('api', 'Customer')
    
    for i in range(0, len(data)):
        Customer.objects.filter(id=i+1).delete()
        
    print("Customers deleted successfully")
    
def seedProduct(apps, schema_editor):
    data = pd.read_csv(path + 'Products.csv', skipinitialspace=True)
    Product = apps.get_model('api', 'Product')
    Category = apps.get_model('api', 'Category')
    
    for i in range(0, len(data)):
        catId = int(data['category'][i])
        cat = Category.objects.filter(id=catId)
        Product.objects.create(
            id=i+1,
            productName=data['name'][i], 
            categoryId=cat[0],
            unit=data['unit'][i], 
            price=data['price'][i],
        )
        
    print("Products created successfully")
   
def deleteProduct(apps, schema_editor):
    data = pd.read_csv(path + 'Products.csv', skipinitialspace=True)
    Product = apps.get_model('api', 'Product')
    
    for i in range(0, len(data)):
        Product.objects.filter(id=i+1).delete()
        
    print("Products deleted successfully")
    
def seedOrder(apps, schema_editor):
    data = pd.read_csv(path + 'Orders.csv', skipinitialspace=True)
    Order = apps.get_model('api', 'Order')
    Customer = apps.get_model('api', 'Customer')
    
    for i in range(0, len(data)):
        cId = int(data['customer'][i])
        c = Customer.objects.filter(id=cId)
        
        Order.objects.create(
            id=data['id'][i],
            customerId=c[0], 
            orderDate=data['date'][i]
        )
        
    print("Orders created successfully")
    
def deleteOrder(apps, schema_editor):
    data = pd.read_csv(path + 'Orders.csv', skipinitialspace=True)
    Order = apps.get_model('api', 'Order')
    
    for i in range(0, len(data)):
        Order.objects.filter(id=data['id'][i]).delete()
        
    print("Orders deleted successfully")
    
def seedOrderDetails(apps, schema_editor):
    data = pd.read_csv(path + 'OrderDetails.csv', skipinitialspace=True)
    Detail = apps.get_model('api', 'OrderDetail')
    Order = apps.get_model('api', 'Order')
    Product = apps.get_model('api', 'Product')
    
    for i in range(0, len(data)):
        oId = int(data['order'][i])
        o = Order.objects.filter(id=oId)
        
        pId = int(data['product'][i])
        p = Product.objects.filter(id=pId)
        
        Detail.objects.create(
            id=i+1,
            orderId=o[0], 
            productId=p[0],
            quantity=int(data['quantity'][i])
        )
        
    print("Order Details created successfully")

def deleteOrderDetails(apps, schema_editor):
    data = pd.read_csv(path + 'OrderDetails.csv', skipinitialspace=True)
    Order = apps.get_model('api', 'OrderDetail')
    
    for i in range(0, len(data)):
        Order.objects.filter(id=i+1).delete()
        
    print("Order Details deleted successfully")

class Migration(migrations.Migration):

    dependencies = [
        ('api', '0001_initial'),
    ]

    operations = [
        migrations.RunPython(
            seedCategory, reverse_code=deleteCategory
        ),
        migrations.RunPython(
            seedCustomer, reverse_code=deleteCustomer
        ),
        migrations.RunPython(
            seedProduct, reverse_code=deleteProduct
        ),
        migrations.RunPython(
            seedOrder, reverse_code=deleteOrder
        ),
        migrations.RunPython(
            seedOrderDetails, reverse_code=deleteOrderDetails
        )
    ]
