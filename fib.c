#include "fib.h"

#include <stdio.h>

typedef void (*bn_func_ptr)(int, struct bn*);

bn_func_ptr original_provider = NULL;
bn_func_ptr fib_provider      = NULL;

struct bn fib_cache[MAX_N + 1];
int computed[MAX_N + 1];

void fib(int term, struct bn* result) {
    if (term == 0) {
        bignum_from_int(result, 0);
        return;
    }
    if (term == 1) {
        bignum_from_int(result, 1);
        return;
    }
    struct bn nsub1;
    struct bn nsub2;
    bignum_init(&nsub1);
    bignum_init(&nsub2);

    (*fib_provider)(term - 1, &nsub1);
    (*fib_provider)(term - 2, &nsub2);

    bignum_add(&nsub1, &nsub2, result);
}

void cache(int fibNTerm, struct bn* result) {
    if (computed[fibNTerm] == -1) {
        // printf("%d Not found, calculating\n", n);
        (*original_provider)(fibNTerm, result);
        bignum_assign(&fib_cache[fibNTerm], result);
        computed[fibNTerm] = 1;
    } else {
        // printf("%d Found, using cache\n", n);
        bignum_assign(result, &fib_cache[fibNTerm]);
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

    printf("Enter Fibonacci number to calculate:\n");
    while (scanf("%d", &n) != EOF) {
        if (n < 0 || n > MAX_N) {
            printf("Invalid input. Please enter a number between 0 and %d\n",
                   MAX_N);
            continue;
        }
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
