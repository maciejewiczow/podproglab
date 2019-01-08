#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "board.h"

typedef struct settings {
    unsigned int cellStayAliveNumber;
    unsigned int createNewCellNumber;
    struct timespec delay;
    bool neighbourhood[3][3];
} Settings;

void simulate(Board*, Board*, const Settings*);
unsigned int countNeighbouringCells(const Board*, unsigned int, unsigned int, const bool[3][3]);
void clearLines(unsigned int);

int main(/* int argCount, char** args */)
{
    // @TODO get board size and other params from stdin or script arguments
    const char* filename = "board.txt";
    const unsigned int delayMs = 500;

    const Settings setup = {
        .cellStayAliveNumber = 23,
        .createNewCellNumber = 3,
        .delay =
            {
                .tv_sec = 0,
                .tv_nsec = delayMs * 1000000L,
            },
        .neighbourhood =
            {
                {1, 1, 1},
                {1, 0, 1},
                {1, 1, 1},
            },
    };

    Board boardCurrent, boardNext;

    FILE* initialStateFile = fopen(filename, "r");

    if (initialStateFile == NULL) {
        printf("Could not open file %s\n", filename);
        return -1;
    }

    unsigned int size = board_getSizeFromFile(initialStateFile);

    boardCurrent.size = boardNext.size = size;
    boardCurrent.cellCount = boardNext.cellCount = 0;

    int error1 = board_new(&boardNext);
    int error2 = board_new(&boardCurrent);

    if (error1 || error2) {
        printf("Error occurred during board allocation. Aborting\n");
        return -1;
    }

    board_loadFromFile(&boardCurrent, initialStateFile);
    board_loadFromFile(&boardNext, initialStateFile);

    fclose(initialStateFile);

    printf("Board initial state loaded from %s\n", filename);
    printf("Size read from file: %ux%u\n\n", size, size);
    board_print(&boardCurrent);

    printf("Press enter to start the simulation\n");
    getchar();

    clearLines(2);
    printf(CLEAR_LINE_CHAR "Time t = 0");
    fflush(stdout);

    simulate(&boardCurrent, &boardNext, &setup);

    board_delete(&boardCurrent);
    board_delete(&boardNext);

    return 0;
}

void clearLines(unsigned int lncount)
{
    for (unsigned int i = 0; i < lncount; i++)
        printf(CLEAR_LINE_CHAR "\r" MOVE_COURSOR_UP_CHAR);
}

unsigned int countNeighbouringCells(
    const Board* b, unsigned int i, unsigned int j, const bool neighbourhood[3][3])
{
    unsigned int result = 0;

    for (int y = -1; y <= 1; y++) {
        if (i == 0 || i + 1 == b->size) continue;
        for (int x = -1; x <= 1; x++) {
            if (j == 0 || j + 1 == b->size) continue;
            if (b->cells[y + i][x + j] && neighbourhood[y + 1][x + 1]) result++;
        }
    }

    return result;
}

void simulate(Board* curr, Board* next, const Settings* settings)
{
    assert(next->size == curr->size);
    unsigned long int t = 0;

    while (curr->cellCount > 0) {
        t++;

        for (unsigned int i = 0; i < curr->size; i++) {
            for (unsigned int j = 0; j < curr->size; j++) {
                unsigned int neighbours =
                    countNeighbouringCells(curr, i, j, settings->neighbourhood);

                // temporary hard-coded values - 23/3 - Conoway's rules
                // @REMINDER to change it to something more portable later on
                if (curr->cells[i][j] && !(neighbours == 2 || neighbours == 3))
                    next->cells[i][j] = false;

                if (!curr->cells[i][j] && neighbours == 3) next->cells[i][j] = true;
            }
        }
        board_countAliveCells(next);

        board_copy(next, curr);

        printf(CLEAR_LINE_CHAR "\r");
        board_printUpdate(curr);
        printf("Time t = %lu", t);
        fflush(stdout);
        nanosleep(&settings->delay, NULL);
    }
}
