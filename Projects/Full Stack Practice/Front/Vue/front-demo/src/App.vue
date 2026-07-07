<script setup lang="ts">
import BannerComponent from './components/banner/banner-component.vue';

</script>

<template>
  <BannerComponent/>
  <div id="content">
    <RouterView />
  </div>
</template>

<style scoped>
  #content {
    display: flow-root;
    height: calc(100vh - 80px);
    margin-top: 80px;
  }
</style>
