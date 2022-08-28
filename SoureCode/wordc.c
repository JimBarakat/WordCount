/* Gruppmedlemmar:
*
* David Spelbacken (ens12dsn)
* Jaime Barakat (dv19jbt)
*/

#include "wordc.h"

static char *clone_string(const char *match)
{
    size_t length = strlen(match);
    char *word = calloc(length + 1, sizeof(char));
    strcpy(word, match);
    return word;
}


struct list *create_list(void) {
  struct list *new_list = malloc(sizeof(struct list));
  new_list->head = malloc(sizeof(struct node));

  new_list->head->word = NULL;
  new_list->head->occurences = 0;

  new_list->head->next = new_list->head;

  return new_list;
}

struct list_pos insert_node(struct list *list, struct list_pos pos, char *word) {
  struct node *new_list_item = malloc(sizeof(struct node));

  new_list_item->occurences = 1;
  new_list_item->word = clone_string(word);
  new_list_item->next = pos.pos->next;
  pos.pos->next = new_list_item;


  struct list_pos new_pos;
  new_pos.pos = new_list_item;
  return new_pos;

}

struct list_pos first_pos(struct list *list)
{
  struct list_pos position;
  position.pos = list->head->next;
  return position;
}

struct list_pos last_pos(struct list *list, struct list_pos pos)
{
  pos.pos = list->head;
  return pos;
}

struct list_pos list_next(struct list_pos pos)
{
  pos.pos = pos.pos->next;
  return pos;
}

struct list_pos remove_node(struct list_pos pos, struct list *l)
{
 struct list_pos prev = first_pos(l);

 while (prev.pos->next != pos.pos) {
   prev = list_next(prev);
 }

 prev.pos->next = pos.pos->next;
 free(pos.pos->word);
 free(pos.pos);
 return prev;
}

void list_destroy(struct list *l)
{

  while(list_is_empty(l) == 0){
    struct list_pos position = first_pos(l);
    remove_node(position, l);
  }
  free (l->head);
  free(l);
}
//LIST INSPECT

//LIST EMPTY
int list_is_empty(const struct list *list)
{
  if(list->head->next == list->head){
    return 1;
  } else {
    return 0;
  }
}
