#include "bigint.h"

#include<stdio.h>
int main() {
    int x = 123456789;
    int y = 234;
    
    bigint a = convert(x);
    bigint b= convert(y);
    
    //addition
    printf("addition \n");
    bigint c = add(a,b);
    print_bigint(c);
    free_bigint(c);
    
    //multiplication
    printf("multiplication \n");
    bigint d = mult(a,b);
    print_bigint(d);
    free_bigint(d);
    
    //fibonacci
    printf("fibonacci \n");
    bigint e = fib(y);
    print_bigint(e);
    free_bigint(e);
    
    //factorial
    printf("factorial \n");
    bigint f = fact(1000);
    print_bigint(f);
    free_bigint(f);
    
    free_bigint(a);
    free_bigint(b);
}
