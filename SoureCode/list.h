#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

/**
 * @defgroup list My List
 *
 * @brief functiondeclarations for creating and using datatype list.
 *
 * Header file "list.h" contains the functions and structure definitions
 * for the creation and use of a doubly linked list containing pointers to
 * char values.
 * List consists three structure types - node, List, and listpos(position),
 * and functions for creating, traversal of, inserting and removing elements
 * to and from, and deleting the list.
 *
 *
 * @{
 */


/**
 * @brief  The type for a node in the list.
 * Contains a pointer to a char address, pointers to the previous and next
 * nodes.
 *
 */
struct node
{
    struct node *next;
    struct node *prev;
    char *value;
};

/**
 * @brief The type for a list.
 * Contains the node head.
 */
typedef struct list
{
    struct node head;
} List;

/**
 * @brief The type for a list position.
 * contains a pointer to a particular node in the list.
 */
typedef struct list_pos
{
    struct node *node;
} ListPos;

/**
 * @brief create and return an empty list.
 *
 * This function creates a struct of type List, containing
 * a "head" node. The head node is dynamically allocated,
 * it's "prev" and "next" pointers point to its own address and
 * it's char* value is set to NULL.
 *
 * @param void
 * @return *List
 */
List *list_create(void);

/**
 * @brief Deallocate the list (and all of its values, if any).
 *
 * uses free() to destroy the list and dynamically allocated values.
 *
 * @param List *list
 * @return void
 */
void list_destroy(List *lst);

/**
 * @brief Check if the list is empty.
 *
 * If list contains any values returns false, true otherwise.
 *
 * @param const List *lst
 * @return bool
 */
bool list_is_empty(const List *lst);

/**
 * @brief Get the position of the first element.
 *
 * Creates and returns a struct Listpos. The List pointers head's next
 * address is allocated to Listpos's node.
 *
 * @param List *lst
 * @return ListPos
 */
ListPos list_first(List *lst);

/**
 * @brief get the posistion after the last element.
 *
 * Creates and returns a struct listpos, which's node is the
 * address of the List pointers head node.
 *
 * @param List *lst
 * @return ListPos
 */
ListPos list_end(List *lst);

/**
 * @brief Check equality between two positions.
 *
 * Compares the positions of two Listpos parameters. If they are
 * equal the function returns true otherwise false.
 *
 * @param ListPos p1, ListPos p2
 * @return bool
 */
bool list_pos_equal(ListPos p1, ListPos p2);

/**
 * @brief forward to the next position.
 *
 * Creates and returns a struct Listpos, which contatins node pointer
 * that points to the "next" pointer contained in the node pointer from the
 * parameter pos.
 *
 * @param ListPos pos
 * @return ListPos
 */
ListPos list_next(ListPos pos);

/**
 * @brief backward to the previous position.
 *
 * Creates and returns a struct Listpos, which contatins node pointer
 * that points to the "prev" pointer contained in the node pointer from the
 * parameter pos.
 *
 * @param ListPos pos
 * @return ListPos
 */
ListPos list_prev(ListPos pos);

/**
 * @brief Insert the value before the postion and return position for new element.
 *
 * calls function make_node() to create a new node containing the *value parameter.
 * pleaces this node in a position before the Listpos pos paramater.
 *
 * @param ListPos pos, const char *value.
 * @return ListPos
 */
ListPos list_insert(ListPos pos, const char *value);

/**
 * @brief Remove the value at the position and return the position of the next element.
 *
 * adjusts the next and prev pointers from the node at position pos so that it
 * no longer has a position in the list, and uses free() to dellocate the node.
 *
 * @param ListPos pos
 * @return ListPos
 */
ListPos list_remove(ListPos pos);

/**
 * @brief Get the value at the position.
 *
 * @param ListPos pos
 * @return const *char
 */
const char *list_inspect(ListPos pos);
/**
 * @}
 */
#endif /* LIST_H */
