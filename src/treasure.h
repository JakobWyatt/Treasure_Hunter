#ifndef GUARD_TREASURE_H
#define GUARD_TREASURE_H

#include "types.h"

/**
    \file treasure.h
    \brief Contains functions to create and manipulate \ref treasure structs.
*/

/**
 * \brief Parses \p str to create a treasure object.
 * \param[in] str The string to parse.
 * \param[out] make The created treasure.
 * \pre \p str must be null-terminated, and must not be NULL.
 * \pre \p make must be dynamically allocated (on the heap) before calling
 *      this function.
 * \post If \p str is empty, \p make->type == 'N'.
 * \return If the string is invalid, return ABORTED.
 *      Otherwise, return COMPLETE.
 * \details If the string is invalid, print an error message to stderr.
 *      Negative treasure values are valid. This is so that negative effects
 *      can be impemented.
 *      For example, if an explorer stumbles across a potion that ends up
 *      being a poison, their magic value is reduced.
 *      Likewise, negative coins could be valid if the explorer
 *      is robbed by bandits.
 */
status make_treasure(char* str, treasure* make);

/**
 * \brief Swaps two treasures.
 * \param[in,out] a The first treasure to swap.
 * \param[in,out] b The second treasure to swap.
 * \pre \p a and \p b must not be NULL.
 */
void swap(treasure* a, treasure* b);

/**
 * \brief Chooses a compare function given a body part.
 * \param[in] str The string representing a body part.
 * \return A function pointer to the correct compare function.
 * \post If \p str is invalid, return NULL.
 */
compare_func chooseCompareFunc(char* str);

/**
 * \brief Writes the textual representation of the gear slot into the string.
 * \param[in] x The treasure containing the gear slot.
 * \param[out] str The string to write the representation into.
 * \pre \p str must be able to hold at least 6 characters.
 * \details If \p x.type != 'G', do not modify \p str.
 */
void slot(treasure x, char* str);

/**
 * \brief Converts the given string to lowercase.
 * \param[in,out] str The string to convert to lowercase.
 */
void toLowerStr(char* str);

/**
 * \brief Prints a treasure to stdout.
 * \param[in] x The treasure to print.
 * \details Used for debugging. If \p x.type == 'N',
 *      do not print anything.
 */
void print(treasure x);

/**
 * \brief Implementation of \ref compare_func for the head slot.
 */
int compareHead(treasure* gear, explorer* person);

/**
 * \brief Implementation of \ref compare_func for the head slot.
 */
int compareChest(treasure* gear, explorer* person);

/**
 * \brief Implementation of \ref compare_func for the head slot.
 */
int compareLegs(treasure* gear, explorer* person);

/**
 * \brief Implementation of \ref compare_func for the head slot.
 */
int compareHands(treasure* gear, explorer* person);

#endif
