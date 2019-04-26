#include "map.h"

#include <stdio.h>
#include <stdlib.h>

status read_map(map* read_into, size_t* rows, size_t* cols, char* filename)
{
    status result = COMPLETE;
    int result;
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error opening file %s for reading: ", filename);
        perror("");
        result = ABORTED;
    } else
    {
        /*Note: fscanf does not protect against integer overflow.*/
        result = fscanf(file, "%zu,%zu", rows, cols);
        if (result != 2)
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
    status result = COMPLETE;
    
}
