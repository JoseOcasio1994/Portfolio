<style src="./cartCard.css"></style>
<script setup lang="ts">
import { computed, type PropType } from 'vue';
import { FontAwesomeIcon } from '@fortawesome/vue-fontawesome';
import { type Product } from '@/models/product';

const props = defineProps({
    product: {
        type: Object as PropType<Product>,
        required: true
    },
    stock:{
        type: Number,
        required: true
    },
});

const imgLink = computed(() => {
 return new URL(`../../assets/images/${props.product?.image}`, import.meta.url).href;
});

function decrease() { 
    if (props.product) {
        //cartService.subtractProduct(product);
    }
}

function increase() { 
    if (props.product) {
        //cartService.addProduct(product);
    }
}

function remove() { 
    if (props.product) {
        //cartService.removeProduct(product);
    }
}

</script>

<template>

    <div class="cart-card-container">
        <div class="image-container">
            <img :src="imgLink">
        </div>

        <div class="cart-product-container">
            <div class="info-container">
                <label> {{props.product?.name}} </label>
                <label> ${{props.product?.price.toFixed(2)}} </label>
            </div>

            <div class="cart-button-container">
                <button @click="decrease()">{{'<'}}</button>
                <input disabled :value="stock" type="number">
                <button @click="increase()">></button>
                <button @click="remove()">
                    <font-awesome-icon icon="fa-solid fa-trash-can" />
                </button>
            </div>
        </div>
    </div>

</template>