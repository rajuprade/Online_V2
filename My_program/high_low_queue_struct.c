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
 // int seq;
 // char timestamp[64];
  char system_name[16];
 // char op_name[16];
 // short int number_param;
 // char parameter_name[32][16];
 // char Argument_Ch1[32][16];
 // char Argument_Ch2[32][16];
 } command;

typedef struct
{
  int front, rear;
  int retrieve ;      
  int store ;         
  command cmd[MAXQUE]; // It indicates the Queue for Commands 
} Queue;


char *name;
extern Queue Q ; 
Queue Q;

extern void q_store(command );
extern command *q_retrieve(int );

void q_store(command element )
{
  if (Q.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(Q.store==Q.retrieve)
  {
    Q.store = 0; Q.retrieve = 0;
  }
   // bzero(&Q.cmd[Q.store],256);
    Q.cmd[Q.store]=element; 
    fprintf(stderr," INSERTING in  Queue ######### %s\n",Q.cmd[Q.store].system_name);
    Q.store++;  // point to next available storage position in queue[]
 }

command * q_retrieve(int indx)
{

  fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((command *) &Q.cmd[indx]); 
}


void* highuser( void* parameters)
{
   int flag;
   command *c1;
   c1 = malloc(sizeof(command));
   while((name=readline("\n >> "))!=NULL)
    {
      if (strcmp(name,"stop")==0)
      continue;
      printf("\n");
      if(name)
      {
        strcpy(c1->system_name,name);
        q_store(*c1);
      }
       
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
  command *cmd_get;
  cmd_get = (command *)malloc(sizeof(command));
  for(;;)
  {
       if((int)(Q.store)>(int)(Q.retrieve))
       {
          pthread_mutex_lock(&lock);
          cmd_get = q_retrieve((int)Q.retrieve);
          if((command *)cmd_get != (command *)NULL)
           {
             fprintf(stderr,"\nGetting from Queue ######### %s\n",cmd_get->system_name);
             Q.retrieve++;
           }
           pthread_mutex_unlock(&lock);
         }
        usleep(50000);
          
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
