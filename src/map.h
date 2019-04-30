#ifndef GUARD_MAP_H
#define GUARD_MAP_H

#include <stddef.h> /*size_t*/
#include <stdio.h> /*FILE*/

#include "explore.h" /*status*/
#include "treasure.h" /*treasure*/

/********************
Type declarations
********************/

/********************
Type definitions
********************/

/*
PURPOSE: Stores information about the map.
IMPLEMENTATION: Typedef of pointer to pointer to treasure.
USAGE: 2D dynamically allocated array of treasure structs.
*/
typedef treasure** map;

/********************
Function declarations
********************/

/*
PURPOSE: Reads in a map from a file.
USAGE: Imports filename. Exports read_into, rows, cols, and status.
    If an error was encountered, it is written to stderr and the returned status is
    ABORTED. Otherwise, the returned status is COMPLETE.
    Use free_map(map, size_t, size_t) to free the data after use.
    This should only be done if the status == COMPLETE.
*/
status read_map(map* read_into, size_t* rows, size_t* cols, char* filename);

/*
PURPOSE: Dynamically allocates a map (2d array of treasure).
USAGE: Returns a dynamically allocated map. If map==NULL, allocation failed.
*/
map allocate_map(size_t rows, size_t cols);

/*
PURPOSE: Deallocates a map.
USAGE: After map has been used, deallocate it.
*/
void free_map(map x, size_t rows, size_t cols);

/*
PURPOSE: Fills a map with information from a file.
USAGE: Imports rows, cols, and file. Exports read_into and status.
    Assumes that read_into has already been allocated correctly and
        file is not null.
    If any errors or invalid rows are encountered,
        an error message is written to stderr and the returned status is ABORTED.
    Otherwise, the returned status is COMPLETE.
*/
status fill_map(map read_into, size_t rows, size_t cols, FILE* file);

/*
PURPOSE: Reads a line from a file.
USAGE: Reads from a file until newline or EOF is encountered.
    Newline is not included in the returned string.
    If an attempt to read from the file immediately results in EOF,
        an empty string is returned.
    The returned string must be freed after use.
*/
char* read_line(FILE* file);

/*
PURPOSE: Splits a string with the given delimiter.
USAGE: tokens is a pointer to an array of char*.
    Each token is stored in tokens as it is parsed.
    If the number of tokens is not equal to tokens_sz, ABORTED is returned.
    Otherwise, COMPLETE is returned.
    Strings stored in tokens remain in scope as long as line remains in scope.
*/
status split(char* line, char delim, char** tokens, size_t tokens_sz);

/*
PURPOSE: Prints a map to stdout.
USAGE: For debugging purposes.
*/
void print_map(map, size_t rows, size_t cols);

#endif
