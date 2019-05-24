#include "list.h"

#include <stdlib.h> /*NULL*/

/**
 * \internal \n \n \b Implementation:
 *  A node named new is dynamically allocated (on the heap),
 *      and \p data is referenced by it.
 *  - If \p iter == NULL, insert at the end of the list.
 *      -# Node before new is \p x->tail.
 *      -# Node after new is NULL.
 *      -# \p x->tail is now new.
 *      -# If there are currently no elements in the list,
 *              set x->head to new. Otherwise, link the node before
 *              new to new.
 *  - Otherwise, the next node is guarenteed to exist.
 *      -# Node before new is \p iter->prev.
 *      -# Node after new is iter.
 *      -# \p iter->prev is new.
 *      -# If iter->prev is NULL (start of list), \p x->head is new.
 *          Otherwise, new->prev->next is new.
 */
void insert(list* x, node* iter, void* data)
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
        new->prev = x->tail;
        new->next = iter;
        x->tail = new;
        if (x->head == NULL)
        {
            x->head = new;
        } else
        {
            new->prev->next = new;
        }
    } else
    {
        new->prev = iter->prev;
        new->next = iter;
        new->next->prev = new;
        if (iter->prev == NULL)
        {
            x->head = new;
        } else 
        {
            new->prev->next = new;
        }
    }
}

/**
 * \internal \n \n \b Implementation:
 * First, free \p iter->data.
 * If \p iter is the first element in \p x,
 *  change the head pointer to \p iter->next.
 * Otherwise, the previous node.next is equal to the
 *  next node.
 * When \p iter is the final element in \p x,
 *  perform the algorithm above but set the tail pointer
 *  and the next node.prev instead.
 */
void remove_node(list* x, node* iter)
{
    free(iter->data);
    /*If the node is head or tail, change list pointers*/
    /*Otherwise, reroute neighbouring nodes*/
    if (iter->prev == NULL)
    {
        x->head = iter->next;
    } else {
        iter->prev->next = iter->next;
    }
    if (iter->next == NULL)
    {
        x->tail = iter->prev;
    } else {
        iter->next->prev = iter->prev;
    }

    free(iter);
}

/**
 * \internal \n \n \b Implementation:
 * Set head and tail to NULL.
 */
list make_list()
{
    list x;
    x.head = NULL;
    x.tail = NULL;
    return x;
}

/**
 * \internal \n \n \b Implementation:
 * Call \ref remove_node on \p x->head until x->head is NULL (list is empty).
 */
void free_list(list* x)
{
    while (x->head != NULL)
    {
        remove_node(x, x->head);
    }
}

/**
 * \internal \n \n \b Implementation:
 * -# Apply \p func to the current node, starting at \p x.head.
 * -# Move the current node forward.
 * Repeat this until the current node is NULL.
 */
void for_each(list x, data_func func)
{
    node* a = x.head;
    while (a != NULL)
    {
        func(a->data);
        a = a->next;
    }
}
