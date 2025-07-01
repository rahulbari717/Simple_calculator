#include "calculator.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Simple history implementation (in-memory)
typedef struct {
    double a, b, res;
    int op;
    bool advanced;
} history_t;

static history_t history[HISTORY_MAX];
static int history_count = 0;

calc_result_t calculator_init(void) {
    history_count = 0;
    return CALC_SUCCESS;
}

void calculator_cleanup(void) {
    // Nothing dynamic to free here
}

static void push_history(double a, double b, double res, int op, bool adv) {
    if (history_count < HISTORY_MAX) {
        history[history_count++] = (history_t){.a = a, .b = b, .res = res, .op = op, .advanced = adv};
    }
}

void add_to_history(double a, double b, double res, int op) {
    push_history(a, b, res, op, false);
}

void add_advanced_to_history(double a, double b, double res, int op) {
    push_history(a, b, res, op, true);
}

void display_calculation_history(void) {
    if (!history_count) {
        printf("\n📜 No calculations yet.\n\n");
        return;
    }
    printf("\n📜 Calculation History:\n");
    for (int i = 0; i < history_count; i++) {
        history_t *h = &history[i];
        printf("%2d: %s %.6g %s %.6g = %.6g\n",
            i + 1,
            h->advanced ? "ADV_OP" : "BAS_OP",
            h->a,
            (h->advanced ? "^" : (h->op==2?"-":h->op==3?"*":"/")),
            h->b,
            h->res);
    }
    printf("\n");
}

// Basic ops
calc_result_t calculate_add(double a, double b, double *res) {
    *res = a + b;
    return isnan(*res) ? CALC_INVALID_INPUT : CALC_SUCCESS;
}
calc_result_t calculate_subtract(double a, double b, double *res) {
    *res = a - b;
    return isnan(*res) ? CALC_INVALID_INPUT : CALC_SUCCESS;
}
calc_result_t calculate_multiply(double a, double b, double *res) {
    *res = a * b;
    return isnan(*res) ? CALC_INVALID_INPUT : CALC_SUCCESS;
}
calc_result_t calculate_divide(double a, double b, double *res) {
    if (b == 0.0) return CALC_DIVISION_BY_ZERO;
    *res = a / b;
    return isfinite(*res) ? CALC_SUCCESS : CALC_OVERFLOW;
}

// Advanced ops
calc_result_t calculate_power(double a, double b, double *res) {
    *res = pow(a, b);
    return isfinite(*res) ? CALC_SUCCESS : CALC_OVERFLOW;
}
calc_result_t calculate_sqrt(double a, double *res) {
    if (a < 0.0) return CALC_DOMAIN_ERROR;
    *res = sqrt(a);
    return CALC_SUCCESS;
}
calc_result_t calculate_log(double a, double *res) {
    if (a <= 0.0) return CALC_DOMAIN_ERROR;
    *res = log(a);
    return CALC_SUCCESS;
}
calc_result_t calculate_sin(double a, double *res) {
    *res = sin(a);
    return CALC_SUCCESS;
}
calc_result_t calculate_cos(double a, double *res) {
    *res = cos(a);
    return CALC_SUCCESS;
}
calc_result_t calculate_tan(double a, double *res) {
    *res = tan(a);
    return CALC_SUCCESS;
}

void handle_calculation_error(calc_result_t err) {
    switch (err) {
        case CALC_DIVISION_BY_ZERO:
            printf("🚫 Division by zero is not allowed.\n");
            break;
        case CALC_DOMAIN_ERROR:
            printf("🚫 Math domain error. Invalid input for this operation.\n");
            break;
        case CALC_OVERFLOW:
            printf("🚫 Result overflowed or isn’t finite.\n");
            break;
        case CALC_UNDERFLOW:
            printf("🚫 Result underflowed.\n");
            break;
        default:
            printf("🚫 Unknown calculation error.\n");
    }
    printf("\n");
}
