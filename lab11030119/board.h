#ifndef LIGE_GAME_H
#    define LIFE_GAME_H

#    include <stdbool.h>

#    define LIVING_CELL "1"
#    define DEAD_CELL "0"

/**
 * This struct represents board, on which the game of life will be taking place
 *
 */
typedef struct board {
    unsigned int size;
    bool** cells;
} Board;

/**
 * Allocates and initalizes new board of given size with dead cells
 *
 * @param Board*: board to initalize
 *
 * @returns error code:
 *      0 on successfull alloctation,
 *      -1 on allocation memorry error
 */
int board_new(Board*);

/**
 * Deallocates memory used by board
 */
void board_delete(Board*);

/**
 * Prints whole board to stdout
 */
void board_print(const Board*);

/**
 * Loads board state from specified file
 *
 * @param Board*: board to be initalized with read state
 * @param FILE*: pointer to file struct, from whitch board is to be initalized
 */
void board_loadFromFile(Board*, FILE*);

/**
 * Determines the side length of board saved in specified file
 *
 * @param FILE* file struct to read data from
 *
 * @returns side length of board or 0 if passed file pointer is NULL
 */
unsigned int board_getSizeFromFile(FILE*);

#endif
