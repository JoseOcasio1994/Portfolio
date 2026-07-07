<style src="./productCard.css"></style>
<script setup lang="ts">
import { computed, type PropType } from 'vue';
import { type Product } from '@/models/product';
import { useCartStore } from '@/stores/cart-service';

const props = defineProps({
    product: {
        type: Object as PropType<Product>,
        required: true
    }
});

const cartStore = useCartStore();

const imgLink = computed(() => {
 return new URL(`../../assets/images/${props.product?.image}`, import.meta.url).href;
});

function addToCart() {
    cartStore.addProduct(props.product);
}

</script>

<template>

    <div class="product-card-container">

        <div class="card-header">
            <img class="product-image" :src="imgLink" :alt="'Image of ' + props.product.name">
        </div>

        <div class="card-body">
            <label class="product-title">{{product?.name}}</label>
            <label class="product-price">${{product?.price?.toFixed(2)}}</label>
            <label class="product-other">Some other Information about this product</label>
        </div>

        <div class="card-footer">
                <button @click="addToCart" v-if="product?.inStock">Add To Cart</button>
                <button disabled v-else>Out of Stock</button>
        </div>

    </div>

</template>