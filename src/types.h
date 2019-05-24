#ifndef GUARD_TYPES_H
#define GUARD_TYPES_H

typedef struct explorer explorer;
typedef struct treasure treasure;

/**
 * \brief Compares the gear with the person gear in the corresponding slot.
 *      If the person gear is worse, swap the gear objects and return 0.
 *      Otherwise, return 1.
 * Preconditions: person must have been initialized with \ref make_explorer.
 * gear must have been initialized with \ref make_treasure.
 */
typedef int (*compare_func)(treasure* gear, explorer* person);

/*
PURPOSE: Describes the current program status.
IMPLEMENTATION: Enum of all possible statuses. This means that a
    status of higher severity will be a higher number.
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
struct treasure
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
USAGE: explorer owns its treasure objects. If a treasure object has type 'N'
    and value < 0,
    then the explorer does not have any gear on that body part.
*/
struct explorer
{
    int magic;
    int coin;
    treasure head;
    treasure chest;
    treasure legs;
    treasure hands;
};

/*
PURPOSE: Creates an explorer with no gear.
USAGE: Returns an empty explorer.
*/
explorer make_explorer();

/*
PURPOSE: Frees the memory owned by the explorer.
USAGE: ex must have been created with make_explorer.
*/
void free_explorer(explorer ex);

/*
PURPOSE: Finds the total gear value of the explorer.
USAGE: Explorer must be initialized using make_explorer.
*/
int gear_value(explorer ex);

/*
PURPOSE: Prints the given status as text, into text_rep.
USAGE: text_rep length >= 10
*/
void status_text(status s, char* text_rep);

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
