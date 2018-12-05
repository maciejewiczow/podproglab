#include <stdio.h>

#define ROZMIAR_TABLICY 10

void main(void)
{
    int tablica_int[ROZMIAR_TABLICY] = {0};

    int i = 0;
    while (i < ROZMIAR_TABLICY)
    {
        tablica_int[i] = rand() % (10 * i + 1);
        int bias;
        scanf("%d", &bias);
        tablica_int[i] *= bias;

        i++;
    }

    i = 0;
    do
    {
        printf("Iteracja %d: tablica_int[%d] = %d\n", i, i, tablica_int[i]);
        i++;
    } while (i < ROZMIAR_TABLICY);
}
