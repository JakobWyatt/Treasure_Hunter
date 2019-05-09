#ifndef GUARD_ADVENTURE_H
#define GUARD_ADVENTURE_H

#include <stdio.h> /*FILE**/

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
    This function does modify the map, and removes any items it encounters.
*/
status resolveAdventure(map items, unsigned long rows, unsigned long cols, list movements, explorer* person, FILE* file);

/*
PURPOSE: Collects the treasure at the given location, and logs it.
USAGE: file must not be null. pseron must not be null. i and j must reference
    a legitimate treasure in the map.
*/
void collectAndLog(FILE* file, map items, explorer* person, unsigned long i, unsigned long j);

/*
PURPOSE: Logs the treasure to a file, and optionally stdout.
USAGE: If collect == 0, then collect. Else, discard.
*/
void logTreasure(FILE* file, treasure x, int collect, unsigned long i, unsigned long j);

/*
PURPOSE: Finds the end block of a given direction.
USAGE: Returns FAILED if out of bounds and CORRECTED if corrected.
*/
status endBlock(unsigned long rows, unsigned long cols,
    unsigned long* i, unsigned long* j, move x);

/*
PURPOSE: Moves a location a given distance in a given direction.
USAGE: dir must not be INVALID.
*/
void move_dist(direction dir, unsigned long distance, unsigned long* i, unsigned long* j);

#endif
