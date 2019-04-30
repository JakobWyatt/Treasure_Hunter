#ifndef GUARD_MOVEMENT_H
#define GUARD_MOVEMENT_H

#include "types.h"
#include "list.h"

/*
PURPOSE: Read moves from a file into a linked list.
USAGE: Imports a filename. Exports a list.
If there is an error in the file, a message is printed to stderr,
and ABORTED is returned.
*/
status read_moves(list* moves, char* filename);

/*
PURPOSE: Parse a movement line, and add it to the linked list.
USAGE: Imports a string that optionally ends with a newline.
Exports moves. line must not be NULL.
If there is an error in the line, a message is printed to stderr,
and ABORTED is returned.
This function modifies moves on failure, and therefore does not have
strong exception safety.
*/
status parse_movement(list* moves, char* line);

#endif
