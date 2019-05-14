#include "types.h"

#include <stdlib.h>
#include <string.h>

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
