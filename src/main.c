/**
 * @file main.c
 * @brief Main entry point for the Simple Calculator application
 * @details Handles user interface, menu navigation, and input validation.
 *          Implements a clean separation of concerns with the calculator logic.
 * @author Rahul B.
 * @date 30th June 2025
 * @version 1.0.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <math.h>

#include "main.h"
#include "calculator.h"


/**
 * @brief Main application entry point
 * @details Initializes the application and starts the main menu loop
 * @return EXIT_SUCCESS on normal termination, EXIT_FAILURE on error
 */
int main(void) {
    printf("🎉 Welcome to Simple Calculator v1.0.0! 🎉\n");
    printf("════════════════════════════════════════════\n");
    printf("👨‍💻 Created with ❤️  by Rahul B. (30th June 2025)\n");
    printf("════════════════════════════════════════════\n\n");
    
    // Show helpful startup message
    printf("🚀 Getting Started:\n");
    printf("   • Choose from Basic or Advanced operations\n");
    printf("   • All calculations are saved in history\n");
    printf("   • Type numbers like: 42, 3.14, 1.5e-3\n");
    printf("   • Need help? Select option 4 from main menu\n\n");
    
    // Initialize calculator state
    if (calculator_init() != CALC_SUCCESS) {
        fprintf(stderr, "❌ Error: Failed to initialize calculator\n");
        return EXIT_FAILURE;
    }
    
    printf("✅ Calculator initialized successfully!\n");
    printf("Press Enter to continue to main menu...");
    getchar();
    printf("\n");
    
    // Start main application loop
    int result = run_main_loop();
    
    // Cleanup resources
    calculator_cleanup();
    
    printf("\n🙏 Thank you for using Simple Calculator!\n");
    printf("Hope it made your calculations easier! 😊\n");
    return result;
}

/**
 * @brief Main application loop handling user interaction
 * @details Displays menu, processes user input, and handles operations
 * @return EXIT_SUCCESS on normal exit, EXIT_FAILURE on error
 */
int run_main_loop(void) {
    int choice;
    bool running = true;
    
    while (running) {
        display_main_menu();
        
        if (get_user_choice(&choice) != INPUT_SUCCESS) {
            printf("Invalid input. Please try again.\n\n");
            continue;
        }
        
        switch (choice) {
            case MENU_BASIC_CALC:
                handle_basic_operations();
                break;
                
            case MENU_ADVANCED_CALC:
                handle_advanced_operations();
                break;
                
            case MENU_HISTORY:
                display_calculation_history();
                break;
                
            case MENU_HELP:
                display_help();
                break;
                
            case MENU_EXIT:
                running = false;
                break;
                
            default:
                printf("Invalid choice. Please select 1-5.\n\n");
                break;
        }
    }
    
    return EXIT_SUCCESS;
}

/**
 * @brief Display the main menu options
 * @details Presents a clean, formatted menu interface to the user
 */
void display_main_menu(void) {
    printf("┌─────────────────────────────────────┐\n");
    printf("│         🧮 MAIN MENU 🧮             │\n");
    printf("├─────────────────────────────────────┤\n");
    printf("│ 1. ➕ Basic Operations              │\n");
    printf("│    (Add, Subtract, Multiply, Divide)│\n");
    printf("│                                     │\n");
    printf("│ 2. 🔬 Advanced Operations           │\n");
    printf("│    (Power, Root, Trig, Log)         │\n");
    printf("│                                     │\n");
    printf("│ 3. 📜 View History                  │\n");
    printf("│    (See all your calculations)      │\n");
    printf("│                                     │\n");
    printf("│ 4. ❓ Help & Examples               │\n");
    printf("│    (Learn how to use features)      │\n");
    printf("│                                     │\n");
    printf("│ 5. 👋 Exit                          │\n");
    printf("└─────────────────────────────────────┘\n");
    printf("💡 Tip: Start with option 1 for basic math!\n");
    printf("Enter your choice (1-5): ");
}

/**
 * @brief Get and validate user menu choice
 * @param[out] choice Pointer to store the validated choice
 * @return INPUT_SUCCESS if valid input, INPUT_ERROR if invalid
 */
