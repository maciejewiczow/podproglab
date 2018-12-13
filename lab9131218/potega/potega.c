#include <limits.h>
#include <stdio.h>

// funkcja oblicza potęgę całkowitą liczby całkowitej
int potega_int(int m, int n);

void main(void)
{
    int i;
    for (i = 0; i < 10; i++) {
        printf("i = %d \t2^i = %d \t(-3)^i = %d\n", i, potega_int(2, i), potega_int(-3, i));
    }
    return;
}

// funkcja oblicza potęgę całkowitą liczby całkowitej
int potega_int(   // funkcja zwraca wartość potegi podstawa^wykładnik
    int podstawa, // [in]: zadana podstawa
    int wykladnik // [in]: zadany wykładnik
)
{
    int potega = 1;
    for (int i = 1; i <= wykladnik; i++) {
        potega *= podstawa;
    }
    return potega;
}

// modyfikacje power_int_1 - sprawdzanie w trakcie obliczeń czy obliczane wartości
//                           nie przekraczają zakresu liczb całkowitych INT_MAX
//                           (zdefiniowane w pliku limits.h)

// Przypadek schematu Hornera dla wielomianu 4 stopnia
// a[0] + a[1]*x + a[2]*x^2 + a[3]*x^3 + a[4]*x^4:
//
// a[0] + x*( a[1] + x*( a[2] + x*( a[3] + x*a[4]) ) )
//
