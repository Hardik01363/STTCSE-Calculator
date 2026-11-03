#ifndef CALCULATOR_H
#define CALCULATOR_H

typedef enum {
    CALC_SUCCESS = 0,
    CALC_ERR_DIV_BY_ZERO,
    CALC_ERR_NEGATIVE_SQRT,
    CALC_ERR_NEGATIVE_FACTORIAL,
    CALC_ERR_OVERFLOW,
    CALC_ERR_INVALID_INPUT
} CalcStatus;

CalcStatus calc_add(double a, double b, double *result);
CalcStatus calc_subtract(double a, double b, double *result);
CalcStatus calc_multiply(double a, double b, double *result);
CalcStatus calc_divide(double a, double b, double *result);
CalcStatus calc_modulo(double a, double b, double *result);
CalcStatus calc_power(double base, double exp, double *result);
CalcStatus calc_sqrt(double a, double *result);
CalcStatus calc_factorial(int n, double *result);

const char *calc_error_string(CalcStatus status);

#endif
