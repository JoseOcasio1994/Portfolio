import django_filters
from .models import Product

class ProductFilter(django_filters.FilterSet):
    # 'price_min' and 'price_max'
    price = django_filters.RangeFilter() 
    productName = django_filters.CharFilter(lookup_expr='icontains')
    category = django_filters.CharFilter(
        field_name='categoryId__categoryName', 
        lookup_expr='icontains'
    )
    
    class Meta:
        model = Product
        fields = ['productName', 'category', 'price'] 