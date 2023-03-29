#include "arb_int.h"
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <CUnit/Basic.h>

static int init_suite()
{
    return 0;
}

static int clean_suite()
{
    return 0;
}

static void test_arb_from_string() {
    arb_int_t a;
    int val = arb_from_string(&a, "+12345123451234512345999");
    CU_ASSERT_EQUAL(val == 0, true);

    arb_int_t b;
    val = arb_from_string(&b, "12345123451235");
    CU_ASSERT_EQUAL(val == 0, true);

    arb_int_t c;
    val = arb_from_string(&c, "-12345123451235");
    CU_ASSERT_EQUAL(val == 0, true);

    arb_int_t d;
    val = arb_from_string(&d, "+0");
    CU_ASSERT_EQUAL(val == 0, true);

    arb_int_t e;
    val = arb_from_string(&e, "-0");
    CU_ASSERT_EQUAL(val == 0, true);

    arb_int_t f;
    val = arb_from_string(&f, "000");
    CU_ASSERT_EQUAL(val == ARB_INT_ERROR, true);

    arb_int_t g;
    val = arb_from_string(&g, "0-00");
    CU_ASSERT_EQUAL(val == ARB_INT_ERROR, true);

    arb_free(&a);
    arb_free(&b);
    arb_free(&c);
    arb_free(&d);
}

static void test_arb_duplicate() {
    arb_int_t a;
    arb_from_string(&a, "+12345123451234512345999");
    arb_int_t b;
    int val = arb_duplicate(&b, a);
    CU_ASSERT_EQUAL(val == 0, true);
    arb_free(&a);
    arb_free(&b);
}

static void test_arb_from_int() {
    arb_int_t a;
    int val = arb_from_int(&a, 123123123123123);
    CU_ASSERT_EQUAL(val == 0, true);
    arb_free(&a);
}

static void test_arb_to_string() {
    arb_int_t a;
    arb_from_int(&a, 123123123123123);
    char s[100];
    arb_to_string(a, s, 100);
    CU_ASSERT_EQUAL(strcmp(s, "123123123123123") == 0, true);

    arb_int_t b;
    arb_from_int(&b, -123123123123123);
    arb_to_string(b, s, 100);
    CU_ASSERT_EQUAL(strcmp(s, "-123123123123123") == 0, true);

    arb_free(&a);
    arb_free(&b);
}

static void test_arb_to_int() {
    arb_int_t a;
    int val = arb_from_string(&a, "+12345123451234512345999");
    assert(val == 0);
    long long int val2;
    int val3 = arb_to_int(a, &val2);
    CU_ASSERT_EQUAL(val3 == ARB_INT_ERROR, true);

    arb_int_t b;
    val = arb_from_string(&b, "+12334512345999");
    assert(val == 0);
    val3 = arb_to_int(b, &val2);
    CU_ASSERT_EQUAL(val3 == 0, true);
    CU_ASSERT_EQUAL(val2 == 12334512345999, true);

    arb_free(&a);
    arb_free(&b);
}

static void test_arb_assign() {
    arb_int_t a;
    arb_from_string(&a, "122133425");
    arb_int_t b;
    arb_from_string(&b, "-1234435");
    int val = arb_assign(a, b);
    CU_ASSERT_EQUAL(val == 0, true);

    arb_free(&a);
    arb_free(&b);
}

static void test_arb_add() {
    arb_int_t a, b;
    arb_from_string(&a, "122133425122133425122133425");
    arb_from_string(&b, "122133425122133425122133425");
    int val = arb_add(a, b);
    CU_ASSERT_EQUAL(val == 0, true);

    arb_from_string(&a, "-122133425122133425122133425");
    arb_from_string(&b, "122133425122133425122133425");
    val = arb_add(a, b);
    CU_ASSERT_EQUAL(val == 0, true);

    arb_from_string(&a, "122133425122133425122133425");
    arb_from_string(&b, "-122133425122133425122133425");
    val = arb_add(a, b);
    CU_ASSERT_EQUAL(val == 0, true);

    arb_free(&a);
    arb_free(&b);
}

static void test_arb_subtract() {
    arb_int_t a, b;
    arb_from_string(&a, "122133425122133425122133425");
    arb_from_string(&b, "122133425122133425122133425");
    int val = arb_subtract(a, b);
    CU_ASSERT_EQUAL(val == 0, true);

    arb_from_string(&a, "-122133425122133425122133425");
    arb_from_string(&b, "122133425122133425122133425");
    val = arb_subtract(a, b);
    CU_ASSERT_EQUAL(val == 0, true);

    arb_from_string(&a, "122133425122133425122133425");
    arb_from_string(&b, "-122133425122133425122133425");
    val = arb_subtract(a, b);
    CU_ASSERT_EQUAL(val == 0, true);

    arb_free(&a);
    arb_free(&b);
}

