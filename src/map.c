#include "map.h"

#include <stdio.h>
#include <stdlib.h> /*malloc*/
#include <string.h> /*strchr*/

#include "treasure.h"

/**
 * \internal \n \n \b Implementation:
 * This function performs the majority of file opening, size determination, and allocation.
 * If there is an error in any of the stages listed below, perform any neccesary cleanup
 *  and exit the function.
 * -# Open the file in "r" mode.
 * -# Read the size of the map.
 * -# Allocate the map with \ref allocate_map.
 * -# Read values into the map with \ref fill_map.
 */
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
        args_read = fscanf(file, "%lu,%lu\n", rows, cols);
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


/**
 * \internal \n \n \b Implementation:
 * The map consists of an array of arrays. Allocate the top level array first.
 * If this was successful, then allocate rows one at a time.
 * If row allocation fails at any point, iterate backwards through the row arrays
 *      that have already been allocated, and free them.
 * After allocation, set the type of each map element to 'N'. This represents the
 *      map having no elements, and allows deallocation to work as expected.
 */
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

/**
 * \internal \n \n \b Implementation:
 * The only dynamically allocated element in \ref treasure is
 *  the detail string.
 * First, iterate through the map and deallocate any detail strings
 *  if the type is either 'G' (gear) or 'M' (magic).
 * Next, deallocate each row array.
 * Finally, deallocate the column array.
 */
void free_map(map x, size_t rows, size_t cols)
{
    size_t i;
    size_t j;
    for (i = 0; i != rows; ++i)
    {
        for (j = 0; j != cols; ++j)
        {
            /*Deallocate the detail string*/
            if (x[i][j].type != 'N' && x[i][j].type != 'C')
            {
                free(x[i][j].detail);
            }
        }
        free(x[i]);
    }
    free(x);
}

/**
 * \internal \n \n \b Implementation:
 * Stop reading the file as soon as incorrect formatting is encountered.
 * While there are still empty map rows:
 *  -# Read the current line of the file with \ref read_line.
 *  -# Split the line with \ref split.
 *  -# If the correct number of tokens has been read, convert each token
 *      into a treasure with \ref make_treasure and add it to the map.
 * Any errors are printed to stderr.
 * Strtok cannot be used for this function, as it skips repeated delimiters.
 */
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
                    fprintf(stderr, "At row %lu, column %lu.\n", (unsigned long)i + 1, (unsigned long)j + 1);
                }
                ++j;
            }
        } else
        {
            /*If we have reached EOF on the file, there is an incorrect number of rows.
            Otherwise, there is an incorrect number of columns.*/
            if (feof(file))
            {
                fprintf(stderr, "Incorrect number of rows: read %lu, expected %lu.\n", (unsigned long)i + 1, (unsigned long)rows);
            } else
            {
                fprintf(stderr, "Incorrect number of columns at line %lu: expected %lu.\n", (unsigned long)i + 2, (unsigned long)cols);
            }
        }
        ++i;
        j = 0;
        free(line);
    }
    free(tokens);

    return result;
}

/**
 * \internal \n \n \b Implementation:
 * \ref read_line attemps to read a line from a file using fgets,
 *      with an initial buffer size of 100. If the last character
 *      in the string has been overwritten then the buffer is
 *      assumed to be too small, and a bigger buffer is allocated.
 *      The file position is then returned to its state at the
 *      start of the function, and reading is attempted again.
 *      This process is repeated until the entire line has been read.
 * Any newline characters in the string are found with strchr, and removed.
 */
char* read_line(FILE* file)
{
    int size = 100;
    char* str = malloc(sizeof(char) * size);
    long pos = ftell(file);
    char* error = str;
    char* end;
    /*Set the final character,
    to check if it has been overwritten or not.*/
    str[size - 1] = 'A';
    error = fgets(str, size, file);

    while (str[size - 1] == '\0' && error != NULL)
    {
        free(str);
        size *= 2;
        /*Does not check for allocation faliure*/
        str = malloc(sizeof(char) * size);
        fseek(file, pos, SEEK_SET);
        str[size - 1] = 'A';
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


/**
 * \internal \n \n \b Implementation:
 * The gist of this function is quite simple, although the implementation
 * becomes more complex as error checking is introduced.
 * At its core, this algorithm:
 *  -# Finds the next delimiter in \p line.
 *  -# Assigns the location of the delimiter in \p line to '\0'.
 *  -# Adds a new element to \p tokens, located 1 after the delimiter.
 *          This is the start of the next token.
 * 
 * Now, assume that the above algorithm ends when either:
 *  - The end of the string has been reached.
 *  - The token array is full.
 * 
 * If the number of tokens is less than tokens_sz, there are too few tokens
 * in \p line and the algorithm ends with status ABORTED.
 * However, if the number of tokens is equal to tokens_sz, it is not yet known
 *      if all delimiters have been found or not. To resolve this, find the next
 *      character that is either a delimiter or a null terminator.
 * If it is a null terminator, then we have read the correct number of tokens,
 *  and the algorithm ends with status COMPLETED.
 * If it is a delimiter, we still have token(s) we have not read yet,
 *  and the algorithm ends with status ABORTED.
 */
status split(char* line, char delim, char** tokens, size_t tokens_sz)
{
    size_t li = 0;
    size_t ti = 1;
    status result = COMPLETE;
    
    /*The first token starts at the beginning of the string*/
    tokens[0] = line;
    
    /*Ensure the token array doesn't go out of bounds.*/
    while(line[li] != '\0' && ti < tokens_sz)
    {
        if (line[li] == delim)
        {
            /*Replace the delimiter with a line ending,
            and add it to the token array.*/
            line[li] = '\0';
            tokens[ti] = line + li + 1;
            ++ti;
        }
        ++li;
    }

    /*
    Check for errors
    */
    if (ti < tokens_sz)
    {
        result = ABORTED;
    } else
    {
        while (line[li] != '\0' && line[li] != delim)
        {
            ++li;
        }
        if (line[li] != '\0')
        {
            result = ABORTED;
        }
    }

    return result;
}

/**
 * \internal \n \n \b Implementation:
 * Iterate through the map, printing each treasure using \ref print(treasure).
 * Also print information about the location of the treasure (row and column).
 */
void print_map(map x, size_t rows, size_t cols)
{
    size_t i;
    size_t j;
    for (i = 0; i != rows; ++i)
    {
        for (j = 0; j != cols; ++j)
        {
            printf("\nRow: %lu. Col: %lu. Treasure: ", (unsigned long)i, (unsigned long)j);
            print(x[i][j]);
        }
    }
}
