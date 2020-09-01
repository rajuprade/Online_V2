#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXTOKENS       256
#define MAXLINE         1024     /* fgets buff */
#define MINLEN          3        /* skip lines shorter as */

char **split(char *string, char *delim);

int main(void) {
 char *delim = ".,:;`'\"+-_(){}[]<>*&^%$#@!?~/|\\= \t\r\n1234567890";
 char **tokens = NULL;
 char line[MAXLINE];
 int i = 0, lcount = 0;

 while(fgets(line, MAXLINE, stdin) != NULL) {
  lcount++;

  if(strlen(line) < MINLEN)
   continue;

  printf("== line: %d\n", lcount);

  tokens = split(line, delim);
  for(i = 0; tokens[i] != NULL; i++)
   printf("%02d: %s\n", i, tokens[i]);

  for(i = 0; tokens[i] != NULL; i++)
   free(tokens[i]);

  free(tokens);
 }

 return 0;
}

/* split string into tokens, return token array */
char **split(char *string, char *delim) {
 char **tokens = NULL;
 char *working = NULL;
 char *token = NULL;
 int idx = 0;

 tokens  = malloc(sizeof(char *) * MAXTOKENS);
 if(tokens == NULL)
  return NULL;
 working = malloc(sizeof(char) * strlen(string) + 1);
 if(working == NULL)
  return NULL;

 /* to make sure, copy string to a safe place */
 strcpy(working, string);
 for(idx = 0; idx < MAXTOKENS; idx++)
  tokens[idx] = NULL;

 token = strtok(working, delim);
 idx = 0;

 /* always keep the last entry NULL termindated */
 while((idx < (MAXTOKENS - 1)) && (token != NULL)) {
  tokens[idx] = malloc(sizeof(char) * strlen(token) + 1);
  if(tokens[idx] != NULL) {
   strcpy(tokens[idx], token);
   idx++;
   token = strtok(NULL, delim);
  }
 }

 free(working);
 return tokens;
}


