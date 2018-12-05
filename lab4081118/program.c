#include <stdio.h>
#include <math.h>

double calculateEulerDouble(int n)
{
    return pow(1.0 + (1.0 / n), n);
}

float calculateEulerFloat(int n)
{
    return powf(1.0f + (1.0f / n), n);
}

void someFunction(int a)
{
    printf("%d\n", a);
}

int main(void)
{
    int a = 1;
    int b = 2;

    printf("Braces used to force precendence of operaitions: \n");
    printf("a+++b = %d\n", a++ + b);
    printf("a+(++b) = %d\n\n", a + (++b));

    double d = 2.0 / 9.0;
    float e = 2.0f / 9.0f;

    printf("Double vs Float precision: \n2/9 as double: %1.55g \n2/9 as float: %1.55f \n", d, e);

    double f = 1.02344884939;

    printf("\nExplicit type conversion: casting double to int - %1.10g -> %d\n", f, (int)f);
    printf("Implicit type conversion: passing double to function argument declared as int: \n");
    printf("void someFunction(int) \n");
    printf("f = %g\n", f);
    printf("someFunction(f): ");
    someFunction(f);

    printf("\nCalculating Euler number using float and double types in calculation: \n");
    printf("Series element number   double value    float value     error compared to math.h E value: dobule    float\n");

    for (int n = 1; n <= 300; n += 10)
    {
        float ef = calculateEulerFloat(n);
        double ed = calculateEulerDouble(n);
        printf("%4d:    %30.55f    %30.55f      %30.20f    %30.20f\n", n, ed, ef, fabs(M_E - ed), fabs(M_E - ef));
    }

    return 0;
}