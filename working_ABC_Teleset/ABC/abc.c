/****** ABC software

=> Opens port at 6000 to communicate with TELESET program 

=> Opens port at 5000 to communicate with MCM device 

 ******/
#include"server.h"

int main()
{
   int server_fd,n;
   // extern char ABC[10];
    ANT_CMD *e1;
    e1 = malloc(sizeof(ANT_CMD));
    ACK *a1;
    a1 = malloc(sizeof(ACK));

    ANT_RESP *p1;
     p1 = malloc(sizeof(ANT_RESP));

    cmd *c1;
    c1 = malloc(sizeof(cmd));
    resp *r1;
    r1 = malloc(sizeof(resp));
   
  if(init_server()== ERROR)
    {
      fprintf(stderr," ########## UNALBLE to CONNECT MCM DEVICE\n");
     }
   else
     {
       fprintf(stderr," ######### STARTED SERVER for MCM DEVICE\n");
     } 
  
     if(connect_to_server()==ERROR)
     {
        fprintf(stderr," ########## UNALBLE to CONNECT ONLINE_V2\n");
     }
   else
     {
       fprintf(stderr," ######### CONNECTED to TELESET SERVER\n");
     } 
      
           while(1)
           {
                    fprintf(stderr," ####### Wanting for MCM device to Connect #######\n");
                     server_fd = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
                     if(server_fd==ERROR)
                     {fprintf(stderr," FAILED to CONNECT TO ANY MCM DEVICE\n");}
                     else
                     {fprintf(stderr," ACCEPTED CONNECTION FROM MCM DEVICE\n");}
             for(;;)
             {
                n = read(sfd,e1,sizeof(ANT_CMD));
                if(!strcmp(ABC,e1->antenna_name))
               {
                 fprintf(stderr,"#########===> ABC matches =====>\n");
                 sprintf(a1->Resp_msg," ACK from %s Antenna",ABC);
                 write(sfd,a1,sizeof(ACK));
               }
                else
               {
                 fprintf(stderr,"#########===> ABC dose not matches =====>\n");
                 strcpy(a1->Ant_name,e1->antenna_name);
                 sprintf(a1->Resp_msg,"ABC software is for ##### => %s => Antenna\n",ABC);
                 write(sfd,a1,sizeof(ACK)); 
               }
             
                 if((c1= &e1->CMD[0])!=(cmd *)NULL)
                  {
                    
                       write(server_fd,c1,sizeof(cmd));
                       printcmd(c1);
                       sleep(1);
                       fprintf(stderr,"\nNow Reading on Socket\n"); 
                      if (readable_timeo(server_fd, 5) == 0)
                      {
                        fprintf(stderr, "SOCKET TIMEOUT\n");
                        close(server_fd);
                      }
                     else
                     {            
                         n=read(server_fd,r1,sizeof(resp));
                          if (n < 0)
                         fprintf(stderr,"ERROR READING socket\n");
                         else
                          {
                           fprintf(stderr,"########## READ from MCM\n");
                            printresp(r1);
                            sleep(1);
                            strcpy(p1->antenna_name,e1->antenna_name);
                            p1->RESP[0]=*r1;
                           write(sfd,p1,sizeof(ANT_RESP));
                          }                       
                      }
                    }
                    else break;
                 }
                }
 
  return 0;
}

