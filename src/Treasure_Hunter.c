#include <stdio.h>
#include <stddef.h>
#include "map.h"
#include "movement.h"
#include "adventure.h"
#include "types.h"

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
        map_result = read_map(&x, &rows, &cols, argv[1]);
        list_result = read_moves(&y, argv[2]);
        logger = fopen("adventure.log", "a");
        person = make_explorer();

        if (logger != NULL && map_result == COMPLETE && list_result == COMPLETE)
        {
            adventure_result = resolveAdventure(x, rows, cols, y, &person, logger);
            status_text(adventure_result, final_status);
            printf("STATUS: %s\nCOINS: %d\nMAGIC: %d\nGEAR: %d\n", final_status,
                person.coin, person.magic, gear_value(person));
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
        free_explorer(person);
        free_list(&y);
    }
    return 0;
}
