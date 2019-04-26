#ifndef GUARD_EXPLORE_H
#define GUARD_EXPLORE_H

#include "map.h" /*treasure*/

/********************
Type declarations
********************/
enum status;

/********************
Type definitions
********************/

/*
PURPOSE: Describes the current program status.
IMPLEMENTATION: Enum of all possible statuses.
USAGE: Returned from functions to show the program status after execution.
*/
typedef enum
{
    COMPLETE,
    CORRECTED,
    FAILED,
    ABORTED
} status;

/*
PURPOSE: Stores the current items owned by the explorer.
IMPLEMENTATION: Struct containing total magic and coin value, as well as
    pointers to gear objects.
USAGE: explorer owns its treasure objects.
*/
typedef struct
{
    int magic;
    int coin;
    treasure head;
    treasure chest;
    treasure legs;
    treasure hands;
} explorer;

/********************
Function declarations
********************/

status explore();

#endif
