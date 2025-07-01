// ==========================================
// FILE: main.c
// ==========================================
/**
 * @file main.c
 * @brief Main application implementation
 * @details Implements the application entry point, initialization, and
 *          main execution loop. Coordinates between menu and calculator
 *          subsystems while maintaining clean separation of concerns.
 * @author Rahul B.
 * @date 2025-07-01
 * @version 1.0.0
 */

#include "main.h"
#include "menu.h"
#include "calculator.h"

// ==========================================
// MARK: - Main Entry Point
// ==========================================

/**
 * @brief Application entry point
 * @details Standard C main function that orchestrates application lifecycle:
 *          initialization, main loop execution, and cleanup.
 * @param argc Argument count (unused)
 * @param argv Argument vector (unused)
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on error
 */
int main(int argc, char *argv[]) {
    // Suppress unused parameter warnings
    (void)argc;
    (void)argv;
    
    app_result_t result;
    
    // Phase 1: Initialize application
    result = app_initialize();
    if (result != APP_SUCCESS) {
        fprintf(stderr, "❌ Fatal Error: Application initialization failed (Code: %d)\n", result);
        return EXIT_FAILURE;
    }
    
    // Phase 2: Run main application loop
    result = app_run_main_loop();
    if (result != APP_SUCCESS) {
        fprintf(stderr, "❌ Warning: Application terminated with error (Code: %d)\n", result);
    }
    
    // Phase 3: Cleanup resources
    app_cleanup();
    
    // Phase 4: Display goodbye message
    app_display_goodbye();
    
    return (result == APP_SUCCESS) ? EXIT_SUCCESS : EXIT_FAILURE;
}

// ==========================================
// MARK: - Application Lifecycle
// ==========================================

app_result_t app_initialize(void) {
    // Display welcome message
    app_display_welcome();
    
    // Initialize calculator subsystem
    calc_result_t calc_init_result = calculator_initialize();
    if (calc_init_result != CALC_SUCCESS) {
        fprintf(stderr, "❌ Error: Calculator initialization failed\n");
        return APP_ERROR_INIT;
    }
    
    // Initialize menu subsystem
    menu_result_t menu_init_result = menu_initialize();
    if (menu_init_result != MENU_SUCCESS) {
        fprintf(stderr, "❌ Error: Menu initialization failed\n");
        calculator_cleanup();
        return APP_ERROR_INIT;
    }
    
    printf("✅ All subsystems initialized successfully!\n");
    printf("Press Enter to continue to main menu...");
    getchar();
    printf("\n");
    
    return APP_SUCCESS;
}

app_result_t app_run_main_loop(void) {
    bool application_running = true;
    menu_choice_t user_choice;
    
    while (application_running) {
        // Display menu and get user choice
        menu_result_t menu_result = menu_display_and_get_choice(&user_choice);
        
        if (menu_result != MENU_SUCCESS) {
            printf("❌ Menu error occurred. Please try again.\n\n");
            continue;
        }
        
        // Process user choice
        switch (user_choice) {
            case MENU_CHOICE_ADD:
            case MENU_CHOICE_SUBTRACT:
            case MENU_CHOICE_MULTIPLY:
            case MENU_CHOICE_DIVIDE:
            case MENU_CHOICE_MODULUS:
            case MENU_CHOICE_POWER:
                menu_handle_calculation(user_choice);
                break;
                
            case MENU_CHOICE_EXIT:
                application_running = false;
                break;
                
            default:
                printf("❌ Internal Error: Invalid menu choice received\n");
                break;
        }
        
        // Pause before next iteration (unless exiting)
        if (application_running) {
            printf("\nPress Enter to continue...");
            getchar();
            printf("\n");
        }
    }
    
    return APP_SUCCESS;
}

void app_cleanup(void) {
    calculator_cleanup();
    menu_cleanup();
    printf("🧹 Application cleanup completed.\n");
}

// ==========================================
// MARK: - Display Functions
// ==========================================

void app_display_welcome(void) {
    printf("\n");
    printf("🎉 Welcome to %s v%s! 🎉\n", APP_NAME, APP_VERSION);
    printf("═════════════════════════════════════════════════════════════════════\n");
    printf("👨‍💻 Crafted with ❤️  by %s on %s\n", APP_AUTHOR, APP_DATE);
    printf("🏆 Designed to deliver fast, reliable, and precise calculations\n");
    printf("🚀 Whether you're a student, engineer, or enthusiast — this is for YOU!\n");
    printf("📈 Packed with essential operations and clean CLI interface\n");
    printf("═════════════════════════════════════════════════════════════════════\n");
}

void app_display_goodbye(void) {
    printf("\n");
    printf("════════════════════════════════════════════════════════\n");
    printf("🙏 Thank you for using %s v%s!\n", APP_NAME, APP_VERSION);
    printf("💫 Hope it made your calculations easier and more efficient!\n");
    printf("🚀 Built with precision, designed for excellence.\n");
    printf("════════════════════════════════════════════════════════\n");
    printf("👋 Goodbye! Come back anytime for more calculations! 😊\n\n");
}
