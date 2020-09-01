#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<time.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>

typedef struct 
{
  char system[28];
  char op[10];
}cmd;
typedef struct
{
  char Ant_name[10];
  cmd c1[10];
} ANT;


int main()
{
  ANT *a1;
  cmd *c2[10];
  int i;
   a1=malloc(sizeof(ANT)) ;
   
   for(i=0;i<10;i++)
   {
    c2[i] = malloc(sizeof(cmd));
    } 

   // c2=malloc(sizeof(cmd)*10);
   strcpy(a1->c1[0].system,"Sentinel");
   strcpy(a1->c1[0].op,"SET");
   c2[0] = &a1->c1[0];
   fprintf(stderr," C2[0] System name is %s\n",c2[0]->system);
   fprintf(stderr," C2[0] OP is %s\n",c2[0]->op);
  // free(c2[0]);

   strcpy(a1->c1[1].system,"SIGCON");
   strcpy(a1->c1[1].op,"RESET");
   c2[1] = &a1->c1[1];
   fprintf(stderr," C2[1] System name is %s\n",c2[1]->system);
   fprintf(stderr," C2[1] OP is %s\n",c2[1]->op);

   strcpy(a1->c1[2].system,"BACKEND");
   strcpy(a1->c1[2].op,"START DAS");
   c2[2] = &a1->c1[2];
   fprintf(stderr," C2[2] System name is %s\n",c2[2]->system);
   fprintf(stderr," C2[2] OP is %s\n",c2[2]->op);
 
 free(a1);
 /* for(i=0;i<9;i++)
   {   printf("DEBUG\n");
       free(c2[i]);
       
   } */
  // free(c2);
 
  return 0;
   
}
