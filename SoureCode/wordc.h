/* Gruppmedlemmar:
*
* David Spelbacken (ens12dsn)
* Jaime Barakat (dv19jbt)
*/

#ifndef WORDC_H
#define WORDC_H

/**
 * @defgroup module List for storing and counting matched regular expressions
 *
 * @author David Spelbacken
 * @author Jaime Barakat
 * @date 20200316
 *
 * @brief Module for storing and counting matched regular expressions.
 *
 * The module serves as the datatype for storing and counting matched phrases
 * from a given regular expression in an a given text. The matched phrase is
 * stored as a string in a node which contains an int to serve as the counter
 * for any subsequent matches of the same word/phrase.
 * The phrases are stored in a singular, circular list, where the last node
 * is the empty head node which points to the first.
 * .
 *
 */

#include <string.h>
#include <regex.h>
#include <stdlib.h>

/**
 * @brief struct for holding the matched word and its occurences
 *
 * Holds the matched word, the number of times the matched word has occured
 * and a pointer to the next node in the list of matches, and is used for
 * traversal.
 *
 */

struct node {
  struct node *next;
  char *word;
  int occurences;
};

/**
 * @brief struct for the list.
 * Contains the pointer the node head.
 */

struct list {
  struct node *head;
};

/**
 * @brief The type for a list position.
 * contains a pointer to a particular node in the list.
 */
struct list_pos {
  struct node *pos;
};


/**
 * @brief create and return an empty list.
 *
 * This function creates a struct of type list, and a node for it's
 * "head" pointer. The head node is kept empty, and serves as
 * the reference point for creation, deletion and travesal of the list.
 * it's char* value is set to NULL.
 *
 * @param void
 * @return struct *list
 */
struct list *create_list(void);

/**
 * @brief determines if the list is empty
 *
 * The list is defined as empty in this module if the "head" node's "next"
 * pointer points to itself. This function uses an if statement to determine
 * if this is true an returns an int 1 if this is the case.
 *
 * @param struct *list
 * @return int
 */
int list_is_empty(const struct list *list);

/**
 * @brief finds the first node in the list
 *
 * This function initializes a list_pos node at the node pointed to
 * the the head's "next" pointer, the first position in the list.
 *
 * @param struct list *list
 * @return struct list_pos
 */
struct list_pos first_pos(struct list *list);

/**
 * @brief finds the last node in the list
 *
 * This function finds the end of the list by returning the position of the
 * pointer to the head of the list.
 *
 * @param struct list *list
 * @param struct list_pos pos
 * @return struct list_pos
 */
struct list_pos last_pos(struct list *list, struct list_pos pos);

/**
 * @brief moves to the next position in the list
 *
 * This function returns the position of the next node in the list
 *
 * @param struct list_pos pos
 * @return struct list_pos
 */
struct list_pos list_next(struct list_pos pos);

/**
 * @brief removes a selected node from the list
 *
 * This function selectively removes and frees the parameter node from
 * the list. First the position of the node before the node to be
 * removed is found by initializing a list_pos for the first node,
 * then using a iteration to move the list_pos node until it
 * returns one in which the next pointer points the removed node.
 * this next pointer is moved to the node after the removed node,
 * at which point the removed node and it's data a freed.
 *
 * @param struct list *list
 * @param struct list_pos pos
 * @return struct list_pos
 */
struct list_pos remove_node(struct list_pos pos, struct list *l);

/**
 * @brief creates a new node in the list
 *
 * This function creates a node for holding a matched word in the list.
 * It dynamically allocates a node, copies the input string to the
 * word pointer, and sets the number of occurances to 1 automatically.
 * the next pointer points the position of the node pointed to by the next
 * pointer of the previous node(the input list_pos parameter), which itself
 * is moved to point to the newly created node.
 *
 * @param struct list *list
 * @param struct list_pos pos
 * @char *word
 * @return struct list_pos
 */
struct list_pos insert_node(struct list *list, struct list_pos pos, char *word);

/**
 * @brief destroy the list and its values
 *
 * This function frees all nodes and values in the list through
 * calling remove_node in a loop until only the head node remains,
 * at which point the head, and subsequently the list are freed.
 *
 * @param struct list *list
 * @return void
 */
void list_destroy(struct list *l);





#endif