input_result_t get_user_choice(int *choice) {
    if (!choice) {
        return INPUT_ERROR;
    }
    
    char buffer[MAX_INPUT_LENGTH];
    char *endptr;
    
    if (!fgets(buffer, sizeof(buffer), stdin)) {
        return INPUT_ERROR;
    }
    
    // Remove newline if present
    buffer[strcspn(buffer, "\n")] = '\0';
    
    // Convert to integer with error checking
    errno = 0;
    long temp = strtol(buffer, &endptr, 10);
    
    if (errno != 0 || *endptr != '\0' || temp < INT_MIN || temp > INT_MAX) {
        return INPUT_ERROR;
    }
    
    *choice = (int)temp;
    return INPUT_SUCCESS;
}

/**
 * @brief Handle basic arithmetic operations
 * @details Manages the flow for addition, subtraction, multiplication, division
 */
void handle_basic_operations(void) {
    printf("\n┌─────────────────────────────────────┐\n");
    printf("│      ➕ BASIC OPERATIONS ➕         │\n");
    printf("├─────────────────────────────────────┤\n");
    printf("│ 1. ➕ Addition       (5 + 3 = 8)   │\n");
    printf("│ 2. ➖ Subtraction    (5 - 3 = 2)   │\n");
    printf("│ 3. ✖️  Multiplication (5 × 3 = 15)  │\n");
    printf("│ 4. ➗ Division       (6 ÷ 3 = 2)   │\n");
    printf("│ 5. 🔙 Back to Main Menu             │\n");
    printf("└─────────────────────────────────────┘\n");
    printf("💡 Example: Enter 12.5 for decimal numbers\n");
    printf("Enter your choice (1-5): ");
    
    int choice;
    if (get_user_choice(&choice) != INPUT_SUCCESS) {
        printf("🤔 Please enter a valid number (1-5).\n\n");
        return;
    }
    
    if (choice == 5) {
        printf("🔙 Going back to main menu...\n");
        return; // Back to main menu
    }
    
    if (choice < 1 || choice > 4) {
        printf("🚫 Please choose between 1-4 for operations, or 5 to go back.\n\n");
        return;
    }
    
    printf("\n📝 Let's do some math! Enter your numbers:\n");
    
    double num1, num2, result;
    
    // Get operands
    if (get_double_input("🔢 Enter first number: ", &num1) != INPUT_SUCCESS ||
        get_double_input("🔢 Enter second number: ", &num2) != INPUT_SUCCESS) {
        printf("❌ Please enter valid numbers (like 5, 3.14, or 1.5e-3).\n");
        printf("💡 Tip: Use decimal point for fractions, e.g., 3.14\n\n");
        return;
    }
    
    // Perform operation
    calc_result_t calc_status;
    const char* operation_name;
    
    switch (choice) {
        case 1:
            calc_status = calculate_add(num1, num2, &result);
            operation_name = "Addition";
            break;
        case 2:
            calc_status = calculate_subtract(num1, num2, &result);
            operation_name = "Subtraction";
            break;
        case 3:
            calc_status = calculate_multiply(num1, num2, &result);
            operation_name = "Multiplication";
            break;
        case 4:
            calc_status = calculate_divide(num1, num2, &result);
            operation_name = "Division";
            break;
        default:
            printf("Internal error: Invalid operation\n\n");
            return;
    }
    
    // Display result
    if (calc_status == CALC_SUCCESS) {
        printf("\n🎉 %s Result: %.6g\n", operation_name, result);
        printf("✅ Calculation saved to history!\n");
        add_to_history(num1, num2, result, choice);
    } else {
        handle_calculation_error(calc_status);
    }
    
    printf("\n💡 Want to do another calculation? Just choose from the menu!\n");
    printf("Press Enter to continue...");
    getchar();
    printf("\n");
}

/**
 * @brief Handle advanced mathematical operations
 * @details Manages the flow for power, square root, and other advanced functions
 */
