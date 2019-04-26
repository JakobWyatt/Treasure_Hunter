#ifndef GUARD_TREASURE_H
#define GUARD_TREASURE_H

#include "explore.h" /*explorer*/

/********************
Type declarations
********************/
struct treasure;

/********************
Type definitions
********************/

/*
PURPOSE: Represent the type of the treasure compare function.
IMPLEMENTATION: Typedef of function pointer.
USAGE: Compares the gear with the persons corresponding gear,
    and swap them if the persons gear is worse.
*/
typedef void (*compare_func)(treasure* gear, explorer* person);

/*
PURPOSE: Stores information about a treasure.
IMPLEMENTATION: Struct containing the type of treasure:
    'C': Coins
    'M': Magic
    'G': Gear
    'N': None

    Value: The value of the treasure (invalid for type='N')
    Detail: A string description of the treasure (invalid for type='N' or 'C')
    Compare: A function pointer for comparison and swapping of the gear.
    (only valid for type='G')
USAGE: Owned by either the map or explorer.
*/
typedef struct
{
    char type;
    int value;
    compare_func compare;
    char* detail;
} treasure;

/********************
Function declarations
********************/

/*
PURPOSE: Swap the two treasures.
USAGE: Imports two pointers to the treasures to be swapped.
*/
void swap(treasure* a, treasure* b);

/*
Implementation of compare_func for head, chest, legs, and hands gear.
ASSERTIONS:
gear.type == 'G'
*/

void compareHead(treasure* gear, explorer* person);

void compareChest(treasure* gear, explorer* person);

void compareLegs(treasure* gear, explorer* person);

void compareHands(treasure* gear, explorer* person);

#endif
