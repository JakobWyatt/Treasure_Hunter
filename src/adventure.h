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

/**
 * \brief Collects the treasure at the given location. Logs this event to a file.
 * \param[in] file File to log information to.
 * \param[in,out] items Map containing item to collect.
 * \param[in,out] person Explorer to collect the item.
 * \param[in] i y location of the treasure to collect.
 * \param[in] j x location of the treasure to collect.
 * \pre \p file must be opened in "a" mode.
 * \post The treasure in \p items is either swapped, destroyed (and deallocated), or retained.
*/
void collectAndLog(FILE* file, map items, explorer* person, unsigned long i, unsigned long j);

/**
 * \brief Logs a treasure to a file, and optionally stdout.
 * \param[in] file File to log information to.
 * \param[in] x Treasure to log.
 * \param[in] collect If \p collect == 0, then log \p x as collected.
 *      Else, log it as discarded.
 * \param[in] i y location of the treasure.
 * \param[in] j x location of the treasure.
 * \pre \p file must be opened in "a" mode.
 * \detail Define LOG to write the information to stdout as well as \p file.
*/
void logTreasure(FILE* file, treasure x, int collect, unsigned long i, unsigned long j);

/**
 * \brief Finds the final block after a movement is performed.
 * \param[in] rows The number of rows in the map.
 * \param[in] cols The number of cols in the map.
 * \param[in,out] i The starting y location. Exports the new y location.
 * \param[in,out] j The starting x location. Exports the new x location.
 * \param[in] x The movement direction and distance.
 * \return SUCCESS if the movement was performed correctly,
 *          CORRECTED if the movement was corrected,
 *          FAILED if the movement is out of bounds.
 * \details Define AI to correct out of bounds movements.
*/
status endBlock(unsigned long rows, unsigned long cols,
    unsigned long* i, unsigned long* j, move x);

/**
 * \brief Moves a given distance in a given direction.
 * \param[in] dir The direction to move.
 * \param[in] distance The distance to move.
 * \param[in,out] i The starting y location. Exports the new y location.
 * \param[in,out] j The starting x location. Exports the new x location.
 * \post Does not check if the distance is valid.
*/
void move_dist(direction dir, unsigned long distance, unsigned long* i, unsigned long* j);

#endif
