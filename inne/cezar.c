#include <stdio.h>

void encode(char* str, int k);
int wrapAround(int x, int min, int max);

int main()
{
    char s[] = "mafciej";
    encode(s, 20);
    printf("%s\n", s);
}

int wrapAround(int x, int min, int max)
{
    if (x < min) {
        return max - (min - x) + 1;
    }
    if (x > max) {
        return min + (x - max) - 1;
    }
    return x;
}

void encode(char* str, int k)
{
    int i = 0;
    k %= 27;

    if (k == 0) return;

    while (str[i] != '\0') {
        int ascii = (int) str[i];
        // jeśli znak nie jest literą to zostawiamy go w spokoju
        if (!(('A' <= ascii && ascii <= 'Z') || ('a' <= ascii && ascii <= 'z'))) {
            i++;
            continue;
        }
        int min, max;

        // w tym momencie znak może być już tylko albo małą albo dużą literą
        // wszystkie małe litery mają kod większy lub równy a, duże mniejszy
        if (ascii >= 'a') {
            min = (int) 'a';
            max = (int) 'z';
        }
        else {
            min = (int) 'A';
            max = (int) 'Z';
        }

        str[i] = (char) wrapAround(ascii + k, min, max);

        i++;
    }
}
