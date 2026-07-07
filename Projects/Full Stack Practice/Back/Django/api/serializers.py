from rest_framework import serializers
from api import models
from django.contrib.auth.models import User

class CategorySerializer(serializers.ModelSerializer):
    class Meta:
        model = models.Category
        fields = ['id', 'categoryName', 'description']
        read_only_fields = ['id']

class CustomerSerializer(serializers.ModelSerializer):
    class Meta:
        model = models.Customer
        fields = ['id', 'customerName', 
                  'contactName', 'address',
                  'city', 'country', 'postalCode'
                 ]
        read_only_fields = ['id']
        
class ProductSerializer(serializers.ModelSerializer):
    
    category = serializers.CharField(source='categoryId.categoryName')
    
    class Meta:
        model = models.Product
        fields = ['id', 'productName', 
                  'category', 'unit', 'price']
        read_only_fields = ['id']
          
class OrderDetailNestedSerializer(serializers.ModelSerializer):
    
    product = serializers.CharField(source='productId.productName')
    
    class Meta:
        model = models.OrderDetail
        fields = ['id', 'product', 'quantity']
        read_only_fields = ['id']
        
    def validate(self, data):
        if self.instance:
            immutable_fields = ['id', 'orderId']

            for field_name in immutable_fields:
                
                if field_name in data:
                    current_value = getattr(self.instance, field_name)
                    new_value = data.get(field_name)

                    if current_value != new_value:
                        raise serializers.ValidationError(
                            {field_name: "This field cannot be changed after creation."}
                        )

        return data
   
class OrderDetailReadSerializer(serializers.ModelSerializer):
    
    productId = ProductSerializer()
    
    class Meta:
        model = models.OrderDetail
        fields = ['id', 'orderId', 'productId', 'quantity']
        read_only_fields = ['id', 'orderId', 'productId', 'quantity']
        
class OrderDetailWriteSerializer(serializers.ModelSerializer):
    
    class Meta:
        model = models.OrderDetail
        fields = ['id', 'orderId', 'productId', 'quantity']
        read_only_fields = ['id']
        
    def create(self, request):
        id = self.context['view'].kwargs.get('id')
        order = models.Order.objects.get(id=id)
        detail = models.OrderDetail.objects.create(orderId=order, productId=request['productId'], quantity=request['quantity'])
        
        return detail
        
    def validate(self, data):
        if self.instance:
            immutable_fields = ['id', 'orderId']

            for field_name in immutable_fields:
                
                if field_name in data:
                    current_value = getattr(self.instance, field_name)
                    new_value = data.get(field_name)

                    if current_value != new_value:
                        raise serializers.ValidationError(
                            {field_name: "This field cannot be changed after creation."}
                        )

        return data
   
class OrderSerializer(serializers.ModelSerializer):
    
    customer = serializers.CharField(source='customerId.customerName')
    details = OrderDetailNestedSerializer(many=True)
    
    class Meta:
        model = models.Order
        fields = ['id', 'customer', 'orderDate', 'details']
        #read_only_fields = ['id']
        
    def create(self, request):
        details = request['details']
        cId = request['customerId']['customerName']
        customer = models.Customer.objects.get(customerName=cId)
        order = models.Order.objects.create(id=request['id'], customerId = customer, orderDate=request['orderDate'])
        
        for d in details:
            product = models.Product.objects.get(productName=d['productId']['productName'])
            detail = models.OrderDetail.objects.create(orderId=order, productId=product, quantity=d['quantity'])
            print(detail)
            
        return order
    
    def validate(self, data):
        if self.instance:
            immutable_fields = ['id', 'customer']

            for field_name in immutable_fields:
                
                if field_name in data:
                    current_value = getattr(self.instance, field_name)
                    new_value = data.get(field_name)

                    if current_value != new_value:
                        raise serializers.ValidationError(
                            {field_name: "This field cannot be changed after creation."}
                        )

        return data
