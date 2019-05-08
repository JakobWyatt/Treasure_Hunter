#include "adventure.h"

#include <stdio.h> /*NULL*/

/*movements.head must not be equal to null
file must not be NULL, and must be opened in "a" mode*/
status resolveAdventure(map items, unsigned long rows, unsigned long cols, list movements, explorer* person, FILE* file)
{
    status result = COMPLETE;
    status temp_result = COMPLETE;
    /*Iterate through the list of movements, keeping track of where we've been so far*/
    unsigned long end_i = 0;
    unsigned long end_j = 0;
    unsigned long i = 0;
    unsigned long j = 0;

    fprintf(file, "---\n");

    /*The control flow of our algorithm is
    get_end -> Check for error -> (Traverse map, log as we go)*/
    node* current = movements.head;
    /*First, find the final block. This is the block we will stop moving on,
    and represents the end of a single command.
    Returns corrected, failed, or success.*/
    temp_result = endBlock(rows, cols, &end_i, &end_j, *(move*)(current->data));
    /*Choose the more severe result*/
    if (result < temp_result)
    {
        result = temp_result;
    }

    while (current != NULL && result != FAILED)
    {
        /*This does not collect/log the final tile after moving*/
        while (i != end_i || j != end_j)
        {
            collectAndLog(file, items, person, i, j);
            ++i;
            ++j;
        }
        current = current->next;
        
    }
    collectAndLog(file, items, person, i, j);

    return result;
}

void collectAndLog(FILE* file, map items, explorer* person, unsigned long i, unsigned long j)
{

}

status endBlock(unsigned long rows, unsigned long cols,
    unsigned long* i, unsigned long* j, move x)
{
    status result = COMPLETE;
    /*Move distance, correct, check bounds.*/
    move_dist(x.dir, x.distance, i, j);

    #ifdef AI
    result = CORRECTED;
    if (*i < 0)
    {
        *i = 0;
    } else if (*i >= rows)
    {
        *i = rows - 1;
    } else if (*j < 0)
    {
        *j = 0;
    } else if (*j >= cols)
    {
        *j = cols - 1;
    } else
    {
        result = COMPLETE;
    }
    #endif

    if (*i < 0 || *i >= rows || *j < 0 || *j >= cols)
    {
        result = FAILED;
    }
}

void move_dist(direction dir, unsigned long distance, unsigned long* i, unsigned long* j)
{
    if (dir == LEFT)
    {
        *i -= distance;
    } else if (dir == RIGHT)
    {
        *i += distance;
    } else if (dir == UP)
    {
        *j -= distance;
    } else if (dir == DOWN)
    {
        *j += distance;
    }
}