void handle_advanced_operations(void) {
    printf("\n┌─────────────────────────────────────┐\n");
    printf("│     🔬 ADVANCED OPERATIONS 🔬       │\n");
    printf("├─────────────────────────────────────┤\n");
    printf("│ 1. 🔢 Power          (2^3 = 8)     │\n");
    printf("│ 2. √  Square Root    (√9 = 3)      │\n");
    printf("│ 3. 📊 Logarithm      (ln e = 1)    │\n");
    printf("│ 4. 📐 Sine           (sin π/2 = 1) │\n");
    printf("│ 5. 📐 Cosine         (cos 0 = 1)   │\n");
    printf("│ 6. 📐 Tangent        (tan π/4 = 1) │\n");
    printf("│ 7. 🔙 Back to Main Menu             │\n");
    printf("└─────────────────────────────────────┘\n");
    printf("⚠️  Trig functions use RADIANS (π ≈ 3.14159)\n");
    printf("💡 To convert degrees: multiply by π/180\n");
    printf("Enter your choice (1-7): ");
    
    int choice;
    if (get_user_choice(&choice) != INPUT_SUCCESS) {
        printf("🤔 Please enter a valid number (1-7).\n\n");
        return;
    }
    
    if (choice == 7) {
        printf("🔙 Going back to main menu...\n");
        return; // Back to main menu
    }
    
    if (choice < 1 || choice > 6) {
        printf("🚫 Please choose between 1-6 for operations, or 7 to go back.\n\n");
        return;
    }
    
    double num1, num2 = 0.0, result;
    calc_result_t calc_status;
    
    // Get input based on operation type
    if (choice == 1) { // Power operation needs two operands
        printf("\n🔢 Power calculation (base^exponent):\n");
        if (get_double_input("Enter base number: ", &num1) != INPUT_SUCCESS ||
            get_double_input("Enter exponent: ", &num2) != INPUT_SUCCESS) {
            printf("❌ Please enter valid numbers.\n");
            printf("💡 Example: 2^3 means base=2, exponent=3\n\n");
            return;
        }
        calc_status = calculate_power(num1, num2, &result);
    } else { // Other operations need one operand
        const char* prompts[] = {"", "", 
            "Enter number for √: ", 
            "Enter number for ln(): ",
            "Enter angle in radians: ", 
            "Enter angle in radians: ", 
            "Enter angle in radians: "};
        
        printf("\n🔢 %s calculation:\n", 
               (const char*[]){"", "", "Square Root", "Natural Log", "Sine", "Cosine", "Tangent"}[choice]);
        
        if (get_double_input(prompts[choice], &num1) != INPUT_SUCCESS) {
            printf("❌ Please enter a valid number.\n");
            if (choice >= 4) printf("💡 Remember: angles should be in radians!\n");
            printf("\n");
            return;
        }
        
        switch (choice) {
            case 2:
                calc_status = calculate_sqrt(num1, &result);
                break;
            case 3:
                calc_status = calculate_log(num1, &result);
                break;
            case 4:
                calc_status = calculate_sin(num1, &result);
                break;
            case 5:
                calc_status = calculate_cos(num1, &result);
                break;
            case 6:
                calc_status = calculate_tan(num1, &result);
                break;
            default:
                printf("Internal error: Invalid operation\n\n");
                return;
        }
    }
    
    // Display result
    if (calc_status == CALC_SUCCESS) {
        const char* operations[] = {"", "Power", "Square Root", "Natural Logarithm", 
                                   "Sine", "Cosine", "Tangent"};
        printf("\n🎉 %s Result: %.6g\n", operations[choice], result);
        printf("✅ Calculation saved to history!\n");
        add_advanced_to_history(num1, num2, result, choice);
    } else {
        handle_calculation_error(calc_status);
    }
    
    printf("\n💡 Want to try another advanced operation?\n");
    printf("Press Enter to continue...");
    getchar();
    printf("\n");
}

/**
 * @brief Get validated double input from user
 * @param[in] prompt The prompt message to display
 * @param[out] value Pointer to store the validated double value
 * @return INPUT_SUCCESS if valid, INPUT_ERROR if invalid
 */
input_result_t get_double_input(const char *prompt, double *value) {
    if (!prompt || !value) {
        return INPUT_ERROR;
    }
    
    char buffer[MAX_INPUT_LENGTH];
    char *endptr;
    
    printf("%s", prompt);
    
    if (!fgets(buffer, sizeof(buffer), stdin)) {
        return INPUT_ERROR;
    }
    
    // Remove newline if present
    buffer[strcspn(buffer, "\n")] = '\0';
    
    // Convert to double with error checking
    errno = 0;
    *value = strtod(buffer, &endptr);
    
    if (errno != 0 || *endptr != '\0') {
        return INPUT_ERROR;
    }
    
    // Check for infinity or NaN
    if (!isfinite(*value)) {
        return INPUT_ERROR;
    }
    
    return INPUT_SUCCESS;
}