static void test_arb_multiply() {
    arb_int_t a, b;
    arb_from_string(&a, "123");
    arb_from_string(&b, "123");
    int val = arb_multiply(a, b);
    CU_ASSERT_EQUAL(val == 0, true);

    arb_from_string(&a, "122133425122133425122133425");
    arb_from_string(&b, "122133425122133425122133425");
    val = arb_multiply(a, b);
    CU_ASSERT_EQUAL(val == 0, true);

    arb_from_string(&a, "-122133425122133425122133425");
    arb_from_string(&b, "122133425122133425122133425");
    val = arb_multiply(a, b);
    CU_ASSERT_EQUAL(val == 0, true);

    arb_from_string(&a, "122133425122133425122133425");
    arb_from_string(&b, "-122133425122133425122133425");
    val = arb_multiply(a, b);
    CU_ASSERT_EQUAL(val == 0, true);

    arb_free(&a);
    arb_free(&b);
}

static void test_arb_compare() {
    arb_int_t a, b;
    arb_from_string(&a, "122133425122133425122133425");
    arb_from_string(&b, "122133425122133425122133425");
    int val = arb_compare(a, b);
    CU_ASSERT_EQUAL(val == 0, true);

    arb_from_string(&a, "-122133425122133425122133425");
    arb_from_string(&b, "122133425122133425122133425");
    val = arb_compare(a, b);
    CU_ASSERT_EQUAL(val == -1, true);

    arb_from_string(&a, "122133425122133425122133425");
    arb_from_string(&b, "-122133425122133425122133425");
    val = arb_compare(a, b);
    CU_ASSERT_EQUAL(val == 1, true);

    arb_from_string(&a, "-122133425122133425122133425");
    arb_from_string(&b, "-122133425122133425122133425");
    val = arb_compare(a, b);
    CU_ASSERT_EQUAL(val == 0, true);

    arb_free(&a);
    arb_free(&b);
}

static void test_arb_digit_count() {
    arb_int_t a;
    arb_from_string(&a, "1234");
    int val = arb_digit_count(a);
    CU_ASSERT_EQUAL(val == 4, true);

    arb_from_string(&a, "-1221");
    val = arb_digit_count(a);
    CU_ASSERT_EQUAL(val == 5, true);

    arb_from_string(&a, "+0");
    val = arb_digit_count(a);
    CU_ASSERT_EQUAL(val == 1, true);

    arb_from_string(&a, "-0");
    val = arb_digit_count(a);
    CU_ASSERT_EQUAL(val == 1, true);

    arb_free(&a);
}

int main(int argc, char** args) {
    if (argc == 4) {
        arb_int_t a, b;
        if (arb_from_string(&a, args[1]) == ARB_INT_ERROR) {
            printf("Error: \'%s\' is not a valid integer!\n", args[1]);
            return EXIT_FAILURE;
        }

        if (arb_from_string(&b, args[3]) == ARB_INT_ERROR) {
            printf("Error:\'%s\' is not a valid integer!\n", args[3]);
            return EXIT_FAILURE;
        }

        if (*args[2] == '+')
            arb_add(a, b);

        else if (*args[2] == '-')
            arb_subtract(a, b);
        
        else if (*args[2] == '*')
            arb_multiply(a, b);

        else {
            printf("Error: \'%c\' is not a valid operator\n", *args[2]);
            return EXIT_FAILURE;
        }

        char x[arb_digit_count(a)];
        arb_to_string(a, x, strlen(x));
        printf("%s\n", x);
        return EXIT_SUCCESS;
    }

    if (argc == 1) {
        srand(getpid());
        CU_pSuite pSuite = NULL;
        if (CUE_SUCCESS != CU_initialize_registry())
            return CU_get_error();

        pSuite = CU_add_suite("table", init_suite, clean_suite);
        if (NULL == pSuite)
        {
            CU_cleanup_registry();
            return CU_get_error();
        }

        if (
                (NULL == CU_add_test(pSuite, "arb_from_string", test_arb_from_string) || 
                NULL == CU_add_test(pSuite, "arb_duplicate", test_arb_duplicate) || 
                NULL == CU_add_test(pSuite, "arb_from_int", test_arb_from_int) || 
                NULL == CU_add_test(pSuite, "arb_to_string", test_arb_to_string) || 
                NULL == CU_add_test(pSuite, "arb_to_int", test_arb_to_int) || 
                NULL == CU_add_test(pSuite, "arb_assign", test_arb_assign) || 
                NULL == CU_add_test(pSuite, "arb_subtract", test_arb_subtract) || 
                NULL == CU_add_test(pSuite, "arb_multiply", test_arb_multiply) ||
                NULL == CU_add_test(pSuite, "arb_compare", test_arb_compare) ||
                NULL == CU_add_test(pSuite, "arb_digit_count", test_arb_digit_count) ||
                NULL == CU_add_test(pSuite, "arb_add", test_arb_add) 
                )
        )
        {
            CU_cleanup_registry();
            return CU_get_error();
        }

        CU_basic_set_mode(CU_BRM_VERBOSE);
        CU_basic_run_tests();
        CU_cleanup_registry();
        return CU_get_error();
    }
    else {
        perror("Not the right number of arguments");
        return EXIT_FAILURE;
    }
}