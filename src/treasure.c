#include "treasure.h"

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
