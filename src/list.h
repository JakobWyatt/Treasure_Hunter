#ifndef GUARD_LIST_H
#define GUARD_LIST_H

/**
    \file list.h
    \brief Contains functions and datatypes used to create and manipulate linked lists.
 */

typedef struct node_s node;

/**
 * \brief Struct to describe a node in a doubly linked list.
*/
struct node_s
{
    /** Pointer to the data. This must be dynamically allocated. */
    void* data;
    /** Pointer to the next node. This is NULL if this is the last element. */
    node* next;
    /** Pointer to the previous node. This is NULL if this is the first element. */
    node* prev;
};

/**
 * \brief Function pointer that performs an operation on \ref node.data
*/
typedef void (*data_func)(void*);

/**
 * \brief Struct to contain a doubly referenced linked list.
 */
typedef struct
{
    /** Pointer to the head node. */
    node* head;
    /** Pointer to the tail node. */
    node* tail;
} list;

/**
 * \brief Insert an element into a linked list.
 * \param[in,out] x The list to insert into.
 * \param[in] iter Insert before this element. If \p iter is NULL,
 *      insert at the end of the list.
 * \param[in] data The pointer to data that will be stored by the node.
 */
void insert(list* x, node* iter, void* data);

/**
 * \brief Remove a node from a linked list.
 * \param[in,out] x The list to remove the node from.
 * \param[in,out] iter The node to remove.
 * \details Calls \ref free() on \p iter.data
 */
void remove_node(list* x, node* iter);

/**
 * \brief Initializes an empty list.
 * \return The empty list.
 * \details The list struct is statically allocated (on the stack).
*/
list make_list();

/**
 * \brief Free all elements in the list.
 * \param[in,out] x The list to free.
 * \details Calls \ref free() on \p node.data for all nodes.
 */
void free_list(list* x);

/**
 * \brief Applies a function to every \ref node in the \ref list.
 * \param[in] x The list to apply \p func to.
 * \param[in] func The function to apply to every node.
 * \details \p func is called on each \ref node in order.
 */
void for_each(list x, data_func func);

#endif
