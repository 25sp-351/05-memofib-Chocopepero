#include "./tiny-bignum-c/bn.h"

#define MAX_N 1000  // Max Fibonacci number to compute

void fib(int n, struct bn* result);
void cache(int n, struct bn* result);
void fib_init();
