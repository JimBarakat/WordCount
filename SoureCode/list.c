#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

static char *clone_string(const char *in)
{
    size_t len = strlen(in);
    char *out = calloc(len + 1, sizeof(char));
    strcpy(out, in);
    return out;
}


static struct node *make_node(const char *value)
{
  struct node *node = calloc(1, sizeof(*node));
  node->value = clone_string(value);
  return node;
}

List *list_create(void)
{
  List *lst = malloc(sizeof(List));
  lst->head.next = &lst->head;
  lst->head.prev = &lst->head;
  lst->head.value = NULL;
  return lst;
}

void list_destroy(List *lst)
{
  if(!list_is_empty(lst)){
    ListPos pos = list_first(lst);
    list_remove(pos);
  }
  free(lst->head.value);
  free(lst);
}

bool list_is_empty(const List *lst)
{
  if(lst->head.next == &lst->head){
    return true;
  } else {
    return false;
  }
}


ListPos list_first(List *lst)
{
    ListPos pos = {
        .node = lst->head.next
    };
    return pos;
}


ListPos list_end(List *lst)
{
    ListPos pos = {
        .node = &lst->head
    };
    return pos;
}


bool list_pos_equal(ListPos p1, ListPos p2)
{
    if(p1.node == p2.node){
    return true;
  } else {return false;}
}


ListPos list_next(ListPos pos)
{
  ListPos next = {
    pos.node->next
  };
  return next;
}


ListPos list_prev(ListPos pos)
{
  ListPos prev = {
    pos.node->prev
  };
  return prev;
}


ListPos list_insert(ListPos pos, const char *value)
{
    // Create a new node.
    struct node *node = make_node(value);
    // Find nodes before and after (may be the same node: the head of the list).
    struct node *before = pos.node->prev;
    struct node *after = pos.node;
    // Link to node after.
    node->next = after;
    after->prev = node;
    // Link to node before.
    node->prev = before;
    before->next = node;
    // Return the position of the new element.
    pos.node = node;

    return pos;
}

ListPos list_remove(ListPos pos)
{
  struct node *after = pos.node->next;
  struct node *before = pos.node->prev;

  after->prev = before;
  before->next = after;

  ListPos deleted = pos;
  deleted.node->next = deleted.node;
  deleted.node->prev = deleted.node;
  pos.node = after;

  free(deleted.node->value);
  free(deleted.node);

  return pos;
}

const char *list_inspect(ListPos pos)
{
    const char *value = pos.node->value;
    return value;
}
