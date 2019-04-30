#ifndef GUARD_LIST_H
#define GUARD_LIST_H

typedef struct node_s node;

/*
PURPOSE: Type describing a node in a doubly linked list.
IMPLEMENTATION: Contains a void pointer to the data stored in the node,
    a pointer to the next node, and a pointer to the previous node.
    The pointer to the next/previous node is NULL if it is the last/first node in the list.
USAGE: The data stored in the node must be manually dynamically allocated,
    and the type of the data stored in the node is maintained by the user.
*/
struct node_s
{
    void* data;
    node* next;
    node* prev;
};

/*
PURPOSE: Type describing a linked list.
IMPLEMENTATION: Contains a pointer to the first element in the list
    and a pointer to the last element in the list.
USAGE: Use the functions declared in list.h to manipulate the list.
*/
typedef struct
{
    node* head;
    node* tail;
} list;

/*
PURPOSE: Insert an element before the given element.
USAGE: data must be dynamically allocated.
If iter == NULL, insert the element at the end of the list.
*/
void insert(list x, node* iter, void* data);

/*
PURPOSE: Deallocates and removes the given element.
USAGE: Pass a pointer to the element to remove.
*/
void remove_node(list x, node* iter);

/*
PURPOSE: Creates an empty list.
USAGE: Use this to create a list initially.
*/
list make_list();

/*
PURPOSE: Free all elements.
USAGE: Each element on the linked list must be dynamically allocated,
    with no unique pointers to dynamically allocated members.
*/
void free_list(list x);

/*
PURPOSE: Apply the given function to all elements.
USAGE: func must not be null.
*/
typedef void (*for_each_func)(void*);

void for_each(list x, for_each_func func);

#endif
