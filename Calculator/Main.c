#include <stdio.h>

int main()
{
    double a, b;
    char op;
    printf("Enter the first number: ");
    scanf("%lf", &a);
    printf("Enter the operator: ");
    scanf(" %c", &op);
    printf("Enter the second number: ");
    scanf("%lf", &b);
    switch (op)
    {
    case '+':
        printf("The sum is %lf\n", a + b);
        break;
    case '-':
        printf("The difference is %lf\n", a - b);
        break;
    case '*':
        printf("The product is %lf\n", a * b);
        break;
    case '/':
        printf("The quotient is %lf\n", a / b);
        break;
    default:
        printf("Invalid operator\n");
    }
    return 0;
}
