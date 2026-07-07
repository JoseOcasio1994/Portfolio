<!-- eslint-disable @typescript-eslint/no-explicit-any -->
<style src="./product.css"></style>
<script setup lang="ts">
import { ref, onMounted, computed } from 'vue';
import filterComponent from '@/components/filter/filter-component.vue';
import { Filter, FilterValueType, StockFilter, PriceFilter, CategoryFilter } from '../../models/filter';
import productCard from '@/components/product-card/product-card.vue';
import { type Product } from '@/models/product';
import paginationComponent from '@/components/pagination/pagination-component.vue';
import { useProductStore } from '@/stores/product-service';

const productStore = useProductStore();

const search = ref("");
const isLoading = ref(false);
const categories = ref<string[]>([]);
const priceRanges = [
    {
        type: FilterValueType.Range,
        label: "Free",
        min: 0,
        max: 0,
        isChecked: false
    },
    {
        type: FilterValueType.Range,
        label: "Under $25",
        min: 0,
        max: 24.99,
        isChecked: false
    },
    {
        type: FilterValueType.Range,
        label: "$25 - $49.99",
        min: 25,
        max: 49.99,
        isChecked: false
    },
    {
        type: FilterValueType.Range,
        label: "$50 - $99.99",
        min: 50,
        max: 99.99,
        isChecked: false
    },
    {
        type: FilterValueType.Range,
        label: "$100 - $249.99",
        min: 100,
        max: 249.99,
        isChecked: false
    },
    {
        type: FilterValueType.Range,
        label: "$250 - $500",
        min: 250,
        max: 500,
        isChecked: false
    }
]
const filters = computed({
    get: () => {
        const tempFilters = [];
        tempFilters.push(new StockFilter("Availability"));
        tempFilters.push(new CategoryFilter("Category", categories.value)),
        tempFilters.push(new PriceFilter("Price", priceRanges));

        return tempFilters;
    },
    set: (data) => {
        return data;
    }
});

const sort = [
    { label: "Price Low To High", value: "price-low-to-high"},
    { label: "Price High To Low", value: "price-high-to-low"},
    { label: "A - Z", value: "alpha-a-to-z" },
    { label: "Z - A", value: "alpha-z-to-a" },
];
const selectedSort = ref(sort[0]?.value);

const productData = ref({
    products: [] as Product[],
    totalItems: 0,
    totalPages: 0
});

const products = computed(() => productData.value.products);
const currentPage = ref(1);
const itemsPerPage = ref(10);
const totalItems = computed(() => productData.value.totalItems);
const totalPages = computed(() => productData.value.totalPages);

onMounted(() => { 
    productStore.GetCategories().then(
        (data) => { categories.value = data; }
    );

    getProducts();
})

function onFilterChange(event: Filter[]) {
    filters.value = event;
    currentPage.value = 1;
    //storageService.setItem(filterKey, filters);
    getProducts();
}

function onSortChange(event: Event) {
    selectedSort.value = (event.target as HTMLInputElement).value;
    currentPage.value = 1;
    //getProducts();
}

function onPageChanged(page: number) {
    currentPage.value = page;
    getProducts();
}

function getProducts() {

    buildSearchParameter();

    productStore.GetProducts(search.value).then(
        (data) => {
            isLoading.value = false;
            productData.value = {
                products: data.products,
                totalItems: data.totalItems,
                totalPages: data.totalPages
            }
            //this.storageService.setItem(this.productKey, productData);
        }
    );
}

function buildSearchParameter() {
    search.value = "?";
    search.value += "page=" + (currentPage.value - 1);
    search.value += "&size=" + itemsPerPage.value;

    switch (selectedSort.value) {
      case "price-high-to-low":
        search.value += "&sort=price%2Cdesc";
        break;
      case "alpha-a-to-z":
        search.value += "&sort=productName%2Casc";
        break;
      case "alpha-z-to-a":
        search.value += "&sort=productName%2Cdesc";
        break;
      default:
        search.value += "&sort=price%2Casc";
        break;
    }

    for (const filter of filters.value) {

      if (filter instanceof StockFilter) {
        if (filter.excludeEmpty) {
          search.value += "&excludeOutOfStock=true";
        }
      }

      else if (filter instanceof PriceFilter) {
        for (const value of filter.values) {
          if (value.isChecked) {
            const min = value.min == null ? 0 : value.min;
            const max = value.max == null ? 1000 : value.max;
            search.value += "&price=%24" + min;
            search.value += "%20-%20";
            search.value += "%24" + max;
          }
        }
      }
        
      else if (filter instanceof CategoryFilter) {
        for (const value of filter.values) {
          if (value.isChecked) {
            console.log(value.value);
            const cat = value.value?.replace(/ /g, "%20")
            search.value += "&category=" + cat;
          }
        }
      }

    }

    /*const pageData = {
      "page": currentPage,
      "size": itemsPerPage,
      "sort": selectedSort.value
    };
    storageService.setItem(paginationKey, pageData);
    */
}

</script>

<template>
    
    <div class="content">

        <filterComponent
            @filter-changed="onFilterChange"
            :filters="filters ?? []"
            :is-loading="isLoading"
        />
        
        <div class="content-container">

            <div class="sort-container" v-if="!isLoading">
                <label>Sort:</label>
                <select id="sort-select" v-model="selectedSort" @change="onSortChange">
                    <option v-for="s in sort" :value="s.value" :key="s.value">
                        {{ s.label }}
                    </option>
                </select>
            </div>
            
            <div class="product-container" v-if="!isLoading">
                <productCard v-for="p of products" :key="p.name" class="grid-item" :product="p" />
            </div>

            <div class="page-container" v-if="!isLoading">
                <paginationComponent
                    :currentPage="currentPage"
                    :itemsPerPage="itemsPerPage" 
                    :totalItems="totalItems"
                    :maxPages="totalPages"
                    @page-changed="onPageChanged($event)"
                />
            </div>
        
            <!-- SKELETON 
            <div class="product-container" v-if="isLoading">
                <ng-container *skeleton="isLoading; 
                                repeat: 6; 
                                className: 'mb-2'; 
                                height: '200px';
                                wclassth: '250px';">
                </ng-container>
            </div>
            -->

        </div>

    </div>
</template>