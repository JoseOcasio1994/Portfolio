from rest_framework import viewsets
from rest_framework.permissions import IsAuthenticated, AllowAny
from rest_framework_simplejwt.authentication import JWTAuthentication
from rest_framework.filters import OrderingFilter, SearchFilter
from rest_framework.pagination import PageNumberPagination
from django_filters.rest_framework import DjangoFilterBackend
from drf_spectacular.utils import extend_schema, OpenApiParameter
from drf_spectacular.types import OpenApiTypes
from api import models, serializers, filters

class ProtectedViewSet(viewsets.ModelViewSet):
    authentication_classes = [JWTAuthentication]
    permission_classes = [IsAuthenticated]

class PublicViewSet(viewsets.ModelViewSet):
    permission_classes = [AllowAny]

class CategoryView(ProtectedViewSet):
    queryset = models.Category.objects.all()
    serializer_class = serializers.CategorySerializer

class CustomerView(PublicViewSet):
    queryset = models.Customer.objects.all()
    serializer_class = serializers.CustomerSerializer
    
class ProductView(PublicViewSet):
    queryset = models.Product.objects.all()
    serializer_class = serializers.ProductSerializer
    
    filter_backends = [DjangoFilterBackend, OrderingFilter, SearchFilter]
    filterset_fields = ['price_min', 'price_max']
    filterset_class = filters.ProductFilter
                        
    search_fields = ['productName', 'unit', 'categoryId__categoryName']
    ordering_fields = ['productName', 'price', 'categoryId__categoryName']
    ordering = ['productName']
    
    pagination_class = PageNumberPagination
    pagination_class.page_size = 10
    pagination_class.page_size_query_param = 'page_size' # /api/products/?page_size=50)
    pagination_class.max_page_size = 100
    
    @extend_schema(
        parameters=[
            OpenApiParameter(
                name='price_min',
                type=OpenApiTypes.INT, # Use OpenApiTypes.DATE or similar for date ranges
                location=OpenApiParameter.QUERY,
                description='Minimum price in range',
                required=False,
            ),
            OpenApiParameter(
                name='price_max',
                type=OpenApiTypes.INT, # Use OpenApiTypes.DATE or similar for date ranges
                location=OpenApiParameter.QUERY,
                description='Maximum price in range',
                required=False,
            ),
        ]
    )
    def get(self, request, *args, **kwargs):
        return super().get(request, *args, **kwargs)
    
class OrderView(PublicViewSet):
    queryset = models.Order.objects.all().prefetch_related('details')
    serializer_class = serializers.OrderSerializer
    
class OrderDetailView(PublicViewSet):
    serializer_class = serializers.OrderDetailReadSerializer
    
    def get_queryset(self):
        id = self.kwargs.get("id")
        if id is not None:
            return models.OrderDetail.objects.filter(orderId=id)
        return models.OrderDetail.objects.all()
    
    def get_serializer_class(self):
        if self.action in ['create', 'update', 'partial_update']:
            return serializers.OrderDetailWriteSerializer
        return serializers.OrderDetailReadSerializer
