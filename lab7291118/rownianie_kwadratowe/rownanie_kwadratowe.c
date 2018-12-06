#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>

#if 1
#    define SCALAR double
#    define FORMAT_OUT "%5.15lf"
#    define SMALL_NUMBER DBL_EPSILON * 1.e+1
#else
#    define SCALAR float
#    define FORMAT_OUT "%5.15f"
#    define SMALL_NUMBER FLT_EPSILON
#endif


typedef struct Cplx {
    SCALAR re;
    SCALAR im;
} Complex;
void complex_print(const Complex*);
bool complex_equals(const Complex*, const Complex*);
bool complex_isReal(const Complex*);
Complex complex_multiply(const Complex*, const Complex*);
Complex complex_add(int, ...);

typedef struct QRoots {
    int count;
    Complex x1;
    Complex x2;
} QuadraticRoots;

QuadraticRoots solveQuadraticEquation(SCALAR, SCALAR, SCALAR);
void printSolution(const QuadraticRoots*);
bool chcekSolution(SCALAR, SCALAR, SCALAR, const QuadraticRoots*);
Complex evaluateQuadratic(const Complex*, const Complex*, const Complex*, const Complex*);

bool veryClose(SCALAR, SCALAR, SCALAR);

#if 0
int main()
{
    // clang-format off
    Complex a = {.re = 1},
            b = {.re = 2},
            c = {.re = -5},
            x1 = {.re = 1.449489742783178},
            x2 = {.re = -3.449489742783178};

    Complex res1 = evaluateQuadratic(&a, &b, &c, &x1);
    Complex res2 = evaluateQuadratic(&a, &b, &c, &x2);

    printf("Res1: ");
    complex_print(&res1);
    printf("\nRes2: ");
    complex_print(&res2);
    printf("\n");
    return 0;
}
#else
int main(void)
{
    // rozwiązanie równania kwadratowego ax^2 + bx + c = 0

    printf("\nProgram rozwiązywania równania kwadratowego ax^2 + bx + c = 0\n");

    SCALAR a, b, c;
    printf("\nPodaj parametr a: ");
    scanf("%lf", &a);
    printf("Podaj parametr b: ");
    scanf("%lf", &b);
    printf("Podaj parametr c: ");
    scanf("%lf", &c);

    QuadraticRoots solution = solveQuadraticEquation(a, b, c);

    // debug print
    printf("\nSolution:\ncount = %d\nx1 = ", solution.count);
    complex_print(&solution.x1);
    printf("\nx2 = ");
    complex_print(&solution.x2);
    printf("\n\n");

    printSolution(&solution);

    printf("\n[Checker] Solution is ");
    if (!chcekSolution(a, b, c, &solution)) {
        printf("wrong!\n");
        return -1;
    }
    printf("right\n");
    return 0;
}
#endif

void complex_print(const Complex* this)
{
    char sign = (this->im >= 0) ? '+' : '-';
    printf(FORMAT_OUT" %c "FORMAT_OUT"i", this->re, sign, fabs(this->im));
}

bool complex_equals(const Complex* a, const Complex* b)
{
    return a->re == b->re && a->im == b->im;
}

bool complex_isReal(const Complex* this)
{
    return this->im == 0;
}

Complex complex_add(int num, ...)
{
    SCALAR re = 0, im = 0;
    va_list args;

    va_start(args, num);

    for (int i = 0; i < num; i++) {
        Complex z = va_arg(args, Complex);
        re += z.re;
        im += z.im;
    }

    va_end(args);

    return (Complex){
        .re = re,
        .im = im,
    };
}

Complex complex_multiply(const Complex* a, const Complex* b)
{
    // clang-format off
    return (Complex) {
        .re = a->re*b->re - a->im*b->im,
        .im = a->re*b->im + a->im*b->re,
    };
    // clang-format on
}

bool veryClose(SCALAR a, SCALAR b, SCALAR tolerance)
{
    return a == b || fabs(a - b) < tolerance;
}

