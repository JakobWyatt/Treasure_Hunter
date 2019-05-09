#ifndef GUARD_TREASURE_H
#define GUARD_TREASURE_H

#include "types.h"

/********************
Function declarations
********************/

/*
PURPOSE: Parses the string and overwrites make's data.
USAGE: If the string was invalid, print the error to stderr and
    return ABORTED. Otherwise, return COMPLETE.
*/
status make_treasure(char* str, treasure* make);

/*
PURPOSE: Swap the two treasures.
USAGE: Imports two pointers to the treasures to be swapped.
*/
void swap(treasure* a, treasure* b);

/*
PURPOSE: Chooses the corresponding compare_func for a given string.
USAGE: If str is invalid, compare_func is NULL.
*/
compare_func chooseCompareFunc(char* str);

/*
PURPOSE: Writes the textual representation of the slot into the string.
USAGE: The number of bytes in string must be >= 6.
*/
void slot(treasure x, char* str);

/*
PURPOSE: Converts the given string to lowercase.
USAGE: str must be null-terminated.
*/
void toLowerStr(char* str);

/*
PURPOSE: Prints a treasures information to stdout.
USAGE: For debugging.
*/
void print(treasure x);

/*
Implementation of compare_func for head, chest, legs, and hands gear.
ASSERTIONS:
gear.value is defined.
*/

int compareHead(treasure* gear, explorer* person);

int compareChest(treasure* gear, explorer* person);

int compareLegs(treasure* gear, explorer* person);

int compareHands(treasure* gear, explorer* person);

#endif
