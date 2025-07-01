// ==========================================
// FILE: main.h
// ==========================================
/**
 * @file main.h
 * @brief Main application header - Entry point and application lifecycle
 * @details Defines the main application interface, return codes, and
 *          coordinates between menu and calculator subsystems.
 * @author Rahul B.
 * @date 2025-07-01
 * @version 1.0.0
 */

#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ==========================================
// MARK: - Application Constants
// ==========================================

/** Application version string */
#define APP_VERSION "1.0.0"

/** Application name */
#define APP_NAME "Simple Calculator"

/** Author information */
#define APP_AUTHOR "Rahul B."

/** Creation date */
#define APP_DATE "30th June 2025"

// ==========================================
// MARK: - Return Codes
// ==========================================

/** Application exit codes */
typedef enum {
    APP_SUCCESS = 0,        ///< Application completed successfully
    APP_ERROR_INIT = 1,     ///< Initialization error
    APP_ERROR_RUNTIME = 2,  ///< Runtime error
    APP_ERROR_MEMORY = 3    ///< Memory allocation error
} app_result_t;

// ==========================================
// MARK: - Function Prototypes
// ==========================================

/**
 * @brief Initialize the application
 * @details Sets up the application environment, displays welcome message,
 *          and prepares all subsystems for operation.
 * @return APP_SUCCESS on success, appropriate error code on failure
 * @note This function must be called before any other application functions
 */
app_result_t app_initialize(void);

/**
 * @brief Run the main application loop
 * @details Manages the primary application workflow, handles user interaction,
 *          and coordinates between menu and calculator subsystems.
 * @return APP_SUCCESS on normal exit, error code on abnormal termination
 * @note This function will block until user chooses to exit
 */
app_result_t app_run_main_loop(void);

/**
 * @brief Clean up application resources
 * @details Performs cleanup operations, releases resources, and prepares
 *          for application termination.
 * @note This function should be called before application exit
 */
void app_cleanup(void);

/**
 * @brief Display application welcome message
 * @details Shows branded welcome screen with version information
 *          and author credits.
 */
void app_display_welcome(void);

/**
 * @brief Display application goodbye message
 * @details Shows farewell message before application termination.
 */
void app_display_goodbye(void);

#endif /* MAIN_H */