#ifndef GUARD_ADVENTURE_H
#define GUARD_ADVENTURE_H

#include <stdio.h> /*FILE**/

#include "types.h"
#include "list.h"

/**
    \file adventure.h
    \brief Contains functions used to explore a map and collect items.
 */

/**
 * \brief Resolve an adventure, given a map and a list of movements.
 * \param[in,out] items Map containing all items.
 * \param[in] rows Number of rows in the map.
 * \param[in] cols Number of columns in the map.
 * \param[in] movements Movements to be made by the explorer.
 * \param[in,out] person Explorer to collect items.
 * \param[in] file File to write logs to.
 * \return SUCCESS if the adventure was sucessful,
 *          CORRECTED if out of bounds movements were corrected,
 *          FAILED if out of bounds movements weren't corrected.
 * \pre \p file must be opened in "a" mode.
 * \post \p items is modified when \ref treasure is picked up by \p person.
 * \post \p items and \p movements are not deallocated by this function.
 * \details Define AI to correct out of bounds movements.
 *          Define LOG to log movements to stdout as well as \p file.
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
