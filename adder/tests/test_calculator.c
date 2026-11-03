#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calculator.h"

#define EPSILON 0.000001

static int total_tests = 0;
static int passed_tests = 0;

static void assert_double_equal(const char *test_name, double actual, double expected) {
    total_tests++;
    if (fabs(actual - expected) < EPSILON) {
        printf("  [PASS] %s: expected %g, got %g\n", test_name, expected, actual);
        passed_tests++;
    } else {
        printf("  [FAIL] %s: expected %g, got %g\n", test_name, expected, actual);
    }
}

static void assert_status(const char *test_name, CalcStatus actual, CalcStatus expected) {
    total_tests++;
    if (actual == expected) {
        printf("  [PASS] %s: status match (%d)\n", test_name, (int)actual);
        passed_tests++;
    } else {
        printf("  [FAIL] %s: expected status %d, got %d\n", test_name, (int)expected, (int)actual);
    }
}

static void test_addition(void) {
    printf("\n--- Testing Addition ---\n");
    double res = 0.0;
    assert_status("add(2, 3) status", calc_add(2.0, 3.0, &res), CALC_SUCCESS);
    assert_double_equal("add(2, 3) value", res, 5.0);

    assert_status("add(-5, 10) status", calc_add(-5.0, 10.0, &res), CALC_SUCCESS);
    assert_double_equal("add(-5, 10) value", res, 5.0);

    assert_status("add(-2.5, -3.5) status", calc_add(-2.5, -3.5, &res), CALC_SUCCESS);
    assert_double_equal("add(-2.5, -3.5) value", res, -6.0);
}

static void test_subtraction(void) {
    printf("\n--- Testing Subtraction ---\n");
    double res = 0.0;
    assert_status("subtract(10, 4) status", calc_subtract(10.0, 4.0, &res), CALC_SUCCESS);
    assert_double_equal("subtract(10, 4) value", res, 6.0);

    assert_status("subtract(3, 7) status", calc_subtract(3.0, 7.0, &res), CALC_SUCCESS);
    assert_double_equal("subtract(3, 7) value", res, -4.0);
}

static void test_multiplication(void) {
    printf("\n--- Testing Multiplication ---\n");
    double res = 0.0;
    assert_status("multiply(6, 7) status", calc_multiply(6.0, 7.0, &res), CALC_SUCCESS);
    assert_double_equal("multiply(6, 7) value", res, 42.0);

    assert_status("multiply(-4, 2.5) status", calc_multiply(-4.0, 2.5, &res), CALC_SUCCESS);
    assert_double_equal("multiply(-4, 2.5) value", res, -10.0);

    assert_status("multiply(99, 0) status", calc_multiply(99.0, 0.0, &res), CALC_SUCCESS);
    assert_double_equal("multiply(99, 0) value", res, 0.0);
}

static void test_division(void) {
    printf("\n--- Testing Division ---\n");
    double res = 0.0;
    assert_status("divide(20, 4) status", calc_divide(20.0, 4.0, &res), CALC_SUCCESS);
    assert_double_equal("divide(20, 4) value", res, 5.0);

    assert_status("divide(5, 2) status", calc_divide(5.0, 2.0, &res), CALC_SUCCESS);
    assert_double_equal("divide(5, 2) value", res, 2.5);

    assert_status("divide by zero check", calc_divide(10.0, 0.0, &res), CALC_ERR_DIV_BY_ZERO);
}

static void test_modulo(void) {
    printf("\n--- Testing Modulo ---\n");
    double res = 0.0;
    assert_status("modulo(10, 3) status", calc_modulo(10.0, 3.0, &res), CALC_SUCCESS);
    assert_double_equal("modulo(10, 3) value", res, 1.0);

    assert_status("modulo by zero check", calc_modulo(10.0, 0.0, &res), CALC_ERR_DIV_BY_ZERO);
}

static void test_power(void) {
    printf("\n--- Testing Power ---\n");
    double res = 0.0;
    assert_status("power(2, 8) status", calc_power(2.0, 8.0, &res), CALC_SUCCESS);
    assert_double_equal("power(2, 8) value", res, 256.0);

    assert_status("power(5, 0) status", calc_power(5.0, 0.0, &res), CALC_SUCCESS);
    assert_double_equal("power(5, 0) value", res, 1.0);

    assert_status("power(0, -2) div by zero", calc_power(0.0, -2.0, &res), CALC_ERR_DIV_BY_ZERO);
}

static void test_sqrt(void) {
    printf("\n--- Testing Square Root ---\n");
    double res = 0.0;
    assert_status("sqrt(16) status", calc_sqrt(16.0, &res), CALC_SUCCESS);
    assert_double_equal("sqrt(16) value", res, 4.0);

    assert_status("sqrt(0) status", calc_sqrt(0.0, &res), CALC_SUCCESS);
    assert_double_equal("sqrt(0) value", res, 0.0);

    assert_status("sqrt(-4) negative check", calc_sqrt(-4.0, &res), CALC_ERR_NEGATIVE_SQRT);
}

static void test_factorial(void) {
    printf("\n--- Testing Factorial ---\n");
    double res = 0.0;
    assert_status("factorial(0) status", calc_factorial(0, &res), CALC_SUCCESS);
    assert_double_equal("factorial(0) value", res, 1.0);

    assert_status("factorial(5) status", calc_factorial(5, &res), CALC_SUCCESS);
    assert_double_equal("factorial(5) value", res, 120.0);

    assert_status("factorial(-1) negative check", calc_factorial(-1, &res), CALC_ERR_NEGATIVE_FACTORIAL);
    assert_status("factorial(200) overflow check", calc_factorial(200, &res), CALC_ERR_OVERFLOW);
}

int main(void) {
    printf("===========================================\n");
    printf("        Running Calculator Unit Tests      \n");
    printf("===========================================\n");

    test_addition();
    test_subtraction();
    test_multiplication();
    test_division();
    test_modulo();
    test_power();
    test_sqrt();
    test_factorial();

    printf("\n===========================================\n");
    printf("Test Results: %d / %d passed\n", passed_tests, total_tests);
    printf("===========================================\n");

    return (passed_tests == total_tests) ? 0 : 1;
}
