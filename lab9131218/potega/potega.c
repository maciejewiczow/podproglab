#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Funkcja oblicza wartość n-tej potgęgi liczby m
 * Jeżeli wynik w trakcie obliczeń wartość prekroczy INT_MAX, jest zwracana w momencie osiągnięcia
 * INT_MAX
 *
 * @param int m - podstawa potęgowania
 * @param int n - wykładnik
 *
 * @returns int - wynik potęgowania lub INT_MAX
 */
int potega_int(int m, int n);

/**
 * Oblicza wratość wielomianu stopnia stopien o wspolczynnikach zawartych w tablicy dla argumentu x
 *
 * @param int* wspolczynniki - tablica współczynników wielomianu
 * @param unsigned int stopien - stopien wielomianu (długosć tablicy wspolczynnikow)
 * @param int x - argument wielomianu
 *
 * @returns int - wartość wielomianu lub INT_MAX, jeżeli wartość była zbyt duża dla typu int
 */
int wartosc_wielomianu(int* wspolczynniki, unsigned int stopien, int x);

/**
 * Sprawdza, czy wynik mnożenia 2 liczb przekroczy wartość INT_MAX
 *
 * @param int a - pierwsza liczba
 * @param int b - druga liczba
 *
 * @returns bool - wartość logiczna określająca, czy nastąpi overflow czy nie
 */
bool willMultiplicationOverflowInt(int a, int b);

int main(void)
{
    for (int i = 0; i < 10; i++) {
        printf("i = %d \t2^i = %d \t(-3)^i = %d\n", i, potega_int(2, i), potega_int(-3, i));
    }

    unsigned int degree = 0;
    int* wspolcz = NULL;
    int x;

    printf("\nPodaj stopień wielomianu: ");
    scanf("%u", &degree);
    printf("\n");

    wspolcz = (int*) calloc(degree, sizeof(int));

    if (wspolcz == NULL) {
        printf("Memorry error: could not allocate memory for array");
        return -1;
    }

    for (unsigned int i = 0; i < degree; i++) {
        printf("a[%d] = ", i);
        scanf("%d", &wspolcz[i]);
    }

    printf("\nW(x) = ");
    for (unsigned int i = 0; i < degree; i++) {
        if (wspolcz[i] == 0) continue;

        int j = degree - i - 1;

        if (wspolcz[i] != 1) printf("%d", wspolcz[i]);
        if (j == 1) {
            printf("x + ");
        }
        else if (j != 0) {
            printf("x^%d + ", j);
        }
    }
    printf("\nx = ");
    scanf("%d", &x);

    int result = wartosc_wielomianu(wspolcz, degree, x);

    printf("\n");
    if (result == INT_MAX) {
        printf("Obliczona wartość była zbyt duża, aby pomieścić ją w typie int\n");
        return 0;
    }

    printf("W(%d) = %d\n", x, result);

    free(wspolcz);
    return 0;
}

bool willMultiplicationOverflowInt(int a, int b)
{
    return (a != 0 && b != 0 && (a * b) / a != b);
}

int potega_int(int podstawa, int wykladnik)
{
    int potega = 1;
    for (int i = 1; i <= wykladnik; i++) {
        if (willMultiplicationOverflowInt(potega, podstawa)) return INT_MAX;
        potega *= podstawa;
    }
    return potega;
}

int wartosc_wielomianu(int* a, unsigned int stopien, int x)
{
    if (stopien == 0) return 0;
    if (stopien == 1) return a[0];
    if (x == 0) return a[stopien - 1];

    int result = a[stopien - 1];
    for (int i = stopien - 2; i >= 0; i--) {
        if (willMultiplicationOverflowInt(x, result)) return INT_MAX;
        result = a[i] + x * result;
    }

    return result;
}

// Przypadek schematu Hornera dla wielomianu 4 stopnia
// a[0] + a[1]*x + a[2]*x^2 + a[3]*x^3 + a[4]*x^4:
//
// a[0] + x*( a[1] + x*( a[2] + x*( a[3] + x*a[4]) ) )
