// ==========================================
// FILE: calculator.h
// ==========================================
/**
 * @file calculator.h
 * @brief Calculator engine header - Core mathematical operations
 * @details Defines the calculator engine interface providing high-precision
 *          mathematical operations with comprehensive error handling.
 *          Designed for reliability, accuracy, and maintainability.
 * @author Rahul B.
 * @date 2025-07-01
 * @version 1.0.0
 */

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <stdbool.h>
#include <math.h>
#include <limits.h>
// ==========================================
// MARK: - Calculator Constants
// ==========================================

/** Maximum precision for floating-point operations */
#define CALC_PRECISION_EPSILON 1e-15

/** Maximum safe integer for modulus operations */
#define CALC_MAX_SAFE_INTEGER INT_MAX

/** Minimum safe integer for modulus operations */
#define CALC_MIN_SAFE_INTEGER INT_MIN

// ==========================================
// MARK: - Calculator Types
// ==========================================

/** Calculator operation result codes */
typedef enum {
    CALC_SUCCESS = 0,               ///< Operation completed successfully
    CALC_ERROR_DIVISION_BY_ZERO,    ///< Division by zero attempted
    CALC_ERROR_DOMAIN,              ///< Invalid domain for operation
    CALC_ERROR_OVERFLOW,            ///< Numeric overflow occurred
    CALC_ERROR_UNDERFLOW,           ///< Numeric underflow occurred
    CALC_ERROR_INVALID_INPUT,       ///< Invalid input provided
    CALC_ERROR_INIT                 ///< Calculator initialization error
} calc_result_t;

// ==========================================
// MARK: - Function Prototypes
// ==========================================

/**
 * @brief Initialize the calculator engine
 * @details Prepares the calculator engine for operation, initializes
 *          internal state, and validates the mathematical environment.
 * @return CALC_SUCCESS on success, appropriate error code on failure
 */
calc_result_t calculator_initialize(void);

/**
 * @brief Clean up calculator resources
 * @details Releases any resources allocated by the calculator engine
 *          and prepares for termination.
 */
void calculator_cleanup(void);

/**
 * @brief Perform addition operation
 * @details Computes the sum of two numbers with overflow detection.
 * @param a First operand
 * @param b Second operand
 * @param result Pointer to store the result
 * @return CALC_SUCCESS on success, error code on failure
 * @pre result must not be NULL
 * @post result contains a + b if CALC_SUCCESS returned
 */
calc_result_t calculator_add(double a, double b, double *result);

/**
 * @brief Perform subtraction operation
 * @details Computes the difference of two numbers with overflow detection.
 * @param a Minuend (number to subtract from)
 * @param b Subtrahend (number to subtract)
 * @param result Pointer to store the result
 * @return CALC_SUCCESS on success, error code on failure
 * @pre result must not be NULL
 * @post result contains a - b if CALC_SUCCESS returned
 */
calc_result_t calculator_subtract(double a, double b, double *result);

/**
 * @brief Perform multiplication operation
 * @details Computes the product of two numbers with overflow detection.
 * @param a First factor
 * @param b Second factor
 * @param result Pointer to store the result
 * @return CALC_SUCCESS on success, error code on failure
 * @pre result must not be NULL
 * @post result contains a * b if CALC_SUCCESS returned
 */
calc_result_t calculator_multiply(double a, double b, double *result);

/**
 * @brief Perform division operation
 * @details Computes the quotient of two numbers with division-by-zero checking.
 * @param a Dividend (number to be divided)
 * @param b Divisor (number to divide by)
 * @param result Pointer to store the result
 * @return CALC_SUCCESS on success, error code on failure
 * @pre result must not be NULL
 * @post result contains a / b if CALC_SUCCESS returned
 */
calc_result_t calculator_divide(double a, double b, double *result);

/**
 * @brief Perform modulus operation
 * @details Computes the remainder of integer division with validation.
 * @param a Dividend (integer to be divided)
 * @param b Divisor (integer to divide by)
 * @param result Pointer to store the result
 * @return CALC_SUCCESS on success, error code on failure
 * @pre result must not be NULL
 * @post result contains a % b if CALC_SUCCESS returned
 */
calc_result_t calculator_modulus(int a, int b, double *result);

/**
 * @brief Perform power operation
 * @details Computes base raised to the power of exponent with domain validation.
 * @param base Base number
 * @param exponent Exponent value
 * @param result Pointer to store the result
 * @return CALC_SUCCESS on success, error code on failure
 * @pre result must not be NULL
 * @post result contains base^exponent if CALC_SUCCESS returned
 */
calc_result_t calculator_power(double base, double exponent, double *result);

/**
 * @brief Validate numeric input
 * @details Checks if a number is finite and within acceptable ranges.
 * @param value The number to validate
 * @return true if valid, false otherwise
 */
bool calculator_is_valid_number(double value);

/**
 * @brief Check for numeric overflow
 * @details Determines if a calculation result represents an overflow condition.
 * @param value The value to check
 * @return true if overflow detected, false otherwise
 */
bool calculator_is_overflow(double value);

/**
 * @brief Check for numeric underflow
 * @details Determines if a calculation result represents an underflow condition.
 * @param value The value to check
 * @return true if underflow detected, false otherwise
 */
bool calculator_is_underflow(double value);

#endif /* CALCULATOR_H */