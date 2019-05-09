#include "types.h"

explorer make_explorer()
{
    explorer ex;
    ex.magic = 0;
    ex.coin = 0;
    ex.head.type = 'N';
    ex.head.value = -1;
    ex.chest.type = 'N';
    ex.chest.value = -1;
    ex.legs.type = 'N';
    ex.legs.value = -1;
    ex.hands.type = 'N';
    ex.hands.value = -1;
    return ex;
}
