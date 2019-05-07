#ifndef GUARD_ADVENTURE_H
#define GUARD_ADVENTURE_H

#include "types.h"
#include "list.h"

/*
PURPOSE: Resolve an adventure, given a map and a list of movements.
USAGE: Returns the status: CORRECTED if any out of bounds movements
    were corrected, FAILED if out of bounds movements weren't corrected,
    and SUCCESS if the adventure completed sucessfully.
    All movements are logged to adventure.log. They are also logged to stdout
    if LOG is defined.
    Out of bounds movements are corrected by defining AI.
    This function does not deallocate map or list.
*/
status resolveAdventure(map items, list movements, explorer* person);

#endif
