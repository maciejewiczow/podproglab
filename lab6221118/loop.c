#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define ROZMIAR_TABLICY 10

const double EPSILON = 1.e-20;

int findMax(int[], int);
int sumAll(int[], int);
void findOneI(int, int[], int);
void findOneD(double, double[], int);
void findAllI(int, int[], int);
void findAllD(double, double[], int);
double avg(int[], int);
bool almostEqual(double, double, double);

void main(void)
{
    int tablica_int[ROZMIAR_TABLICY] = {0};

    int i = 0;
    while (i < ROZMIAR_TABLICY)
    {
        tablica_int[i] = rand() % 100;
        i++;
    }

    i = 0;
    do
    {
        printf("Iteracja %d: tablica_int[%d] = %d\n", i, i, tablica_int[i]);
        i++;
    } while (i < ROZMIAR_TABLICY);

    printf("\nSum of all elements is %d\n", sumAll(tablica_int, ROZMIAR_TABLICY));
    printf("Greatest element of array is %d\n", findMax(tablica_int, ROZMIAR_TABLICY));
    printf("Average value of all elements is %f\n", avg(tablica_int, ROZMIAR_TABLICY));
    findAllI(0, tablica_int, ROZMIAR_TABLICY);
    findOneI(2137, tablica_int, ROZMIAR_TABLICY);
}

bool almostEqual(double a, double b, double tolerance)
{
    return a == b || (b - tolerance <= a && a <= b + tolerance);
}

int findMax(int arr[], int size)
{
    int max = INT_MIN;

    for (int i = 0; i < size; i++)
        if (arr[i] > max)
            max = arr[i];

    return max;
}

int sumAll(int arr[], int size)
{
    int result = 0;

    for (int i = 0; i < size; i++)
        result += arr[i];

    return result;
}

double avg(int arr[], int size)
{
    return sumAll(arr, size) / size;
}

void findOneI(int target, int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == target)
        {
            printf("Target %d found at position %d\n", target, i);
            return;
        }
    }

    printf("Target %d is not present in provided array\n", target);
}

void findAllI(int target, int arr[], int size)
{
    printf("%d ocurres at positions: ", target);
    bool foundAny = false;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == target)
        {
            printf("%d ", i);
            foundAny = true;
        }
    }

    if (!foundAny)
        printf("none \nTarget %d is not present in provided array\n", target);
    else
        printf("\n");
}

void findOneD(double target, double arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (almostEqual(arr[i], target, EPSILON))
        {
            printf("Target %f found at position %d\n", target, i);
            return;
        }
    }

    printf("Target %f is not present in provided array\n", target);
}

void findAllD(double target, double arr[], int size)
{
    printf("%d ocurres at positions: ", target);
    bool foundAny = false;
    for (int i = 0; i < size; i++)
    {
        if (almostEqual(arr[i], target, EPSILON))
        {
            printf("%d ", i);
            foundAny = true;
        }
    }

    if (!foundAny)
        printf("none \nTarget %f is not present in provided array\n", target);
    else
        printf("\n");
}
