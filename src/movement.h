#ifndef GUARD_MOVEMENT_H
#define GUARD_MOVEMENT_H

#include "types.h"
#include "list.h"

/**
    \file movement.h
    \brief Contains functions to read movements from a file into a linked list.
*/

/**
 * \brief Reads moves from a file into a linked list.
 * \param[out] moves The list to read moves into.
 * \param[in] filename The filename to read from.
 * \return If the file contains incorrect formatting, return ABORTED.
 *      Otherwise, return COMPLETE.
 * \pre \p moves is created with \ref make_list.
 * \post \p moves must be deallocated with \ref free_list, regardless
 *      of the return status of this function.
 * \details If the file contains incorrect formatting, print a message
 *      to stderr.
 */
status read_moves(list* moves, char* filename);

/**
 * \brief Parse a line of movement and add it to the list.
 * \param[out] moves The list to read the movement into.
 * \param[in] line The line to read from.
 * \return If there is an error in the line, return ABORTED.
 *      Otherwise, return COMPLETE.
 * \pre \p line must be null-terminated, and must not be NULL.
 * \details This function modifies \p moves on faliure, and therefore
 *      does not have strong exception safety. If there is an error
 *      in the line, a message is printed to stderr.
 */
status parse_movement(list* moves, char* line);

/**
 * \brief Converts a string to a \ref direction.
 * \param[in] dir The string describing the direction.
 * \return The direction represented by \p dir. If the direction is invalid,
 *      return INVALID.
 * \pre \p dir must be null-terminated, and must not be NULL.
 * \post \p dir is converted to lowercase in this process.
 */
direction choose_dir(char* dir);

/**
 * \brief Converts a direction to an uppercase string.
 * \param[in] d The direction to convert.
 * \param[out] str The string to write the direction to.
 * \post \p str must be able to hold at least 8 characters.
 */
void direction_to_string(direction d, char* str);

/**
 * \brief Prints a move to stdout.
 * \param[in] m A pointer to the \ref move to print.
 * \details \p m is a void* so that this function is compatible with \ref for_each.
 *      Used for debugging purposes.
 */
void print_move(void* m);

#endif
