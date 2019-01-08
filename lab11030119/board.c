#include <assert.h>
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

void board_printUpdate(const Board* this)
{
    // erase previously printed board
    for (unsigned int i = 0; i < this->size; i++)
        printf(CLEAR_LINE_CHAR "\r" MOVE_COURSOR_UP_CHAR);

    // print new one
    board_print(this);
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

    // revind file pointer, to avoid errors with loading board from the same struct later
    fseek(file, 0, SEEK_SET);
    return ceil((double) result / 2);
}

void board_countAliveCells(Board* this)
{
    this->cellCount = 0;
    for (unsigned int i = 0; i < this->size; i++)
        for (unsigned int j = 0; j < this->size; j++)
            if (this->cells[i][j]) this->cellCount++;
}

void board_loadFromFile(Board* this, FILE* file)
{
    unsigned int col, row;
    int c;

    col = row = 0;

    while ((c = getc(file)) != EOF) {
        if (col == this->size) col = 0;
        if (row == this->size) break;

        switch (c) {
            case '\n':
                row++;
                col = 0;
                break;
            case '1':
                this->cells[row][col] = true;
                this->cellCount++;
                // fall through
            case '0':
                col++;
                break;
        }
    }

    // bring the file struct to previous state, because why not
    fseek(file, 0, SEEK_SET);
}

void board_copy(const Board* src, Board* dest)
{
    assert(src->size == dest->size);

    dest->cellCount = src->cellCount;

    for (unsigned int i = 0; i < dest->size; i++)
        for (unsigned int j = 0; j < dest->size; j++)
            dest->cells[i][j] = src->cells[i][j];
}
