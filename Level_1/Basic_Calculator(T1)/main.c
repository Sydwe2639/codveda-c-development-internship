/*
 * Level 1 (Basic) - Task 1: Basic Calculator
 *
 * Description: A simple calculator that performs addition, subtraction,
 * multiplication, and division, with proper handling of division by zero.

 */

#include <stdio.h>

int main(void) {
    double num1, num2, result;
    char op;
    int validInput = 1;

    printf("===== Simple Calculator =====\n");
    printf("Enter expression in the form: num1 operator num2\n");
    printf("Operators supported: + - * /\n");
    printf("Example: 12 + 5\n\n");

    if (scanf("%lf %c %lf", &num1, &op, &num2) != 3) {
        printf("Invalid input format. Please enter: number operator number\n");
        return 1;
    }

    switch (op) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            if (num2 == 0) {
                printf("Error: Division by zero is not allowed.\n");
                validInput = 0;
                result = 0;
            } else {
                result = num1 / num2;
            }
            break;
        default:
            printf("Error: Unsupported operator '%c'. Use one of + - * /\n", op);
            validInput = 0;
            result = 0;
    }

    if (validInput) {
        printf("Result: %.2lf %c %.2lf = %.4lf\n", num1, op, num2, result);
    }

    return 0;
}
