#include "movement.h"

#include <stdio.h>
#include <string.h>

#include "list.h"

#define MOVE_LINE_BUFFER_SIZE 29

status read_moves(list* moves, char* filename)
{
    /*Read and process each line until the end of file is reached.
    As each line has to store an integer, and the largest valid integer representation in c
    is 22 characters long (representation + sign + number), the maximum string size needed is
    29 characters.*/
    char line[MOVE_LINE_BUFFER_SIZE];
    status result = COMPLETE;
    char* line_read;
    char* space;
    int i = 1;
    FILE* file = fopen(filename, "r");
    *moves = make_list();
    
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file %s for reading: ", filename);
        perror("");
        result = ABORTED;
    } else
    {
        /*We must initially read from the file,
        as line_read cannot be null when passed to parse_movement.*/
        line_read = fgets(line, MOVE_LINE_BUFFER_SIZE, filename);
        while (result == COMPLETE && line_read != NULL)
        {
            result = parse_movement(moves, line_read);
            if (result != COMPLETE)
            {
                fprintf(stderr, "At line %d.\n", i);
            }
            line_read = fgets(line, MOVE_LINE_BUFFER_SIZE, filename);
            ++i;
        }

        /*Check for empty list without errors (empty file)*/
        if (moves->head == NULL && result == COMPLETE)
        {
            fprintf(stderr, "File %s was empty.\n", filename);
            result = ABORTED;
        }

        /*Cleanup file reads: check error state and close stream.*/
        if (ferror(file))
        {
            fprintf(stderr, "Error occured while reading from %s: ", filename);
            perror("");
            result = ABORTED;
        }
        fclose(file);
    }

    return result;
}
