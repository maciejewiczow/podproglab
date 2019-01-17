#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "arguments.h"

/**
 * Helper function, used to load file contents into 3x3 array of bools
 * value 1 is treated like true, every other thing is treated as false.
 * For more information, refer to 'Input files' section in README.md
 */
static int loadNeighbourhoodFromFile(char*, bool[3][3]);

void initalizeWithArguments(int argc, char* args[], Settings* setup)
{
    if (argc < 2) {
        // no arguments supplied, print help and exit
        printf(HELPTEXT, args[0]);
        exit(EXIT_FAILURE);
    }

    // initalize with defaults
    setup->boardFilename = NULL;
    setup->cellSurviveNumbers = "23";
    setup->createNewCellNumbers = "3";
    setup->delay = (struct timespec){
        .tv_sec = 1,
        .tv_nsec = 0,
    };

    for (int i = 0; i < 3; i += 2)
        for (int j = 0; j < 3; j++)
            setup->neighbourhood[i][j] = 1;

    setup->neighbourhood[1][0] = 1;
    setup->neighbourhood[1][1] = 0;
    setup->neighbourhood[1][2] = 1;

    const char* shortops = "d:c:s:n:h";
    const struct option longopts[] = {
        {"delay", required_argument, NULL, 'd'},
        {"createnum", required_argument, NULL, 'c'},
        {"survivenum", required_argument, NULL, 's'},
        {"neigbourhood", required_argument, NULL, 'n'},
        {"help", no_argument, NULL, 'h'},
        {0, 0, 0, 0},
    };

    int c;

    while ((c = getopt_long(argc, args, shortops, longopts, NULL)) != -1) {
        switch (c) {
            case 'd':;
                long ms = atol(optarg);

                setup->delay = (struct timespec){
                    .tv_sec = (long) (ms / 1000),
                    .tv_nsec = (ms % 1000) * 1000000L,
                };
                break;
            case 'c':
                setup->createNewCellNumbers = optarg;
                break;
            case 's':
                setup->cellSurviveNumbers = optarg;
                break;
            case 'n':;
                memset(&setup->neighbourhood, 0, sizeof(setup->neighbourhood));
                int error = loadNeighbourhoodFromFile(optarg, setup->neighbourhood);

                if (error) {
                    printf("Could not load neigbourhood from file %s. Aborting\n", optarg);
                    exit(EXIT_FAILURE);
                }

                printf("Loaded neighbourhood mask:\n");
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++)
                        printf("%d ", setup->neighbourhood[i][j]);

                    printf("\n");
                }

                break;
            case 'h':
                printf(HELPTEXT, args[0]);
                exit(EXIT_SUCCESS);
                break;
            default:
                // in case of '?' getopt_long will print out appropiate error message for me, so
                // just exit, other values not possible (afaik)
                exit(EXIT_FAILURE);
        }
    }

    if (optind == argc) {
        // after parsing options there was nothing left = only options were provided, w/out filename
        printf("No file to read initial board state from given. Run with -h or --help for usage "
               "instructions\n");
        exit(EXIT_FAILURE);
    }

    if (optind < argc) {
        // take first of remaining args as filename, ignore the rest
        setup->boardFilename = args[optind];
    }
}

static int loadNeighbourhoodFromFile(char* filename, bool neighbourhood[3][3])
{
    FILE* f = fopen(filename, "r");

    if (f == NULL) return -1;

    int c, row = 0, col = 0;
    while ((c = getc(f)) != EOF) {
        if (row == 1 && col == 1) col++;

        if ((int) (col / 2) == 3) col = 0;

        if (row == 3) break;

        switch (c) {
            case '\n':
                row++;
                col = 0;
                break;
            case '1':
                neighbourhood[row][(int) (col / 2)] = true;
                // fall-through
            default:
                col++;
        }
    }

    return 0;
}
