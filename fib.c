#include "fib.h"

#include <stdio.h>


typedef void (*bn_func_ptr)(int, struct bn*);

bn_func_ptr original_provider = NULL;
bn_func_ptr fib_provider      = NULL;

struct bn fib_cache[MAX_N + 1];
int computed[MAX_N + 1];

void fib(int n, struct bn* result) {
    if (n == 0) {
        bignum_from_int(result, 0);
        return;
    }
    if (n == 1) {
        bignum_from_int(result, 1);
        return;
    }
    struct bn a, b;
    bignum_init(&a);
    bignum_init(&b);

    (*fib_provider)(n - 1, &a);
    (*fib_provider)(n - 2, &b);

    bignum_add(&a, &b, result);

    bignum_assign(&fib_cache[n], result);
    computed[n] = 1;   
}

void cache(int n, struct bn* result) {
    if (computed[n] == -1) {
        //printf("%d Not found, calculating\n", n);
        (*original_provider)(n, result);
    } else {
        //printf("%d Found, using cache\n", n);
        bignum_assign(result, &fib_cache[n]);
    }
}

void fib_init() {
    fib_provider      = cache;
    original_provider = fib;
    // This wouldn't work unless each index was initialized manually.
    for (int i = 0; i <= MAX_N; i++) {
        bignum_init(&fib_cache[i]);
        computed[i] = -1;
    }
}

void process_input() {
    struct bn result;
    bignum_init(&result);
    char str[1000];
    int n;

    printf("Enter Fibonacci number to calculate (Ctrl+D to end):\n");
    while (scanf("%d", &n) != EOF) {
        bignum_init(&result);
        fib(n, &result);
        bignum_to_string(&result, str, 1000);
        printf("Fib(%d) = %s\n", n, str);
    }
}

int main() {
    fib_init();
    process_input();
    return 0;
}