#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include<signal.h>
int done = 0;
int main(int argc, char *argv[])
{
      
       pid_t pid,pid1,pid2;
       char *buf;
        rl_bind_key('\t',rl_abort);//disable auto-complete
         
            for(;done==0;)
             {
                  buf = readline("\n >> ");

                 if(strcmp(buf,"DAS")==0)
                  {                
                     pid=fork();
                     if(pid==0)
                     {       
                           for(;;){          
                            fprintf(stderr,"DAS SERVER started\n");
                            sleep(2);
                           }
                           
                     } 
                   }
                 
                 if(strcmp(buf,"STOP")==0)
                  { 
                         kill(pid,SIGKILL); 
                         fprintf(stderr,"DAS SERVER PID KILLED\n");                      
                  }
                
               /* if(strcmp(buf,"ABC SERVER")==0)
                   {
                      pid1=fork();
                      if(pid1 == 0)
                      {
                        fprintf(stderr,"ABC SERVER started\n");
                        //continue;
                      } 
                 
                    }
                   if(strcmp(buf,"ANALOG BACKEND")==0)
                     {
                        pid2=fork();
                        if(pid2 == 0)
                        {
                          fprintf(stderr,"ANALOG BACKEN SERVER started\n");
                         //continue;
                        } 
                     } */
           
         if (buf[0]!=0)
          add_history(buf);
         }
    free(buf);  
 
      return 0; 
}
