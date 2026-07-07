from rest_framework.routers import DefaultRouter
from api import views
from django.urls import path, include

router = DefaultRouter()
router.register(r'categories', views.CategoryView)
router.register(r'customers', views.CustomerView)
router.register(r'products', views.ProductView)
router.register(r'orders', views.OrderView)
router.register(r'orders/(?P<id>\d+)/details', views.OrderDetailView, basename='orderDetail')

urlpatterns = [
    path('', include(router.urls)),
    path("auth/", include("dj_rest_auth.urls")),
    path('auth/registration/', include('dj_rest_auth.registration.urls'))
]
