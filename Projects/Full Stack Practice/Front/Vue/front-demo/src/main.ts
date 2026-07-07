import { createApp } from 'vue'
import { piniaInstance } from './global';
import { library } from '@fortawesome/fontawesome-svg-core';
import { FontAwesomeIcon } from '@fortawesome/vue-fontawesome';
import { faBars, faXmark, faUser, faMagnifyingGlass, faCartShopping, faEye, faEyeSlash, faTrashCan } from '@fortawesome/free-solid-svg-icons';

import 'vuetify/styles';
import { vuetify } from './global';

import App from './App.vue'
import router from './router'
import './main.css'

library.add(faBars, faXmark, faUser, faMagnifyingGlass, faCartShopping, faEye, faEyeSlash, faTrashCan);

const app = createApp(App)

app.use(router)
app.use(piniaInstance)
app.use(vuetify)

app.component('font-awesome-icon', FontAwesomeIcon);
app.mount('#app')
