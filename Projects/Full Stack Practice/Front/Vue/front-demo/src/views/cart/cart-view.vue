
<style src="./cart.css"></style>
<script setup lang="ts">
import { ref, onMounted } from 'vue';
import cartCard from '@/components/cart-card/cart-card.vue';
import { useCartStore } from '@/stores/cart-service';

const cartStore = useCartStore();
const products = ref(new Map<number, any>());

onMounted(() => {
    products.value = cartStore.getProducts();
})

function Tax(): Number {
    return cartStore.getTax();
}

function subTotal(): Number  {
    return cartStore.subtotal;
}

</script>

<template>
    <div class="cart-container">

        <ul class="product-list">
            <li v-for="[, value] in products" :key="value.product.name">
                <cartCard :product="value.product" :stock="value.count"/>
            </li>
        </ul>

        <div class="price-container">
            <label><b>Subtotal:</b> ${{subTotal().toFixed(2)}}</label>
            <label><b>Tax:</b> ${{Tax().toFixed(2)}}</label>
            <label><b>Total:</b> ${{subTotal().toFixed(2)}}</label>
            <button>Proceed To Checkout</button>
        </div>
    </div>
</template>