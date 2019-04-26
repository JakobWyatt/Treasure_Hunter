#include <stdio.h>

int main(int argc, char* argv[])
{
    /*
    General flow of events:
    - Read the map into a 2d array. The datatype of this array will be a struct consisting of:
        An enum, describing what the datatype of the item is.
        A void ptr, which points to the location of the item.
    -Read the adventure file into a linked list.
        Any errors in these first two steps are written to stderr, and changes the status to ABORTED.
    -Resolve the adventure, keeping track of:
        Gear equipped.
        Total magic value.
        Total coins.

        This is done by iterating through the linked list.
        Boundary checking is done conditionally.
        Logging is done via the file adventure.log, and is conditionally written to stdout.
        If an out of bounds error is encountered, control flow ends and the status is FAILED.
        If the path is changed, control flow continues and the status is CORRECTED.
    -Print the output of the program.
    */
}
