#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "arguments.h"
#include "board.h"

void simulate(Board*, Board*, const Settings*);
void clearLines(unsigned int);
bool isAnyOf(int, char*);

int main(int argCount, char* args[])
{
    Settings setup;

    initalizeWithArguments(argCount, args, &setup);

    printf("Iteration delay: ");
    if (setup.delay.tv_nsec == 0 && setup.delay.tv_sec == 0)
        printf("manual\n");
    else
        printf("%lums\n", setup.delay.tv_sec * 1000 + (setup.delay.tv_nsec / 1000000L));

    printf("Rules: %s/%s\n", setup.cellSurviveNumbers, setup.createNewCellNumbers);

    Board boardCurrent, boardNext;

    FILE* initialStateFile = fopen(setup.boardFilename, "r");

    if (initialStateFile == NULL) {
        printf("Could not open file %s\n", setup.boardFilename);
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

    printf("Board initial state loaded from %s\n", setup.boardFilename);
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

void simulate(Board* curr, Board* next, const Settings* settings)
{
    assert(next->size == curr->size);
    unsigned long int t = 0;

    while (curr->cellCount > 0) {
        t++;

        for (unsigned int i = 0; i < curr->size; i++) {
            for (unsigned int j = 0; j < curr->size; j++) {
                unsigned int neighbCount =
                    board_countAliveCellsAroundInd(curr, i, j, settings->neighbourhood);

                // alive cells tested against dying
                if (curr->cells[i][j] && !isAnyOf(neighbCount, settings->cellSurviveNumbers))
                    next->cells[i][j] = false;

                // dead cell tested against beeing born
                if (!curr->cells[i][j] && isAnyOf(neighbCount, settings->createNewCellNumbers))
                    next->cells[i][j] = true;
            }
        }
        board_countAliveCells(next);

        board_copy(next, curr);

        printf(CLEAR_LINE_CHAR "\r");
        board_printUpdate(curr);
        printf("Time t = %lu", t);

        if (settings->delay.tv_sec == 0 && settings->delay.tv_nsec == 0) {
            getchar();
            printf(MOVE_COURSOR_UP_CHAR);
        }
        else {
            // force printf to print immeditally, instead of keeping text in a buffer
            // because it would negate the delay between time ticks
            fflush(stdout);
            nanosleep(&settings->delay, NULL);
        }
    }
}

bool isAnyOf(int x, char* possible)
{
    bool result = false;

    for (int i = 0; possible[i] != '\0'; i++) {
        // ignore non-digits
        if (!isdigit(possible[i])) continue;
        char curr = possible[i] - '0';

        result = result || (curr == x);
    }

    return result;
}
