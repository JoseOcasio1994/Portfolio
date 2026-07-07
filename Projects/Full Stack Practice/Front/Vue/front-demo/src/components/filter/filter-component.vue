<style src="./filter.css"></style>
<script setup lang="ts">
import { computed } from 'vue';
import { type PropType } from 'vue';
import {
  Filter, type FilterValue, FilterValueType
} from '../../models/filter';

const props = defineProps({
    filters: {
        type: Object as PropType<Array<Filter>>,
        required: true
    },
    isLoading: {
        type: Boolean,
        required: true
    }
});

const isLoading = computed(() => props.isLoading);
const filters = computed(() => props.filters);
const emit = defineEmits(['filterChanged']);

function onFilterChange(filter: Filter, value: FilterValue) {
    filter.update(value);
    emit('filterChanged', filters.value);
}

</script>

<template>

    <div class="filter-container" v-if="!isLoading">
        <div class="filter-item" v-for="f in filters" :key="f.name">
            <label class="filter-header">{{f.name}}</label>

            <ul class="filter-list" v-for="v in f.values" :key="v.label">
                <label v-if="v.type === FilterValueType.Default || v.type === FilterValueType.Range">
                    <input type="checkbox" 
                        v-model="v.isChecked"
                        @change="onFilterChange(f, v)">
                    {{ v.label }}
                </label>

                <div class="range-container" v-else>
                    <input type="number" v-model="v.min">
                    <label>to</label>
                    <input type="number" v-model="v.max">
                    <button @click="onFilterChange(f, v)">SET</button>
                </div>
            </ul>

        </div>
    </div>

    <!-- SKELETON 
    <div class="filter-container" v-else>
        <div class="filter-item">
            <ng-container *skeleton="isLoading; 
                            repeat: 1; 
                            className: 'mb-2'; 
                            height: '200px';
                            wclassth: '200px';">
            </ng-container>
        </div>
        <div class="filter-item">
            <ng-container *skeleton="isLoading; 
                            repeat: 1; 
                            className: 'mb-2'; 
                            height: '200px';
                            wclassth: '200px';">
            </ng-container>
        </div>
        <div class="filter-item">
            <ng-container *skeleton="isLoading; 
                            repeat: 1; 
                            className: 'mb-2'; 
                            height: '200px';
                            wclassth: '200px';">
            </ng-container>
        </div>
    </div>
    -->

</template>