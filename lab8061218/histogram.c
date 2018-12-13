#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DEBUG_PRINTS false

typedef struct Entry {
    char key;
    int value;
} DictEntry;

typedef struct Dict {
    unsigned int length;
    unsigned int end;
    DictEntry* entries;
} Dictionary;
void dict_new(Dictionary*, unsigned int);
void dict_delete(Dictionary*);
DictEntry* dict_getEntryByKey(const Dictionary*, const char);
int dict_addEntry(Dictionary*, const char, const int);
void dict_print(const Dictionary*);
void dict_sort(Dictionary*);

void fillArrayWithRandomValues(char*, const int, const char, const char);
void createStringHistorgram(Dictionary*, const char*);
void printHistogramFromDict(const Dictionary*);
int max(int, int);
int min(int, int);

int main(void)
{
    srand(time(0));
    unsigned int arrayLength = 50;
    char start = 'a';
    char end = 'z';

    printf("Please enter length of string to analise: ");
    scanf("%u", &arrayLength);

    printf("Please enter bounding characters of (inclusive) range, from which random string will "
           "be generated:\nstart: ");
    scanf(" %c", &start);
    printf("end: ");
    scanf(" %c", &end);

#if DEBUG_PRINTS
    printf("%c(%d) %c(%d)\n", start, (int) start, end, (int) end);
#endif

    int temp = (int) start;
    start = (char) min(start, end);
    end = (char) max(temp, end);

    assert(start < end);

#if DEBUG_PRINTS
    printf("%c - %c\n", start, end);
#endif

    char* array = (char*) calloc(arrayLength, sizeof(char));
    if (array == NULL) {
        printf("Memory Error: couldn't allocate enough memory for string. Aborting");
        return -1;
    }

#if DEBUG_PRINTS
    printf("%s\n", array);
#endif

    fillArrayWithRandomValues(array, arrayLength, start, end);
    array[arrayLength - 1] = '\0';

    Dictionary dict;
    dict_new(&dict, (end - start) + 1);

    printf("%s\n\n", array);

    createStringHistorgram(&dict, array);

    dict_sort(&dict);

#if DEBUG_PRINTS
    dict_print(&dict);
#endif

    printHistogramFromDict(&dict);

    dict_delete(&dict);
    free(array);

    return 0;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}
int min(int a, int b)
{
    return (a < b) ? a : b;
}

void createStringHistorgram(Dictionary* dict, const char* string)
{
    int i = 0;
    char c;

    while ((c = string[i]) != '\0') {
        DictEntry* e = dict_getEntryByKey(dict, c);

        if (e == NULL) {
            int error = dict_addEntry(dict, c, 1);
            if (error) {
                printf(
                    "Error (%d): dictionary is too small for all this values. Aborting\n", error);
                exit(-1);
            }
        }
        else {
            e->value++;
        }
        i++;
    }
}

void fillArrayWithRandomValues(char* arr, const int length, const char min, const char max)
{
    // leaving null terminator intact or a free slot if there wasn't one to begin with
    for (int i = 0; i < (length - 1); i++)
        arr[i] = (char) (random() % (max - min + 1)) + min;
}

void printHistogramFromDict(const Dictionary* dict)
{
    for (unsigned int i = 0; i < dict->end; i++) {
        DictEntry record = dict->entries[i];
        printf("%c  ", record.key);
        for (int j = 0; j < record.value; j++)
            printf("*");
        printf("\n");
    }
}

void dict_new(Dictionary* this, unsigned int numberOfRecords)
{
    this->length = numberOfRecords;
    this->end = 0;

    DictEntry* p = (DictEntry*) calloc(numberOfRecords, sizeof(DictEntry));

    if (p == NULL) {
        printf("Memory Error: Could not allocate memory for the dictionary");
        exit(-1);
    }

    this->entries = p;
}

void dict_delete(Dictionary* this)
{
    free(this->entries);
}

void dict_print(const Dictionary* this)
{
    printf("Length: %d\nEnd: %d\n", this->length, this->end);

    for (unsigned int i = 0; i < this->end; i++)
        printf("%d   (int %d) %c: %d\n", i, (int) this->entries[i].key, this->entries[i].key,
            this->entries[i].value);
}

DictEntry* dict_getEntryByKey(const Dictionary* this, const char key)
{
    for (unsigned int i = 0; i < this->end; i++) {
        if (this->entries[i].key == key) return &this->entries[i];
    }
    return NULL;
}

void dict_sort(Dictionary* this)
{
    bool swapped;

    do {
        swapped = false;
        for (unsigned int i = 0; i < this->end - 1; i++) {
            if (this->entries[i].key > this->entries[i + 1].key) {
                DictEntry temp = this->entries[i];
                this->entries[i] = this->entries[i + 1];
                this->entries[i + 1] = temp;
                swapped = true;
            }
        }
    } while (swapped);
}

int dict_addEntry(Dictionary* this, char key, int value)
{
    // dictionary is full, no room for another record
    if (this->end == this->length) return -1;

    DictEntry* entry = dict_getEntryByKey(this, key);

    if (entry == NULL) {
        this->entries[this->end++] = (DictEntry){
            .key = key,
            .value = value,
        };
    }

    return 0;
}
