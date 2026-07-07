<style src="./login.css"></style>
<script setup lang="ts">

import { FontAwesomeIcon } from '@fortawesome/vue-fontawesome';
import * as loginComp from './login';

const forgotName = loginComp.forgotName;
const forgotPass = loginComp.forgotPass;
const goToRegister = loginComp.goToRegister;
const { passVisible, passType, togglePass } = loginComp.usePassSettings();
const form = loginComp.useLoginForm();

</script>

<template>
    
    <div class="login-container">
        
        <div class="error-container" v-if="form.errorText.value">
            <label>{{form.errorText.value}}</label>
        </div>

        <div class="username-container">
            <label>Username / Email</label>
            <input type="text" placeholder="Name..." v-model="form.email.value" @input="form.validateEmail()"/>
            <button @click="forgotName()">Forgot Username?</button>
        </div>

        <div class="password-container">
            <label>Password</label>
            <div class="password-field-container">
                <input :type="passType" placeholder="Password..." v-model="form.password.value" @input="form.validatePass()"/>
                <button @click="togglePass()">
                    <font-awesome-icon icon="fa-solid fa-eye" v-if="passVisible"/>
                    <font-awesome-icon icon="fa-solid fa-eye-slash" v-else/>
                </button>
            </div>
            <button @click="forgotPass()">Forgot Password?</button>
        </div>

        <div class="button-container">
            <button @click="form.tryLogin()" :disabled="!form.loginEnabled()"> Signin </button>
            <button @click="goToRegister()"> Create Account</button>
        </div>

    </div>

</template>