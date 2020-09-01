#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *words[]= {"add_user", "delete_user", "sub_array"};
enum { One, Two, Three } ;

void print(int i);

void print(int i)
{
   switch(i)
   {
     case One: printf("ADD USER\n");break;
     case Two: printf("DELETE USER\n");break;
     case Three:printf("SUB ARRAY\n");break;
     default : break;
   }
}



void f(char *str);

int main(void) {
    char str[20];
    while(1)
    {
      fprintf(stderr,"ENTER The command\n");
      scanf("%s",&str);
      f(str);
    }
      // f("add_user");
    return 0;
}

void f(char *str) {

    int i;
    for (i = 0; i < sizeof words/sizeof words[0]; i++) {
        if (!strcmp(str, words[i])) {
           fprintf(stderr,"####### STRING is %s %d\n",str,i);
            print(i);
            /* Do something */
        }
    }
}
