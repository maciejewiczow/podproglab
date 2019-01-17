#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "board.h"

int board_new(Board* this)
{
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

    while ((c = getc(file)) != EOF && c != '\n')
        result++;

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

unsigned int board_countAliveCellsAroundInd(
    const Board* b, unsigned int i, unsigned int j, const bool neighbourhood[3][3])
{
    unsigned int result = 0;

    for (int y = -1; y <= 1; y++) {
        // skip this index if checked cell is on the edge of board
        if (i == 0 || i + 1 == b->size) continue;
        for (int x = -1; x <= 1; x++) {
            // also skip
            if (j == 0 || j + 1 == b->size) continue;
            if (b->cells[y + i][x + j] && neighbourhood[y + 1][x + 1]) result++;
        }
    }

    return result;
}

void board_loadFromFile(Board* this, FILE* file)
{
    unsigned int col, row;
    int c;

    col = row = 0;

    while ((c = getc(file)) != EOF) {
        if ((unsigned int) (col / 2) == this->size) col = 0;
        if (row == this->size) break;

        switch (c) {
            case '\n':
                row++;
                col = 0;
                break;
            case '1':
                this->cells[row][(unsigned int) (col / 2)] = true;
                this->cellCount++;
                // fall through
            default:
                col++;
                break;
        }
    }

    // rewind file after finishing, because why not
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
