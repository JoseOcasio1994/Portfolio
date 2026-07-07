import { ref } from 'vue';
import { type Router } from 'vue-router';

const menuList = ref([
    'Category 1',
    'Category 2',
    'Category 3',
    'Category 4',
    'Category 5',
])

export function getMenuList() {
    return menuList.value;
}

export function useToggleMenu() {
    const menuOpened = ref(false);

    function toggleMenu() {
        menuOpened.value = !menuOpened.value
    }

    return {
        menuOpened,
        toggleMenu
    };
}

export function useSearch() {
    const searchTerm = ref('')

    function search() {
        console.log("Searching For", searchTerm.value)
    }

    return {
        searchTerm,
        search
    };
}

export function goToLogin(router: Router) {
    router.push('/login');
}

export function goToCart(router: Router) {
    router.push('/cart');
}