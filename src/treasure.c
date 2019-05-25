#include "treasure.h"
#include <stdlib.h> /*malloc*/
#include <stdio.h> /*sscanf*/
#include <ctype.h> /*toupper*/
#include <string.h> /*strchr*/

/**
 * \internal \n \n \b Implementation:
 * The first character in the string is the type of \ref treasure.
 * - If the type is 'C' (coin), then read in the value of the treasure.
 * - If the type is 'M' (magic), then:
 *      -# Find the first colon in the string.
 *      -# Copy the detail string from \p str + 2 to the seperator.
 *          This skips the type character, and the space after the type character.
 *      -# Parse the value, located at one past the seperator to the end of \p str.
 * - If the type is 'G' (gear), then:
 *      -# Find both delimiters ':' in the string.
 *      -# Copy the detail string from \p str + 2 to the seperator.
 *      -# Find the gear slot with \ref chooseCompareFunc. This is located between the two seperators.
 *      -# Parse the value, located at one past the second seperator to the end of \p str.
 * - If the type is '\0', then \p str is empty and the type of treasure is 'N' (none).
 */
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

/**
 * \internal \n \n \b Implementation:
 * Create a temporary variable and use it to swap the two values.
 */
void swap(treasure* a, treasure* b)
{
    treasure tmp = *a;
    *a = *b;
    *b = tmp;
}

/**
 * \internal \n \n \b Implementation:
 * First, convert the string to lowercase.
 * Next, use a simple else-if ladder to determine
 * which \ref compare_func to use.
 */
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

/**
 * \internal \n \n \b Implementation:
 * Use a simple else-if ladder to determine which string to use,
 * comparing the \p x.compare function pointer.
 */
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

/**
 * \internal \n \n \b Implementation:
 * Iterate through the string, using \ref tolower to convert
 * each character to lowercase.
 */
void toLowerStr(char* str)
{
    while (*str != '\0')
    {
        *str = tolower(*str);
        ++str;
    }
}

/**
 * \internal \n \n \b Implementation:
 * If the type is 'N', do not print anything.
 * All non-empty \ref treasures have types and values.
 * These are printed.
 * If the type is not 'C' (coin), the treasure has a detail string.
 * This is printed.
 * If the type is 'G' (gear), print the slot it refers to.
 *      This uses \ref slot to convert \p x.compare into a string.
 */
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

/**
 * \internal \n \n \b Implementation:
 * If \p person->head.value is less than \p gear.value,
 * use \ref swap to swap the objects.
 */
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

/**
 * \internal \n \n \b Implementation:
 * Same as \ref compareHead, except the Chest slot is compared instead.
 */
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

/**
 * \internal \n \n \b Implementation:
 * Same as \ref compareHead, except the Legs slot is compared instead.
 */
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

/**
 * \internal \n \n \b Implementation:
 * Same as \ref compareHead, except the Hands slot is compared instead.
 */
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
