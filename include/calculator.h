#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <stdbool.h>

// Constants
#define HISTORY_MAX 50

// Result codes
typedef enum {
    CALC_SUCCESS = 0,
    CALC_DIVISION_BY_ZERO,
    CALC_DOMAIN_ERROR,
    CALC_OVERFLOW,
    CALC_UNDERFLOW,
    CALC_INVALID_INPUT
} calc_result_t;

// Input status
typedef enum {
    INPUT_SUCCESS = 0,
    INPUT_ERROR
} input_result_t;

// Initialization & cleanup
calc_result_t calculator_init(void);
void calculator_cleanup(void);

// Basic operations
calc_result_t calculate_add(double a, double b, double *res);
calc_result_t calculate_subtract(double a, double b, double *res);
calc_result_t calculate_multiply(double a, double b, double *res);
calc_result_t calculate_divide(double a, double b, double *res);

// Advanced operations
calc_result_t calculate_power(double a, double b, double *res);
calc_result_t calculate_sqrt(double a, double *res);
calc_result_t calculate_log(double a, double *res);
calc_result_t calculate_sin(double a, double *res);
calc_result_t calculate_cos(double a, double *res);
calc_result_t calculate_tan(double a, double *res);

// History storage & display
void add_to_history(double a, double b, double res, int op);
void add_advanced_to_history(double a, double b, double res, int op);
void display_calculation_history(void);

// Error handling & helpers
void handle_calculation_error(calc_result_t err);
input_result_t get_double_input(const char *prompt, double *value);

// Main loop & menu functions
int run_main_loop(void);
void display_main_menu(void);
input_result_t get_user_choice(int *choice);
void handle_basic_operations(void);
void handle_advanced_operations(void);
void display_help(void);

#endif // CALCULATOR_H
