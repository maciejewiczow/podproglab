#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "board.h"

int main()
{
    // @TODO get board size and other params from stdin or script arguments
    const char* filename = "board.txt";
    const unsigned int delayMs = 750;

    Board boardCurrent, boardPrevious;

    FILE* initialStateFile = fopen(filename, "r");

    if (initialStateFile == NULL) {
        printf("Could not open file %s", filename);
        return -1;
    }

    unsigned int size = board_getSizeFromFile(initialStateFile);

    boardCurrent.size = boardPrevious.size = size;

    int error1 = board_new(&boardPrevious);
    int error2 = board_new(&boardCurrent);

    if (error1 || error2) {
        printf("Error occurred during board allocation. Aborting");
        return -1;
    }

    board_loadFromFile(&boardCurrent, initialStateFile);
    // board_loadFromFile(&boardPrevious, initialStateFile);

    fclose(initialStateFile);

    printf("Board initial state loaded from %s\n", filename);
    printf("Size read from file: %ux%u\n\n", size, size);
    board_print(&boardPrevious);

    sleep(1);

    struct timespec delaySpec = {
        .tv_sec = 0,
        .tv_nsec = delayMs * 100000L,
    };

    board_printUpdate(&boardCurrent);

    for (unsigned int i = 0; i < boardCurrent.size; i++) {
        for (unsigned int j = 0; j < boardCurrent.size; j++) {
            boardCurrent.cells[i][j] = false;
            nanosleep(&delaySpec, NULL);
            board_printUpdate(&boardCurrent);
        }
    }

    board_delete(&boardCurrent);
    board_delete(&boardPrevious);
}
