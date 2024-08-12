#include <stdio.h>

int main() {
    int a, b;
    char op;
    printf("Enter the first number: ");
    scanf("%d", &a);
    printf("Enter the operator: ");
    scanf(" %c", &op);
    printf("Enter the second number: ");
    scanf("%d", &b);
    switch(op) {
        case '+':
            printf("The sum is %d\n", a + b);
            break;
        case '-':
            printf("The difference is %d\n", a - b);
            break;
        case '*':
            printf("The product is %d\n", a * b);
            break;
        case '/':
            printf("The quotient is %d\n", a / b);
            break;
        default:
            printf("Invalid operator\n");
    }
    return 0;
}
