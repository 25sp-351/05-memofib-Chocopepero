#include "bignum-helper.h"

#define BASE_10 10
#define BITS 8
#define BUFFER_SIZE 1024

// Most of this was AI-Generated. Turns BN to Decimal as to_string makes it hex.

DTYPE_TMP bignum_divide_by_small(struct bn *n, DTYPE_TMP divisor) {
    DTYPE_TMP remainder = 0;
    int base_bits       = BITS * WORD_SIZE;

    for (int i = BN_ARRAY_SIZE - 1; i >= 0; i--) {
        DTYPE_TMP current = ((DTYPE_TMP)remainder << base_bits) | n->array[i];
        n->array[i]       = current / divisor;
        remainder         = current % divisor;
    }
    return remainder;
}

void bignum_to_decimal_string(const struct bn *orig, char *str, int maxsize) {

    struct bn temp;
    bignum_assign(&temp, (struct bn *)orig);

    char buffer[BUFFER_SIZE];
    int pos = 0;

    while (!bignum_is_zero(&temp)) {
        if (pos >= (int)(sizeof(buffer) - 1))
            break;
        DTYPE_TMP remainder = bignum_divide_by_small(&temp, BASE_10);
        buffer[pos++]       = '0' + (char)remainder;
    }

    if (pos == 0)
        buffer[pos++] = '0';
    buffer[pos] = '\0';

    int len     = pos;
    int i;
    for (i = 0; i < len && i < maxsize - 1; i++)
        str[i] = buffer[len - i - 1];
    str[i] = '\0';
}
