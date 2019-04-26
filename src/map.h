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
    Use free_map(map, size_t) to free the data after use.
*/
status read_map(map* read_into, size_t* rows, size_t* cols, char* filename);

/*
PURPOSE: Dynamically allocates a map (2d array of treasure).
USAGE: Returns a dynamically allocated map. If map==NULL, allocation failed.
*/
map allocate_map(size_t rows, size_t cols);

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

#endif
