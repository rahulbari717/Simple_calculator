// ==========================================
// FILE: calculator.c
// ==========================================
/**
 * @file calculator.c
 * @brief Calculator engine implementation
 * @details Implements the core mathematical operations with enterprise-grade
 *          error handling, precision management, and validation. Built to
 *          Apple's rigorous quality standards for numerical computing.
 * @author Senior Apple Developer
 * @date 2025-07-01
 * @version 1.0.0
 * @copyright © 2025 Calculator Corp. All rights reserved.
 */

#include "calculator.h"
#include <stdio.h>
#include <float.h>
#include <errno.h>

// ==========================================
// MARK: - Calculator Lifecycle
// ==========================================

calc_result_t calculator_initialize(void) {
    // Validate mathematical environment
    if (!isfinite(1.0) || !isfinite(0.0)) {
        return CALC_ERROR_INIT;
    }
    
    // Reset errno for mathematical operations
    errno = 0;
    
    return CALC_SUCCESS;
}

void calculator_cleanup(void) {
    // Calculator engine is stateless, no cleanup required
}

// ==========================================
// MARK: - Arithmetic Operations
// ==========================================

calc_result_t calculator_add(double a, double b, double *result) {
    if (result == NULL) {
        return CALC_ERROR_INVALID_INPUT;
    }
    
    // Validate inputs
    if (!calculator_is_valid_number(a) || !calculator_is_valid_number(b)) {
        return CALC_ERROR_INVALID_INPUT;
    }
    
    // Perform subtraction
    *result = a + b;
    
    // Check for overflow/underflow
    if (calculator_is_overflow(*result)) {
        return CALC_ERROR_OVERFLOW;
    }
    if (calculator_is_underflow(*result)) {
        return CALC_ERROR_UNDERFLOW;
    }
    
    return CALC_SUCCESS;
}

calc_result_t calculator_subtract(double a, double b, double *result) {
    if (result == NULL) {
        return CALC_ERROR_INVALID_INPUT;
    }
    
    // Validate inputs
    if (!calculator_is_valid_number(a) || !calculator_is_valid_number(b)) {
        return CALC_ERROR_INVALID_INPUT;
    }
    
    // Perform subtraction
    *result = a - b;
    
    // Check for overflow/underflow
    if (calculator_is_overflow(*result)) {
        return CALC_ERROR_OVERFLOW;
    }
    if (calculator_is_underflow(*result)) {
        return CALC_ERROR_UNDERFLOW;
    }
    
    return CALC_SUCCESS;
}

calc_result_t calculator_multiply(double a, double b, double *result) {
    if (result == NULL) {
        return CALC_ERROR_INVALID_INPUT;
    }
    
    // Validate inputs
    if (!calculator_is_valid_number(a) || !calculator_is_valid_number(b)) {
        return CALC_ERROR_INVALID_INPUT;
    }
    
    // Perform multiplication
    *result = a * b;
    
    // Check for overflow/underflow
    if (calculator_is_overflow(*result)) {
        return CALC_ERROR_OVERFLOW;
    }
    if (calculator_is_underflow(*result)) {
        return CALC_ERROR_UNDERFLOW;
    }
    
    return CALC_SUCCESS;
}

calc_result_t calculator_divide(double a, double b, double *result) {
    if (result == NULL) {
        return CALC_ERROR_INVALID_INPUT;
    }
    
    // Validate inputs
    if (!calculator_is_valid_number(a) || !calculator_is_valid_number(b)) {
        return CALC_ERROR_INVALID_INPUT;
    }
    
    // Check for division by zero
    if (fabs(b) < CALC_PRECISION_EPSILON) {
        return CALC_ERROR_DIVISION_BY_ZERO;
    }
    
    // Perform division
    *result = a / b;
    
    // Check for overflow/underflow
    if (calculator_is_overflow(*result)) {
        return CALC_ERROR_OVERFLOW;
    }
    if (calculator_is_underflow(*result)) {
        return CALC_ERROR_UNDERFLOW;
    }
    
    return CALC_SUCCESS;
}

calc_result_t calculator_modulus(int a, int b, double *result) {
    if (result == NULL) {
        return CALC_ERROR_INVALID_INPUT;
    }
    
    // Validate input ranges for integer operations
    if (a > CALC_MAX_SAFE_INTEGER || a < CALC_MIN_SAFE_INTEGER ||
        b > CALC_MAX_SAFE_INTEGER || b < CALC_MIN_SAFE_INTEGER) {
        return CALC_ERROR_INVALID_INPUT;
    }
    
    // Check for modulus by zero
    if (b == 0) {
        return CALC_ERROR_DIVISION_BY_ZERO;
    }
    
    // Perform modulus operation
    *result = (double)(a % b);
    
    return CALC_SUCCESS;
}

calc_result_t calculator_power(double base, double exponent, double *result) {
    if (result == NULL) {
        return CALC_ERROR_INVALID_INPUT;
    }
    
    // Validate inputs
    if (!calculator_is_valid_number(base) || !calculator_is_valid_number(exponent)) {
        return CALC_ERROR_INVALID_INPUT;
    }
    
    // Handle special cases
    if (base == 0.0 && exponent < 0.0) {
        return CALC_ERROR_DIVISION_BY_ZERO;
    }
    
    if (base < 0.0 && floor(exponent) != exponent) {
        return CALC_ERROR_DOMAIN; // Negative base with non-integer exponent
    }
    
    // Clear errno before math operation
    errno = 0;
    
    // Perform power operation
    *result = pow(base, exponent);
    
    // Check for math errors
    if (errno == EDOM) {
        return CALC_ERROR_DOMAIN;
    }
    if (errno == ERANGE) {
        if (calculator_is_overflow(*result)) {
            return CALC_ERROR_OVERFLOW;
        }
        if (calculator_is_underflow(*result)) {
            return CALC_ERROR_UNDERFLOW;
        }
    }
    
    // Additional overflow/underflow checks
    if (calculator_is_overflow(*result)) {
        return CALC_ERROR_OVERFLOW;
    }
    if (calculator_is_underflow(*result)) {
        return CALC_ERROR_UNDERFLOW;
    }
    
    return CALC_SUCCESS;
}

// ==========================================
// MARK: - Validation Functions
// ==========================================

bool calculator_is_valid_number(double value) {
    return isfinite(value) && !isnan(value);
}

bool calculator_is_overflow(double value) {
    return isinf(value) && value > 0.0;
}

bool calculator_is_underflow(double value) {
    return (value == 0.0 && !calculator_is_valid_number(value)) || 
           (isinf(value) && value < 0.0);
}