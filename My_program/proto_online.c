#include<stdio.h>
#include<string.h>    //strlen
#include<stdlib.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include<pthread.h> //for threading , link with lpthread
#include <setjmp.h>
#define ERROR -1

jmp_buf Env; // global variable for long jump and set jump. 

void* gsb ( void* parameters)
{
   /* cast the cookies pointer to the right type */
  
    int *p=  parameters;
 //   int i;
   
   //for(i= 0; i< p->count ; i++)
   printf("****** Value of I in GSB ===> %d\n",*p);
   return NULL;
}
void* antenna( void* parameters)
{
   /* cast the cookies pointer to the right type */
  
    int *p=  parameters;
 //   int i;
   
   //for(i= 0; i< p->count ; i++)
   while(setjmp(Env)!=1)
   {
     printf("****** Value of Of J in ANtenna ===> %d\n",*p);
   }
   return NULL;
}
void* ab( void* parameters)
{
   /* cast the cookies pointer to the right type */
  
    int *p=  parameters;
    int r=0;
 //   int i;
   
  for(r= 0; r<5 ; r++)
   {
     printf("****** Value of K in AB===> %d\n",*p);
   }
   longjmp(Env,1);
   return NULL;
}
int main()
{
  pthread_t gsb1;
  pthread_t antenna1;
  pthread_t ana_back;
  int i=1,j=1,k=1;

   pthread_create(&gsb1 ,NULL,&gsb,(void *)&i);
   sleep(1);
   pthread_create(&antenna1 ,NULL,&antenna,(void *)&j);
   sleep(1);
   pthread_create(&ana_back ,NULL,&ab,(void *)&k);
   sleep(1);
   pthread_join(gsb1,NULL);	
   pthread_join(antenna1,NULL);
   pthread_join(ana_back,NULL);	
 
   return 0;
}
