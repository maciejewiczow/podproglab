#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "board.h"

int board_new(Board* this)
{
    if (this == NULL) return -2;

    this->cells = (bool**) calloc(this->size, sizeof(bool*));

    if (this->cells == NULL) return -1;

    for (unsigned int i = 0; i < this->size; i++) {
        bool* p = calloc(this->size, sizeof(bool));

        if (p == NULL) return -1;

        this->cells[i] = p;
    }

    return 0;
}

void board_delete(Board* this)
{
    for (unsigned int i = 0; i < this->size; i++)
        free(this->cells[i]);

    free(this->cells);
}

// @TODO make this method update console content instead of printing new one on each call
void board_print(const Board* this)
{
    if (this == NULL) return;

    for (unsigned int i = 0; i < this->size; i++) {
        bool* row = this->cells[i];
        for (unsigned int j = 0; j < this->size; j++) {
            if (row[j]) {
                printf(LIVING_CELL);
            }
            else {
                printf(DEAD_CELL);
            }
            printf(" ");
        }
        printf("\n");
    }
}

unsigned int board_getSizeFromFile(FILE* file)
{
    if (file == NULL) return 0;

    unsigned int result = 0;
    int c;

    while ((c = getc(file)) != EOF) {
        if (c == '\n') break;
        result++;
    }

    return ceil((double) result / 2);
}

void board_loadFromFile(Board* this, FILE* file)
{
    unsigned int col, row;
    int c;

    col = row = 0;

    while ((c = getc(file)) != EOF) {
        if (col == this->size * 2 - 1) col = 0;
        if (row == this->size * 2 - 1) break;

        switch (c) {
            case '\n':
                row++;
                col = 0;
                break;
            case '1':
                this->cells[row][col] = true;
            case '0':
                col++;
                break;
        }
        printf("%d row: %u col: %u\n", c, row, col);
    }
}
