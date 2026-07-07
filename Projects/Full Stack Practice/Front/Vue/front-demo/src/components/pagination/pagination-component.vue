<style src="./pagination.css"></style>
<script setup lang="ts">
import { computed } from 'vue';

const props = defineProps({
    totalItems: {
        type: Number,
        required: true,
    },
    itemsPerPage: {
        type: Number,
        required: true
    },
    currentPage: {
        type: Number,
        required: true
    },
    maxPages: {
        type: Number,
        required: true
    }
});

const totalItems = computed(() => props.totalItems);
const itemsPerPage =  computed(() => props.itemsPerPage);
const currentPage =  computed(() => props.currentPage);
const maxPages =  computed(() => props.maxPages);
const emit = defineEmits(['pageChanged']);

function pageChanged(page: number): void {
    //currentPage.value = page;
    emit('pageChanged', page);
}

function currentIndex(): number {
    if (totalItems.value < 1)
      return 0;

    return (currentPage.value - 1) * itemsPerPage.value + 1;
}

function lastIndex(): number {
    return Math.min(totalItems.value, currentPage.value * itemsPerPage.value);
}

function toDisplay(): string[] {

    const max = maxPages.value;
    const cur = currentPage.value;

    if (max < 4) {
      const resp = [];
      for (let i = 1; i <= max; ++i) {
        resp.push(i.toString());
      }
      return resp;
    }

    if (cur < 4) {
      return ["1", "2", "3", "...", max.toString()];
    }

    if (cur > max - 3) {
      const a = (max - 2).toString();
      const b = (max - 1).toString();
      return ["1", "...", a, b, max.toString()];
    }

    const a = (cur - 1).toString();
    const b = cur.toString();
    const c = (cur+1).toString();
    
    return ["1", "...", a, b, c, "...", max.toString()];
}

</script>

<template>
  
    <div class="page-container">

        <div class="count-container">
            <label>{{currentIndex()}}-{{lastIndex()}} of {{totalItems}} items</label>
        </div>

        <div class="button-container">
            <button v-if="currentPage != 1" @click="pageChanged(currentPage-1)">{{'<'}}</button>

            <div v-for="(x, index) in toDisplay()" :key="'pagination'+index">
            
                <label v-if="x === '...'">...</label>
                
                <button v-else-if="+x === currentPage" class="active" @click="pageChanged(+x)">{{x}}</button>
                
                <button v-else @click="pageChanged(+x)">{{x}}</button>
            
            </div>

            <button v-if="maxPages > 0 && currentPage != maxPages" @click="pageChanged(currentPage+1)">></button>
            
        </div>

    </div>
</template>