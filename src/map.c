#include "map.h"

#include <stdio.h>
#include <stdlib.h> /*malloc*/
#include <string.h> /*strchr*/

#include "treasure.h"

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
                if (result == ABORTED)
                {
                    free_map(*read_into, *rows, *cols);
                }
            }
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

map allocate_map(size_t rows, size_t cols)
{
    map result = (map)malloc(sizeof(treasure*) * rows);
    int i = 0;
    int j;
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

    /*After filling the map, assign every treasure.type == N,
    so that deallocation occurs successfully.*/
    if (result != NULL)
    {
        for (i = 0; i != rows; ++i)
        {
            for (j = 0; j != cols; ++j)
            {
                result[i][j].type = 'N';
            }
        }
    }
    return result;
}

void free_map(map x, size_t rows, size_t cols)
{
    size_t i;
    size_t j;
    for (i = 0; i != rows; ++i)
    {
        for (j = 0; j != cols; ++j)
        {
            /*Deallocate the detail string*/
            if (x[i][j].type != 'N')
            {
                free(x[i][j].detail);
            }
        }
        free(x[i]);
    }
    free(x);
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
        result = split(line, ',', tokens, cols);
        if (result == COMPLETE)
        {
            /*The token array has been filled.*/
            while (j < cols && result == COMPLETE)
            {
                result = make_treasure(tokens[j], read_into[i] + j);
                /*make_treasure will print an error if formatting is incorrect.
                However, it will not print where this error occured.*/
                if (result != COMPLETE)
                {
                    fprintf(stderr, "At row %zu, column %zu.\n", i + 1, j + 1);
                }
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

char* read_line(FILE* file)
{
    /*
    Attempt to read a line from a file with fgets.
    If the line was too big for the buffer,
    create a bigger array and try to read again.
    */
    int size = 100;
    char* str = malloc(sizeof(char) * size);
    long pos = ftell(file);
    char* error = str;
    char* end;
    str[size - 1] = 1;
    fgets(str, size, file);

    while (str[size - 1] == '\0' && error != NULL)
    {
        free(str);
        size *= 2;
        /*Does not check for allocation faliure*/
        str = malloc(sizeof(char) * size);
        fseek(file, pos, SEEK_SET);
        str[size - 1] = 1;
        error = fgets(str, size, file);
    }

    /*If a file error has occured,
    or we have reached eof before any characters could be read,
    create an empty string.*/
    if (error == NULL)
    {
        str[0] = '\0';
    }

    /*Remove any newlines at the end of the string*/
    end = strchr(str, '\n');
    if (end != NULL)
    {
        *end = '\0';
    }

    return str;
}

status split(char* line, char delim, char** tokens, size_t tokens_sz)
{
    size_t li = 0;
    size_t ti = 0;
    status result = COMPLETE;
    while(line[li] != '\0')
    {
        if (line[li] == delim)
        {
            /*Replace the delimiter with a line ending,
            and add it to the token array.*/
            line[li] = '\0';
            tokens[ti] = line + li;
            ++ti;
        }
        ++li;
    }

    if (ti != tokens_sz)
    {
        result = ABORTED;
    }
    return result;
}

void print_map(map x, size_t rows, size_t cols)
{
    size_t i;
    size_t j;
    for (i = 0; i != rows; ++i)
    {
        for (j = 0; j != cols; ++j)
        {
            printf("\nRow: %zu. Col: %zu. Treasure: ", i, j);
            print(x[i][j]);
        }
    }
}
