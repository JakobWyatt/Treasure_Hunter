#include <stdio.h>
#include <stddef.h>
#include "map.h"
#include "movement.h"
#include "adventure.h"
#include "types.h"

/**
    \file Treasure_Hunter.c
    \brief Contains top level main function to run the game.
*/

int main(int argc, char* argv[])
{
    size_t rows;
    size_t cols;
    map x;
    list y;
    status map_result;
    status list_result;
    status adventure_result;
    FILE* logger;
    explorer person;
    char final_status[10];
    if (argc != 3)
    {
        printf("Usage: ./TreasureHunter <map_file> <movement_file>\n");
    } else
    {
        /* Initialize the values needed before adventure resolution. */
        map_result = read_map(&x, &rows, &cols, argv[1]);
        list_result = read_moves(&y, argv[2]);
        logger = fopen("adventure.log", "a");
        person = make_explorer();

        /* Ensure that file reading worked properly. */
        if (logger != NULL && map_result == COMPLETE && list_result == COMPLETE)
        {
            /* Resolve the adventure and print the result. */
            adventure_result = resolveAdventure(x, rows, cols, y, &person, logger);
            status_text(adventure_result, final_status);
            printf("STATUS: %s\nCOINS: %d\nMAGIC: %d\nGEAR: %d\n", final_status,
                person.coin, person.magic, gear_value(person));
        }

        /* Clean up memory and files. */
        if (map_result == COMPLETE)
        {
            free_map(x, rows, cols);
        }
        if (ferror(logger))
        {
            fprintf(stderr, "An error occured while writing to the log file.\n");
        }
        if (logger != NULL)
        {
            fclose(logger);
        }
        free_explorer(person);
        free_list(&y);
    }
    return 0;
}
