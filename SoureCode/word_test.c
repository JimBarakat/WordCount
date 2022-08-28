#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>
#include <stdlib.h>
#include "list.h"
//#define REG_E "^[A-Za-z]*[AEIOUYaeiouy][AEIOUYaeiouy][A-Za-z]*(ly|ing)$"
#define REG_E "^[A-Za-z]*[AEIOUYaeiouy][AEIOUYaeiouy][A-Za-z]*(ly|ing)$"
//#define REG_E "[A-Za-z]*5675"

int main(int argc, char *argv[]){
  FILE *fp = fopen(argv[1], "r");
  //size_t length;
    //length = strlen((char*)fp);
  regex_t r_e;
  int re_1;
  if ((re_1 = regcomp(&r_e, REG_E, REG_EXTENDED))) {
    printf("Could not compile reg expression.\n");
    return 1;
  }

  char piece[128], c;

  size_t length = sizeof(piece);

  char *line = malloc(length);

  regmatch_t matches[length];



// Clean up
  if(regexec(&r_e, "AAly", 0, NULL, 0) == 0) {
    printf("Test sleeping: Fixad!\n");
  }

  int index = 0;

  while((c = fgetc(fp)) != EOF){
    if (c > 64 && c < 123) {
      piece[index] = c;
      index++;
    }
    else {
        piece[index] = '\0';
        index = 0;
        if(regexec(&r_e, piece, 0, matches, 0)==0){
          strcpy(line, piece);
          printf("%s\n", line);

          // Fix array/table with words and their occurences
        }

    }



    if(length - strlen(line) < sizeof(piece)){
      length *= 2;
      if((line = realloc(line, length)) == NULL){
        printf("error\n");
        exit(1);
      }
    }
  }

//  strcat(line, piece);

  //if(line[strlen(line)-1]=='\n'){
  //  printf("%s\n\n", line);
  //}
  /*
  while(!feof(fp)){
    fgets(line, length, fp);
    printf("%s", line);
  }*/
  free(line);
  fclose(fp);
  regfree(&r_e);
  return 0;
}
