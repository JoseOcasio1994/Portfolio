import { createRouter, createWebHistory } from 'vue-router'
import homeview from '../views/home/home-view.vue'
import loginView from '@/views/login/login-view.vue'
import registerView from '@/views/register/register-view.vue'
import productView from '@/views/products/product-view.vue'
import cartView from '@/views/cart/cart-view.vue'

const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes: [
    {
      path: '/',
      name: 'root',
      redirect: { name: 'home'}
    },
    {
      path: '/home',
      name: 'home',
      component: homeview
    },
    {
      path: '/products',
      name: 'products',
      component: productView
    },
    {
      path: '/register',
      name: 'register',
      component: registerView
    },
    {
      path: '/login',
      name: 'login',
      component: loginView
    },
    {
      path: '/cart',
      name: 'cart',
      component: cartView
    }
    
  ],
})

export default router
