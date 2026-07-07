
import { ref } from 'vue'
import { defineStore } from 'pinia'
import type { Product } from '@/models/product';

export const useCartStore = defineStore("Cart", () => {
                              //id    Product + Count
  const products = ref(new Map<number, any>());
  const tax = .07;
  const subtotal = ref(0);

  function addProduct(product: Product) {
    if (products.value.has(product.id)) {
      products.value.get(product.id).count += 1;
    }
    else {
      const item = {count: 1, product: product};
      products.value.set(product.id, item);
    }

    subtotal.value += product.price;
    //storageService.setItem(cartKey, products);
  }

  function subtractProduct(product: Product) {
    if (products.value.has(product.id)) {

      products.value.get(product.id).count -= 1;

      if (products.value.get(product.id).count == 0) {
        products.value.delete(product.id);
        return;
      }

      subtotal.value -= product.price;
      //storageService.setItem(cartKey, products);
    }
  }

  function removeProduct(product: Product) {
    if (products.value.has(product.id)) {
      subtotal.value -= product.price * products.value.get(product.id).count;
      products.value.delete(product.id);

      if (products.value.size != 0) {
        //storageService.setItem(cartKey, products);
      }
      else {
        //storageService.removeItem(cartKey);
      }
    }
  }

  function updateSubtotal() {
    subtotal.value = 0;
    
    for (const [key, value] of products.value.entries()) {
      subtotal.value += value.count * value.product.price;
    };
  }

  function getProducts() {
    if (products.value.size != 0) {
      return products.value;
    }

    const temp = ""//storageService.getItem(cartKey);

    if (temp) {
      products.value = new Map(JSON.parse(temp));
      updateSubtotal();
    }

    return products.value;
  }

  function getTax() {
    return Floor2(tax * subtotal.value);
  }

  function Floor2(value: number): number {
    return Math.floor(value * 100) / 100;
  }

  return {
    subtotal,
    getProducts,
    addProduct,
    subtractProduct,
    removeProduct,
    getTax
  }

})
