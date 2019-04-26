#include "treasure.h"
#include <stdio.h> /*sscanf*/
#include <ctype.h> /*toupper*/
#include <string.h> /*strchr*/

status make_treasure(char* str, treasure* make)
{
    status result = COMPLETE;
    int args_read;
    char* seperator;
    char type = '\0';
    char gear_slot[6];
    sscanf(str, "%c", &type);
    toupper(type);
    switch (type)
    {
        case 'C':
            args_read = sscanf(str, "%*c %d", &make->value);
            break;
        case 'M':
            seperator = strchr(str, ':');
            break;
        case 'G':
            break;
        default:
            result = ABORTED;
            fprintf(stderr, "%c is not a valid treasure type.\n", type);
    }
    return result;
}

void swap(treasure* a, treasure* b)
{
    treasure tmp = *a;
    *a = *b;
    *b = tmp;
}

void compareHead(treasure* gear, explorer* person)
{
    if (gear->value > person->head.value)
    {
        swap(gear, &person->head);
    }
}

void compareChest(treasure* gear, explorer* person)
{
    if (gear->value > person->chest.value)
    {
        swap(gear, &person->chest);
    }
}

void compareLegs(treasure* gear, explorer* person)
{
    if (gear->value > person->legs.value)
    {
        swap(gear, &person->legs);
    }
}

void compareHands(treasure* gear, explorer* person)
{
    if (gear->value > person->hands.value)
    {
        swap(gear, &person->hands);
    }
}
