#include "memo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fib.h"

bn_func_ptr original_provider = NULL;
bn_func_ptr fib_provider      = NULL;

struct bn fib_cache[MAX_N + 1];
int computed[MAX_N + 1];

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
