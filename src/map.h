#ifndef GUARD_MAP_H
#define GUARD_MAP_H

#include <stddef.h> /*size_t*/
#include <stdio.h> /*FILE*/

#include "types.h" /*status*/

/**
    \file map.h
    \brief Contains functions to read, allocate, and free a 2D map.
 */

/**
 * \brief Reads in a map from a file.
 * \param[out] read_into Pointer to the created map.
 * \param[out] rows The number of rows in the map.
 * \param[out] cols The number of cols in the map.
 * \param[in] filename The name of the file to read into.
 * \return If an error occurs, returns ABORTED. Otherwise,
 *      returns COMPLETE.
 * \post \p read_into must be deallocated with \ref free_map.
 * \details Writes to stderr if an error has occured. Only deallocate \p read_into
 *      if this function returns COMPLETE.
 */
status read_map(map* read_into, size_t* rows, size_t* cols, char* filename);

/**
 * \brief Allocates a map dynamically (on the heap).
 * \param[in] rows The number of rows in the map.
 * \param[in] cols The number of columns in the map.
 * \return The allocated map. This is NULL if allocation failed.
 * \post \ref free_map must be called on the returned map if it is not NULL.
 */
map allocate_map(size_t rows, size_t cols);

/**
 * \brief Deallocates a map that has been created with \ref allocate_map.
 * \param[in,out] x The map to free.
 * \param[in] rows The number of rows in the map.
 * \param[in] cols The number of columns in the map.
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

/**
 * \brief Fills a map
 * \param[in,out] read_into The map to read values into. This must be created with
 *      \ref allocate_map.
 * \param[in] rows The number of rows in the map.
 * \param[in] cols The number of columns in the map.
 * \param[in] 
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
