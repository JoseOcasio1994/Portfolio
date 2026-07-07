<script lang="ts"></script>
<style src="./home.css"></style>

<template>
    <div class="home-container">
    
        <label>Home Page</label>
        <ul>
            <li><RouterLink to="/login" >Login</RouterLink ></li>
            <li><RouterLink to="/register" >Register</RouterLink ></li>
            <li><RouterLink to="/products" >Products</RouterLink ></li>
            <!--
            <li><RouterLink to="/admin">Admin</RouterLink></li>
            -->
        </ul>

    </div>
</template>