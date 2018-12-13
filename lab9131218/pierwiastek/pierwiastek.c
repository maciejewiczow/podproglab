#include <math.h>
#include <stdio.h>

#define ACCURACY (1.e-5) // do przeprowadzania obliczeń i sprawdzenia dokładności wyniku

#define DEBUG_PRINTS 1

/**
 * Funkcja obliczająca pierwiastek danej liczby zmiennoprzecinkowej za pomocą wzoru Herona
 * @param double x - liczba pierwiastkowana
 * @returns double - wynik pierwiastkowania lub -1 w przypadku błędnych danych (x < 0)
 */
double squareRoot(double x);

int main(void)
{
    double liczba;

    for (;;) {

        printf("\nPodaj wartość liczby dodatniej (-1 kończy program):\n");
        scanf("%lf", &liczba);

        if (liczba < 0) return 0;

        double result = squareRoot(liczba);
        double refference = sqrt(liczba);

        printf("\nliczba %20.15lf, założona dokładność obliczania pierwiastka: %20.15lf\n", liczba,
            ACCURACY);
        printf("\tpierwiastek liczby: obliczony %20.15lf, dokładny %20.15lf\n", result, refference);
        printf("\tbłąd bezwzględny: %20.15lf, błąd względny: %20.15lf\n", result - refference,
            (result - refference) / refference);
    }
    return 0;
}

double squareRoot(double x)
{
    if (x < 0.0) return -1;

    double result = 1.0;
    double prev;

#if DEBUG_PRINTS
    printf("Aktualna obliczona wartość, \tbłąd względny kolejnych iteracji, \tbłąd wzgledny "
           "kwadratu\n");
#endif
    // obliczenia pierwiastka za pomocą wzoru Herona
    do {
        prev = result;
        result = 0.5 * (prev + x / prev);
#if DEBUG_PRINTS
        printf("wartość %20.15lf, \tbłąd  %20.15lf,     błąd kwadratu %20.15lf\n", result,
            fabs(result - prev) / result, fabs(result * result - x) / x);
#endif
        // sprawdzenie warunku wyjścia z pętli - błąd względny obliczania pierwiastka
    } while (fabs(result * result - x) / x > ACCURACY);

    return result;
}
