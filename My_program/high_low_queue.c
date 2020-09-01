#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#define MAXQUE     256

pthread_mutex_t lock;
typedef struct
{
  int front, rear;
  int retrieve ;      
  int store ;         
  char cmd[MAXQUE];
} Queue;

char *words[]= {"add_user", "delete_user", "sub_array","set","domon"}; // decalaration automatically find the memory 
enum { ADD_USER,DELETE_USER,SUB_ARRAY,SET,DOMON,END } ;
int ret=0;
char *name;
char *token;
char *del = " ";

void print(int i);

extern Queue Q ; 
Queue Q;

extern void q_store(char *);
extern char *q_retrieve(int );

void q_store( char *element )
{
  if (Q.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(Q.store==Q.retrieve)
  {
    Q.store = 0; Q.retrieve = 0;
  }
    bzero(&Q.cmd[Q.store],256);
    strcpy(&Q.cmd[Q.store],element); 
    fprintf(stderr," INSERTING in  Queue ######### %s\n",&Q.cmd[Q.store]);
    Q.store++;  // point to next available storage position in queue[]
 }

char * q_retrieve(int indx)
{

  fprintf(stderr, "q_retrieve() %d \n",indx);
  return((char *) &Q.cmd[indx]); 
}

void print(int i)
{
   switch(i)
   {
     case ADD_USER: printf("ADD USER\n");break;
     case DELETE_USER: printf("DELETE USER\n");break;
     case SUB_ARRAY:printf("SUB ARRAY\n");break;
     case SET: printf("SET COMMAND\n"); 
               token=strtok(name,del); // It works as per our expectation 
               while(token !=NULL)
               { 
                 fprintf(stderr," STRTOK retrun %s\n",token); 
                 token =  strtok(NULL," ");
                }
               break;
     case DOMON:printf("DOMON COMMAND\n");break;
     default : break;
   }
}

void* highuser( void* parameters)
{
   int flag;
   while((name=readline("\n >> "))!=NULL)
    {
      if (strcmp(name,"stop")==0)
      continue;
      printf("\n");
      if(name)
      {
        q_store(name);
        ret=1;}
       else
        { ret=0; }
      usleep(10000);
       if (name[0]!=0)
            add_history(name);
     }
   free(name);
   return NULL;
}
void* lowuser( void* parameters)
{
  int i;
  char *cmd_get;
  cmd_get = (char *)malloc(100);
  for(;;)
  {
       if(ret){
       fprintf(stderr,"HIGH USER INPUT ===>%s\n",name);
       for (i = 0; i < END; i++) 
        {
          if (!strcasecmp(name, words[i]))
          {
             fprintf(stderr,"####### STRING is %s %d\n",name,i);
              print(i);
          }
           
       }
       if((int)(Q.store)>(int)(Q.retrieve))
       {
          pthread_mutex_lock(&lock);
          cmd_get = q_retrieve((int)Q.retrieve);
          if((char *)cmd_get != (char *)NULL)
           {
             fprintf(stderr," Getting from Queue ######### %s\n",cmd_get);
             Q.retrieve++;
           }
           pthread_mutex_unlock(&lock);
         }
      ret=0;
      usleep(50000);
    }
      
   }
   return NULL;
}

int main()
{
  pthread_t high,low;
     
  pthread_create(&high ,NULL,&highuser,NULL);
  
  pthread_create(&low,NULL ,&lowuser,NULL);
   
  pthread_join(high,NULL);	
  pthread_join(low,NULL); 
 
  printf(" ALL THREAD CLOSED\n");
  return 0;
} 
