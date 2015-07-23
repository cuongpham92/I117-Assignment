#include "bigint.h"

#include<stdio.h>
#include<stdlib.h>

bigint convert(int x) {
    bigint a;
    if(x == 0) {    //if x == 0, return an array with only one element 0
        a.array = malloc(sizeof(int));
        a.n = 1;
        a.array[0] = 0;
    } else {
        int n = 0, temp = x;
        //count the length of x with the variable n
        while (temp != 0) {
            temp = temp / BASE;
            n++;
        }
        //convert x into a.array
        int i = 0;
        a.array = malloc(sizeof(int) * n);
        a.n = n;
        while (x != 0) {
            a.array[i] = x % BASE;
            x = x / BASE;
            i++;
        }
    }
    
    return a;
}

void print_bigint(bigint a) {
    for (int i = a.n - 1; i >= 0; --i) {
        if(i != a.n-1 && a.array[i] < 10) {
            printf("00%d", a.array[i]);
        } else if(i != a.n-1 && a.array[i] < 100 && a.array[i] > 9){
            printf("0%d", a.array[i]);
        } else {
            printf("%d", a.array[i]);
        }
        
    }
    printf("\n");
}

void free_bigint(bigint a) {
    free(a.array);
    a.n = 0;
}

bigint add(bigint a, bigint b) {
    bigint c;  //the result of a+b
    int carry = 0, sum = 0, i = 0;
    
    //define the length for c
    int n = (a.n > b.n ? a.n : b.n) + 1;
    
    c.array = malloc(sizeof(int) * n);
    c.n = n;
    while (i < n - 1) {
        sum = carry + (i < a.n ? a.array[i] : 0) + (i < b.n ? b.array[i] : 0);
        c.array[i] = sum % BASE;
        carry = sum / BASE;
        i++;
    }
    if (carry != 0) {
        c.array[i] = carry;
    } else {
        c.n--;
    }
    
    return c;
}

bigint mult(bigint a, bigint b) {
    //make sure that the multiplier is always the longer number
    if(a.n > b.n) {
        return mult(b,a);
    }
    //declare the result c and product p, initially c = 0
    bigint c = convert(0);
    bigint product;
    for (int i = 0; i < a.n; i++) {
        //define the length of product
        product.array = malloc(sizeof(int) * (b.n + i + 1));
        product.n = b.n + i + 1;
        
        int carry = 0, j = 0;
        while (j < b.n + i) {
            if (j < i) {
                product.array[j] = 0;
            } else {
                product.array[j] = (carry + a.array[i] * b.array[j-i]) % BASE;
                carry = (carry + a.array[i] * b.array[j-i]) / BASE;
            }
            j++;
        }
        if (carry != 0) {
            product.array[j] = carry;
        } else {
            product.n--;
        }
        bigint temp = c;
        c = add(c, product);
        free_bigint(temp);
        free_bigint(product);
    }
    return c;
}

bigint fib(int x) {
  if(x == 0) {   //return 0 if x = 0
    return convert(0);
  }
  
  bigint a = convert(0);
  bigint b = convert(1);
  for(int i = 1; i < x; i++){
    bigint temp = add(a,b);
    free_bigint(a);
    a = b;
    b = temp;
  }
  free_bigint(a);
  return b;
}

bigint fact(int x) {
    bigint t, temp;
    if (x == 0) {  //return 1 if x = 0
        return convert(1);
    }
    bigint z = convert(1);
    for(int i = 1; i <= x; i++){
        t = convert(i);
        temp = z;
        z = mult(z,t);
        free_bigint(t);
        free_bigint(temp);
    }
    return z;
}




