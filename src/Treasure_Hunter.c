#include <stdio.h>
#include <stddef.h>
#include "map.h"

int main(int argc, char* argv[])
{
    /*
    General flow of events:
    - Read the map into a 2d array. The datatype of this array will be a struct consisting of:
        An enum, describing what the datatype of the item is.
        A void ptr, which points to the location of the item.
    -Read the adventure file into a linked list.
        Any errors in these first two steps are written to stderr, and changes the status to ABORTED.
    -Resolve the adventure, keeping track of:
        Gear equipped.
        Total magic value.
        Total coins.

        This is done by iterating through the linked list.
        Boundary checking is done conditionally.
        Logging is done via the file adventure.log, and is conditionally written to stdout.
        If an out of bounds error is encountered, control flow ends and the status is FAILED.
        If the path is changed, control flow continues and the status is CORRECTED.
    -Print the output of the program.
    */

    size_t rows;
    size_t cols;
    map x;
    status result;
    if (argc != 2)
    {
        printf("Usage: ./TreasureHunter <map_file>");
    } else
    {
        result = read_map(&x, &rows, &cols, argv[1]);
        if (result == COMPLETE)
        {
            print_map(x, rows, cols);
            free_map(x, rows, cols);
        }
    }
}