// /**
//  * @brief Handle and display calculation errors
//  * @param[in] error The calculation error code
//  */
// void handle_calculation_error(calc_result_t error) {
//     printf("\n❌ Oops! Something went wrong:\n");
//     switch (error) {
//         case CALC_DIVISION_BY_ZERO:
//             printf("   🚫 Division by zero is not allowed!\n");
//             printf("   💡 Try a different number (not zero) for division.\n");
//             break;
//         case CALC_DOMAIN_ERROR:
//             printf("   🔍 The number you entered is outside the valid range.\n");
//             printf("   💡 Examples: √(-4) won't work, try √4 instead.\n");
//             printf("              ln(-2) won't work, try ln(2) instead.\n");
//             break;
//         case CALC_OVERFLOW:
//             printf("   📈 The result is too big to calculate!\n");
//             printf("   💡 Try smaller numbers. Large powers can get huge quickly.\n");
//             break;
//         case CALC_UNDERFLOW:
//             printf("   📉 The result is too small to represent accurately.\n");
//             printf("   💡 This usually happens with very tiny decimal results.\n");
//             break;
//         case CALC_INVALID_INPUT:
//             printf("   📝 Please check your input format.\n");
//             printf("   💡 Use numbers like: 5, 3.14, -2.5, 1.23e-4\n");
//             break;
//         default:
//             printf("   🤷 An unexpected error occurred.\n");
//             printf("   💡 Please try again with different numbers.\n");
//             break;
//     }
// }

/**
 * @brief Display application help information
 * @details Provides comprehensive usage instructions and tips
 */
void display_help(void) {
    printf("\n┌─────────────────────────────────────────────────────┐\n");
    printf("│                🎓 HELP GUIDE 🎓                     │\n");
    printf("├─────────────────────────────────────────────────────┤\n");
    printf("│                                                     │\n");
    printf("│ 🔢 HOW TO ENTER NUMBERS:                            │\n");
    printf("│  • Whole numbers: 42, -17, 0                       │\n");
    printf("│  • Decimals: 3.14159, -2.5, 0.001                  │\n");
    printf("│  • Scientific: 1.23e-4, 6.02e23, 2.5E10            │\n");
    printf("│                                                     │\n");
    printf("│ ➕ BASIC OPERATIONS - Perfect for everyday math:    │\n");
    printf("│  • Addition: 5 + 3 = 8                             │\n");
    printf("│  • Subtraction: 10 - 4 = 6                         │\n");
    printf("│  • Multiplication: 7 × 8 = 56                      │\n");
    printf("│  • Division: 15 ÷ 3 = 5                             │\n");
    printf("│                                                     │\n");
    printf("│ 🔬 ADVANCED OPERATIONS - For scientific calculations:│\n");
    printf("│  • Power: 2^3 = 8, 10^2 = 100                      │\n");
    printf("│  • Square Root: √9 = 3, √16 = 4                    │\n");
    printf("│  • Natural Log: ln(e) = 1, ln(1) = 0               │\n");
    printf("│                                                     │\n");
    printf("│ 📐 TRIGONOMETRY - Remember to use RADIANS:          │\n");
    printf("│  • sin(π/2) = 1, cos(0) = 1, tan(π/4) = 1          │\n");
    printf("│  • Convert degrees to radians: degrees × π/180     │\n");
    printf("│  • Common angles: 30° = π/6, 45° = π/4, 90° = π/2  │\n");
    printf("│                                                     │\n");
    printf("│ 📜 FEATURES YOU'LL LOVE:                            │\n");
    printf("│  • ✅ All calculations automatically saved          │\n");
    printf("│  • 🔍 View history anytime from main menu          │\n");
    printf("│  • 🛡️  Smart error handling with helpful tips      │\n");
    printf("│  • 🎯 High precision for accurate results          │\n");
    printf("│                                                     │\n");
    printf("│ 💡 QUICK EXAMPLES TO GET YOU STARTED:              │\n");
    printf("│  • Calculate tip: 25.50 × 0.15 = 3.825             │\n");
    printf("│  • Circle area: π × r² (use 3.14159 for π)         │\n");
    printf("│  • Compound interest: P × (1 + r)^t                │\n");
    printf("│                                                     │\n");
    printf("│ 🆘 NEED MORE HELP?                                  │\n");
    printf("│  • Start with Basic Operations (option 1)          │\n");
    printf("│  • Try simple numbers first: 2 + 3                 │\n");
    printf("│  • Check your calculation history (option 3)       │\n");
    printf("│  • Press Ctrl+C to exit anytime                    │\n");
    printf("│                                                     │\n");
    printf("└─────────────────────────────────────────────────────┘\n\n");
    
    printf("🎯 Ready to calculate? Press Enter to return to main menu!");
    getchar();
    printf("\n");
}