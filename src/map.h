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
 * \details Writes to stderr if an error has occured.
 *      Only deallocate \p read_into
 *      if this function returns COMPLETE.
 */
status read_map(map* read_into, long* rows, long* cols, char* filename);

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

/**
 * \brief Fills a map with information from a csv file.
 * \param[in,out] read_into The map to read values into.
 * \param[in] rows The number of rows in the map.
 * \param[in] cols The number of columns in the map.
 * \param[in] file The file to read from.
 * \pre \p read_into must be created with \ref allocate_map.
 * \pre \p file must be opened in "r" mode.
 * \post \p file is not closed by this function.
 * \return If an error occurs, return ABORTED. Otherwise, return COMPLETE.
 * \details Writes to stderr if an error occurs.
 */
status fill_map(map read_into, size_t rows, size_t cols, FILE* file);

/**
 * \brief Reads a line from a file.
 * \param[in] file The file to read from.
 * \return The line that has been read from the file.
 * \pre \p file must be opened in "r" mode.
 * \post \ref free must be called on the returned string after use.
 * \post 
 * \details Reads until a newline or EOF is encountered.
 *      The newline is not included in the returned string.
 *      If no characters can be read, an empty string ('\0') is returned.
 */
char* read_line(FILE* file);

/**
 * \brief Splits a string into tokens, seperated by the given delimiter.
 * \param[in,out] line The string to split.
 * \param[in] delim The delimiter to split the string on.
 * \param[out] tokens An array of char*.
 *      Each element in the array points to a null-terminated token string.
 *      These tokens are "stored" in \p line.
 * \param[in] tokens_sz The size of \p tokens.
 * \return If the amount of potential tokens in \p line does not equal
 *      \p tokens_sz, return ABORTED. Otherwise, return COMPLETE.
 * \post \p line should not be read after splitting.
 * \details The delimiter is not included in a token.
 *      If multiple delimiters occur in order,
 *          the corresponding tokens are empty strings.
 *      The lifetime of \p tokens is equal to the lifetime of \p line.
 */
status split(char* line, char delim, char** tokens, size_t tokens_sz);

/**
 * \brief Prints a map to stdout.
 * \param[in] x The map to print.
 * \param[in] rows The number of rows in the map.
 * \param[in] cols The number of columns in the map.
 * \details Used for debugging purposes.
*/
void print_map(map x, size_t rows, size_t cols);

#endif
