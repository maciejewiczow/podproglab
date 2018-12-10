#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_LENGTH 200

#define DEBUG_PRINTS false

#define RANGE_START '0'
#define RANGE_END 'z'

typedef struct Entry {
    char key;
    int value;
} DictEntry;

typedef struct Dict {
    int length;
    int end;
    DictEntry* entries;
} Dictionary;
void dict_new(Dictionary*, int);
void dict_delete(Dictionary*);
DictEntry* dict_getEntryByKey(const Dictionary*, const char);
int dict_addEntry(Dictionary*, char, int);
void dict_print(const Dictionary*);
void dict_sort(Dictionary*);

void fillArrayWithRandomValues(char*, const int, const char, const char);

void printHistogramFromDict(const Dictionary*);

int main(void)
{
    char array[ARRAY_LENGTH];
    srand(time(0));

    Dictionary dict;
    dict_new(&dict, (RANGE_END - RANGE_START) + 1);

    fillArrayWithRandomValues(array, ARRAY_LENGTH, RANGE_START, RANGE_END);

    printf("%s\n\n", array);

    for (int i = 0; i < ARRAY_LENGTH; i++) {
        DictEntry* e = dict_getEntryByKey(&dict, array[i]);

        if (e == NULL) {
            int error = dict_addEntry(&dict, array[i], 1);
            if (error) {
                printf(
                    "Error (%d), dictionary is too small for all this values. Aborting\n", error);
                return -1;
            }
        }
        else {
            e->value++;
        }
    }

    dict_sort(&dict);

#if DEBUG_PRINTS
    dict_print(&dict);
#endif

    printHistogramFromDict(&dict);

    dict_delete(&dict);

    return 0;
}

void fillArrayWithRandomValues(char* arr, const int length, const char min, const char max)
{
    for (int i = 0; i < length; i++)
        arr[i] = (char) (random() % (max - min + 1)) + min;
}

void printHistogramFromDict(const Dictionary* dict)
{
    for (int i = 0; i < dict->end; i++) {
        DictEntry record = dict->entries[i];
        printf("%c  ", record.key);
        for (int j = 0; j < record.value; j++)
            printf("*");
        printf("\n");
    }
}

void dict_new(Dictionary* this, int numberOfRecords)
{
    this->length = numberOfRecords;
    this->end = 0;

    DictEntry* p;
    p = (DictEntry*) calloc(numberOfRecords, sizeof(DictEntry));

    this->entries = p;
}

void dict_delete(Dictionary* this)
{
    free(this->entries);
}

void dict_print(const Dictionary* this)
{
    printf("Length: %d\nEnd: %d\n", this->length, this->end);

    for (int i = 0; i < this->end; i++)
        printf("%d   (int %d) %c: %d\n", i, (int) this->entries[i].key, this->entries[i].key,
            this->entries[i].value);
}

DictEntry* dict_getEntryByKey(const Dictionary* this, const char key)
{
    for (int i = 0; i < this->end; i++) {
        if (this->entries[i].key == key) return &this->entries[i];
    }
    return NULL;
}

void dict_sort(Dictionary* this)
{
    bool swapped;

    do {
        swapped = false;
        for (int i = 0; i < this->end - 1; i++) {
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