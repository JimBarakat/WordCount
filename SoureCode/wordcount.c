/* Gruppmedlemmar:
*
* David Spelbacken (ens12dsn)
* Jaime Barakat (dv19jbt)
*/


#include <stdio.h>
#include <ctype.h>

#include "wordc.h"

void print_list(FILE *out, struct list *list, struct list_pos pos);

int main(int argc, char *argv[])
{
  FILE *fp = fopen(argv[1], "r");
  if(fp == NULL){
    printf("Could not open input file\n");
    return 1;
  };

  FILE *fo = fopen("pg35-wordcount.txt", "w");
  if(fo == NULL){
    printf("Could not open output file\n");
    return 1;
  };


  regex_t r_e;
  int re_1;

  //compile the regular expression
  if ((re_1 = regcomp(&r_e,
      "^[A-Za-z]*[AEIOUYaeiouy][AEIOUYaeiouy][A-Za-z]*(ly|Ly|lY|LY|ing|Ing|INg|iNg|inG|iNG|ING)$",
      REG_EXTENDED)))
  {
    printf("Could not compile reg expression.\n");
    return 1;
  }

  char word[128];
  int c;
  size_t length = sizeof(word);
  char *line = malloc(length);
;

  int index = 0;

  struct list *list = create_list();
  struct list_pos pos = first_pos(list);

  //count total list positions
  int list_counter = 0;


  while((c = fgetc(fp)) != EOF)
  {
    if ((c > 64 && c < 91) || (c > 96 && c < 123)){
    word[index] = c;
    index++;
      }
    else{

      word[index] = '\0';
      index = 0;
      //compare word from text to regular expression,
      if(regexec(&r_e, word, 0, NULL, 0)==0){
        for(int i = 0; i < strlen(word); i++){
             if(isupper(word[i]) > 0){
             word[i] = tolower(word[i]);
           }
        }

        strcpy(line, word);
        //PLACES FIRST MATCH IN LIST
        if(list_is_empty(list) == 1){
            pos = insert_node(list, pos, line);
            list_counter += 1;
        }
        else{
              int j = 0;
              pos.pos = list->head->next;
              for(int i = 0; i < list_counter; i++)
              {
                //moves one position in list if match not found
                if(strcmp(pos.pos->word, line) != 0 && pos.pos->next
                   != list->head){
                  pos.pos = pos.pos->next;
                  }
                //makes new node for match if not currently in list
                else if(strcmp(pos.pos->word, line) != 0 && pos.pos->next
                         == list->head){
                       pos = insert_node(list, pos, line);
                       list_counter += 1;
                       pos.pos = list->head->next;
                       }
                //if match already in list, add one to counter.
                else if(strcmp(pos.pos->word, line) == 0 && j == 0){
                       pos.pos->occurences = pos.pos->occurences + 1;
                       j = 1;
                       }
               }
             }
        }
      }
    }


  
  print_list(fo, list, pos);


  list_destroy(list);
  free(line);
  fclose(fp);
  fclose(fo);
  regfree(&r_e);
  return 0;
}





void print_list(FILE *out, struct list *list, struct list_pos pos)
{
  struct list_pos place = last_pos(list, pos);
  place = list_next(place);
  while(place.pos->word != NULL){
  fprintf(out, "%s %d\n", place.pos->word, place.pos->occurences);
  printf("%s %d\n",  place.pos->word, place.pos->occurences);
  place = list_next(place);
  }
}
