#ifndef GUARD_TYPES_H
#define GUARD_TYPES_H

/**
    \file types.h
    \brief Contains miscellaneous types used in the program,
        as well as simple functions to manipulate these types.
*/

typedef struct explorer explorer;
typedef struct treasure treasure;

/**
 * \brief Compares \p gear with \p person gear, in the corresponding slot.
 *  Swaps the gear objects if \p person gear is worse.
 * \param[in,out] gear The gear to compare.
 * \param[in,out] person The person to compare.
 * \return If the gear objects are swapped, return 0. Otherwise, return 1.
 * \pre \p person must be initialized with \ref make_explorer.
 * \pre \p gear must be initialized with \ref make_treasure.
 */
typedef int (*compare_func)(treasure* gear, explorer* person);

/**
 * \brief Describes all possible final program statuses.
 * \details A status of higher severity will be represented as a higher number.
 */
typedef enum
{
    /** The program completed sucessfully. */
    COMPLETE,
    /** While traversing the map, a movement went out of bounds
     * and was corrected. */
    CORRECTED,
    /** While traversing the map, a movement went out of bounds
     * and was not corrected. */
    FAILED,
    /** There was an error while reading a file. */
    ABORTED
} status;

/** 
 * \brief Stores information about a treasure.
 * \details Memory should be owned by either \ref map or \ref explorer at all times.
*/
struct treasure
{
    /** Type can be either 'N' (None), 'G' (Gear), 'M' (Magic), 'C' (Coins). */
    char type;
    /** The value of the treasure. Invalid for type == 'N'. */
    int value;
    /** A function pointer to swap the gear in the correct slot. Valid iff type == 'G'. */
    compare_func compare;
    /** A string description of the treasure. Invalid for type == 'N' || type == 'C'. */
    char* detail;
};

/**
 * \brief Stores the current items owned by the explorer.
 * \details If any \ref treasure object has type == 'N' and value < 0,
 *      \ref explorer does not have any gear on that body part.
 */
struct explorer
{
    /** The total accumulated magic value the explorer has collected. */
    int magic;
    /* The total accumulated coin value the explorer has collected. */
    int coin;
    /* Gear on the head slot. */
    treasure head;
    /* Gear on the chest slot. */
    treasure chest;
    /* Gear on the legs slot. */
    treasure legs;
    /* Gear on the hands slot. */
    treasure hands;
};

/**
 * \brief Creates an explorer.
 * \return An explorer with no magic, coin, or gear.
 */
explorer make_explorer();

/**
 * \brief Frees any memory owned by the explorer.
 * \param[in,out] ex The explorer to free.
 */
void free_explorer(explorer ex);

/**
 * \brief Finds the total value of all gear owned by the explorer.
 * \param[in] ex The explorer to calculate the total value of all gear for.
 * \return The total value of all gear.
 * \pre \p ex must be created with \ref make_explorer.
 */
int gear_value(explorer ex);

/**
 * \brief Converts the status to text.
 * \param[in] s The status to convert.
 * \param[out] text_rep The location to print the status string.
 * \pre \p text_rep must be able to hold at least 10 characters.
 */
void status_text(status s, char* text_rep);

/**
 * \brief Typedef to store a map.
 * \details Consists of a 2D dynamically allocated array of treasure structs.
 */
typedef treasure** map;

/**
 * \brief Stores the direction of a move.
 */
typedef enum
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    INVALID
} direction;

/**
 * \brief Stores a move action.
 * \details Used inside a linked list to show all actions to be taken by \ref explorer.
 */
typedef struct
{
    /** The direction to move. */
    direction dir;
    /** The distance to move. */
    int distance;
} move;

#endif
