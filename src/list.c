#include "list.h"

#include <stddef.h> /*NULL*/

void insert(list x, node* iter, void* data);

void remove(list x, node* iter)
{
    free(iter->data);
    /*If the node is head or tail, change list pointers*/
    /*Otherwise, reroute neighbouring nodes*/
    if (iter->prev == NULL)
    {
        x.head = iter->next;
    } else {
        iter->prev->next = iter->next;
    }
    if (iter->next == NULL)
    {
        x.tail = iter->prev;
    } else {
        iter->next->prev = iter->prev;
    }

    free(iter);
}

list make_list();

void free_list(list x);
