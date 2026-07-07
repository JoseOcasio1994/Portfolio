/* eslint-disable @typescript-eslint/no-explicit-any */
import { ref, computed } from 'vue'
import { defineStore } from 'pinia'
import axios from 'axios';
import { type Product } from '@/models/product';

const api = import.meta.env.VITE_API_URL;
const productsEP = api + import.meta.env.VITE_PRODUCT_EP;
const categoryEP = api + import.meta.env.VITE_CATEGORY_EP;
const images: Record<string, string> = {
		"Beverages": "soda.png",
		"Condiments": "condiment.png",
		"Confections": "cake.png",
		"Dairy Products": "dairy.png",
		"Grains/Cereals": "cereal.png",
		"Meat/Poultry": "meat.png",
		"Produce": "produce.png",
		"Seafood": "fish.png",
};
  
export const useProductStore = defineStore('products', () => {
  const products = ref<Product[]>();
  const categories = ref<string[]>();
  const totalItems = ref(0);
  const totalPages = ref(0);

  async function GetCategories() {

    if (categories.value && categories.value.length > 0) {
      return categories.value;
    }

    const resp = await axios.get(categoryEP);
    return processCategories(resp.data);
	}

  async function GetProducts(filter: string) {
		const resp = await axios.get(productsEP + filter);
    return processProducts(resp.data);
	}

	function processCategories(data: any[]) {
		const temp: string[] = [];
		for ( const item of data) {
			temp.push(item.categoryName);
    }
    categories.value = temp;
		return categories.value;
	}

	function processProducts(data: any){
		const temp: Product[] = [];
		
    for (const item of data.content) {
      temp.push(
				{
					id: item.id,
					name: item.productName,
					category: item.category,
					price: item.price,
					rating: getRandomIntInclusive(1, 5),
					inStock: item.id % 7 != 3 ? true : false,
					image: images[item.category] ?? ""
				}
			);
		}
		
    products.value = temp,
    totalItems.value = data.totalElements,
    totalPages.value = data.totalPages

		return {
			products: products.value,
			totalItems: totalItems.value,
			totalPages: totalPages.value
		};
	}

	function getRandomIntInclusive(min: number, max: number): number {
		min = Math.ceil(min);
		max = Math.floor(max);
		return Math.floor(Math.random() * (max - min + 1)) + min;
  }

  return {
    products,
    categories,
    totalItems,
    totalPages,
    GetCategories,
    GetProducts
  }

})
