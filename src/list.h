#ifndef GUARD_LIST_H
#define GUARD_LIST_H

typedef struct node_s node;

/*
PURPOSE: Type describing a node in a linked list.
IMPLEMENTATION: Contains a void pointer to the data stored in the node,
    and a pointer to the next node. The pointer to the next node is NULL
    if it is the last node in the list.
USAGE: The data stored in the node must be manually dynamically allocated,
    and the type of the data stored in the node is maintained by the user.
*/
struct node_s
{
    void* data;
    node* next;
};

/*
PURPOSE: Type describing a linked list.
IMPLEMENTATION: Contains a pointer to the first element in the list.
    In future, a pointer to the last element in the list may be added,
    to speed up inserts.
USAGE: Use the functions declared in list.h to manipulate the list.
*/
typedef struct
{
    node* head;
} list;

#endif
