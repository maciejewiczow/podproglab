#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#define CALCULATION_PRECISION 13
#define DEBUG_PRINTS false

double findApproximateFibbonaciBaseFor(double targetNumber);
double fib(double f1, int n);
int findLastFibNLessOrEqlTo(double number);
bool almostEqual(double a, double b, double tolerance);

int main()
{
    printf("Podaj liczbę, która ma się pojawić w ciągu: ");
    double target;
    scanf("%lf", &target);
    double result = findApproximateFibbonaciBaseFor(target);
    printf("\nBaza ciągu to %10.30lf, fib(%lf, n) = %10.30lf\n", result, result,
        fib(result, findLastFibNLessOrEqlTo(target)));
    return 0;
}

double fib(double f1, int n)
{
    double a = 0, b = f1, temp;

    for (int i = 2; i <= n; i++) {
        temp = a + b;
        a = b;
        b = temp;
    }

    return b;
}

int findLastFibNLessOrEqlTo(double number)
{
    if (number == 0) return 0;
    int n = 1;

    while (fib(1, n) <= number) {
        n++;
    }

    return n - 1;
}

bool almostEqual(double a, double b, double tolerance)
{
    return a == b || fabs(a - b) <= tolerance;
}

double findApproximateFibbonaciBaseFor(double targetNumber)
{
    int targetN = findLastFibNLessOrEqlTo(targetNumber);

    double df1, f1 = df1 = 1;

    double tolerance = pow(10, -CALCULATION_PRECISION);

    while (!almostEqual(fib(f1, targetN), targetNumber, tolerance)) {
        df1 *= 0.1;
        double currentFib;
        do {
            if (f1 + df1 == f1) {
                printf("Calculation precision limit reached. Futher approximation impossible due "
                       "to floating point errors\n");
                return f1 + df1;
            }
            f1 += df1;
            currentFib = fib(f1, targetN);

#if DEBUG_PRINTS
            printf("%5.30lf    %5.30lf    %5.30lf\n", currentFib, f1, df1);
#endif
        } while (currentFib < targetNumber);

        f1 -= df1;
    }

    f1 += df1;

    return f1;
}
