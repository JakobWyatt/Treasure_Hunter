#include "map.h"

#include <stdio.h>
#include <stdlib.h> /*malloc*/

status read_map(map* read_into, size_t* rows, size_t* cols, char* filename)
{
    status result = COMPLETE;
    int args_read;
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file %s for reading: ", filename);
        perror("");
        result = ABORTED;
    } else
    {
        /*Note: fscanf does not protect against integer overflow.*/
        args_read = fscanf(file, "%zu,%zu", rows, cols);
        if (args_read != 2)
        {
            fprintf(stderr, "Incorrect formatting in %s, line 1: Expected <rows>,<cols>\n", filename);
            result = ABORTED;
        } else
        {
            *read_into = allocate_map(*rows, *cols);
            if (*read_into == NULL)
            {
                perror("Failed to allocate memory for map: ");
                result = ABORTED;
            } else {
                result = fill_map(*read_into, *rows, *cols, file);
            }
        }
        /*Cleanup file reads: check error state and close stream.*/
        if (ferror(file))
        {
            fprintf("Error occured while reading from %s: ", filename);
            perror("");
            result = ABORTED;
        }
        fclose(file);
    }
    return result;
}

map allocate_map(size_t rows, size_t cols)
{
    map result = (map)malloc(sizeof(treasure*) * rows);
    int i = 0;
    if (result != NULL)
    {
        /*If allocation fails at any point,
        stop trying to allocate more memory.*/
        do
        {
            result[i] = (treasure*)malloc(sizeof(treasure) * cols);
            ++i;
        } while (i < rows && result[i - 1] != NULL);

        /*Has allocation failed?*/
        if (result[i - 1] == NULL)
        {
            /*deallocate all memory so far*/
            --i;
            while (i >= 0)
            {
                free(result[i]);
                --i;
            }
            free(result);
            result = NULL;
        }
    }
    return result;
}

status fill_map(map read_into, size_t rows, size_t cols, FILE* file)
{
    size_t i = 0;
    size_t j = 0;
    char* line;
    char** tokens = (char**)malloc(sizeof(char*) * cols);
    status result = COMPLETE;
    /*As soon as incorrect formatting is encountered, stop reading the file*/
    while (i < rows && result == COMPLETE)
    {
        /*To fill the map, we will:
            -Read the line.
            -Split the line using split.
            -Use make_treasure to construct a new treasure, and add it to the map.

            strtok cannot be used, as it skips over repeated delimiters.
            Creating a function to read up until a delimiter can be used,
                however it complicates matters when the file does not end with a newline.
        */
        line = read_line(file);
        result = split(tokens, cols, line, ',');
        if (result == COMPLETE)
        {
            /*The token array has been filled.*/
            while (j < cols && result == COMPLETE)
            {
                result = make_treasure(tokens[j], read_into[i] + j);
                ++j;
            }
        } else
        {
            /*If we have reached EOF on the file, there is an incorrect number of rows.
            Otherwise, there is an incorrect number of columns.*/
            if (feof(file))
            {
                fprintf(stderr, "Incorrect number of rows: read %zu, expected %zu.\n", i, rows);
            } else
            {
                fprintf(stderr, "Incorrect number of columns at row %zu: expected %zu.\n", i + 1, cols);
            }
        }
        ++i;
        j = 0;
        free(line);
    }
    free(tokens);

    return result;
}
/*
char* read_line(file)
{

}
*/