QuadraticRoots solveQuadraticEquation(SCALAR a, SCALAR b, SCALAR c)
{
    bool aCloseToZero = veryClose(a, 0, SMALL_NUMBER), bCloseToZero = veryClose(b, 0, SMALL_NUMBER),
         cCloseToZero = veryClose(c, 0, SMALL_NUMBER);

    if (aCloseToZero && bCloseToZero && cCloseToZero) {
        QuadraticRoots result = {.count = INT_MAX};
        return result;
    }

    if (aCloseToZero && bCloseToZero) {
        QuadraticRoots result = {.count = 0};
        return result;
    }

    if (aCloseToZero) {
        // clang-format off
        QuadraticRoots result = {
            .count = 1,
            .x1 = {.re = -c / b,}
        };
        // clang-format on

        return result;
    }

    SCALAR delta;
    delta = b * b - 4 * a * c;
    if (delta < 0) {

        SCALAR deltaSqrt = sqrt(-delta);

        // clang-format off
        QuadraticRoots result = {
            .count = 2,
            .x1 = {
                .re = -b/2*a,
                .im = deltaSqrt/2*a
            },
            .x2 = {
                .re = -b/2*a,
                .im = -deltaSqrt/2*a
            }
        };
        // clang-format on
        return result;
    }
    if (delta == 0) {
        // clang-format off
        QuadraticRoots result = {
            .count = 2,
            .x1 = {.re = -b/2*a},
            .x2 = result.x1
        };
        // clang-format on
        return result;
    }

    SCALAR deltaSqrt = sqrt(delta);

    // clang-format off
    QuadraticRoots result = {
        .count = 2,
        .x1 = {.re = (-b + deltaSqrt)/2*a},
        .x2 = {.re = (-b - deltaSqrt)/2*a}
    };
    // clang-format on
    return result;
}

void printSolution(const QuadraticRoots* solution)
{
    if (!(solution->count == 2)) {
        printf("Równanie liniowe - ");

        switch (solution->count) {
            case 0:
                printf("linia pozioma y =/= 0 -> brak miejsc zerowych\n");
                return;
            case 1:
                printf("linia ukośna -> miejsce zerowe w x = " FORMAT_OUT "\n", solution->x1.re);
                return;
            case INT_MAX:
                printf("linia pozioma y = 0 -> nieskończenie wiele miejsc zerowych\n");
                return;
        }
    }

    printf("Równanie kwadratowe - ");

    if (complex_equals(&solution->x1, &solution->x2)) {
        printf("jeden pierwiastek rzeczywisty w x0 = " FORMAT_OUT "\n", solution->x1.re);
        return;
    }

    printf("dwa pierwiastki ");
    if (complex_isReal(&solution->x1) && complex_isReal(&solution->x2)) {
        printf("rzeczywiste:\nx1 = " FORMAT_OUT "\nx2 = " FORMAT_OUT "\n", solution->x1.re,
            solution->x2.re);
        return;
    }

    printf("zespolone:\n");


    printf("x1 = ");
    complex_print(&solution->x1);

    printf("\nx2 = ");
    complex_print(&solution->x2);
    printf("\n");

    return;
}

Complex evaluateQuadratic(const Complex* a, const Complex* b, const Complex* c, const Complex* x)
{
    Complex xSquared = complex_multiply(x, x);
    Complex axSquared = complex_multiply(a, &xSquared);
    Complex bx = complex_multiply(b, x);

    return complex_add(3, axSquared, bx, *c);
}

bool chcekSolution(SCALAR realA, SCALAR realB, SCALAR realC, const QuadraticRoots* solution)
{
    bool aCloseToZero = veryClose(realA, 0, SMALL_NUMBER),
         bCloseToZero = veryClose(realB, 0, SMALL_NUMBER),
         cCloseToZero = veryClose(realC, 0, SMALL_NUMBER);

    // clang-format off
    Complex a = {.re = realA, .im = 0},
            b = {.re = realB, .im = 0},
            c = {.re = realC, .im = 0};
    // clang-format on

    if (solution->count == 0) return aCloseToZero && bCloseToZero && !cCloseToZero;
    if (solution->count == 1) return veryClose(realB * solution->x1.re + realC, 0, SMALL_NUMBER);
    if (solution->count == INT_MAX) return aCloseToZero && bCloseToZero && cCloseToZero;

    Complex x1 = solution->x1, x2 = solution->x2;

    Complex result1 = evaluateQuadratic(&a, &b, &c, &x1);
    Complex result2 = evaluateQuadratic(&a, &b, &c, &x2);

    return veryClose(result1.re, 0, SMALL_NUMBER) && veryClose(result1.im, 0, SMALL_NUMBER) &&
           veryClose(result2.re, 0, SMALL_NUMBER) && veryClose(result2.im, 0, SMALL_NUMBER);
}
