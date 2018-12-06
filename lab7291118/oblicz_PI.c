#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//#define SCALAR double
#define SCALAR float

#define SMALL_NUMBER 1.e-20

#ifndef M_PI // standardy C99 i C11 nie wymagają definiowania stałej M_PI
#    define M_PI (3.14159265358979323846)
#endif

#define DOKLADNOSC 0.001
#define MAX_LICZBA_WYRAZOW 111111

/**
 * program obliczania przybliżenia PI za pomocą wzoru Leibniza
 * PI = 4 * ( 1 - 1/3 + 1/5 - 1/7 + 1/9 - 1/11 + itd. )
 */
void main(void)
{
    int max_liczba_wyrazow = MAX_LICZBA_WYRAZOW;
    // printf("Podaj maksymalną liczbę wyrazów do obliczenia przybliżenia PI\n");
    // scanf("%d", &max_liczba_wyrazow);

    SCALAR dokladnosc = DOKLADNOSC;
    printf("Podaj dokładność obliczenia przybliżenia PI\n");
    if (sizeof(SCALAR) == 4) { // czterobajtowe liczby zmiennoprzecinkowe -> float
        scanf("%f", &dokladnosc);
    }
    else {
        scanf("%lf", &dokladnosc);
    }

    // wzór: PI/4 = 1 - 1/3 + 1/5 - 1/7 + 1/9 itd. itp.
    SCALAR suma_plus = 0.0;
    SCALAR suma_minus = 0.0;

    int i = 0;
    int j = 1;
    // alternatywa: for(i=0; i< (max_liczba_wyrazow/2.0) + 1; i++){
    do {

        j = 1 + 4 * i; // alternatywa: usunąć

        suma_plus += 1.0 / j;
        suma_minus += 1.0 / (j + 2.0);

        i++; // alternatywa: j += 4;

        printf("PI obliczone: %20.15lf, aktualna poprawka: %20.15lf\n",
            4 * (suma_plus - suma_minus), 4.0 / j - 4.0 / (j + 2.0));

        // alternatywa: i = (j-1)/4;
        if (i >= ceil(max_liczba_wyrazow / 2.0)) {
            printf("Przekroczona maksymalna liczba wyrazów %d", max_liczba_wyrazow);
            printf(" przed osiagnięciem założonej dokładności - break\n");
            break;
        }

        // niska dokładność float - znany przykład (a+b)-a = 0 zamiast b
        //    if(sizeof(SCALAR)==4){ // czterobajtowe liczby zmiennoprzecinkowe -> float

        //      SCALAR temp_PI = 4*(suma_plus-suma_minus);
        //	SCALAR temp_poprawka = (4.0/j-4.0/(j+2.0)); // zawsze dodatnia
        //	if( (temp_PI + temp_poprawka) - temp_PI < SMALL_NUMBER ){

        //	  printf("Dodatkowe wyrazy przestają zmieniać wynik! Przerwanie obliczeń!\n");
        //	  break;

        //	}

        //      }


        //} while(i<ceil(max_liczba_wyrazow/2.0));
        //} while(i<ceil(max_liczba_wyrazow/2.0) && 4.0/j > dokladnosc);
    } while ((4.0 / j - 4.0 / (j + 2.0)) > dokladnosc);

    printf("PI obliczone: %20.15lf, PI z biblioteki matematycznej: %20.15lf\n",
        4 * (suma_plus - suma_minus), M_PI);
    printf("Założona dokładność: %20.15lf, rzeczywisty błąd: %20.15lf\n", dokladnosc,
        fabs(4 * (suma_plus - suma_minus) - M_PI));
}


// całka
/*
 h   = 1.0 / (SCALAR) n;
 sum = 0.0;
 for (i = myid + 1; i <= n; i += numprocs) {
   x = h * ((SCALAR)i - 0.5);
   sum += 4.0 / (1.0 + x*x);
 }
 mypi = h * sum;
*/
