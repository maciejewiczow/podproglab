#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#if 1
#    define SCALAR double
#    define FORMAT_IN "%lf"
#    define FORMAT_OUT "%5.20lf"
#    define EPSILON DBL_EPSILON
#else
#    define SCALAR float
#    define FORMAT_IN "%f"
#    define FORMAT_OUT "%5.20f"
#    define EPSILON FLT_EPSILON
#endif

#define ITERATION_LIMIT 1.e+8

#define DEBUG_PRINTS false

SCALAR eulerFromSeries(int n);
SCALAR eulerFromErrorTolerance(SCALAR tolerance);
bool veryClose(SCALAR, SCALAR, SCALAR);

int main(void)
{
    SCALAR precision;

    printf("Hello\nPlease tell me, how precisely should I calculate e for you:\n");
    scanf(FORMAT_IN, &precision);

    SCALAR result = eulerFromErrorTolerance(precision);
    printf("\ne ~= " FORMAT_OUT "\nError: " FORMAT_OUT, result, fabs(result - M_E));
}

SCALAR eulerFromSeries(int n)
{
    if (n == 0) return 1;

    SCALAR partial = ((SCALAR) 1.0 + ((SCALAR) 1.0) / n);
    return (sizeof(SCALAR) == 8) ? pow(partial, n) : powf(partial, n);
}

bool veryClose(SCALAR a, SCALAR b, SCALAR tolerance)
{
    return a == b || (sizeof(SCALAR) == 4) ? fabsf(a - b) < tolerance : fabs(a - b) < tolerance;
}

SCALAR eulerFromErrorTolerance(SCALAR tolerance)
{
    if (tolerance <= EPSILON) {
        printf("\nI am nothing but a mere rock, that people tricked into doing math (because they "
               "were too lazy to do it by themeselves). I can't perform computations THAT precise, "
               "sorry.\n");
        return -1;
    }

    SCALAR result;
    int n = 1;
    do {
        result = eulerFromSeries(n);

#if DEBUG_PRINTS
        printf("n: %d " FORMAT_OUT "\n", n, result);
#endif

        n++;
    } while (n < ITERATION_LIMIT && !veryClose(result, M_E, tolerance));

    printf("\nItertions: %d\n", n);

    return result;
}
