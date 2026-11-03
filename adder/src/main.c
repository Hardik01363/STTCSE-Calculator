#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calculator.h"

static void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

static void print_banner(void) {
    printf("===========================================\n");
    printf("            STTCSE Calculator              \n");
    printf("===========================================\n");
}

static void print_menu(void) {
    printf("\nChoose an operation:\n");
    printf("  1. Addition (+)\n");
    printf("  2. Subtraction (-)\n");
    printf("  3. Multiplication (*)\n");
    printf("  4. Division (/)\n");
    printf("  5. Modulo (%%)\n");
    printf("  6. Power (^)\n");
    printf("  7. Square Root (sqrt)\n");
    printf("  8. Factorial (!)\n");
    printf("  9. Exit\n");
    printf("Enter choice (1-9): ");
}

static void print_help(const char *prog_name) {
    printf("Usage:\n");
    printf("  %s                           Run interactive mode\n", prog_name);
    printf("  %s <num1> <op> <num2>        Perform binary operation\n", prog_name);
    printf("  %s sqrt <num>                Compute square root\n", prog_name);
    printf("  %s fact <int>                Compute factorial\n", prog_name);
    printf("\nSupported operators: +, -, *, x, /, %%, ^\n");
    printf("Examples:\n");
    printf("  %s 10 + 5\n", prog_name);
    printf("  %s 10 / 2\n", prog_name);
    printf("  %s 2 ^ 8\n", prog_name);
    printf("  %s sqrt 25\n", prog_name);
    printf("  %s fact 5\n", prog_name);
}

static int run_cli_args(int argc, char *argv[]) {
    if (argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
        print_help(argv[0]);
        return 0;
    }

    double result = 0.0;
    CalcStatus status = CALC_SUCCESS;

    if (argc == 3) {
        if (strcmp(argv[1], "sqrt") == 0) {
            char *endptr;
            double val = strtod(argv[2], &endptr);
            if (*endptr != '\0') {
                fprintf(stderr, "Error: Invalid number '%s'\n", argv[2]);
                return 1;
            }
            status = calc_sqrt(val, &result);
            if (status == CALC_SUCCESS) {
                printf("sqrt(%g) = %g\n", val, result);
                return 0;
            } else {
                fprintf(stderr, "%s\n", calc_error_string(status));
                return 1;
            }
        } else if (strcmp(argv[1], "fact") == 0) {
            char *endptr;
            long val = strtol(argv[2], &endptr, 10);
            if (*endptr != '\0') {
                fprintf(stderr, "Error: Invalid integer '%s'\n", argv[2]);
                return 1;
            }
            status = calc_factorial((int)val, &result);
            if (status == CALC_SUCCESS) {
                printf("%ld! = %g\n", val, result);
                return 0;
            } else {
                fprintf(stderr, "%s\n", calc_error_string(status));
                return 1;
            }
        }
    }

    if (argc == 4) {
        char *endptr1, *endptr2;
        double a = strtod(argv[1], &endptr1);
        const char *op = argv[2];
        double b = strtod(argv[3], &endptr2);

        if (*endptr1 != '\0' || *endptr2 != '\0') {
            fprintf(stderr, "Error: Invalid numeric operands.\n");
            return 1;
        }

        if (strcmp(op, "+") == 0) {
            status = calc_add(a, b, &result);
        } else if (strcmp(op, "-") == 0) {
            status = calc_subtract(a, b, &result);
        } else if (strcmp(op, "*") == 0 || strcmp(op, "x") == 0) {
            status = calc_multiply(a, b, &result);
        } else if (strcmp(op, "/") == 0) {
            status = calc_divide(a, b, &result);
        } else if (strcmp(op, "%") == 0) {
            status = calc_modulo(a, b, &result);
        } else if (strcmp(op, "^") == 0) {
            status = calc_power(a, b, &result);
        } else {
            fprintf(stderr, "Error: Unsupported operator '%s'.\n", op);
            print_help(argv[0]);
            return 1;
        }

        if (status == CALC_SUCCESS) {
            printf("%g %s %g = %g\n", a, op, b, result);
            return 0;
        } else {
            fprintf(stderr, "%s\n", calc_error_string(status));
            return 1;
        }
    }

    fprintf(stderr, "Error: Invalid arguments.\n");
    print_help(argv[0]);
    return 1;
}

static void run_interactive(void) {
    print_banner();
    int choice = 0;

    while (1) {
        print_menu();
        if (scanf("%d", &choice) != 1) {
            if (feof(stdin)) {
                printf("\nExiting calculator. Goodbye!\n");
                break;
            }
            printf("Invalid input. Please enter a valid number.\n");
            clear_input_buffer();
            continue;
        }

        if (choice == 9) {
            printf("Exiting calculator. Goodbye!\n");
            break;
        }

        double a = 0.0, b = 0.0, result = 0.0;
        CalcStatus status = CALC_SUCCESS;

        if (choice >= 1 && choice <= 6) {
            printf("Enter first operand: ");
            if (scanf("%lf", &a) != 1) {
                printf("Error: Invalid numeric input.\n");
                clear_input_buffer();
                continue;
            }
            printf("Enter second operand: ");
            if (scanf("%lf", &b) != 1) {
                printf("Error: Invalid numeric input.\n");
                clear_input_buffer();
                continue;
            }

            switch (choice) {
                case 1:
                    status = calc_add(a, b, &result);
                    if (status == CALC_SUCCESS) printf("Result: %g + %g = %g\n", a, b, result);
                    break;
                case 2:
                    status = calc_subtract(a, b, &result);
                    if (status == CALC_SUCCESS) printf("Result: %g - %g = %g\n", a, b, result);
                    break;
                case 3:
                    status = calc_multiply(a, b, &result);
                    if (status == CALC_SUCCESS) printf("Result: %g * %g = %g\n", a, b, result);
                    break;
                case 4:
                    status = calc_divide(a, b, &result);
                    if (status == CALC_SUCCESS) printf("Result: %g / %g = %g\n", a, b, result);
                    break;
                case 5:
                    status = calc_modulo(a, b, &result);
                    if (status == CALC_SUCCESS) printf("Result: %g %% %g = %g\n", a, b, result);
                    break;
                case 6:
                    status = calc_power(a, b, &result);
                    if (status == CALC_SUCCESS) printf("Result: %g ^ %g = %g\n", a, b, result);
                    break;
            }
        } else if (choice == 7) {
            printf("Enter operand: ");
            if (scanf("%lf", &a) != 1) {
                printf("Error: Invalid numeric input.\n");
                clear_input_buffer();
                continue;
            }
            status = calc_sqrt(a, &result);
            if (status == CALC_SUCCESS) {
                printf("Result: sqrt(%g) = %g\n", a, result);
            }
        } else if (choice == 8) {
            int n = 0;
            printf("Enter non-negative integer: ");
            if (scanf("%d", &n) != 1) {
                printf("Error: Invalid integer input.\n");
                clear_input_buffer();
                continue;
            }
            status = calc_factorial(n, &result);
            if (status == CALC_SUCCESS) {
                printf("Result: %d! = %g\n", n, result);
            }
        } else {
            printf("Invalid selection. Please choose an option from 1 to 9.\n");
            clear_input_buffer();
            continue;
        }

        if (status != CALC_SUCCESS) {
            printf("%s\n", calc_error_string(status));
        }
        clear_input_buffer();
    }
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        return run_cli_args(argc, argv);
    }
    run_interactive();
    return 0;
}
