package com.example.demo.models.other;

import java.util.List;
import lombok.Data;
import lombok.NoArgsConstructor;

@NoArgsConstructor
@Data
public class ProductFilter {

    public class PriceRange {
        public float min, max;

        public PriceRange(int min, int max) {
            this.min = Math.min(min, max);
            this.max = Math.max(min, max);
        }

        public PriceRange(String range) {
            String[] newRange = range.replaceAll("\\$", "").split("-");
            float a = Float.parseFloat(newRange[0]);
            float b = Float.parseFloat(newRange[1]);
            this.min = Math.min(a, b);
            this.max = Math.max(a, b);
        }
    }

    private boolean excludeOutOfStock = false;
    private List<String> category;
    private List<String> price;
    
    public PriceRange toRange(String s) {
        return new PriceRange(s);
    }

}

