
export default class User {
    email: string = "";
    name: string = "";
    role: string = "";
    id: number = 0;

    constructor(id: number, name: string, email: string, role: string) {
        this.id = id;
        this.name = name;
        this.email = email;
        this.role = role;
    }
}