#include "treasure.h"
#include <stdlib.h> /*malloc*/
#include <stdio.h> /*sscanf*/
#include <ctype.h> /*toupper*/
#include <string.h> /*strchr*/

/*TODO: Split this into multiple functions*/
status make_treasure(char* str, treasure* make)
{
    status result = COMPLETE;
    int args_read;
    char* seperator1;
    char* seperator2;
    char type = '\0';
    sscanf(str, "%c", &type);
    type = toupper(type);
    make->type = type;
    switch (type)
    {
        case 'C':
            args_read = sscanf(str, "%*c %d", &make->value);
            if (args_read != 1)
            {
                fprintf(stderr, "Incorrect formatting. Coins are represented as: \"C <value>\"\n");
                result = ABORTED;
            }
            break;
        case 'M':
            seperator1 = strchr(str, ':');
            /*Ensure there is a :, and if so, there is at least one character in the detail string.*/
            if (seperator1 == NULL || seperator1 - str < 3)
            {
                result = ABORTED;
            } else
            {
                /*Turn the seperator1 into a string termination character, essentially splitting the string.*/
                /*Allocate enough memory to store the detail string. Do not check if allocation was sucessful.*/
                *seperator1 = '\0';
                make->detail = (char*)malloc(sizeof(char) * (seperator1 - str - 1));
                strncpy(make->detail, str + 2, seperator1 - str - 1);
                args_read = sscanf(seperator1 + 1, "%d", &make->value);
                if (args_read != 1)
                {
                    result = ABORTED;
                }
            }

            if (result == ABORTED)
            {
                fprintf(stderr, "Incorrect formatting. Magic items are represented as: \"M <detail>:<value>\"\n");
            }
            break;
        case 'G':
            seperator1 = strchr(str, ':');
            if (seperator1 == NULL || seperator1 - str < 3)
            {
                result = ABORTED;
            } else
            {
                seperator2 = strchr(seperator1 + 1, ':');
                if (seperator2 == NULL)
                {
                    result = ABORTED;
                } else {
                    /*At this point, we have two pointers to both seperators*/
                    *seperator1 = '\0';
                    *seperator2 = '\0';
                    /*create detail*/
                    make->detail = (char*)malloc(sizeof(char) * (seperator1 - str - 1));
                    strncpy(make->detail, str + 2, seperator1 - str - 1);
                    /*create gear*/
                    make->compare = chooseCompareFunc(seperator1 + 1);
                    /*create value*/
                    args_read = sscanf(seperator2 + 1, "%d", &make->value);
                    /*check for errors*/
                    if (make->compare == NULL || args_read != 1)
                    {
                        result = ABORTED;
                    }
                }
            }

            if (result == ABORTED)
            {
                fprintf(stderr, "Incorrect formatting. Gear is represented as: \"G <detail>:<slot>:<value>\"\n");
            }
            break;
        case '\0':
            /*There is no treasure at this location*/
            make->type = 'N';
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

compare_func chooseCompareFunc(char* str)
{
    compare_func func = NULL;
    toLowerStr(str);
    if (strcmp(str, "head") == 0)
    {
        func = &compareHead;
    } else if (strcmp(str, "legs") == 0)
    {
        func = &compareLegs;
    } else if (strcmp(str, "chest") == 0)
    {
        func = &compareChest;
    } else if (strcmp(str, "hands") == 0)
    {
        func = &compareHands;
    }

    return func;
}

void slot(treasure x, char* str)
{
    if (x.compare == &compareHead)
    {
        strncpy(str, "head", 6);
    } else if (x.compare == &compareLegs)
    {
        strncpy(str, "legs", 6);
    } else if (x.compare == &compareChest)
    {
        strncpy(str, "chest", 6);
    } else if (x.compare == &compareHands)
    {
        strncpy(str, "hands", 6);
    }
}

void toLowerStr(char* str)
{
    while (*str != '\0')
    {
        *str = tolower(*str);
        ++str;
    }
}

void print(treasure x)
{
    char slot_str[6];
    if (x.type != 'N')
    {
        printf(" type: %c", x.type);
        printf(" value: %d", x.value);
        if (x.type != 'C')
        {
            printf(" detail: %s", x.detail);
            if (x.type != 'M')
            {
                slot(x, slot_str);
                printf( " slot: %s", slot_str);
            }
        }
    }
}

int compareHead(treasure* gear, explorer* person)
{
    int result = 1;
    if (gear->value > person->head.value)
    {
        swap(gear, &person->head);
        result = 0;
    }
    return result;
}

int compareChest(treasure* gear, explorer* person)
{
    int result = 1;
    if (gear->value > person->chest.value)
    {
        swap(gear, &person->chest);
        result = 0;
    }
    return result;
}

int compareLegs(treasure* gear, explorer* person)
{
    int result = 1;
    if (gear->value > person->legs.value)
    {
        swap(gear, &person->legs);
        result = 0;
    }
    return result;
}

int compareHands(treasure* gear, explorer* person)
{
    int result = 1;
    if (gear->value > person->hands.value)
    {
        swap(gear, &person->hands);
        result = 0;
    }
    return result;
}
