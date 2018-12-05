#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define SCALAR double
//#define SCALAR float

const double SMALL_NUMBER = 1.e-20;

typedef struct
{
  double re;
  double im;
} complex;

void solveQuadraticEquation(SCALAR, SCALAR, SCALAR);
char *complexToString(complex);

int main(void)
{
  // rozwiązanie równania kwadratowego ax^2 + bx + c = 0

  printf("\nProgram rozwiązywania równania kwadratowego ax^2 + bx + c = 0\n");

  SCALAR a, b, c;
  // rozważania o kontrakcie... (czy uwzględnia skończoną precyzję?)
  // input - uodpornianie na błędy wczytywania danych
  printf("\nPodaj parametr a: ");
  scanf("%lf", &a);
  printf("Podaj parametr b: ");
  scanf("%lf", &b);
  printf("Podaj parametr c: ");
  scanf("%lf", &c);

  solveQuadraticEquation(a, b, c);

  return (0);
}

char *complexToString(complex z)
{
  char *result;
  char sign = (z.im > 0) ? '+' : '-';
  sprintf(&result, "%f %c %fi", z.re, sign, z.im);
  return result;
}

void solveQuadraticEquation(const SCALAR a, const SCALAR b, const SCALAR c)
{
  if (fabs(a) < SMALL_NUMBER && fabs(b) < SMALL_NUMBER)
  {
    printf("Błędne dane: a i b równe 0 (zbyt bliskie 0). Przerwanie programu.\n");

    return;
  }

  if (a == 0)
  {
    if (b == 0)
    {
      if (c == 0)
      {
        printf("Równanie liniowe - linia pozioma  y = 0 - nieskończenie wiele miejsc zerowych\n");
      }
      else
      {
        printf("Równanie liniowe - linia pozioma y =/= 0 - brak miejsc zerowych\n");
      }
      return;
    }

    printf("Równanie liniowe - miejsce zerowe w x = %20.15lf\n", -b / c);
    return;
  }

  SCALAR delta;
  delta = b * b - 4 * a * c;
  if (delta < 0)
  {
    complex x1;
    complex x2;

    SCALAR temp = sqrt(-delta);

    x1.re = -b / 2 * a;
    x1.im = temp / 2 * a;

    x2.re = -b / 2 * a;
    x2.im = -temp / 2 * a;

    printf("Dwa pierwiastki zespolone: x1 = %s, x2 = %s\n", complexToString(x1), complexToString(x2));
  }
  else if (delta == 0)
  {
    printf("Jeden pierwiastek rzeczywisty: x = %20.15lf\n", -b / (2 * a));
  }
  else
  {
    SCALAR temp = sqrt(delta);
    printf("Dwa pierwiastki rzeczywiste: x1 = %20.15lf, x2 = %20.15lf\n",
           (-b - temp) / (2 * a), (-b + temp) / (2 * a));
  }
}