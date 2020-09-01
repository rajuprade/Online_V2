#include<stdio.h>
#include<pthread.h>
#include<string.h>
/* parameters to print_function */

typedef struct 
{
   /* The character to print */
    
    char sys_name[10];
}emp;

void* servo( void* parameters)
{
   /* cast the cookies pointer to the right type */
  
   emp * p = (emp*) parameters;
   for(;;)
   {
     sleep(1);
    fprintf(stderr,"$$$$$$$$$$$$$$$ 5 Thread Prints ===>%s\n",p->sys_name);
   }
   return NULL;
}
void* bb( void* parameters)
{
   /* cast the cookies pointer to the right type */
  
   emp * p = (emp*) parameters;
   for(;;)
   {
     sleep(1);
    fprintf(stderr,"$$$$$$$$$$$$$$$ 3nd Thread Prints ===>%s\n",p->sys_name);
   }
   return NULL;
}
void* analog( void* parameters)
{
   /* cast the cookies pointer to the right type */
  
   emp * p = (emp*) parameters;
   for(;;)
   {
     sleep(1);
    fprintf(stderr,"$$$$$$$$$$$$$$$ 4nd Thread Prints ===>%s\n",p->sys_name);
   }
   return NULL;
}


void* sentinel( void* parameters)
{
   /* cast the cookies pointer to the right type */
  
   emp * p = (emp*) parameters;
  for(;;)
  {
     fprintf(stderr,"############# 1st THREAD Prints ====>%s\n",p->sys_name);
      sleep(1);
   }
   return NULL;
}
void* Sigcon( void* parameters)
{
   /* cast the cookies pointer to the right type */
  
   emp * p = (emp*) parameters;
   for(;;)
  {
     sleep(2);
    fprintf(stderr,"$$$$$$$$$$$$$$$ 2nd Thread Prints ===>%s\n",p->sys_name);
   }
   return NULL;
}
int main()
{
  pthread_t s1,s2,s3,s4,s5;
  
   emp e1,e2,e3,e4,e5;
   
  
  strcpy(e1.sys_name,"sentinel");
  if(!strcasecmp(e1.sys_name,"sentinel"))
  {
     fprintf(stderr," Starting Thread for Sentinel\n");
     pthread_create(&s1 ,NULL,&sentinel,&e1);
  }
 
     strcpy(e2.sys_name,"Sigcon");
    if(!strcasecmp(e2.sys_name,"Sigcon"))
     {
       fprintf(stderr," Starting Thread for SIGCON\n");
       pthread_create(&s2,NULL ,&Sigcon,&e2);
     }

     strcpy(e3.sys_name,"Analog");
    if(!strcasecmp(e3.sys_name,"Analog"))
     {
       fprintf(stderr," Starting Thread for Analog\n");
       pthread_create(&s3,NULL ,&analog,&e3);
     }

      strcpy(e4.sys_name,"Baseband");
    if(!strcasecmp(e4.sys_name,"Baseband"))
     {
       fprintf(stderr," Starting Thread for Baseband Analog\n");
       pthread_create(&s4,NULL ,&bb,&e4);
     }
       strcpy(e5.sys_name,"servo");
    if(!strcasecmp(e5.sys_name,"servo"))
     {
       fprintf(stderr," Starting Thread for SERVO\n");
       pthread_create(&s5,NULL ,&servo,&e5);
     }

  /*  pthread_detach(s1);
    pthread_detach(s2);
    pthread_detach(s3);
    pthread_detach(s4);
    pthread_detach(s5); */
    
   /* Make sure d first thread has finished. */
  pthread_join(s1,NULL);	
  pthread_join(s2,NULL); 
  pthread_join(s3,NULL);
  pthread_join(s4,NULL);
  pthread_join(s5,NULL); 
 /* pthread_cancel(s5);	
  pthread_cancel(s4);	
  pthread_cancel(s3);
  pthread_cancel(s2);
  pthread_cancel(s1); */ 
  printf(" ALL THREAD CLOSED\n");
  return 0;
} 
