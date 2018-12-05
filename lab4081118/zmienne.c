#include <stdio.h> // USES

#define JednaTrzecia (1.0 / 3.0)        // uwaga na odczyt przy podstawieniu (nawiasy)
#define JednaTrzeciaFloat (1.0f / 3.0f) // wszelkie stałe liczby ("magic numbers")
// najlepiej zebrać w jedno miejsce kodu i nadac im symboliczne nazwy
// kompilator w pierwszej fazie działania zastąpi wszystkie wystąpienia

// zwrot kodu błędu lub sukcesu (0)
int main(void)
{

    // definicje
    int n; // nazwy zmiennych - znaczące, niekoniecznie krótkie, z dużymi i małymi literami
    char znak_do_testowania;

    // inicjowanie
    n = 1 / 3;                // instrukcja przypisania - stałe liczbowe i podstawowe operacje
    znak_do_testowania = 'a'; // stała znakowa

    // definicja z inicjowaniem
    float f = 1.0 / 3.0;  // stałe - magic numbers?
    double d = 1.0 / 3.0; // zapis
    //d = f;

    // możliwe notacje dla liczb zmiennoprzecinkowych
    printf("liczby i znaki: znak = %c, n = %7d, f = %20.15f, d = %20.15lf\n",
           znak_do_testowania, n, f, d);

    // Operatory oraz niejawne i jawne konwersje typów
    d = 1111 + 1000 * n; // d = (double) n;
    n = f + 2.5;         // n = (int) f;
    f = n / 3;           // (double) n / 3;, n / 3.0, (double) n/3
    printf("\nNiejawne i jawne konwersje typów:\n");
    printf("liczby i znaki: n = %d, f = %f, d = %lf lub d = %le\n", n, f, d, d);

    // Precyzja stałych i zmiennych
    d = JednaTrzecia * 3.0;
    double e = JednaTrzeciaFloat * 3.0;
    float g = JednaTrzeciaFloat * 3.0f;
    printf("\nPrecyzja stałych i niejawne konwersje:\n");
    printf("\td = %20.15lf; e = %20.15lf, g = %20.15lf\n",
           d, e, g);

    // operatory i ich priorytety - programowanie zaawansowane a programowanie bezpieczne
    double h;
    h = f + d; // f++d;? f+++d;? (f+d; f++;) (++d;f+d) - nawiasy!
    printf("\nPriorytety operatorów:\n");
    printf("\td = %20.15lf; f = %20.15lf, h = %20.15lf\n",
           d, f, h);

    // operatory i ich priorytety
    // x = a++;  x = ++a;
    n = 1574;
    int m = n % 7;
    int o = n / 7;
    printf("\nn = %d, n/7 = %d, n%7 = %d, n = (n/7)*7 + (n%7) = %d\n",
           n, o, m, o * 7 + m);

    // wartość logiczna wyrażeń
    printf("\nWartość logiczna wyrażenia: %d<%d wynosi %d\n", n, m, n < m);
    printf("\nWartość logiczna wyrażenia: %d<%d lub %d>%d wynosi %d\n", n, m, n, m, (n < m) || (n > m));

    // obsługa błędów - temat rzeka
    return (0);
}
