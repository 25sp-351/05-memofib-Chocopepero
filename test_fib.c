#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./munit/munit.h"
#include "./tiny-bignum-c/bn.h"
#include "bignum-helper.h"
#include "fib.h"
#include "memo.h"

// Test for fib
static MunitResult test_fib(const MunitParameter params[], void* data) {
    fib_init();
    struct bn result;
    struct bn test_val;

    bignum_init(&result);
    bignum_init(&test_val);

    // Test for 0
    fib(0, &result);
    bignum_from_int(&test_val, 0);
    munit_assert_not_null(&result);
    munit_assert_false(bignum_cmp(&result, &test_val));

    // Test for 1
    fib(1, &result);
    bignum_from_int(&test_val, 1);
    munit_assert_not_null(&result);
    munit_assert_false(bignum_cmp(&result, &test_val));

    // Test for 2
    fib(2, &result);
    bignum_from_int(&test_val, 1);
    munit_assert_not_null(&result);
    munit_assert_false(bignum_cmp(&result, &test_val));

    // Test for 20
    fib(20, &result);
    bignum_from_int(&test_val, 6765);
    munit_assert_not_null(&result);
    munit_assert_false(bignum_cmp(&result, &test_val));

    return MUNIT_OK;
}

// Test for memoization
static MunitResult test_memo(const MunitParameter params[], void* data) {
    fib_init();
    struct bn result;
    struct bn test_val;

    bignum_init(&result);
    bignum_init(&test_val);

    // Test for 0
    cache(0, &result);
    cache(0, &test_val);
    munit_assert_not_null(&result);
    munit_assert_false(bignum_cmp(&result, &test_val));
    munit_assert_memory_equal(sizeof(result), &result, &test_val);

    // Test for 1
    cache(1, &result);
    cache(1, &test_val);
    munit_assert_not_null(&result);
    munit_assert_false(bignum_cmp(&result, &test_val));
    munit_assert_memory_equal(sizeof(result), &result, &test_val);

    // Test for 100
    cache(100, &result);
    cache(100, &test_val);
    munit_assert_not_null(&result);
    munit_assert_false(bignum_cmp(&result, &test_val));
    munit_assert_memory_equal(sizeof(result), &result, &test_val);
    return MUNIT_OK;
}

// Test suite
static MunitTest test_suite_tests[] = {
    {(char*)"/test_fib", test_fib, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {(char*)"/test_memo", test_memo, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

// Test suite
static const MunitSuite test_suite = {(char*)"/test_suite", test_suite_tests,
                                      NULL, 1, MUNIT_SUITE_OPTION_NONE};

// Main function
int main(int argc, char* argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&test_suite, NULL, argc, argv);
}
