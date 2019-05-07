#include "movement.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "list.h" /*for obvious reasons*/
#include "treasure.h" /*toLowerStr*/

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
            free_list(*moves);
        }

        /*Cleanup file reads: check error state and close stream.*/
        if (ferror(file))
        {
            fprintf(stderr, "Error occured while reading from %s: ", filename);
            perror("");
            result = ABORTED;
            free_list(*moves);
        }
        fclose(file);
    }

    return result;
}

status parse_movement(list* moves, char* line)
{
    /*Does not check for broken allocation*/
    status result = COMPLETE;
    char* space = strchr(line, ' ');
    int args_read = 0;

    /*We do not guarentee strong exception safety, so allocation and
    addition to the list can be done immidiately. This improves the chance
    we get memory safety right.*/
    move* data = (move*)malloc(sizeof(move));
    insert(*moves, NULL, data);

    if (space == NULL)
    {
        fprintf(stderr, "Invalid formatting\n");
        result = ABORTED;
    } else
    {
        *space = '\0';
        data->dir = choose_dir(line);
        args_read = sscanf(space + 1, " %d ", &data->distance);
    }

    /*Check for errors*/
    if (args_read != 1)
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

    return result;
}

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

void direction_to_string(direction d, char* str)
{
    if (d == UP)
    {
        strncpy(str, "UP", 6);
    } else if (d == DOWN)
    {
        strncpy(str, "DOWN", 6);
    } else if (d == LEFT)
    {
        strncpy(str, "LEFT", 6);
    } else if (d == RIGHT)
    {
        strncpy(str, "RIGHT", 6);
    } else if (d == INVALID)
    {
        strncpy(str, "INVALID", 6);
    }
}

void print_move(void* m)
{
    char str[6];
    move* a = (move*)m;
    direction_to_string(a->dir, str);
    printf("%s %d", str, a->distance);
}
