<style src="./register.css"></style>
<script setup lang="ts">

import { FontAwesomeIcon } from '@fortawesome/vue-fontawesome';
import * as registerComp from './register';

const form = registerComp.useRegisterForm();
const passChecks = form.passChecks.value;
</script>

<template>
    <div class="login-container">
    
        <div class="email-container">
            <label>Email</label>
            <input type="text" placeholder="example@gmail.com" v-model="form.email.value" @input="form.validateEmail()">
            
            <small class="error" v-if="form.emailValid.value === false">
                Input does not match the required format.
            </small>
            <small class="error" v-if="form.emailExists.value === true">
                Account Already Exists.
            </small>
        </div>

        <div class="password-container">
            <label>Password</label>
            <div class="password-field-container">
                <input :type="form.passType.value" placeholder="Password..." v-model="form.password.value" @input="form.validatePass()">
                <button @click="form.togglePass()">
                    <font-awesome-icon icon="fa-solid fa-eye" v-if="form.passVisible.value"/>
                    <font-awesome-icon icon="fa-solid fa-eye-slash" v-else/>
                </button>
            </div>
            <ul>
                <li :class="passChecks['length']">At Least 8 Characters</li>
                <li :class="passChecks['upper']">At Least 1 Uppercase letter</li>
                <li :class="passChecks['lower']">At Least 1 Lowercase letter</li>
                <li :class="passChecks['number']">At Least 1 Number</li>
                <li :class="passChecks['special']">At Least 1 Special Character (!@#$%^&*)</li>
            </ul>
        </div>

        <div class="name-container">
            <label>Name</label>
            <input type="text" placeholder="Name..." v-model="form.name.value" @input="form.validateName()">
        </div>

        <div class="button-container">
            <button :disabled="!form.registerEnabled()" @click="form.register()"> Confirm </button>
        </div>

    </div>

</template>