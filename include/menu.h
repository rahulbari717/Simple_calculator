// ==========================================
// FILE: menu.h
// ==========================================
/**
 * @file menu.h
 * @brief Menu subsystem header - User interface and navigation
 * @details Defines the menu interface, user choices, and navigation logic.
 *          Provides a clean abstraction for user interaction while maintaining
 *          separation from business logic.
 * @author Rahul B.
 * @date 2025-07-01
 * @version 1.0.0
 */

#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdbool.h>

// ==========================================
// MARK: - Menu Constants
// ==========================================

/** Maximum number of menu choices */
#define MENU_MAX_CHOICES 7

/** Menu choice validation bounds */
#define MENU_MIN_CHOICE 1
#define MENU_MAX_CHOICE 7

// ==========================================
// MARK: - Menu Types
// ==========================================

/** Menu operation result codes */
typedef enum {
    MENU_SUCCESS = 0,           ///< Menu operation completed successfully
    MENU_ERROR_INVALID_INPUT,   ///< Invalid user input received
    MENU_ERROR_IO,             ///< Input/output error
    MENU_ERROR_INIT            ///< Menu initialization error
} menu_result_t;

/** Available menu choices */
typedef enum {
    MENU_CHOICE_INVALID = 0,    ///< Invalid choice (used for error handling)
    MENU_CHOICE_ADD = 1,        ///< Addition operation
    MENU_CHOICE_SUBTRACT = 2,   ///< Subtraction operation
    MENU_CHOICE_MULTIPLY = 3,   ///< Multiplication operation
    MENU_CHOICE_DIVIDE = 4,     ///< Division operation
    MENU_CHOICE_MODULUS = 5,    ///< Modulus operation
    MENU_CHOICE_POWER = 6,      ///< Power operation
    MENU_CHOICE_EXIT = 7        ///< Exit application
} menu_choice_t;

// ==========================================
// MARK: - Function Prototypes
// ==========================================

/**
 * @brief Initialize the menu subsystem
 * @details Prepares the menu subsystem for operation, sets up any required
 *          resources, and validates the environment.
 * @return MENU_SUCCESS on success, appropriate error code on failure
 */
menu_result_t menu_initialize(void);

/**
 * @brief Clean up menu subsystem resources
 * @details Releases any resources allocated by the menu subsystem and
 *          prepares for termination.
 */
void menu_cleanup(void);

/**
 * @brief Display menu and get user choice
 * @details Presents the main menu to the user and captures their selection.
 *          Includes input validation and error handling.
 * @param choice Pointer to store the user's menu choice
 * @return MENU_SUCCESS on valid choice, error code on invalid input
 * @pre choice must not be NULL
 * @post choice contains a valid menu_choice_t value if MENU_SUCCESS returned
 */
menu_result_t menu_display_and_get_choice(menu_choice_t *choice);

/**
 * @brief Handle calculation request from menu
 * @details Coordinates with calculator subsystem to perform the requested
 *          operation, handles user input, and displays results.
 * @param operation The calculation operation to perform
 * @return MENU_SUCCESS on successful operation, error code on failure
 * @pre operation must be a valid calculation choice (not EXIT or INVALID)
 */
menu_result_t menu_handle_calculation(menu_choice_t operation);

/**
 * @brief Display the main menu
 * @details Renders the formatted main menu interface to stdout.
 */
void menu_display_main_menu(void);

/**
 * @brief Get and validate user input
 * @details Safely reads user input and validates it against menu choices.
 * @param choice Pointer to store the validated choice
 * @return MENU_SUCCESS on valid input, error code on invalid input
 * @pre choice must not be NULL
 */
menu_result_t menu_get_user_input(menu_choice_t *choice);

/**
 * @brief Get numeric input from user
 * @details Safely reads and validates numeric input from the user.
 * @param prompt Message to display to the user
 * @param value Pointer to store the numeric value
 * @return MENU_SUCCESS on valid input, error code on invalid input
 * @pre prompt must not be NULL, value must not be NULL
 */
menu_result_t menu_get_numeric_input(const char *prompt, double *value);

/**
 * @brief Clear input buffer
 * @details Clears the input buffer to prevent input contamination.
 */
void menu_clear_input_buffer(void);

/**
 * @brief Convert menu choice to operation name
 * @details Returns a human-readable string for the given menu choice.
 * @param choice The menu choice to convert
 * @return String representation of the operation, or "Unknown" if invalid
 */
const char* menu_choice_to_string(menu_choice_t choice);

#endif /* MENU_H */