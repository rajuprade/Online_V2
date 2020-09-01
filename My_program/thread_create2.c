#include<stdio.h>
#include<pthread.h>

/* parameters to print_function */

struct char_print_parms
{
   /* The character to print */
    
    char character;
    int count;
};

void* char_print ( void* parameters)
{
   /* cast the cookies pointer to the right type */
  
   struct char_print_parms* p = (struct char_print_parms*) parameters;
   int i;
   
   for(i= 0; i< p->count ; i++)
   printf("%c",p->character);
   return NULL;
}

int main()
{
  pthread_t thread1_id;
  pthread_t thread2_id;
  
  struct char_print_parms thread1_args;
  struct char_print_parms thread2_args;

  thread1_args.character = 'x';
  thread1_args.count     = 300;
  
  pthread_create(&thread1_id ,NULL,&char_print,(void *)&thread1_args);

  thread2_args.character = 'o';
  thread2_args.count = 200;
  pthread_create(&thread2_id ,NULL ,&char_print,(void *)&thread2_args);
  
  /* Make sure d first thread has finished. */
  pthread_join(thread1_id,NULL);	
  pthread_join(thread2_id,NULL);
  return 0;
} 
