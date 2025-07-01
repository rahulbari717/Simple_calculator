// ==========================================
// FILE: menu.c
// ==========================================
/**
 * @file menu.c
 * @brief Menu subsystem implementation
 * @details Implements the user interface layer, handling menu display,
 *          user input validation, and coordination with calculator operations.
 *          Follows Apple's UI design principles for clarity and usability.
 * @author Rahul B.
 * @date 2025-07-01
 * @version 1.0.0
 */

#include "menu.h"
#include "calculator.h"
#include <stdlib.h>

// ==========================================
// MARK: - Menu Lifecycle
// ==========================================

menu_result_t menu_initialize(void) {
    // Menu subsystem is stateless, no initialization required
    return MENU_SUCCESS;
}

void menu_cleanup(void) {
    // Menu subsystem is stateless, no cleanup required
}

// ==========================================
// MARK: - Menu Display and Input
// ==========================================

menu_result_t menu_display_and_get_choice(menu_choice_t *choice) {
    if (choice == NULL) {
        return MENU_ERROR_INVALID_INPUT;
    }
    
    menu_display_main_menu();
    return menu_get_user_input(choice);
}

void menu_display_main_menu(void) {
    printf("┌─────────────────────────────────────────┐\n");
    printf("│           🧮 CALCULATOR MENU 🧮         │\n");
    printf("├─────────────────────────────────────────┤\n");
    printf("│                                         │\n");
    printf("│  1. ➕ Addition       (a + b)           │\n");
    printf("│  2. ➖ Subtraction    (a - b)           │\n");
    printf("│  3. ✖️  Multiplication (a × b)          │\n");
    printf("│  4. ➗ Division       (a ÷ b)           │\n");
    printf("│  5. %% Modulus        (a %% b)          │\n");
    printf("│  6. ^ Power          (a ^ b)            │\n");
    printf("│  7. 👋 Exit Application                 │\n");
    printf("│                                         │\n");
    printf("└─────────────────────────────────────────┘\n");
    printf("💡 Tip: Choose 1-6 for calculations, 7 to exit\n");
    printf("Enter your choice (1-7): ");
}

menu_result_t menu_get_user_input(menu_choice_t *choice) {
    if (choice == NULL) {
        return MENU_ERROR_INVALID_INPUT;
    }
    
    int input;
    if (scanf("%d", &input) != 1) {
        menu_clear_input_buffer();
        *choice = MENU_CHOICE_INVALID;
        return MENU_ERROR_INVALID_INPUT;
    }
    
    menu_clear_input_buffer();
    
    // Validate input range
    if (input < MENU_MIN_CHOICE || input > MENU_MAX_CHOICE) {
        *choice = MENU_CHOICE_INVALID;
        return MENU_ERROR_INVALID_INPUT;
    }
    
    *choice = (menu_choice_t)input;
    return MENU_SUCCESS;
}

// ==========================================
// MARK: - Calculation Handling
// ==========================================

