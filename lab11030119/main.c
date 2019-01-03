#include <stdio.h>

#include "board.h"

int main()
{
    // @TODO get board size and other params from stdin or script arguments
    const char* filename = "board.txt";

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
    board_loadFromFile(&boardPrevious, initialStateFile);

    fclose(initialStateFile);

    printf("Board initial state loaded from %s\n", filename);
    printf("Size read from file: %u\n", size);
    board_print(&boardCurrent);
}
