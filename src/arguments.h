#ifndef __GUARD_ARGS_H
#define __GUARD_ARGS_H

#include <stdbool.h>
#include <time.h>
#include <unistd.h>

#define HELPTEXT                                                                                   \
    "Usage: %s <file> [OPTIONS]\n"                                                                 \
    "\t-d --delay\tset ms of delay between simulation time ticks. \n\t\t0 means that program "     \
    "will wait for keypress between each tick (default 1000ms)\n"                                  \
    "\t-c --createnum\t numbers of nearby alive cells, that cause new cell to be born (default "   \
    "3)\n"                                                                                         \
    "\t-s --survivenum \tnumbers of nearby alive cells, that provide survival of given cell "      \
    "(default 23)\n"                                                                               \
    "\n\t-n --neighbourhood\tname of file containing neigbourhood mask, that will be used in "     \
    "simulation. Default is Moore's neighbourghood\n"                                              \
    "\t-h --help \t displays this help text\n"

/**
 * Holds parameters (rules) used to perform the simulation.
 *
 * bool neigbourhood[3][3] - 3x3 matrix of booleans, used as a bit mask to determine rules of
 *      neighbourhood, when counting number of alive neighbours of a given cell. Middle term's value
 *      ([1][1]) is always ignored.
 * struct timespec delay - struct passed as an argument to nanosleep().
 *      Determines the duration of pause between time ticks. If NULL, then each frame is confirmed
 *      manually with an ENTER key.
 * char* boardFilename - name of a file, from which initial board config will be loaded
 * char* cellSurviveNumbers - numbers of neighbouring cells, for whitch given cell can continue to
 *      live. Each character of string is treated as a single digit. Non-digit chars are ignored.
 * char* createNewCellNumbers - numbers of alive neighbours required for a new cell to be born in an
 *      empty place. Format is the same as in previous field.
 */
typedef struct settings {
    struct timespec delay;
    bool neighbourhood[3][3];
    char* boardFilename;
    char* cellSurviveNumbers;
    char* createNewCellNumbers;
} Settings;

/**
 * Parses script arguments passed to main() in argc and argv and fills passed settings struct with
 * appropiate values, eithier entered by user or defaults
 *
 * @param int argc - argument count passed to main()
 * @param char*[] argv - argument vector passed to main()
 * @param Settings* - pointer to settings struct
 */
void initalizeWithArguments(int, char* [], Settings*);

#endif
