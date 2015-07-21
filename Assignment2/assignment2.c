#include<stdio.h>
#include<stdlib.h>
#define BASE 1000

typedef struct {
    int *array;
    int n;
} bigint;
bigint convert(int x){
    bigint b;
    if(x == 0){
        b.array = (int*)malloc(sizeof(int));
        b.n = 1;
        b.array[0] =0;
    }else{
        int  n =0, i = 0, temp = x;
        while(temp != 0) {
            temp /= BASE;
            n++;
        }
        b.array = (int*) malloc(sizeof(int)*n);
        b.n = n;
        while(x != 0){
            b.array[i] = x% BASE;
            x /=BASE;
            i++;
        }
    }
    return b;
}
void print_bigint(bigint a){
    for(int i =0; i < a.n; i++){
        printf("%d ", a.array[a.n - i -1]);
    }
    printf("\n");
}
void free_bigint(bigint a){
    free(a.array);
    a.n = 0;
}
bigint add(bigint a, bigint b){
    int m =  (a.n > b.n ? a.n : b.n) + 1;
    bigint z;
    z.array = (int*) malloc(sizeof(int)* m);
    z.n = m;
    int c = 0, i =0, sum = 0 ;
    for(i = 0 ; i < m - 1; ++i){
        sum = c + (i < a.n ? a.array[i] : 0) + (i < b.n ? b.array[i] : 0);
        z.array[i] = sum % BASE;
        c = sum / BASE;
    }
    if(c != 0 )	z.array[i] = c;
    else{
        z.n--;
    }
    return z;
}
bigint mult(bigint a, bigint b){
    
    if (a.n > b.n) return mult(b,a);
    else{
        bigint z = convert(0);
        bigint p;
        for(int i = 0; i < a.n; i++){
            
            p.n = b.n + i + 1;
            p.array = (int*) malloc(sizeof(int) * (b.n + i +1));
            int c = 0, j = 0;
            for(j = 0; j <i ; j++)
                p.array[j] = 0;
            for( j = i; j < b.n + i; j++){
                p.array[j] = (c + a.array[i] * b.array[j-i]) % BASE;
                c = (c + a.array[i] * b.array[j-i]) / BASE;
            }
            if(c != 0) p.array[j] = c;
            else p.n = p.n -1;
            z = add(z,p);
            free_bigint(p);
        }
        return z;
    }
    
}

/**/
bigint fact(int x){
    if(x == 0) return convert(1);
    int t  = sizeof(int);
    int limit = 8;
    if( t == 4) limit = 12;
    int prod = 1;
    for(int i = 1; i <= x && i <= limit ; i++){
        prod *= i;
    }
    bigint z = convert(prod);
    for(int i = limit +1; i <= x; i++){
        z = mult(z,convert(i));
    }
    return z;
}

bigint fib(int x){
    
    int t  = sizeof(int);
    int limit = 22;
    if( t == 4) limit = 26;
    int a = 0, b = 1;
    for( int i =0; i < x && i < limit; i++){
        int tmp = a;
        a = b;
        b = tmp + b;
        
    }
    bigint c = convert(a);
    bigint z = convert(b);
    for( int i =limit; i < x; i++){
        bigint tmp = c;
        c = z;
        z = add(c,z);
        
    }
    return z;
}
int fibInt(int x){
    
    int a = 0, b = 1;
    for( int i =0; i < x; i++){
        int tmp = a;
        a = b;
        b = tmp + b;
        
    }
    return b;
}
int main(){
    bigint b = convert(479001600);
    bigint a = convert(2);
    print_bigint(a);
    
    print_bigint(b);
    bigint  z = mult(a,b);
    free_bigint(a);
    free_bigint(b);
    print_bigint(z);
    free_bigint(z);
    
    bigint t =  fact(25);
    
    print_bigint(t);
    free_bigint(t);
    
    bigint t1 = fib(3);
    print_bigint(t1);
    free_bigint(t1);
    printf("%d", fibInt(3));
}