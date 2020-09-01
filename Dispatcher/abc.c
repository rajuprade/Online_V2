/****** ABC software

=> Opens port at 6000 to communicate with TELESET program 

=> Opens port at 5000 to communicate with MCM device 

 ******/
#include"server.h"
#include"queue.h"
#include"ant_thread.h"
#include"mcm_thread.h"


int main()
{
    pthread_t antenna_thread;
    pthread_t sen_th;
    pthread_t fiber_th;
    pthread_t front_th;
    pthread_t backend_th;
    pthread_t self_th;
    pthread_attr_t custom_attr_fifo, custom_attr_rr;	
    int fifo_max_prio, rr_min_prio;	
    struct sched_param fifo_param, rr_param;	

   pthread_attr_init(&custom_attr_fifo);	
   pthread_attr_setschedpolicy(&custom_attr_fifo, SCHED_FIFO);	
   fifo_param.sched_priority = sched_get_priority_max(SCHED_FIFO);	
   pthread_attr_setschedparam(&custom_attr_fifo, &fifo_param);	
   pthread_attr_init(&custom_attr_rr);	
   pthread_attr_setschedpolicy(&custom_attr_rr, SCHED_RR);	
   rr_param.sched_priority = sched_get_priority_min(SCHED_RR);	
   pthread_attr_setschedparam(&custom_attr_rr, &rr_param);	
  
    int server_fd, *new_sock,Ret;
     ssize_t n=-1;
   /*  ANT_CMD *ant_cmd;
     ant_cmd = malloc(sizeof(ANT_CMD));
  
     ANT_RESP *ant_resp;
     ant_resp = malloc(sizeof(ANT_RESP));
     cmd *c1;
     c1 = malloc(sizeof(cmd));
    resp *r1;
    r1 = malloc(sizeof(resp)); */
   
   
  if(init_server()== ERROR)
    {
      fprintf(stderr," ########## UNALBLE to CONNECT MCM DEVICE\n");
     }
   else
     {
       fprintf(stderr," ######### STARTED SERVER for MCM DEVICE\n");
     } 
   
           pthread_create(&antenna_thread ,&custom_attr_fifo,&ant_thread,NULL);
            clilen = sizeof(cli_addr);
           while(1)
           {
                    fprintf(stderr," ####### Wanting for MCM device to Connect #######\n");

                     server_fd = accept(sockfd,(struct sockaddr *)&cli_addr,&clilen);
                     if(!strcmp(inet_ntoa(cli_addr.sin_addr),SENTINEL_IP))
                     { 
                        new_sock = malloc(1);
                        *new_sock = server_fd;
                        fprintf(stderr," ACCEPTED CONNECTION FROM MCM DEVICE %s\n",inet_ntoa(cli_addr.sin_addr));
                         Ret= pthread_create(&sen_th,NULL,&sentinel_thread,(void *)new_sock); 
                          if(Ret)
                           { 
                             fprintf(stderr,"Error in Opening SENTINEL thread %d\n",Ret);
                           }
                          else 
                          {
                            fprintf(stderr,"SENTINEL thread opened succesfully=> %d\n",Ret); 
                         }
                     }
                     else if(!strcmp(inet_ntoa(cli_addr.sin_addr),FIBER_IP))
                     { 
                        new_sock = malloc(1);
                        *new_sock = server_fd;
                        fprintf(stderr," ACCEPTED CONNECTION FROM MCM DEVICE %s\n",inet_ntoa(cli_addr.sin_addr));
                         Ret= pthread_create(&fiber_th,NULL,&fiber_thread,(void *)new_sock); 
                          if(Ret)
                           { 
                             fprintf(stderr,"Error in Opening FIBER thread %d\n",Ret);
                           }
                          else 
                          {
                            fprintf(stderr,"FIBER thread opened succesfully=> %d\n",Ret); 
                         }
                     }
                      else if(!strcmp(inet_ntoa(cli_addr.sin_addr),FRONT_IP))
                      { 
                        new_sock = malloc(1);
                        *new_sock = server_fd;
                        fprintf(stderr," ACCEPTED CONNECTION FROM MCM DEVICE %s\n",inet_ntoa(cli_addr.sin_addr));
                         Ret= pthread_create(&front_th,NULL,&front_thread,(void *)new_sock); 
                          if(Ret)
                           { 
                             fprintf(stderr,"Error in Opening FRONT thread %d\n",Ret);
                           }
                          else 
                          {
                            fprintf(stderr,"FRONT thread opened succesfully=> %d\n",Ret); 
                         }
                     }
                      else if(!strcmp(inet_ntoa(cli_addr.sin_addr),BACKEND_IP))
                      { 
                        new_sock = malloc(1);
                        *new_sock = server_fd;
                        fprintf(stderr," ACCEPTED CONNECTION FROM MCM DEVICE %s\n",inet_ntoa(cli_addr.sin_addr));
                         Ret= pthread_create(&backend_th,NULL,&backend_thread,(void *)new_sock); 
                          if(Ret)
                           { 
                             fprintf(stderr,"Error in Opening BACKEND thread %d\n",Ret);
                           }
                          else 
                          {
                            fprintf(stderr,"BACKEND thread opened succesfully=> %d\n",Ret); 
                         }
                     }
                      else if(!strcmp(inet_ntoa(cli_addr.sin_addr),SELF_IP))
                      { 
                        new_sock = malloc(1);
                        *new_sock = server_fd;
                        fprintf(stderr," ACCEPTED CONNECTION FROM MCM DEVICE %s\n",inet_ntoa(cli_addr.sin_addr));
                         Ret= pthread_create(&self_th,NULL,&self_thread,(void *)new_sock); 
                          if(Ret)
                           { 
                             fprintf(stderr,"Error in Opening SELF thread %d\n",Ret);
                           }
                          else 
                          {
                            fprintf(stderr,"SELF thread opened succesfully=> %d\n",Ret); 
                         }
                     }
                     else
                     { fprintf(stderr,"######### NOT AUTHORIZED IP ##########\n"); }
         
                }

  pthread_join(antenna_thread,NULL);
  pthread_join(sen_th,NULL); 
  pthread_join(fiber_th,NULL);
  pthread_join(front_th,NULL);
  pthread_join(backend_th,NULL);
  pthread_join(self_th,NULL);
      
  return 0;
}

