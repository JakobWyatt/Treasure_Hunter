#include "adventure.h"

#include <stdlib.h>/*free*/

#include "treasure.h"

/**
 * \internal \n \n \b Implementation:
 * Iterate through the list of movements, and keep track of the current location of \p person.
 * This is done in 2 steps:
 *      -# Get the next movement from the list, and calculate the final block \p person will be on after this movement.
 *          This is done with \ref endBlock.
 *      -# Travel in the direction of the movement using \ref moveDist until the final block is reached.
 *          Treasures are collected and logged with \ref collectAndLog.\n \n
 *  This is done until \p movements is exhausted or an error status is set.
 */
status resolveAdventure(map items, unsigned long rows, unsigned long cols, list movements, explorer* person, FILE* file)
{
    status result = COMPLETE;
    status temp_result = COMPLETE;
    /*Iterate through the list of movements, keeping track of where we've been so far*/
    long end_i = 0;
    long end_j = 0;
    long i = 0;
    long j = 0;
    /*The control flow of our algorithm is
    get_end -> Check for error -> (Traverse map, log as we go)*/
    node* current = movements.head;

    fprintf(file, "---\n");

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
            move_dist(((move*)(current->data))->dir, 1, &i, &j);
        }
        current = current->next;
        if (current != NULL)
        {
            temp_result = endBlock(rows, cols, &end_i, &end_j, *(move*)(current->data));
            if (result < temp_result)
            {
                result = temp_result;
            }
        }
    }
    collectAndLog(file, items, person, i, j);

    return result;
}

/**
 * \internal \n \n \b Implementation:
 * Switch on the type of the treasure.
 * coin: Deallocate and increase \p explorer.coin by \ref treasure.value.
 * magic: Deallocate and increase \p explorer.magic by \ref treasure.value.
 * gear: Use \ref treasure.compare to compare and conditionally swap the two treasures.
 * Log with \ref logTreasure if any deallocation or swapping occured.
 */
void collectAndLog(FILE* file, map items, explorer* person, long i, long j)
{
    int swapped;
    treasure temp;
    switch (items[i][j].type)
    {
        case 'C':
            person->coin += items[i][j].value;
            logTreasure(file, items[i][j], 0, i, j);
            items[i][j].type = 'N';
            break;
        case 'M':
            person->magic += items[i][j].value;
            logTreasure(file, items[i][j], 0, i, j);
            free(items[i][j].detail);
            items[i][j].type = 'N';
            break;
        case 'G':
            temp = items[i][j];
            swapped = items[i][j].compare(&items[i][j], person);
            if (swapped == 0)
            {
                logTreasure(file, temp, 0, i, j);
                logTreasure(file, items[i][j], 1, i, j);
            }
            break;
    }
}

/**
 * \internal \n \n \b Implementation:
 * Switch on \p x.type, and log the treasure according to the assignment specification.
 */
void logTreasure(FILE* file, treasure x, int collect, long i, long j)
{
    char slotStr[6];
    switch (x.type)
    {
        case 'C':
            fprintf(file, "COLLECT<ITEM:COINS, XLOC:%lu, YLOC:%lu, VALUE:%d>\n",
                i, j, x.value);
            break;
        case 'M':
            fprintf(file, "COLLECT<ITEM:MAGIC, XLOC:%lu, YLOC:%lu, DESCRIPTION:%s, VALUE:%d>\n",
                i, j, x.detail, x.value);
            break;
        case 'G':
            slot(x, slotStr);
            if (collect == 0)
            {
                fprintf(file, "COLLECT");
            } else
            {
                fprintf(file, "DISCARD");
            }
            fprintf(file, "<ITEM:GEAR, XLOC:%lu, YLOC:%lu, DESCRIPTION:%s, SLOT:%s, VALUE:%d>\n",
                    i, j, x.detail, slotStr, x.value);
            break;
    }

    #ifdef LOG
    switch (x.type)
    {
        case 'C':
            printf("COLLECT<ITEM:COINS, XLOC:%lu, YLOC:%lu, VALUE:%d>\n",
                i, j, x.value);
            break;
        case 'M':
            printf("COLLECT<ITEM:MAGIC, XLOC:%lu, YLOC:%lu, DESCRIPTION:%s, VALUE:%d>\n",
                i, j, x.detail, x.value);
            break;
        case 'G':
            slot(x, slotStr);
            if (collect == 0)
            {
                printf("COLLECT");
            } else
            {
                printf("DISCARD");
            }
            printf("<ITEM:GEAR, XLOC:%lu, YLOC:%lu, DESCRIPTION:%s, SLOT:%s, VALUE:%d>\n",
                    i, j, x.detail, slotStr, x.value);
            break;
    }
    #endif
}

/**
 * \internal \n \n \b Implementation:
 * Move the given distance with \ref move_dist.
 * If AI is defined, correct the location if out of bounds.
 * If the distance is still out of bounds, return FAILED.
 */
status endBlock(unsigned long rows, unsigned long cols,
    long* i, long* j, move x)
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
    return result;
}

/**
 * \internal \n \n \b Implementation:
 * Depending on the direction, change the relevant coordinate.
 */
void move_dist(direction dir, unsigned long distance, long* i, long* j)
{
    if (dir == LEFT)
    {
        *j -= distance;
    } else if (dir == RIGHT)
    {
        *j += distance;
    } else if (dir == UP)
    {
        *i -= distance;
    } else if (dir == DOWN)
    {
        *i += distance;
    }
}
