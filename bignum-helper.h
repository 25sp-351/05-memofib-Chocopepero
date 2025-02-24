#ifndef BIGNUM_HELPER_H
#define BIGNUM_HELPER_H

#include "./tiny-bignum-c/bn.h"

DTYPE_TMP bignum_divide_by_small(struct bn *n, DTYPE_TMP divisor);
void bignum_to_decimal_string(const struct bn *orig, char *str, int maxsize);

#endif
