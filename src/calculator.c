#include "calculator.h"
#include <math.h>

CalcStatus calc_add(double a, double b, double *result) {
    if (!result) return CALC_ERR_INVALID_INPUT;
    *result = a + b;
    return CALC_SUCCESS;
}

CalcStatus calc_subtract(double a, double b, double *result) {
    if (!result) return CALC_ERR_INVALID_INPUT;
    *result = a - b;
    return CALC_SUCCESS;
}

CalcStatus calc_multiply(double a, double b, double *result) {
    if (!result) return CALC_ERR_INVALID_INPUT;
    *result = a * b;
    return CALC_SUCCESS;
}

CalcStatus calc_divide(double a, double b, double *result) {
    if (!result) return CALC_ERR_INVALID_INPUT;
    if (b == 0.0) return CALC_ERR_DIV_BY_ZERO;
    *result = a / b;
    return CALC_SUCCESS;
}

CalcStatus calc_modulo(double a, double b, double *result) {
    if (!result) return CALC_ERR_INVALID_INPUT;
    if (b == 0.0) return CALC_ERR_DIV_BY_ZERO;
    *result = fmod(a, b);
    return CALC_SUCCESS;
}

CalcStatus calc_power(double base, double exp, double *result) {
    if (!result) return CALC_ERR_INVALID_INPUT;
    if (base == 0.0 && exp < 0.0) return CALC_ERR_DIV_BY_ZERO;
    if (base < 0.0 && floor(exp) != exp) return CALC_ERR_INVALID_INPUT;
    *result = pow(base, exp);
    return CALC_SUCCESS;
}

CalcStatus calc_sqrt(double a, double *result) {
    if (!result) return CALC_ERR_INVALID_INPUT;
    if (a < 0.0) return CALC_ERR_NEGATIVE_SQRT;
    *result = sqrt(a);
    return CALC_SUCCESS;
}

CalcStatus calc_factorial(int n, double *result) {
    if (!result) return CALC_ERR_INVALID_INPUT;
    if (n < 0) return CALC_ERR_NEGATIVE_FACTORIAL;
    if (n > 170) return CALC_ERR_OVERFLOW;

    double fact = 1.0;
    for (int i = 2; i <= n; i++) {
        fact *= i;
    }
    *result = fact;
    return CALC_SUCCESS;
}

const char *calc_error_string(CalcStatus status) {
    switch (status) {
        case CALC_SUCCESS:
            return "Success";
        case CALC_ERR_DIV_BY_ZERO:
            return "Error: Division by zero is undefined.";
        case CALC_ERR_NEGATIVE_SQRT:
            return "Error: Cannot calculate square root of a negative number.";
        case CALC_ERR_NEGATIVE_FACTORIAL:
            return "Error: Cannot calculate factorial of a negative integer.";
        case CALC_ERR_OVERFLOW:
            return "Error: Arithmetic overflow (result exceeds capacity).";
        case CALC_ERR_INVALID_INPUT:
            return "Error: Invalid input parameters.";
        default:
            return "Error: Unknown error occurred.";
    }
}
