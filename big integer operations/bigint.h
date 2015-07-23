#ifndef BIGINT_H
#define BIGINT_H

#define BASE 1000

typedef struct {
    int *array;
    int n;
} bigint;

bigint convert(int x);
void print_bigint(bigint a);
void free_bigint(bigint a);

bigint add(bigint a, bigint b);
bigint mult(bigint a, bigint b);

bigint fact(int x);
bigint fib(int x);

#endif