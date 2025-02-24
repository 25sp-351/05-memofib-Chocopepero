#include "fib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bignum-helper.h"
#include "memo.h"

#define BUFFER_SIZE 1024

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

void process_input() {
    struct bn result;
    bignum_init(&result);
    char str[BUFFER_SIZE];
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
        bignum_to_string(&result, str, BUFFER_SIZE);
        char decStr[1024];
        bignum_to_decimal_string(&result, decStr, sizeof(decStr));

        printf("Decimal representation: %s\n", decStr);
        printf("Fib(%d) = %s\n", n, str);
    }
}

