import { ref } from 'vue';
import router from '@/router'
import { useUserStore} from '@/stores/login-service';

const emailRegex = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$/;

export function useRegisterForm() {
    const email = ref('');
    const name = ref('');
    const password = ref('');

    const passVisible = ref(false);
    const passType = ref("password");
    const passValid = ref(false);
    const passChecks = ref({
        "length": "error",
        "upper": "error",
        "lower": "error",
        "number": "error",
        "special": "error"
    });

    const emailValid = ref<boolean>();
    const emailExists = ref(false);
    const nameValid = ref<boolean>();

    function registerEnabled() {
        return (emailValid.value == true) &&
            (nameValid.value == true) &&
            (passValid.value == true);
    }

    function validateEmail() {
        emailValid.value =
            email.value.trim() == "" ?
                undefined :
                emailRegex.test(email.value);
    }

    function validatePass() {
        const pass = password.value;
        const lengthCheck = pass.trim().length >= 8;
        const upperCheck = /[A-Z]/.test(pass);
        const lowerCheck = /[a-z]/.test(pass);
        const numberCheck = /[0-9]/.test(pass);
        const specialCheck = /[!@#$%^&*]/.test(pass);

        passChecks.value['length'] = lengthCheck ? "success" : "error";
        passChecks.value['upper'] = upperCheck ? "success" : "error";
        passChecks.value['lower'] = lowerCheck ? "success" : "error";
        passChecks.value['number'] = numberCheck ? "success" : "error";
        passChecks.value['special'] = specialCheck ? "success" : "error";
    
        passValid.value = lengthCheck && upperCheck && lowerCheck && numberCheck && specialCheck;
    }

    function validateName() {
        nameValid.value = name.value.trim().length != 0;
    }

    async function register() {
        emailExists.value = false;

        const userStore = useUserStore();
        const data = await userStore.Register(name.value, email.value, password.value);

        if (data.error) {
            if (data.error === "Account already exists") {
                emailExists.value = true;
            }
        }
        else {
            const user = data.user;
            router.push('/home');
        }
        router.push('/home');
    }

    function togglePass() {
        passVisible.value = !passVisible.value;
        passType.value = passVisible.value ? "text" : "password";
    }

    return {
        email,
        emailValid,
        emailExists,
        name,
        nameValid,
        password,
        passValid,
        passVisible,
        passType,
        passChecks,
        validateEmail,
        validateName,
        validatePass,
        togglePass,
        registerEnabled,
        register
    };

}