menu_result_t menu_handle_calculation(menu_choice_t operation) {
    double operand1, operand2, result;
    calc_result_t calc_result;
    
    printf("\n");
    printf("🔢 %s Operation\n", menu_choice_to_string(operation));
    printf("────────────────────────────────\n");
    
    // Get operands from user
    if (menu_get_numeric_input("Enter first number: ", &operand1) != MENU_SUCCESS) {
        printf("❌ Invalid first number. Operation cancelled.\n");
        return MENU_ERROR_INVALID_INPUT;
    }
    
    if (menu_get_numeric_input("Enter second number: ", &operand2) != MENU_SUCCESS) {
        printf("❌ Invalid second number. Operation cancelled.\n");
        return MENU_ERROR_INVALID_INPUT;
    }
    
    // Perform calculation based on operation
    switch (operation) {
        case MENU_CHOICE_ADD:
            calc_result = calculator_add(operand1, operand2, &result);
            break;
        case MENU_CHOICE_SUBTRACT:
            calc_result = calculator_subtract(operand1, operand2, &result);
            break;
        case MENU_CHOICE_MULTIPLY:
            calc_result = calculator_multiply(operand1, operand2, &result);
            break;
        case MENU_CHOICE_DIVIDE:
            calc_result = calculator_divide(operand1, operand2, &result);
            break;
        case MENU_CHOICE_MODULUS:
            calc_result = calculator_modulus((int)operand1, (int)operand2, &result);
            break;
        case MENU_CHOICE_POWER:
            calc_result = calculator_power(operand1, operand2, &result);
            break;
        default:
            printf("❌ Internal Error: Invalid operation\n");
            return MENU_ERROR_INVALID_INPUT;
    }
    
    // Display result
    if (calc_result == CALC_SUCCESS) {
        printf("\n|━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━|");
        printf("\n| 🎉 Result: ");
        if (operation == MENU_CHOICE_MODULUS) {
            printf("%.0f %s %.0f = %.0f\n", operand1, 
                   (operation == MENU_CHOICE_ADD) ? "+" :
                   (operation == MENU_CHOICE_SUBTRACT) ? "-" :
                   (operation == MENU_CHOICE_MULTIPLY) ? "×" :
                   (operation == MENU_CHOICE_DIVIDE) ? "÷" :
                   (operation == MENU_CHOICE_MODULUS) ? "%" : "^",
                   operand2, result);
        } else {
            printf("%.6g %s %.6g = %.6g\n", operand1,
                   (operation == MENU_CHOICE_ADD) ? "+" :
                   (operation == MENU_CHOICE_SUBTRACT) ? "-" :
                   (operation == MENU_CHOICE_MULTIPLY) ? "×" :
                   (operation == MENU_CHOICE_DIVIDE) ? "÷" :
                   (operation == MENU_CHOICE_POWER) ? "^" : "?",
                   operand2, result);
        }
        printf("| ✅ Calculation completed successfully!      ");
        printf("\n|━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━|");
    } else {
        // Handle calculation errors
        switch (calc_result) {
            case CALC_ERROR_DIVISION_BY_ZERO:
                printf("❌ Error: Division by zero is not allowed!\n");
                break;
            case CALC_ERROR_DOMAIN:
                printf("❌ Error: Invalid domain for this operation!\n");
                break;
            case CALC_ERROR_OVERFLOW:
                printf("❌ Error: Result too large to represent!\n");
                break;
            case CALC_ERROR_UNDERFLOW:
                printf("❌ Error: Result too small to represent!\n");
                break;
            default:
                printf("❌ Error: Calculation failed with error code %d\n", calc_result);
                break;
        }
    }
    
    return MENU_SUCCESS;
}

// ==========================================
// MARK: - Utility Functions
// ==========================================

menu_result_t menu_get_numeric_input(const char *prompt, double *value) {
    if (prompt == NULL || value == NULL) {
        return MENU_ERROR_INVALID_INPUT;
    }
    
    printf("%s", prompt);
    
    if (scanf("%lf", value) != 1) {
        menu_clear_input_buffer();
        return MENU_ERROR_INVALID_INPUT;
    }
    
    menu_clear_input_buffer();
    return MENU_SUCCESS;
}

void menu_clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // Clear buffer
    }
}

const char* menu_choice_to_string(menu_choice_t choice) {
    switch (choice) {
        case MENU_CHOICE_ADD:      return "Addition";
        case MENU_CHOICE_SUBTRACT: return "Subtraction";
        case MENU_CHOICE_MULTIPLY: return "Multiplication";
        case MENU_CHOICE_DIVIDE:   return "Division";
        case MENU_CHOICE_MODULUS:  return "Modulus";
        case MENU_CHOICE_POWER:    return "Power";
        case MENU_CHOICE_EXIT:     return "Exit";
        default:                   return "Unknown";
    }
}