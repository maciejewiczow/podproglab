#ifndef __GUARD_BOARD_H
#define __GUARD_BOARD_H

#include <stdbool.h>

#define LIVING_CELL "*"
#define DEAD_CELL " "

#define CLEAR_LINE_CHAR "\33[2K"
#define MOVE_COURSOR_UP_CHAR "\033[A"

/**
 * This struct represents board, on which the game of life will be taking place
 *
 * unsigned int size - the side length of board
 * usnigned int cellCount - number of alive cells left on board
 * bool** cells - 2D array of booleans, in which value of true represents a living cell, and false
 * dead one
 */
typedef struct board {
    unsigned int size;
    unsigned int cellCount;
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
 * Erases previously printed board and prints a new one
 */
void board_printUpdate(const Board*);

/**
 * Loads board state from specified file
 * Updates cell count property
 *
 * @param 1 Board*: board to be initalized with read state
 * @param 2 FILE*: pointer to file struct, from whitch board is to be initalized
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

/**
 * Updates the cellCount property inside given Board struct
 */
void board_countAliveCells(Board*);

/**
 * Copies entire content of one board to another
 * @param 1 - source
 * @param 2 - destination
 */
void board_copy(const Board*, Board*);

#endif
