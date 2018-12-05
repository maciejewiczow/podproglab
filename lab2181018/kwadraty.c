#include <stdio.h>

char *empty = " ";
char *fill = "x";

void square(int side)
{
    for (int i = 0; i < side; i++)
    {
        for (int j = 0; j < side * 2; j++)
            printf(fill);

        printf("\n");
    }
}

void triangle(int side)
{
    int h = side;
    int w = side * 2;
    int correction = side % 2;

    for (int i = 1; i <= h; i++)
    {
        for (int spaces = 0; spaces < (w / 2) - i; spaces++)
            printf(empty);
        for (int dots = 0; dots < (i * 2) - correction; dots++)
            printf(fill);
        printf("\n");
    }
}

void iks(int side)
{
    int h = side;
    int w = side * 2;

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
            if (i * 2 == j || i * 2 == w - j - 1)
            {
                printf(fill);
            }
            else
            {
                printf(empty);
            }
        printf("\n");
    }
}

int main(void)
{
    int side;

    printf("Podaj szerokość boku: ");
    scanf("%d", &side);

    square(side);
    printf("\n");
    triangle(side);
    printf("\n");
    iks(side);
    return 0;
}