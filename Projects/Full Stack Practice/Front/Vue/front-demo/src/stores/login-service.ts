/* eslint-disable @typescript-eslint/no-explicit-any */
import type User from '../models/user';
import axios from 'axios';
import { ref } from 'vue'
import { defineStore } from 'pinia'

const api = import.meta.env.VITE_API_URL;
const registerEP = api + import.meta.env.VITE_REGISTER_EP;
const loginEP = api + import.meta.env.VITE_LOGIN_EP;

export const useUserStore = defineStore("User", () => {

  const user = ref<User>()
  
  async function TryLogin(email: string, password: string) {
  
    const data = { "username": email, "password": password };
    
    try {
      const resp = await axios.post(loginEP, data);
      processData(resp.data.user);
      return resp.data;
    }
    catch (error: any) {
      console.log('Error creating user:', error.response);

      let msg = "Server Error";
      if (error.response.status == 404) { msg = "Account Not Found" }
      else if (error.response.status == 400) { msg = "Incorrect Password" }
      
      return { "error": msg };
    }
  
  }

  async function Register(name: string, email: string, password: string) {
    
    const data = {
      "name": name,
      "email": email,
      "password": password,
      "role": "ROLE_USER",
    };
    
    try {
      const resp = await axios.post(registerEP, data);
      processData(resp.data.user);
      return resp.data;
    }
    catch (error: any) {
      console.log('Error creating user:', error.response);
      return { "error": error.response.data };
    }
  }

  function Logout() {
    user.value = undefined;
    //storageService.removeItemLocal(UserKey);
  }

  function GetUser() {

    if (user.value) {
      return user.value;
    }

    /*const data = storageService.getItemLocal(UserKey);
    if (data) {
      user.value = JSON.parse(data);
    }
    */
    return user.value;
  }

  function processData(data: User | undefined) {
    if (data) {
      user.value = data;
      //storageService.setItemLocal(UserKey, user);
    }

    return user.value;
  }

  return {
    TryLogin,
    Register,
    Logout,
    GetUser
  }

})
