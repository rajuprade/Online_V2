#include"server.h"

#if defined(LIBXML_TREE_ENABLED) && defined(LIBXML_OUTPUT_ENABLED)

int main(int argc, char *argv[])
{
     int n;
     setdata *set;  
     set = (setdata *)malloc(sizeof(setdata));
     
     ANT_CMD *a1;
     a1= malloc(sizeof(ANT_CMD));
    
     ANT_RESP *b1;
     b1= malloc(sizeof(ANT_RESP));
      
     ACK *ack;
     ack = malloc(sizeof(ACK));
 
     cmd *c1;
     c1 = malloc(sizeof(cmd));
     resp *r1;
     r1 = malloc(sizeof(resp));
     char *tstamp;
     tstamp = malloc(25);
     int socfd[30];
      printf("Enter 0 for file input and 1 for user input\n");
      scanf("%d",&n);
      exec(set,n);
      write_us_shm(set);

     if(init_server()== ERROR)
     {
       fprintf(stderr," ####### ERROR Opening Socket ##########\n");
     }
    clilen = sizeof(cli_addr); 
        while(1)
       {     

            /* If a separate structure which will have antenna name and socketfd as variable is declared,
                typedef struct 
                {
                    char antenna_name[28];
                    int sockfd;
                }Thread_struct;
                 Thread_struct *p1;
                 p1=malloc(sizeof(Thread_struct));
               Particular thread for Antenna can be created by passing this structure as argument */
           fprintf(stderr,"############# SERVER WANTING FOR CLIENT CONNECTION #####\n");
           socfd[0] = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen); 
           strcpy(a1->antenna_name,set->Tx[0].s_a[0].ant_name[0]); // copy the first antenna name from file/user input 
           for(;;)
           {
             printf("\n\nEnter the system number from the list\n");
             printf("0.sentinal\n");
             printf("1.front_end\n");
             printf("2:fiber_optics\n");
             printf("3:back_end\n");
             printf("4:self_test\n\n");                                                  
             scanf("%d",&n);
             exec_cmd(n,a1);
                  
             tstamp = tp(tstamp);
             strcpy(a1->CMD[0].timestamp,tstamp);
             write(socfd[0],a1,sizeof(ANT_CMD));
             sleep(1);
             fprintf(stderr,"\nNow Reading on Socket\n"); 
              if (readable_timeo(socfd[0], 5) == 0)
               {
                 fprintf(stderr, "SOCKET TIMEOUT\n");
                  close(socfd[0]);
                  break;
               }
             else
              {            
                  n=read(socfd[0],ack,sizeof(ACK));
                  if (n < 0)
                  fprintf(stderr,"ERROR READING socket\n");
                  else
                  fprintf(stderr,"########## ACK from ABC of %s ANTEANNA ####### %s \n",ack->Ant_name,ack->Resp_msg);
              }
              c1 = &a1->CMD[0];
              sleep(1);
             read(socfd[0],b1,sizeof(ANT_RESP));
             r1= &b1->RESP[0];
            
              #ifdef DEBUG  
              fprintf(stderr,"RESPONSE got from %s Antenna\n",b1->antenna_name);
              printcmd(c1);
              printresp(r1);
              #endif
              write_shm(c1,r1); 
              write_command_xml(c1);
              write_response_xml(r1);        
         }
       }     
     return 0; 
}
#else
int main(void) {
    fprintf(stderr, "server2 support not compiled in\n");
    exit(1);
}
#endif

