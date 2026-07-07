<style src="./banner.css"></style>
<script setup lang="ts">

import { computed } from 'vue';
import { useRouter } from 'vue-router';
import { useUserStore } from '@/stores/login-service.ts';
import { useCartStore } from '@/stores/cart-service.ts';
import { FontAwesomeIcon } from '@fortawesome/vue-fontawesome';
import {
    getMenuList,
    useToggleMenu,
    useSearch,
    goToCart,
    goToLogin
} from './banner.ts';

const router = useRouter();
const userStore = useUserStore();
const user = computed(() => userStore.GetUser());

const cartStore = useCartStore();
const cartSize = computed(() => cartStore.getProducts().size);

const menuList = getMenuList();
const { menuOpened, toggleMenu } = useToggleMenu();
const { searchTerm, search } = useSearch();

</script>

<template>
    <div class="banner">

        <div class="menu-container">

            <button @click="toggleMenu()" class="menu">
                <font-awesome-icon icon="fa-solid fa-bars" v-if="menuOpened === false"/>
                <font-awesome-icon icon="fa-solid fa-xmark" v-else/>
                Menu
            </button>

            <div class="flyout-content" v-if="menuOpened === true">
                <ul v-if="menuList.length > 0">
                    <li v-for="item in menuList" :key="item" >
                        <label>{{item}}</label>
                    </li>
                </ul>
                <ul v-else>
                    <li>There are no items to display.</li>
                </ul>
            </div>

        </div>

        <div class="search-container">
            <input type="text" placeholder="Search.." v-model="searchTerm">
            <button @click=" search()">
                <font-awesome-icon icon="fa-solid fa-magnifying-glass"/>
            </button>
        </div>

        <button @click="goToLogin(router)" class="login" v-if="!user">
            <font-awesome-icon icon="fa-solid fa-user" />
            <label>Login</label>
        </button>
        <button class="login" v-else>
            <font-awesome-icon icon="fa-solid fa-user" />
            <label>{{user.name}}</label>
        </button>
        
        <v-badge location="top right" color="success" :content="cartSize" 
            :offset-y="10" :offset-x="-10" overlap :model-value="cartSize > 0"
        >
            <button class="cart" @click="goToCart(router)">
                <font-awesome-icon icon="fa-solid fa-cart-shopping" />
                <label>Cart</label>
            </button>
        </v-badge>
    </div>
</template>