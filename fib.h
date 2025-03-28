#ifndef FIB_H
#define FIB_H
#include "./tiny-bignum-c/bn.h"

#define MAX_N 10000

void fib(int n, struct bn* result);
void cache(int n, struct bn* result);
#endif
