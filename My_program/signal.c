#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<signal.h>

/* handler for SIGINT */

static void sigint_handler(int signo)
{
   printf("caught SIGINT!\n");
   exit(EXIT_SUCCESS);
}

int main(void)
{
   if(signal(SIGINT,sigint_handler) == SIG_ERR)
   {
     fprintf(stderr,"cannot handle SIGINT!\n");
     exit(EXIT_FAILURE);
   }

    for(;;)
        pause();
     return 0;
}
 
