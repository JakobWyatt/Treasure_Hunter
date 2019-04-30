#ifndef GUARD_TYPES_H
#define GUARD_TYPES_H

typedef struct explorer_s explorer;
typedef struct treasure_s treasure;

/*
PURPOSE: Represent the type of the treasure compare function.
IMPLEMENTATION: Typedef of function pointer.
USAGE: Compares the gear with the persons corresponding gear,
    and swap them if the persons gear is worse.
*/
typedef void (*compare_func)(treasure* gear, explorer* person);

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
struct treasure_s
{
    char type;
    int value;
    compare_func compare;
    char* detail;
};

/*
PURPOSE: Stores the current items owned by the explorer.
IMPLEMENTATION: Struct containing total magic and coin value, as well as
    pointers to gear objects.
USAGE: explorer owns its treasure objects.
*/
struct explorer_s
{
    int magic;
    int coin;
    treasure head;
    treasure chest;
    treasure legs;
    treasure hands;
};

/*
PURPOSE: Stores information about the map.
IMPLEMENTATION: Typedef of pointer to pointer to treasure.
USAGE: 2D dynamically allocated array of treasure structs.
*/
typedef treasure** map;

/*
PURPOSE: Stores the direction of a move action.
IMPLEMENTATION: Enum of all possible directions.
USAGE: Used inside move struct.
*/
typedef enum
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    INVALID
} direction;

/*
PURPOSE: Stores a move action, which consists of a direction and distance.
IMPLEMENTATION: Struct of direction enum and distance.
USAGE: Stored in linked list to show all user actions.
*/
typedef struct
{
    direction dir;
    int distance;
} move;

#endif
