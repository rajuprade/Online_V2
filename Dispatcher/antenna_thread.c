#include"ant_thread.h"
void* ant_thread( void* parameters)
{
    ssize_t bytes=-1; 
    int ant_fd = (int)parameters; 
     fprintf(stderr," ######### Antenna Thread %d SOCKET\n",ant_fd);
    ANT_CMD *e1;
    e1 = malloc(sizeof(ANT_CMD));
  
     ANT_RESP *p1;
     p1 = malloc(sizeof(ANT_RESP));
    
    ACK *a1;
    a1 = malloc(sizeof(ACK));
    cmd *Cmd1;
    Cmd1 = malloc(sizeof(cmd));
    resp *r2;
    r2 = malloc(sizeof(resp));
    if(connect_to_server()==ERROR)
     {
        fprintf(stderr," ########## UNALBLE to CONNECT ONLINE_V2\n");
     }
   else
     {
       fprintf(stderr," ######### CONNECTED to TELESET SERVER\n");
     } 

    for(;;)
    {       
               // bzero(e1,sizeof(ANT_CMD));  
               //fprintf(stderr,"*");
                if((bytes = read_from_online(sfd,(unsigned char*)e1,sizeof(ANT_CMD)))!= sizeof(ANT_CMD))
                { 
                 // fprintf(stderr," ERROR in Reading from Online server\n");
                }
                /* if((bytes=readn(sfd,e1,sizeof(ANT_CMD)))!=sizeof(ANT_CMD))
                  {  //fprintf(stderr," Error reading from Online\n");
                  } */
                 else
                {              
                    if(!strcmp(ABC,e1->antenna_name))
                    {
                       bytes = -1;
                       //fprintf(stderr,"#########===> ABC matches =====>\n");
                        sprintf(a1->Resp_msg," ACK from C00 Antenna");
                       // sleep(1);
                        if((bytes =writen(sfd,(unsigned char *)a1,sizeof(ACK)))!=sizeof(ACK))
                         { fprintf(stderr," ACK wiritng Failed [%d] !!\n",bytes); }
                           Cmd1= &e1->CMD; // copies the command to put in the queue
                           if(!strcmp(Cmd1->system_name,"sentinel"))
                            { 
                              fprintf(stderr,"###### ANTENNA THREAD =>QUEUE IN %s\n",Cmd1->system_name);
                              pthread_mutex_lock(&lock);
                              senq_store(*Cmd1);
                             pthread_mutex_unlock(&lock);                    
                            }
                            else if(!strcmp(Cmd1->system_name,"front_end"))
                            { 
                              fprintf(stderr,"###### ANTENNA THREAD =>QUEUE IN %s\n",Cmd1->system_name);
                              pthread_mutex_lock(&lock);
                               q_store(*Cmd1);
                             pthread_mutex_unlock(&lock);                    
                            }
                             else if(!strcmp(Cmd1->system_name,"fiber_optics"))
                            { 
                              fprintf(stderr,"###### ANTENNA THREAD =>QUEUE IN %s\n",Cmd1->system_name);
                              pthread_mutex_lock(&lock);
                              fiberq_store(*Cmd1);
                             pthread_mutex_unlock(&lock);                    
                            }
                            else if(!strcmp(Cmd1->system_name,"back_end"))
                            { 
                              fprintf(stderr,"###### ANTENNA THREAD =>QUEUE IN %s\n",Cmd1->system_name);
                              pthread_mutex_lock(&lock);
                              backq_store(*Cmd1);
                             pthread_mutex_unlock(&lock);                    
                            }
                             else
                            { 
                              fprintf(stderr,"###### No SUCH SYSTEM %s\n",Cmd1->system_name);
                                                
                            }
                     }
                   else
                    {
                       bytes = -1;
                       fprintf(stderr,"#########===> ABC dose not matches =====>\n");
                       strcpy(a1->Ant_name,e1->antenna_name);
                        sprintf(a1->Resp_msg,"ABC software is for ##### => %s => Antenna\n",ABC);
                       if((bytes =writen(sfd,(unsigned char *)a1,sizeof(ACK)))!=sizeof(ACK))
                       { fprintf(stderr," ACK wiritng Failed [%d] !!\n",bytes); }
                    }
 
          
                 /*   if((int)(RQ.s)>(int)(RQ.ret))
                     {
                       pthread_mutex_lock(&lock);
                       r2 = rq_retrieve((int)RQ.ret);
                       pthread_mutex_unlock(&lock);   
                       if((resp *)r2 != (resp *)NULL)
                          {   
                            
                              fprintf(stderr,"\n ####### ANTENNA THREAD from Response Queue %s\n",r2->system_name);
                             //strcpy(p1->antenna_name,e1->antenna_name);
                             // p1->RESP[0]=*r2; 
                              printresp(r2);
                              usleep(500000);
                              if((bytes =writen(sfd,(unsigned char * )r2,sizeof(resp)))!=sizeof(resp))
                              { fprintf(stderr," ANT RESPONSE wiritng Failed [%d] !!\n",bytes); }
                              else 
                              {fprintf(stderr," SUCESSFULLY Written ANT RESPONSE\n"); }

                                RQ.ret++; 
                          }
                        //pthread_mutex_unlock(&lock);                               
                     
                      } */
                  
            }
        }
     
   return NULL;
}
