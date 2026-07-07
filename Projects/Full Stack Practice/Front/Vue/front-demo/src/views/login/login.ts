import { ref } from 'vue';
import router from '@/router'
import { useUserStore } from '@/stores/login-service';

export function useLoginForm() {
    const email = ref('');
    const password = ref('');
    
    const emailValid = ref(false);
    const passValid = ref(false);

    const errorText = ref<string>();

    async function tryLogin() {
        const userStore = useUserStore();
        const resp = await userStore.TryLogin(email.value, password.value);

        if (resp.error) {
            errorText.value = resp.error;
        }
        else {
            const user = resp.user;
            router.push('/home');
        }
    }

    function validateEmail() {
        emailValid.value = email.value.trim().length != 0;
    }

    function validatePass() {
        passValid.value = password.value.trim().length != 0;
    }

    function loginEnabled(): boolean {
        return emailValid.value && passValid.value;
    }

    return {
        email,
        emailValid,
        password,
        passValid,
        errorText,
        validateEmail,
        validatePass,
        loginEnabled,
        tryLogin
    };
}

export function usePassSettings() {
    const passVisible = ref(false);
    const passType = ref("password");

    function togglePass() {
        passVisible.value = !passVisible.value;
        passType.value = passVisible.value ? "text" : "password";
    }

    return {
        passVisible,
        passType,
        togglePass
    }
}

export function forgotName() {
    console.log("Forgot Name");
}

export function forgotPass() {
    console.log("Forgot Password");
}

export function goToRegister() {
    router.push('/register');
}