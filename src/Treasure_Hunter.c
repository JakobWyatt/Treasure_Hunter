#include <stdio.h>
#include <stddef.h>
#include "map.h"
#include "movement.h"
#include "adventure.h"

int main(int argc, char* argv[])
{
    size_t rows;
    size_t cols;
    map x;
    list y;
    status map_result;
    status list_result;
    explorer person;
    FILE* logger;
    if (argc != 3)
    {
        printf("Usage: ./TreasureHunter <map_file> <movement_file>\n");
    } else
    {
        map_result = read_map(&x, &rows, &cols, argv[1]);
        list_result = read_moves(&y, argv[2]);
        logger = fopen("adventure.log", "a");

        if (logger != NULL && map_result == COMPLETE && list_result == COMPLETE)
        {
            resolveAdventure(x, rows, cols, y, &person, logger);
        }

        /*clean up*/
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
        free_list(&y);
    }
    printf("\n");
    return 0;
}
