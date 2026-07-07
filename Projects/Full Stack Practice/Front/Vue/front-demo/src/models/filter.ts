/* eslint-disable @typescript-eslint/no-explicit-any */
import { type Product } from "./product";

export enum FilterValueType {
    Default,
    RangeInput,
    Range
}

export interface FilterValue {
    type: FilterValueType;
    label: string
    isChecked: boolean;
    value?: string;
    min?: number;
    max?: number;
}

export abstract class Filter {
    name: string = "";
    values: FilterValue[] = [];
    numChecked: number = 0;

    constructor(name: string) {
        this.name = name;
    }

    applyFilter(items: any): any { }
    
    update(filter: FilterValue) {
        this.numChecked += filter.isChecked ? 1 : -1;
    }
}

export class StockFilter extends Filter {

    excludeEmpty: boolean = false;

    constructor(name: string) {
        super(name);
        this.values.push({
            type: FilterValueType.Default,
            label: "Exclude out of Stock",
            isChecked: false,
        });
    }

    override applyFilter(items: any): any {

        if (this.excludeEmpty) {
            console.log("Filter Out of Stock");
            return items.filter((x: Product) => x.inStock == true);
        }

        return items;
    }

    override update(filter: FilterValue) {
        super.update(filter);
        this.excludeEmpty = filter.isChecked;
    }

}

export class CategoryFilter extends Filter {

    constructor(name: string, categories: string[]) {
        super(name);
        categories.forEach(x => { 
            this.values.push({
                type: FilterValueType.Default,
                label: x,
                value: x,
                isChecked: false,
            });
        })
    }

    override applyFilter(items: any): any {

        if (this.numChecked > 0) {
            let resp: Product[] = [];
            this.values.forEach(x => {
                if (x.isChecked) {
                    const match = items.filter((y: Product) => y.category === x.value);
                    resp = [...resp, ...match];
                }
            })

            return resp;
        }

        return items;
    }

}

export class PriceFilter extends Filter {

    constructor(name: string, values: FilterValue[]) {
        super(name);
        this.values.push({
            type: FilterValueType.RangeInput,
            label: "",
            isChecked: false,
        });
        this.values = [...this.values, ...values];
    }

    override applyFilter(items: any): any {

        if (this.numChecked > 0) {
            let resp: any[] = [];
            this.values.forEach(x => {
                if (x.isChecked) {
                    const match = items.filter((y: Product) => {
                        const min: number = x.min == undefined ? 0 : x.min;
                        const max: number = x.max == undefined ? Number.MAX_SAFE_INTEGER : x.max;
                        return y.price >= min && y.price <= max;
                    });
                    
                    resp = [...resp, ...match];
                }
            })

            return resp;
        }

        return items;
    }

    override update(filter: FilterValue) {
        if (filter.type == FilterValueType.RangeInput) {
            if (filter.min != undefined || filter.max != undefined) {
                this.values.forEach(x => x.isChecked = false);
                filter.isChecked = true;
                this.numChecked = 1;
            }
            else {
                filter.isChecked = false;
            }

        }
        else {
            super.update(filter);
            if (this.values[0]?.isChecked) {
                this.numChecked -= 1;
                this.values[0].isChecked = false;
            }
        }
    }

}