#include "movement.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "treasure.h" /*toLowerStr*/

#define MOVE_LINE_BUFFER_SIZE 29


/**
 * \internal \n \n \b Implementation:
 * First, open the file in "r" mode. Then, read and process each line until
 *  EOF is reached.
 * The maximum valid line size is 29 characters long, as the largest valid
 *  integer representation in c is 22 characters long.
 * (+ 5 characters for RIGHT direction, +1 character for space,
 *  +1 for null-terminator).
 * Use \ref fgets to read a line of the file into this buffer.
 *  \ref parse_movement is then
 *  used to parse the line and add the movement to \p moves.
 */
status read_moves(list* moves, char* filename)
{
    char line[MOVE_LINE_BUFFER_SIZE];
    status result = COMPLETE;
    char* line_read;
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
        line_read = fgets(line, MOVE_LINE_BUFFER_SIZE, file);
        while (result == COMPLETE && line_read != NULL)
        {
            result = parse_movement(moves, line_read);
            if (result != COMPLETE)
            {
                fprintf(stderr, "At line %d.\n", i);
            }
            line_read = fgets(line, MOVE_LINE_BUFFER_SIZE, file);
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
            fprintf(stderr, "Error occured while reading from %s: ",
                filename);
            perror("");
            result = ABORTED;
        }
        fclose(file);
    }

    return result;
}


/**
 * \internal \n \n \b Implementation:
 * First, allocate space for the move and add it to the end of \p moves.
 * Doing this early on reduces the chance memory safety is
 *  programmed incorrectly.
 * Modifying \p moves is okay, as strong exception safety is not guarenteed
 *  by this function.
 * 
 * Next, check for a space in the line.
 * This is the seperator between the direction and the distance.
 * If there are no spaces in the line, the string is incorrectly formatted\
 *  and the algorithm ends.
 * 
 * Finally, parse the direction with \ref choose_dir
 *  and the distance with \ref sscanf, and check for errors.
 */
status parse_movement(list* moves, char* line)
{
    status result = COMPLETE;
    char* space = strchr(line, ' ');
    int args_read = 0;
    int chars_read;

    /*Does not check for failed allocation*/
    move* data = (move*)malloc(sizeof(move));
    insert(moves, NULL, data);

    if (space == NULL)
    {
        fprintf(stderr, "No space\n");
        result = ABORTED;
    } else
    {
        *space = '\0';
        data->dir = choose_dir(line);
        args_read = sscanf(space + 1, " %d %n", &data->distance,
            &chars_read);
        /*Check for errors*/
        if (args_read != 1 || chars_read != strlen(space + 1))
        {
            fprintf(stderr, "Distance must be an integer\n");
            result = ABORTED;
        } else if (data->distance < 0)
        {
            fprintf(stderr, "Distance must be positive\n");
            result = ABORTED;
        } else if (data->dir == INVALID)
        {
            fprintf(stderr, "Invalid direction\n");
            result = ABORTED;
        }
    }

    return result;
}

/**
 * \internal \n \n \b Implementation:
 * First, convert the string to lowercase.
 * Next, use a simple else-if ladder to choose the correct direction.
 */
direction choose_dir(char* str)
{
    direction dir;
    toLowerStr(str);
    if (strcmp(str, "up") == 0)
    {
        dir = UP;
    } else if (strcmp(str, "down") == 0)
    {
        dir = DOWN;   
    } else if (strcmp(str, "left") == 0)
    {
        dir = LEFT;
    } else if (strcmp(str, "right") == 0)
    {
        dir = RIGHT;
    } else
    {
        dir = INVALID;
    }

    return dir;
}

/**
 * \internal \n \n \b Implementation:
 * Use a simple else-if ladder to determine the direction,
 *  and print the corresponding string into \p str.
 * Another method of implementing this would be to create an
 * array linking enumerations to strings.
 */
void direction_to_string(direction d, char* str)
{
    if (d == UP)
    {
        strncpy(str, "UP", 8);
    } else if (d == DOWN)
    {
        strncpy(str, "DOWN", 8);
    } else if (d == LEFT)
    {
        strncpy(str, "LEFT", 8);
    } else if (d == RIGHT)
    {
        strncpy(str, "RIGHT", 8);
    } else if (d == INVALID)
    {
        strncpy(str, "INVALID", 8);
    }
}

/**
 * \internal \n \n \b Implementation:
 * Convert the direction to a string with \ref direction_to_string,
 *  and print both the direction and distance to stdout.
 */
void print_move(void* m)
{
    char str[8];
    move* a = (move*)m;
    direction_to_string(a->dir, str);
    printf("\n%s %d", str, a->distance);
}
