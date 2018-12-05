#include <stdio.h>

float add(const int a, const int b)
{
    return a + b;
}

float multiply(const float a, const float b)
{
    return a * b;
}

float calculate(int a, int b, char operator)
{
    switch (operator)
    {
    case '+':
        return add(a, b);
    case '-':
        return add(a, -b);
    case '*':
        return multiply(a, b);
    case '/':
        return multiply(a, (float)1 / b);
    default:
        return 0;
    }
}

int main(void)
{
    int operand1, operand2;
    char operator;

    printf("Podaj wyrażenie: \n< ");
    scanf("%d", &operand1);
    scanf("%c", &operator);
    scanf("%d", &operand2);

    if (operator== '/' && operand2 == 0)
        return -1;

    printf("> %f\n", calculate(operand1, operand2, operator));

    return 0;
}