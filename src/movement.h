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

#endif
