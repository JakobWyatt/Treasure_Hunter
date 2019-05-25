#include "types.h"

#include <stdlib.h>
#include <string.h>

/**
 * \internal \n \n \b Implementation:
 * Initialize magic and coin to 0.
 * Initialize gear.type to 'N'.
 * Initialize gear.value to -1, so that when compared
 * the empty slot is always initially swapped.
 */
explorer make_explorer()
{
    explorer ex;
    ex.magic = 0;
    ex.coin = 0;
    ex.head.type = 'N';
    ex.head.value = -1;
    ex.chest.type = 'N';
    ex.chest.value = -1;
    ex.legs.type = 'N';
    ex.legs.value = -1;
    ex.hands.type = 'N';
    ex.hands.value = -1;
    return ex;
}

/**
 * \internal \n \n \b Implementation:
 * If gear.type == 'G' (non-empty), free the corresponding detail string.
 */
void free_explorer(explorer ex)
{
    if (ex.head.type == 'G')
    {
        free(ex.head.detail);
    }
    if (ex.chest.type == 'G')
    {
        free(ex.chest.detail);
    }
    if (ex.legs.type == 'G')
    {
        free(ex.legs.detail);
    }
    if (ex.hands.type == 'G')
    {
        free(ex.hands.detail);
    }
}

/**
 * \internal \n \n \b Implementation:
 * Simple else-if ladder to read the correct string
 * into \p text_rep.
 */
void status_text(status s, char* text_rep)
{
    if (s == COMPLETE)
    {
        strncpy(text_rep, "COMPLETE", 10);
    } else if (s == CORRECTED)
    {
        strncpy(text_rep, "CORRECTED", 10);
    } else if (s == FAILED)
    {
        strncpy(text_rep, "FAILED", 10);
    } else if (s == ABORTED)
    {
        strncpy(text_rep, "ABORTED", 10);
    }
}

/**
 * \internal \n \n \b Implementation:
 * If gear.type == 'G' (there is gear in that slot),
 * increment the accumulator by that gear's value.
 */
int gear_value(explorer ex)
{
    int value = 0;
    if (ex.head.type == 'G')
    {
        value += ex.head.value;
    }
    if (ex.chest.type == 'G')
    {
        value += ex.chest.value;
    }
    if (ex.legs.type == 'G')
    {
        value += ex.legs.value;
    }
    if (ex.hands.type == 'G')
    {
        value += ex.hands.value;
    }
    return value;
}
