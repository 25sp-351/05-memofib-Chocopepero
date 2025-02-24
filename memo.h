#ifndef MEMO_H
#define MEMO_H

#include "./tiny-bignum-c/bn.h"

typedef void (*bn_func_ptr)(int, struct bn*);

extern bn_func_ptr original_provider;
extern bn_func_ptr fib_provider;

void fib_init();
void cache(int fibNTerm, struct bn* result);

#endif
