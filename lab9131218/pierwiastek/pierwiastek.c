#include <math.h>
#include <stdio.h>

#define ACCURACY (1.e-5) // do przeprowadzania obliczeń i sprawdzenia dokładności wyniku

void main(void)
{

    double liczba;

    for (;;) {

        printf("\nPodaj wartość liczby dodatniej (-1 kończy program):\n");
        scanf("%lf", &liczba);

        if (liczba < 0.0) break;

        double pierwiastek = 1.0;
        double temp;
        // obliczenia pierwiastka za pomocą wzoru Herona
        do {
            temp = pierwiastek;
            pierwiastek = 0.5 * (temp + liczba / temp);

            // sprawdzenie warunku wyjścia z pętli - błąd względny obliczania pierwiastka
        } while (fabs(pierwiastek * pierwiastek - liczba) / liczba > ACCURACY);

        printf("\nliczba %20.15lf, założona dokładność obliczania pierwiastka: %20.15lf\n", liczba,
            ACCURACY);
        printf("\tpierwiastek liczby: obliczony %20.15lf, dokładny %20.15lf\n", pierwiastek,
            sqrt(liczba));
        printf("\tbłąd bezwzględny: %20.15lf, błąd względny: %20.15lf\n",
            pierwiastek - sqrt(liczba), (pierwiastek - sqrt(liczba)) / sqrt(liczba));
    }
}

// definicja funkcji + komentarze (z komentarzy można tworzyć dokumentację):

// funkcja oblicz_pierwiastek oblicza pierwiastek za pomocą wzoru Herona
//               dla dowolnej liczby podwójnej precyzji większej od zera
// wariant 1. funkcja zakłada, że argument jest nie mniejszy niż zero
// wariant 2. dla liczb mniejszych od zera funkcja zwraca kod błędu: -1
//   implementacja w kodzie, np.
//  if(arg<0){
//    // obsługa błędu wejścia, np.
//    return(-1.0); // wyjaśnienie w dokumentacji
//  }

// wydruki kontrolne do sprawdzenia działania funkcji:

//  printf("aktualna obliczona wartość, \tbłąd względny kolejnych iteracji, \tbłąd wzgledny
//  kwadratu\n");
//
// do{ ....
//
//    printf("wartość %20.15lf, \tbłąd  %20.15lf,     błąd kwadratu %20.15lf\n",
//	   pierwiastek, fabs(pierwiastek - temp)/pierwiastek,
//	   fabs(pierwiastek*pierwiastek - arg)/arg);
//
//    ....}
