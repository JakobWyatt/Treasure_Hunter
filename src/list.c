#include "list.h"

#include <stdlib.h> /*NULL*/

void insert(list x, node* iter, void* data)
{
    /*create new node*/
    node* new = (node*)malloc(sizeof(node));
    new->data = data;

    /*If iter is null, insert at the end of the list.
    Else if iter is head, insert at the beginning of the list.
    Else, reroute nearby nodes.
    Might be able to clean up logic a bit. Already generalised some LOC
    to be identical.*/
    if (iter == NULL)
    {
        new->prev = x.tail;
        new->next = iter;
        new->prev->next = new;
        x.tail = new;
        if (x.head == NULL)
        {
            x.head = new;
        }
    } else if (iter->prev == NULL)
    {
        new->prev = iter->prev;
        new->next = iter;
        new->next->prev = new;
        x.head = new;
    } else
    {
        new->prev = iter->prev;
        new->next = iter;
        new->next->prev = new;
        new->prev->next = new;
    }
}

void remove_node(list x, node* iter)
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

list make_list()
{
    list x;
    x.head = NULL;
    x.tail = NULL;
    return x;
}

void free_list(list x)
{
    while (x.head != NULL)
    {
        remove_node(x, x.head);
    }
}

void for_each(list x, for_each_func func)
{
    node* a = x.head;
    while (a != NULL)
    {
        func(a->data);
        a = a->next;
    }
}
