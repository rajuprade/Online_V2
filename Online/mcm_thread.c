#include"mcm_thread.h"

void* sentinel_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
    
     resp *r1;
     r1 = malloc(sizeof(resp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       senQ.store = 0; senQ.retrieve = 0;
              for(;;)
              {
                    if((int)(senQ.store)>(int)(senQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) senq_retrieve((int)senQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                              //  if(!strcasecmp(c1->system_name,"sentinel"))
                              if((!strcasecmp(c1->system_name,"sentinel"))||(!strcasecmp(c1->system_name,"fiber_optics")))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C00 sentinel/Fiber  MCM device\n"); }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "C00 Sentinel/fiber MCM TIMEOUT\n");
                                        
                                      }
                                      else
                                     { 
                                         printcmd(c1);
                                         bzero(c1,sizeof(cmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(1);
                                  bzero(r1,sizeof(resp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING C00 sentinel MCM RESPONSE\n");
                                     terminate_thread(server_fd);
                                  }
                                  else if(n==0)
                                  {
                                     fprintf(stderr,"C00 sentinel MCM closed it's Socket connection\n");
                                      terminate_thread(server_fd);
                                  }    
                                 else
                                 {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from SENTINEL THREAD SUCCESSFUL\n");
                                 } 
                                senQ.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                      else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C00");
                           strcpy(a1->CMD.system_name,"sentinel");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                          
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C00 sentinel MCM device\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C00 Sentinel MCM TIMEOUT #Perodic Monitoring\n");
                             
                           }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(1);
                            bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C00 Sentinel MCM RESPONSE\n");
                                     terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"C00 sentinel MCM closed it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           
                           else
                           {
                               write_shm(a1,r1); 
                            } 
                          }
                
                    }
  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}

void* fiber_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
      char *tstamp;
     tstamp = malloc(25);
      resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       fiberQ.store = 0; fiberQ.retrieve = 0;
              for(;;)
              {
                    if((int)(fiberQ.store)>(int)(fiberQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD*) fiberq_retrieve((int)fiberQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"fiber_optics"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C00 FIBER MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);
                                         bzero(c1,sizeof(cmd));
                                       
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                    usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C00 FIBER MCM RESPONSE\n"); 
                                     terminate_thread(server_fd);
                                  }
                               else if(n==0)
                                {
                                  fprintf(stderr,"C00  FIBER OPTICS MCM closed it's Socket connection\n");
                                   terminate_thread(server_fd);
                                }
                              else
                              {
                                     printresp(r1);
                                     write_shm(a1,r1);                  
                                     fprintf(stderr," Writing to ONLINE from FIBER THREAD SUCCESSFUL\n");
                               } 
                            
                             fiberQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                       else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C00");
                           strcpy(a1->CMD.system_name,"fiber_optics");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                          
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           {
                             fprintf(stderr," ERROR READING C00 FIBER MCM RESPONSE\n"); 
                              terminate_thread(server_fd);
                           }
                             
                           else if(n==0)
                            {
                              fprintf(stderr,"C00  FIBER OPTICS MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              printresp(r1);
                              write_shm(a1,r1); 
                            } 
                          } 
                      
                    }
  free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* front_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
    
     cmd *c1;
     c1 = malloc(sizeof(cmd));
 
      char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;

       frontQ.store = 0; frontQ.retrieve = 0;
              for(;;)
              {
                    if((int)(frontQ.store)>(int)(frontQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = ( ANT_CMD*) frontq_retrieve((int)frontQ.retrieve);
                        pthread_mutex_unlock(&lock);
                      
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"front_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C00 FRONT END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);   bzero(c1,sizeof(cmd));
                                        
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   sleep(1); // for the time being Dt:3 July/07/2015
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C00 FRONT END MCM RESPONSE\n");
                                     terminate_thread(server_fd); 
                                  }
                              else if(n==0)
                            {
                              fprintf(stderr,"C00 FRONT END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                              else
                              {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from FRONT END SUCCESSFUL\n");
                                  
                               } 
                           
                             frontQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       
                       }
                       
                     /* else
                         { // Periodic Monitoring in the background
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C00");
                           strcpy(a1->CMD.system_name,"front_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                     
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C00 FRONT END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C00 FRONTEND MCM RESPONSE\n"); 
                               terminate_thread(server_fd);
                           }
                             
                           else if(n==0)
                            {
                              fprintf(stderr,"C00 FRONT END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           
                           else
                           {
                             //printresp(r1);
                              write_shm(a1,r1); 
                            
                           }
                        
                         } */
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* backend_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
     char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       backQ.store = 0; backQ.retrieve = 0;
              for(;;)
              {
                    if((int)(backQ.store)>(int)(backQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) backq_retrieve((int)backQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"back_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to C00 BACKEND MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);bzero(c1,sizeof(cmd));
                                        
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   sleep(1);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C00 BACKEND MCM RESPONSE\n"); 
                                     terminate_thread(server_fd);
                                  }
                               else if(n==0)
                               {
                                 fprintf(stderr,"C00 BACKEND MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               }
                           
                              else
                              {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                    fprintf(stderr," Writing to ONLINE from BACKEND THREAD SUCCESSFUL\n");
                              } 
                           
                             backQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                      
                       }
                       else
                         { // Periodic Monitoring in the background
                             bzero(c1,sizeof(cmd));
                            strcpy(a1->antenna_name,"C00");
                           strcpy(a1->CMD.system_name,"back_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C00 BACKEND MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C00 back END MCM RESPONSE\n");
                              terminate_thread(server_fd);
                           }
                             
                           else if(n==0)
                            {
                              fprintf(stderr,"C00 BACKEND MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           
                           else
                           {
                             // printresp(r1);
                              write_shm(a1,r1); 
                             
                           } 
                            
                         }
                          
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* self_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1= malloc(sizeof(ANT_CMD));
 
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
     char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
   
       selfQ.store = 0; selfQ.retrieve = 0;
              for(;;)
              {
                    if((int)(selfQ.store)>(int)(selfQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) selfq_retrieve((int)selfQ.retrieve);
                        pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"self_test"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to C00 SELF SYSTEM MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                                     
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C00 SELF SYSTEM MCM RESPONSE\n");
                                     terminate_thread(server_fd);
                                  }
                                else if(n==0)
                            {
                              fprintf(stderr,"C00 SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                              else
                              {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                      bzero(r1,sizeof(resp));
                                     fprintf(stderr," Writing to ONLINE SUCCESSFUL\n");
                                   
                                                                                    
                               }
                            
                             selfQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                       else
                         { // Periodic Monitoring in the background 
                             bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C00");
                           strcpy(a1->CMD.system_name,"self_test");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                           
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C00 SELF SYSTEM MCM RESPONSE\n");
                              terminate_thread(server_fd);
                           }
                             
                           else if(n==0)
                            {
                              fprintf(stderr,"C00 SELF SYSTEM MCM closed it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           
                           else
                           {
                             //printresp(r1);
                              write_shm(a1,r1); 
                           }
                          
                         }
                    }
  free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* fps_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
    
     resp *r1;
     r1 = malloc(sizeof(resp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       fpsQ.store = 0; fpsQ.retrieve = 0;
              for(;;)
              {
                    if((int)(fpsQ.store)>(int)(fpsQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) fpsq_retrieve((int)fpsQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                              //  if(!strcasecmp(c1->system_name,"sentinel"))
                              if(!strcasecmp(c1->system_name,"fps"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C00 FPS MCM device\n"); }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "FPS MCM TIMEOUT\n");
                                         terminate_thread(server_fd);
                                        
                                      }
                                      else
                                     { 
                                         printcmd(c1);
                                         bzero(c1,sizeof(cmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(3);
                                  bzero(r1,sizeof(resp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING C00 FPS MCM RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                  else if(n==0)
                                  {
                                     fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                                     terminate_thread(server_fd);
                                  }    
                                 else
                                 {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from FPS THREAD SUCCESSFUL\n");
                                 } 
                                fpsQ.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                     else
                         { // Periodic Monitoring in the background 
                          // sleep(5); // Sleep put as per CPK request Date 2/12/2014
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C00");
                           strcpy(a1->CMD.system_name,"fps");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"null");
                          //  strcpy(a1->CMD.op_name,"read_version");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                         
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C00 FPS MCM device\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C00 FPS MCM TIMEOUT #Perodic Monitoring\n");
                                terminate_thread(server_fd);
                             
                           }
                            else if(n==0)
                            {
                              fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(5);
                            bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C00 FPS 1 SECONDS MONITORING MCM RESPONSE\n");
                                   terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              // printresp(r1);
                              write_shm(a1,r1); bzero(r1,sizeof(resp));
                            } 
                          } 
                
                    }

  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}


/*************************************** C01 Antenna syste Thread functions here ******/

void* C01_fps_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
    
     resp *r1;
     r1 = malloc(sizeof(resp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       c1fpsQ.store = 0; c1fpsQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c1fpsQ.store)>(int)(c1fpsQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c1_fpsq_retrieve((int)c1fpsQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                              //  if(!strcasecmp(c1->system_name,"sentinel"))
                              if(!strcasecmp(c1->system_name,"fps"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C01 FPS MCM device\n"); }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "C01 FPS MCM TIMEOUT\n");
                                         terminate_thread(server_fd);
                                        
                                      }
                                      else
                                     { 
                                         printcmd(c1);
                                         bzero(c1,sizeof(cmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(3);
                                  bzero(r1,sizeof(resp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING C00 FPS MCM RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                  else if(n==0)
                                  {
                                     fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                                     terminate_thread(server_fd);
                                  }    
                                 else
                                 {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from FPS THREAD SUCCESSFUL\n");
                                 } 
                                c1fpsQ.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                     else
                         { // Periodic Monitoring in the background 
                          // sleep(5); // Sleep put as per CPK request Date 2/12/2014
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C01");
                           strcpy(a1->CMD.system_name,"fps");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"null");
                          //  strcpy(a1->CMD.op_name,"read_version");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                         
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C01 FPS MCM device\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C00 FPS MCM TIMEOUT #Perodic Monitoring\n");
                                terminate_thread(server_fd);
                             
                           }
                            else if(n==0)
                            {
                              fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(5);
                            bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C01 FPS 1 SECONDS MONITORING MCM RESPONSE\n");
                                   terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"C01 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              // printresp(r1);
                              write_shm(a1,r1); bzero(r1,sizeof(resp));
                            } 
                          } 
                
                    }

  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}

void* C01_sentinel_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       c1senQ.store = 0; c1senQ.retrieve = 0;
              for(;;)
              {
                   if((int)(c1senQ.store)>(int)(c1senQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c1_senq_retrieve((int)c1senQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                               // if(!strcasecmp(c1->system_name,"sentinel"))
                             if((!strcasecmp(c1->system_name,"sentinel"))||(!strcasecmp(c1->system_name,"fiber_optics")))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD C01 sentinel MCM device\n"); }
                                    else
                                   { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                        // bzero(c1,sizeof(cmd));   
                                         
                                    }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  usleep(500000);
                                 bzero(r1,sizeof(resp)); 
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING C01 sentinel MCM RESPONSE\n");  
                                     terminate_thread(server_fd); }
                               else if(n==0)
                                {
                                  fprintf(stderr,"C01 sentinel MCM closed it's Socket connection\n");
                                   terminate_thread(server_fd);
                                }     
                            else
                              {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from SENTINEL THREAD SUCCESSFUL\n");
                               } 
                             c1senQ.retrieve++; 
                                             
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                       else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C01");
                           strcpy(a1->CMD.system_name,"sentinel");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C01 sentinel MCM MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C01 Sentinel MCM RESPONSE\n"); terminate_thread(server_fd);  }
                            else if(n==0)
                            {
                              fprintf(stderr,"C01 sentinel MCM closed it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           else
                           {
                           
                                write_shm(a1,r1); 
                           } 
                         
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* C01_fiber_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
      char *tstamp;
     tstamp = malloc(25);
    
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       c1fiberQ.store = 0; c1fiberQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c1fiberQ.store)>(int)(c1fiberQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD*) c1_fiberq_retrieve((int)c1fiberQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"fiber_optics"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C01 FIBER OPTICS MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                       
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                    usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C01 FIBER OPTICS MCM RESPONSE\n"); terminate_thread(server_fd); }
                                else if(n==0)
                                {
                                 fprintf(stderr,"C01 FIBER OPTICS MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              {
                                     printresp(r1);
                                     write_shm(a1,r1);                  
                                     fprintf(stderr," Writing to ONLINE from FIBER THREAD SUCCESSFUL\n");
                               } 
                            
                             c1fiberQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                      else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C01");
                           strcpy(a1->CMD.system_name,"fiber_optics");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C01 FIBER OPTICS MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C01  FIBER OPTICS MCM RESPONSE\n");shutdown(server_fd,SHUT_RDWR);
                                     close(server_fd);
                                     pthread_exit(NULL);  }
                             else if(n==0)
                            {
                              fprintf(stderr,"C01 FIBER OPTICS MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           {
                             
                                write_shm(a1,r1);  
                            
                           } 
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* C01_front_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
 
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
      char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       c1frontQ.store = 0; c1frontQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c1frontQ.store)>(int)(c1frontQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = ( ANT_CMD*) c1_frontq_retrieve((int)c1frontQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"front_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C01 FRONT END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C01 FRONT END MCM RESPONSE\n"); 
                                    terminate_thread(server_fd);}
                               else if(n==0)
                              {
                                fprintf(stderr,"C01 FRONT END MCM closed it's Socket connection\n");
                                 terminate_thread(server_fd);
                              }
                              else
                              { printresp(r1); write_shm(a1,r1);  }
                           
                             c1frontQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       
                       }
                  /*    else
                       { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C01");
                           strcpy(a1->CMD.system_name,"front_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                           strcpy(a1->CMD.timestamp,tstamp);
                           c1 = &a1->CMD;
                              
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C01 FRONT END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C01 FRONT END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"C01 FRONT END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           {printresp(r1); write_shm(a1,r1);  }
                          
                         } */
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* C01_backend_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
        char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       c1backQ.store = 0; c1backQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c1backQ.store)>(int)(c1backQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c1_backq_retrieve((int)c1backQ.retrieve);
                        pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"back_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to C01 BACK END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C01 BACK END MCM RESPONSE\n");
                                    terminate_thread(server_fd);}
                                else if(n==0)
                               {
                                 fprintf(stderr,"C01 BACK END MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              { printresp(r1);write_shm(a1,r1); } 
                           
                             c1backQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                      else
                         { // Periodic Monitoring in the background
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C01");
                           strcpy(a1->CMD.system_name,"back_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C01 BACK END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C01 Back END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"C01 BACK END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           { write_shm(a1,r1); }
                       
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* C01_self_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1= malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       c1selfQ.store = 0; c1selfQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c1selfQ.store)>(int)(c1selfQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c1_selfq_retrieve((int)c1selfQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"self_test"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                                     
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C01  SELF SYSTEM  MCM RESPONSE\n"); 
                                     terminate_thread(server_fd); }
                              else if(n==0)
                            {
                              fprintf(stderr,"C01  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd); 
                            }
                              else
                              { write_shm(a1,r1); } 
                           
                             c1selfQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                     else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C01");
                           strcpy(a1->CMD.system_name,"self_test");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C01  SELF SYSTEM  MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                            { fprintf(stderr," ERROR READING C01 Self Test MCM RESPONSE\n"); terminate_thread(server_fd);}
                             else if(n==0)
                            {
                              fprintf(stderr,"C01  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1); } 
                           
                         }
                    }
  free(a1);
  free(r1);
  free(c1);
   return NULL;
}

/*************************************** C02 Antenna syste Thread functions here ******/

void* C02_fps_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
    
     resp *r1;
     r1 = malloc(sizeof(resp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       c2fpsQ.store = 0; c2fpsQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c2fpsQ.store)>(int)(c2fpsQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c2_fpsq_retrieve((int)c2fpsQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                              //  if(!strcasecmp(c1->system_name,"sentinel"))
                              if(!strcasecmp(c1->system_name,"fps"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C01 FPS MCM device\n"); }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "C01 FPS MCM TIMEOUT\n");
                                         terminate_thread(server_fd);
                                        
                                      }
                                      else
                                     { 
                                         printcmd(c1);
                                         bzero(c1,sizeof(cmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(3);
                                  bzero(r1,sizeof(resp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING C02 FPS MCM RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                  else if(n==0)
                                  {
                                     fprintf(stderr,"C02 FPS MCM closed it's Socket connection\n");
                                     terminate_thread(server_fd);
                                  }    
                                 else
                                 {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from FPS THREAD SUCCESSFUL\n");
                                 } 
                                c2fpsQ.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                     else
                         { // Periodic Monitoring in the background 
                          // sleep(5); // Sleep put as per CPK request Date 2/12/2014
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C02");
                           strcpy(a1->CMD.system_name,"fps");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"null");
                          //  strcpy(a1->CMD.op_name,"read_version");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                         
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C02 FPS MCM device\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C02 FPS MCM TIMEOUT #Perodic Monitoring\n");
                                terminate_thread(server_fd);
                             
                           }
                            else if(n==0)
                            {
                              fprintf(stderr,"C02 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(5);
                            bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C02 FPS 1 SECONDS MONITORING MCM RESPONSE\n");
                                   terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"C01 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              // printresp(r1);
                              write_shm(a1,r1); bzero(r1,sizeof(resp));
                            } 
                          } 
                
                    }

  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}


void* C02_sentinel_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       c2senQ.store = 0; c2senQ.retrieve = 0;
              for(;;)
              {
                   if((int)(c2senQ.store)>(int)(c2senQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c2_senq_retrieve((int)c2senQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                               // if(!strcasecmp(c1->system_name,"sentinel"))
                             if((!strcasecmp(c1->system_name,"sentinel"))||(!strcasecmp(c1->system_name,"fiber_optics")))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD C02 sentinel MCM device\n"); }
                                    else
                                   { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                        // bzero(c1,sizeof(cmd));   
                                         
                                    }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  usleep(500000);
                                 bzero(r1,sizeof(resp)); 
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING C02 sentinel MCM RESPONSE\n");  
                                     terminate_thread(server_fd); }
                               else if(n==0)
                                {
                                  fprintf(stderr,"C02 sentinel MCM closed it's Socket connection\n");
                                   terminate_thread(server_fd);
                                }     
                            else
                              {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from SENTINEL THREAD SUCCESSFUL\n");
                               } 
                             c2senQ.retrieve++; 
                                             
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                       else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C02");
                           strcpy(a1->CMD.system_name,"sentinel");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C02 sentinel MCM MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C02 Sentinel MCM RESPONSE\n"); terminate_thread(server_fd);  }
                            else if(n==0)
                            {
                              fprintf(stderr,"C02 sentinel MCM closed it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           else
                           {
                           
                                write_shm(a1,r1); 
                           } 
                         
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* C02_fiber_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
      char *tstamp;
     tstamp = malloc(25);
    
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       c2fiberQ.store = 0; c2fiberQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c2fiberQ.store)>(int)(c2fiberQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD*) c2_fiberq_retrieve((int)c2fiberQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"fiber_optics"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C02 FIBER OPTICS MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                       
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                    usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C02 FIBER OPTICS MCM RESPONSE\n");
                                    terminate_thread(server_fd); }
                                else if(n==0)
                                {
                                 fprintf(stderr,"C02 FIBER OPTICS MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              {
                                     printresp(r1);
                                     write_shm(a1,r1);                  
                                     fprintf(stderr," Writing to ONLINE from FIBER THREAD SUCCESSFUL\n");
                               } 
                            
                             c2fiberQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                      else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C02");
                           strcpy(a1->CMD.system_name,"fiber_optics");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C02 FIBER OPTICS MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C02  FIBER OPTICS MCM RESPONSE\n");
                                     shutdown(server_fd,SHUT_RDWR);
                                     close(server_fd);
                                     pthread_exit(NULL);  }
                             else if(n==0)
                            {
                              fprintf(stderr,"C02 FIBER OPTICS MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           {
                              write_shm(a1,r1);  
                            
                           } 
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* C02_front_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
 
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
      char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       c2frontQ.store = 0; c2frontQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c2frontQ.store)>(int)(c2frontQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = ( ANT_CMD*) c2_frontq_retrieve((int)c2frontQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"front_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C02 FRONT END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C02 FRONT END MCM RESPONSE\n"); 
                                    terminate_thread(server_fd);}
                               else if(n==0)
                              {
                                fprintf(stderr,"C02 FRONT END MCM closed it's Socket connection\n");
                                 terminate_thread(server_fd);
                              }
                              else
                              { printresp(r1); write_shm(a1,r1);  }
                           
                             c2frontQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       
                       }
                     else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C02");
                           strcpy(a1->CMD.system_name,"front_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                           strcpy(a1->CMD.timestamp,tstamp);
                           c1 = &a1->CMD;
                              
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C02 FRONT END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C02 FRONT END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"C02 FRONT END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1);  }
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* C02_backend_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
        char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       c2backQ.store = 0; c2backQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c2backQ.store)>(int)(c2backQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c2_backq_retrieve((int)c2backQ.retrieve);
                        pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"back_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to C02 BACK END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C02 BACK END MCM RESPONSE\n");
                                    terminate_thread(server_fd);}
                                else if(n==0)
                               {
                                 fprintf(stderr,"C02 BACK END MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              { printresp(r1);write_shm(a1,r1); } 
                           
                             c2backQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                      else
                         { // Periodic Monitoring in the background
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C02");
                           strcpy(a1->CMD.system_name,"back_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C02 BACK END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C02 Back END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"C02 BACK END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           { write_shm(a1,r1); }
                       
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* C02_self_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1= malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       c2selfQ.store = 0; c2selfQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c2selfQ.store)>(int)(c2selfQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c2_selfq_retrieve((int)c2selfQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"self_test"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                                     
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C02  SELF SYSTEM  MCM RESPONSE\n"); 
                                     terminate_thread(server_fd); }
                              else if(n==0)
                            {
                              fprintf(stderr,"C02 SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd); 
                            }
                              else
                              { write_shm(a1,r1); } 
                           
                             c2selfQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                     else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C02");
                           strcpy(a1->CMD.system_name,"self_test");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C02  SELF SYSTEM  MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                            { fprintf(stderr," ERROR READING C02 Self Test MCM RESPONSE\n"); terminate_thread(server_fd);}
                             else if(n==0)
                            {
                              fprintf(stderr,"C02  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1); } 
                           
                         }
                    }
  free(a1);
  free(r1);
  free(c1);
   return NULL;
}

/*************************************** C03 Antenna syste Thread functions here ******/

void* C03_fps_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
    
     resp *r1;
     r1 = malloc(sizeof(resp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       c3fpsQ.store = 0; c3fpsQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c3fpsQ.store)>(int)(c3fpsQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c3_fpsq_retrieve((int)c3fpsQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                              //  if(!strcasecmp(c1->system_name,"sentinel"))
                              if(!strcasecmp(c1->system_name,"fps"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C03 FPS MCM device\n"); }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "C03 FPS MCM TIMEOUT\n");
                                         terminate_thread(server_fd);
                                        
                                      }
                                      else
                                     { 
                                         printcmd(c1);
                                         bzero(c1,sizeof(cmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(3);
                                  bzero(r1,sizeof(resp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING C03 FPS MCM RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                  else if(n==0)
                                  {
                                     fprintf(stderr,"C03 FPS MCM closed it's Socket connection\n");
                                     terminate_thread(server_fd);
                                  }    
                                 else
                                 {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from FPS THREAD SUCCESSFUL\n");
                                 } 
                                c3fpsQ.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                     else
                         { // Periodic Monitoring in the background 
                          // sleep(5); // Sleep put as per CPK request Date 2/12/2014
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C03");
                           strcpy(a1->CMD.system_name,"fps");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"null");
                          //  strcpy(a1->CMD.op_name,"read_version");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                         
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C03 FPS MCM device\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C03 FPS MCM TIMEOUT #Perodic Monitoring\n");
                                terminate_thread(server_fd);
                             
                           }
                            else if(n==0)
                            {
                              fprintf(stderr,"C03 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(5);
                            bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C03 FPS 1 SECONDS MONITORING MCM RESPONSE\n");
                                   terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"C03 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              // printresp(r1);
                              write_shm(a1,r1); bzero(r1,sizeof(resp));
                            } 
                          } 
                
                    }

  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}


void* C03_sentinel_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       c3senQ.store = 0; c3senQ.retrieve = 0;
              for(;;)
              {
                   if((int)(c3senQ.store)>(int)(c3senQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c3_senq_retrieve((int)c3senQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                //if(!strcasecmp(c1->system_name,"sentinel"))
                            if((!strcasecmp(c1->system_name,"sentinel"))||(!strcasecmp(c1->system_name,"fiber_optics")))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD C03 sentinel MCM device\n"); }
                                    else
                                   { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                        // bzero(c1,sizeof(cmd));   
                                         
                                    }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  usleep(500000);
                                 bzero(r1,sizeof(resp)); 
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING C03 sentinel MCM RESPONSE\n");  
                                     terminate_thread(server_fd); }
                               else if(n==0)
                                {
                                  fprintf(stderr,"C03 sentinel MCM closed it's Socket connection\n");
                                   terminate_thread(server_fd);
                                }     
                            else
                              {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from SENTINEL THREAD SUCCESSFUL\n");
                               } 
                             c3senQ.retrieve++; 
                                             
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                       else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C03");
                           strcpy(a1->CMD.system_name,"sentinel");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C03 sentinel MCM MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C03 Sentinel MCM RESPONSE\n"); terminate_thread(server_fd);  }
                            else if(n==0)
                            {
                              fprintf(stderr,"C01 sentinel MCM closed it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           else
                           {
                           
                                write_shm(a1,r1); 
                           } 
                         
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* C03_fiber_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
      char *tstamp;
     tstamp = malloc(25);
    
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       c3fiberQ.store = 0; c3fiberQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c3fiberQ.store)>(int)(c3fiberQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD*) c3_fiberq_retrieve((int)c3fiberQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"fiber_optics"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C03 FIBER OPTICS MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                       
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                    usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C03 FIBER OPTICS MCM RESPONSE\n"); terminate_thread(server_fd); }
                                else if(n==0)
                                {
                                 fprintf(stderr,"C03 FIBER OPTICS MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              {
                                     printresp(r1);
                                     write_shm(a1,r1);                  
                                     fprintf(stderr," Writing to ONLINE from FIBER THREAD SUCCESSFUL\n");
                               } 
                            
                             c3fiberQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                      else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C03");
                           strcpy(a1->CMD.system_name,"fiber_optics");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C03 FIBER OPTICS MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C03  FIBER OPTICS MCM RESPONSE\n");shutdown(server_fd,SHUT_RDWR);
                                     close(server_fd);
                                     pthread_exit(NULL);  }
                             else if(n==0)
                            {
                              fprintf(stderr,"C03 FIBER OPTICS MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           {
                             
                                write_shm(a1,r1);  
                            
                           } 
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* C03_front_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
 
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
      char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       c3frontQ.store = 0; c3frontQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c3frontQ.store)>(int)(c3frontQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = ( ANT_CMD*) c3_frontq_retrieve((int)c3frontQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"front_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C03 FRONT END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C03 FRONT END MCM RESPONSE\n"); 
                                    terminate_thread(server_fd);}
                               else if(n==0)
                              {
                                fprintf(stderr,"C03 FRONT END MCM closed it's Socket connection\n");
                                 terminate_thread(server_fd);
                              }
                              else
                              { printresp(r1); write_shm(a1,r1);  }
                           
                             c3frontQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       
                       }
                     else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C03");
                           strcpy(a1->CMD.system_name,"front_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                           strcpy(a1->CMD.timestamp,tstamp);
                           c1 = &a1->CMD;
                              
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C03 FRONT END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C03 FRONT END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"C01 FRONT END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1);  }
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* C03_backend_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
        char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       c3backQ.store = 0; c3backQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c3backQ.store)>(int)(c3backQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c3_backq_retrieve((int)c3backQ.retrieve);
                        pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"back_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to C03 BACK END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C03 BACK END MCM RESPONSE\n");
                                    terminate_thread(server_fd);}
                                else if(n==0)
                               {
                                 fprintf(stderr,"C03 BACK END MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              { printresp(r1);write_shm(a1,r1); } 
                           
                             c3backQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                      else
                         { // Periodic Monitoring in the background
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C03");
                           strcpy(a1->CMD.system_name,"back_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C03 BACK END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C03 Back END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"C03 BACK END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           { write_shm(a1,r1); }
                       
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* C03_self_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1= malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       c3selfQ.store = 0; c3selfQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c3selfQ.store)>(int)(c3selfQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c3_selfq_retrieve((int)c3selfQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"self_test"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                                     
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C03  SELF SYSTEM  MCM RESPONSE\n"); 
                                     terminate_thread(server_fd); }
                              else if(n==0)
                            {
                              fprintf(stderr,"C03  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd); 
                            }
                              else
                              { write_shm(a1,r1); } 
                           
                             c3selfQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                     else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C03");
                           strcpy(a1->CMD.system_name,"self_test");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C03  SELF SYSTEM  MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                            { fprintf(stderr," ERROR READING C03 Self Test MCM RESPONSE\n"); terminate_thread(server_fd);}
                             else if(n==0)
                            {
                              fprintf(stderr,"C03  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1); } 
                           
                         }
                    }
  free(a1);
  free(r1);
  free(c1);
   return NULL;
}

/*************************************** C04 Antenna syste Thread functions here ******/

void* C04_fps_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
    
     resp *r1;
     r1 = malloc(sizeof(resp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       c4fpsQ.store = 0; c4fpsQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c4fpsQ.store)>(int)(c4fpsQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c4_fpsq_retrieve((int)c4fpsQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                              //  if(!strcasecmp(c1->system_name,"sentinel"))
                              if(!strcasecmp(c1->system_name,"fps"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C04 FPS MCM device\n"); }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "C04 FPS MCM TIMEOUT\n");
                                         terminate_thread(server_fd);
                                        
                                      }
                                      else
                                     { 
                                         printcmd(c1);
                                         bzero(c1,sizeof(cmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(3);
                                  bzero(r1,sizeof(resp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING C04 FPS MCM RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                  else if(n==0)
                                  {
                                     fprintf(stderr,"C04 FPS MCM closed it's Socket connection\n");
                                     terminate_thread(server_fd);
                                  }    
                                 else
                                 {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from FPS THREAD SUCCESSFUL\n");
                                 } 
                                c4fpsQ.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                     else
                         { // Periodic Monitoring in the background 
                          // sleep(5); // Sleep put as per CPK request Date 2/12/2014
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C04");
                           strcpy(a1->CMD.system_name,"fps");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"null");
                          //  strcpy(a1->CMD.op_name,"read_version");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                         
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C04 FPS MCM device\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C04 FPS MCM TIMEOUT #Perodic Monitoring\n");
                                terminate_thread(server_fd);
                             
                           }
                            else if(n==0)
                            {
                              fprintf(stderr,"C04 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(5);
                            bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C04 FPS 1 SECONDS MONITORING MCM RESPONSE\n");
                                   terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"C04 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              // printresp(r1);
                              write_shm(a1,r1); bzero(r1,sizeof(resp));
                            } 
                          } 
                
                    }

  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}
void* C04_sentinel_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       c4senQ.store = 0; c4senQ.retrieve = 0;
              for(;;)
              {
                   if((int)(c4senQ.store)>(int)(c4senQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c4_senq_retrieve((int)c4senQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                              //  if(!strcasecmp(c1->system_name,"sentinel"))
                              if((!strcasecmp(c1->system_name,"sentinel"))||(!strcasecmp(c1->system_name,"fiber_optics")))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD C04 sentinel MCM device\n"); }
                                    else
                                   { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                        // bzero(c1,sizeof(cmd));   
                                         
                                    }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  usleep(500000);
                                 bzero(r1,sizeof(resp)); 
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING C04 sentinel MCM RESPONSE\n");  
                                     terminate_thread(server_fd); }
                               else if(n==0)
                                {
                                  fprintf(stderr,"C04 sentinel MCM closed it's Socket connection\n");
                                   terminate_thread(server_fd);
                                }     
                            else
                              {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from SENTINEL THREAD SUCCESSFUL\n");
                               } 
                             c4senQ.retrieve++; 
                                             
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                       else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C04");
                           strcpy(a1->CMD.system_name,"sentinel");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C04 sentinel MCM MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C04 Sentinel MCM RESPONSE\n"); terminate_thread(server_fd);  }
                            else if(n==0)
                            {
                              fprintf(stderr,"C04 sentinel MCM closed it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           else
                           {
                           
                                write_shm(a1,r1); 
                           } 
                         
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* C04_fiber_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
      char *tstamp;
     tstamp = malloc(25);
    
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       c4fiberQ.store = 0; c4fiberQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c4fiberQ.store)>(int)(c4fiberQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD*) c4_fiberq_retrieve((int)c4fiberQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"fiber_optics"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C04 FIBER OPTICS MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                       
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                    usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C04 FIBER OPTICS MCM RESPONSE\n"); terminate_thread(server_fd); }
                                else if(n==0)
                                {
                                 fprintf(stderr,"C04 FIBER OPTICS MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              {
                                     printresp(r1);
                                     write_shm(a1,r1);                  
                                     fprintf(stderr," Writing to ONLINE from FIBER THREAD SUCCESSFUL\n");
                               } 
                            
                             c4fiberQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                      else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C04");
                           strcpy(a1->CMD.system_name,"fiber_optics");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C04 FIBER OPTICS MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C04  FIBER OPTICS MCM RESPONSE\n");shutdown(server_fd,SHUT_RDWR);
                                     close(server_fd);
                                     pthread_exit(NULL);  }
                             else if(n==0)
                            {
                              fprintf(stderr,"C01 FIBER OPTICS MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           {
                             
                                write_shm(a1,r1);  
                            
                           } 
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* C04_front_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
 
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
      char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       c4frontQ.store = 0; c4frontQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c4frontQ.store)>(int)(c4frontQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = ( ANT_CMD*) c4_frontq_retrieve((int)c4frontQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"front_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C04 FRONT END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C04 FRONT END MCM RESPONSE\n"); 
                                    terminate_thread(server_fd);}
                               else if(n==0)
                              {
                                fprintf(stderr,"C01 FRONT END MCM closed it's Socket connection\n");
                                 terminate_thread(server_fd);
                              }
                              else
                              { printresp(r1); write_shm(a1,r1);  }
                           
                             c4frontQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       
                       }
                     else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C04");
                           strcpy(a1->CMD.system_name,"front_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                           strcpy(a1->CMD.timestamp,tstamp);
                           c1 = &a1->CMD;
                              
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C04 FRONT END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C04 FRONT END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"C04 FRONT END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1);  }
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* C04_backend_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
        char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       c4backQ.store = 0; c4backQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c4backQ.store)>(int)(c4backQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c4_backq_retrieve((int)c4backQ.retrieve);
                        pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"back_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to C04 BACK END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C04 BACK END MCM RESPONSE\n");
                                    terminate_thread(server_fd);}
                                else if(n==0)
                               {
                                 fprintf(stderr,"C04 BACK END MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              { printresp(r1);write_shm(a1,r1); } 
                           
                             c4backQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                      else
                         { // Periodic Monitoring in the background
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C04");
                           strcpy(a1->CMD.system_name,"back_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C04 BACK END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C04 Back END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"C04 BACK END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           { write_shm(a1,r1); }
                       
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* C04_self_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1= malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       c4selfQ.store = 0; c4selfQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c4selfQ.store)>(int)(c4selfQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c4_selfq_retrieve((int)c4selfQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"self_test"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                                     
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C04  SELF SYSTEM  MCM RESPONSE\n"); 
                                     terminate_thread(server_fd); }
                              else if(n==0)
                            {
                              fprintf(stderr,"C04  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd); 
                            }
                              else
                              { write_shm(a1,r1); } 
                           
                             c4selfQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                     else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C04");
                           strcpy(a1->CMD.system_name,"self_test");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C04 SELF SYSTEM  MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                            { fprintf(stderr," ERROR READING C01 Self Test MCM RESPONSE\n"); terminate_thread(server_fd);}
                             else if(n==0)
                            {
                              fprintf(stderr,"C04 SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1); } 
                           
                         }
                    }
  free(a1);
  free(r1);
  free(c1);
   return NULL;
}

/*************************************** C05 Antenna syste Thread functions here ******/

void* C05_fps_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
    
     resp *r1;
     r1 = malloc(sizeof(resp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       c5fpsQ.store = 0; c5fpsQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c5fpsQ.store)>(int)(c5fpsQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c5_fpsq_retrieve((int)c5fpsQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                              //  if(!strcasecmp(c1->system_name,"sentinel"))
                              if(!strcasecmp(c1->system_name,"fps"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C05 FPS MCM device\n"); }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "C05 FPS MCM TIMEOUT\n");
                                         terminate_thread(server_fd);
                                        
                                      }
                                      else
                                     { 
                                         printcmd(c1);
                                         bzero(c1,sizeof(cmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(3);
                                  bzero(r1,sizeof(resp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING C05 FPS MCM RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                  else if(n==0)
                                  {
                                     fprintf(stderr,"C05 FPS MCM closed it's Socket connection\n");
                                     terminate_thread(server_fd);
                                  }    
                                 else
                                 {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from FPS THREAD SUCCESSFUL\n");
                                 } 
                                c5fpsQ.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                     else
                         { // Periodic Monitoring in the background 
                          // sleep(5); // Sleep put as per CPK request Date 2/12/2014
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C05");
                           strcpy(a1->CMD.system_name,"fps");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"null");
                          //  strcpy(a1->CMD.op_name,"read_version");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                         
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C05 FPS MCM device\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C05 FPS MCM TIMEOUT #Perodic Monitoring\n");
                                terminate_thread(server_fd);
                             
                           }
                            else if(n==0)
                            {
                              fprintf(stderr,"C05 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(5);
                            bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C05 FPS 1 SECONDS MONITORING MCM RESPONSE\n");
                                   terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"C05 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              // printresp(r1);
                              write_shm(a1,r1); bzero(r1,sizeof(resp));
                            } 
                          } 
                
                    }

  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}


void* C05_sentinel_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       c5senQ.store = 0; c5senQ.retrieve = 0;
              for(;;)
              {
                   if((int)(c5senQ.store)>(int)(c5senQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c5_senq_retrieve((int)c5senQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                //if(!strcasecmp(c1->system_name,"sentinel"))
                            if((!strcasecmp(c1->system_name,"sentinel"))||(!strcasecmp(c1->system_name,"fiber_optics")))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD C05 sentinel MCM device\n"); }
                                    else
                                   { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                        // bzero(c1,sizeof(cmd));   
                                         
                                    }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  usleep(500000);
                                 bzero(r1,sizeof(resp)); 
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING C05 sentinel MCM RESPONSE\n");  
                                     terminate_thread(server_fd); }
                               else if(n==0)
                                {
                                  fprintf(stderr,"C05 sentinel MCM closed it's Socket connection\n");
                                   terminate_thread(server_fd);
                                }     
                            else
                              {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from SENTINEL THREAD SUCCESSFUL\n");
                               } 
                             c5senQ.retrieve++; 
                                             
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                       else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C05");
                           strcpy(a1->CMD.system_name,"sentinel");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C05 sentinel MCM MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C05 Sentinel MCM RESPONSE\n"); terminate_thread(server_fd);  }
                            else if(n==0)
                            {
                              fprintf(stderr,"C05 sentinel MCM closed it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           else
                           {
                           
                                write_shm(a1,r1); 
                           } 
                         
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* C05_fiber_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
      char *tstamp;
     tstamp = malloc(25);
    
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       c5fiberQ.store = 0; c5fiberQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c5fiberQ.store)>(int)(c5fiberQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD*) c5_fiberq_retrieve((int)c5fiberQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"fiber_optics"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C05 FIBER OPTICS MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                       
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                    usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C05 FIBER OPTICS MCM RESPONSE\n"); terminate_thread(server_fd); }
                                else if(n==0)
                                {
                                 fprintf(stderr,"C05 FIBER OPTICS MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              {
                                     printresp(r1);
                                     write_shm(a1,r1);                  
                                     fprintf(stderr," Writing to ONLINE from FIBER THREAD SUCCESSFUL\n");
                               } 
                            
                             c5fiberQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                      else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C05");
                           strcpy(a1->CMD.system_name,"fiber_optics");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C05 FIBER OPTICS MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C05 FIBER OPTICS MCM RESPONSE\n");shutdown(server_fd,SHUT_RDWR);
                                     close(server_fd);
                                     pthread_exit(NULL);  }
                             else if(n==0)
                            {
                              fprintf(stderr,"C05 FIBER OPTICS MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           {
                             
                                write_shm(a1,r1);  
                            
                           } 
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* C05_front_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
 
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
      char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       c5frontQ.store = 0; c5frontQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c5frontQ.store)>(int)(c5frontQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = ( ANT_CMD*) c5_frontq_retrieve((int)c5frontQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"front_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C05 FRONT END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C05 FRONT END MCM RESPONSE\n"); 
                                    terminate_thread(server_fd);}
                               else if(n==0)
                              {
                                fprintf(stderr,"C05 FRONT END MCM closed it's Socket connection\n");
                                 terminate_thread(server_fd);
                              }
                              else
                              { printresp(r1); write_shm(a1,r1);  }
                           
                             c5frontQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       
                       }
                     else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C05");
                           strcpy(a1->CMD.system_name,"front_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                           strcpy(a1->CMD.timestamp,tstamp);
                           c1 = &a1->CMD;
                              
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C05 FRONT END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C05 FRONT END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"C01 FRONT END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1);  }
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* C05_backend_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
        char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       c5backQ.store = 0; c5backQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c5backQ.store)>(int)(c5backQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c5_backq_retrieve((int)c5backQ.retrieve);
                        pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"back_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to C05 BACK END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C05 BACK END MCM RESPONSE\n");
                                    terminate_thread(server_fd);}
                                else if(n==0)
                               {
                                 fprintf(stderr,"C05 BACK END MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              { printresp(r1);write_shm(a1,r1); } 
                           
                             c5backQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                      else
                         { // Periodic Monitoring in the background
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C05");
                           strcpy(a1->CMD.system_name,"back_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C05 BACK END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C05 Back END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"C05 BACK END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           { write_shm(a1,r1); }
                       
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* C05_self_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1= malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       c5selfQ.store = 0; c5selfQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c5selfQ.store)>(int)(c5selfQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c5_selfq_retrieve((int)c5selfQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"self_test"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                                     
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C05  SELF SYSTEM  MCM RESPONSE\n"); 
                                     terminate_thread(server_fd); }
                              else if(n==0)
                            {
                              fprintf(stderr,"C05  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd); 
                            }
                              else
                              { write_shm(a1,r1); } 
                           
                             c5selfQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                     else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C05");
                           strcpy(a1->CMD.system_name,"self_test");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C05  SELF SYSTEM  MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                            { fprintf(stderr," ERROR READING C05 Self Test MCM RESPONSE\n"); terminate_thread(server_fd);}
                             else if(n==0)
                            {
                              fprintf(stderr,"C05 SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1); } 
                           
                         }
                    }
  free(a1);
  free(r1);
  free(c1);
   return NULL;
}

/*************************************** C06 Antenna syste Thread functions here ******/

void* C06_fps_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
    
     resp *r1;
     r1 = malloc(sizeof(resp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       c6fpsQ.store = 0; c6fpsQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c6fpsQ.store)>(int)(c6fpsQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c6_fpsq_retrieve((int)c6fpsQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                              //  if(!strcasecmp(c1->system_name,"sentinel"))
                              if(!strcasecmp(c1->system_name,"fps"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C06 FPS MCM device\n"); }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "C06 FPS MCM TIMEOUT\n");
                                         terminate_thread(server_fd);
                                        
                                      }
                                      else
                                     { 
                                         printcmd(c1);
                                         bzero(c1,sizeof(cmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(5);
                                  bzero(r1,sizeof(resp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING C06 FPS MCM RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                  else if(n==0)
                                  {
                                     fprintf(stderr,"C06 FPS MCM closed it's Socket connection\n");
                                     terminate_thread(server_fd);
                                  }    
                                 else
                                 {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from FPS THREAD SUCCESSFUL\n");
                                 } 
                                c6fpsQ.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                     else
                         { // Periodic Monitoring in the background 
                          // sleep(5); // Sleep put as per CPK request Date 2/12/2014
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C06");
                           strcpy(a1->CMD.system_name,"fps");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"null");
                          //  strcpy(a1->CMD.op_name,"read_version");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                         
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C06 FPS MCM device\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C06 FPS MCM TIMEOUT #Perodic Monitoring\n");
                                terminate_thread(server_fd);
                             
                           }
                            else if(n==0)
                            {
                              fprintf(stderr,"C06 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(10);
                            bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C06 FPS 1 SECONDS MONITORING MCM RESPONSE\n");
                                   terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"C06 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              // printresp(r1);
                              write_shm(a1,r1); bzero(r1,sizeof(resp));
                            } 
                          } 
                
                    }

  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}

void* C06_sentinel_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       c6senQ.store = 0; c6senQ.retrieve = 0;
              for(;;)
              {
                   if((int)(c6senQ.store)>(int)(c6senQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c6_senq_retrieve((int)c6senQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                              //  if(!strcasecmp(c1->system_name,"sentinel"))
                            if((!strcasecmp(c1->system_name,"sentinel"))||(!strcasecmp(c1->system_name,"fiber_optics")))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD C06 sentinel MCM device\n"); }
                                    else
                                   { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                        // bzero(c1,sizeof(cmd));   
                                         
                                    }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  usleep(500000);
                                 bzero(r1,sizeof(resp)); 
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING C06 sentinel MCM RESPONSE\n");  
                                     terminate_thread(server_fd); }
                               else if(n==0)
                                {
                                  fprintf(stderr,"C06 sentinel MCM closed it's Socket connection\n");
                                   terminate_thread(server_fd);
                                }     
                            else
                              {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from SENTINEL THREAD SUCCESSFUL\n");
                               } 
                             c6senQ.retrieve++; 
                                             
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                       else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C06");
                           strcpy(a1->CMD.system_name,"sentinel");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C06 sentinel MCM MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C06 Sentinel MCM RESPONSE\n"); terminate_thread(server_fd);  }
                            else if(n==0)
                            {
                              fprintf(stderr,"C06 sentinel MCM closed it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           else
                           {
                           
                                write_shm(a1,r1); 
                           } 
                         
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* C06_fiber_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
      char *tstamp;
     tstamp = malloc(25);
    
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       c6fiberQ.store = 0; c6fiberQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c6fiberQ.store)>(int)(c6fiberQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD*) c6_fiberq_retrieve((int)c6fiberQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"fiber_optics"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C06 FIBER OPTICS MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                       
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                    usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C06 FIBER OPTICS MCM RESPONSE\n"); terminate_thread(server_fd); }
                                else if(n==0)
                                {
                                 fprintf(stderr,"C06 FIBER OPTICS MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              {
                                     printresp(r1);
                                     write_shm(a1,r1);                  
                                     fprintf(stderr," Writing to ONLINE from FIBER THREAD SUCCESSFUL\n");
                               } 
                            
                             c6fiberQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                      else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C06");
                           strcpy(a1->CMD.system_name,"fiber_optics");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C06 FIBER OPTICS MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C06 FIBER OPTICS MCM RESPONSE\n");
                                terminate_thread(server_fd);       }
                             else if(n==0)
                            {
                              fprintf(stderr,"C06 FIBER OPTICS MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           {
                             
                                write_shm(a1,r1);  
                            
                           } 
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* C06_front_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
 
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
      char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       c6frontQ.store = 0; c6frontQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c6frontQ.store)>(int)(c6frontQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = ( ANT_CMD*) c6_frontq_retrieve((int)c6frontQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"front_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C06 FRONT END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C06 FRONT END MCM RESPONSE\n"); 
                                    terminate_thread(server_fd);}
                               else if(n==0)
                              {
                                fprintf(stderr,"C06 FRONT END MCM closed it's Socket connection\n");
                                 terminate_thread(server_fd);
                              }
                              else
                              { printresp(r1); write_shm(a1,r1);  }
                           
                             c6frontQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       
                       }
                     else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C06");
                           strcpy(a1->CMD.system_name,"front_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                           strcpy(a1->CMD.timestamp,tstamp);
                           c1 = &a1->CMD;
                              
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C06 FRONT END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C06 FRONT END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"C06 FRONT END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1);  }
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* C06_backend_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
        char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       c6backQ.store = 0; c6backQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c6backQ.store)>(int)(c6backQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c6_backq_retrieve((int)c6backQ.retrieve);
                        pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"back_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to C06 BACK END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C06 BACK END MCM RESPONSE\n");
                                    terminate_thread(server_fd);}
                                else if(n==0)
                               {
                                 fprintf(stderr,"C06 BACK END MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              { printresp(r1);write_shm(a1,r1); } 
                           
                             c6backQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                      else
                         { // Periodic Monitoring in the background
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C06");
                           strcpy(a1->CMD.system_name,"back_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C06 BACK END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C06 Back END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"C05 BACK END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           { write_shm(a1,r1); }
                       
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* C06_self_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1= malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       c6selfQ.store = 0; c6selfQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c6selfQ.store)>(int)(c6selfQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c6_selfq_retrieve((int)c6selfQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"self_test"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                                     
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C06  SELF SYSTEM  MCM RESPONSE\n"); 
                                     terminate_thread(server_fd); }
                              else if(n==0)
                            {
                              fprintf(stderr,"C06  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd); 
                            }
                              else
                              { write_shm(a1,r1); } 
                           
                             c6selfQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                     else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C06");
                           strcpy(a1->CMD.system_name,"self_test");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C06  SELF SYSTEM  MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                            { fprintf(stderr," ERROR READING C06 Self Test MCM RESPONSE\n"); terminate_thread(server_fd);}
                             else if(n==0)
                            {
                              fprintf(stderr,"C06 SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1); } 
                           
                         }
                    }
  free(a1);
  free(r1);
  free(c1);
   return NULL;
}


/*************************************** C08 Antenna syste Thread functions here ******/

void* C08_fps_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
    
     resp *r1;
     r1 = malloc(sizeof(resp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       c8fpsQ.store = 0; c8fpsQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c8fpsQ.store)>(int)(c8fpsQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c8_fpsq_retrieve((int)c8fpsQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                              //  if(!strcasecmp(c1->system_name,"sentinel"))
                              if(!strcasecmp(c1->system_name,"fps"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C08 FPS MCM device\n"); }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "C08 FPS MCM TIMEOUT\n");
                                         terminate_thread(server_fd);
                                        
                                      }
                                      else
                                     { 
                                         printcmd(c1);
                                         bzero(c1,sizeof(cmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(3);
                                  bzero(r1,sizeof(resp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING C08 FPS MCM RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                  else if(n==0)
                                  {
                                     fprintf(stderr,"C08 FPS MCM closed it's Socket connection\n");
                                     terminate_thread(server_fd);
                                  }    
                                 else
                                 {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from FPS THREAD SUCCESSFUL\n");
                                 } 
                                c8fpsQ.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                     else
                         { // Periodic Monitoring in the background 
                          // sleep(5); // Sleep put as per CPK request Date 2/12/2014
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C08");
                           strcpy(a1->CMD.system_name,"fps");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"null");
                          //  strcpy(a1->CMD.op_name,"read_version");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                         
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C08 FPS MCM device\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C08 FPS MCM TIMEOUT #Perodic Monitoring\n");
                                terminate_thread(server_fd);
                             
                           }
                            else if(n==0)
                            {
                              fprintf(stderr,"C08 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(5);
                            bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C08 FPS 1 SECONDS MONITORING MCM RESPONSE\n");
                                   terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"C08 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              // printresp(r1);
                              write_shm(a1,r1); bzero(r1,sizeof(resp));
                            } 
                          } 
                
                    }

  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}


void* C08_sentinel_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       c8senQ.store = 0; c8senQ.retrieve = 0;
              for(;;)
              {
                   if((int)(c8senQ.store)>(int)(c8senQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c8_senq_retrieve((int)c8senQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                               // if(!strcasecmp(c1->system_name,"sentinel"))
                            if((!strcasecmp(c1->system_name,"sentinel"))||(!strcasecmp(c1->system_name,"fiber_optics")))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD C08 sentinel MCM device\n"); }
                                    else
                                   { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                        // bzero(c1,sizeof(cmd));   
                                         
                                    }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  usleep(500000);
                                 bzero(r1,sizeof(resp)); 
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING C08 sentinel MCM RESPONSE\n");  
                                     terminate_thread(server_fd); }
                               else if(n==0)
                                {
                                  fprintf(stderr,"C08 sentinel MCM closed it's Socket connection\n");
                                   terminate_thread(server_fd);
                                }     
                            else
                              {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from SENTINEL THREAD SUCCESSFUL\n");
                               } 
                             c8senQ.retrieve++; 
                                             
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                       else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C08");
                           strcpy(a1->CMD.system_name,"sentinel");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C08 sentinel MCM MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C08 Sentinel MCM RESPONSE\n"); terminate_thread(server_fd);  }
                            else if(n==0)
                            {
                              fprintf(stderr,"C08 sentinel MCM closed it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           else
                           {
                           
                                write_shm(a1,r1); 
                           } 
                         
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* C08_fiber_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
      char *tstamp;
     tstamp = malloc(25);
    
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       c8fiberQ.store = 0; c8fiberQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c8fiberQ.store)>(int)(c8fiberQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD*) c8_fiberq_retrieve((int)c8fiberQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"fiber_optics"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C08 FIBER OPTICS MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                       
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                    usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C08 FIBER OPTICS MCM RESPONSE\n"); terminate_thread(server_fd); }
                                else if(n==0)
                                {
                                 fprintf(stderr,"C08 FIBER OPTICS MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              {
                                     printresp(r1);
                                     write_shm(a1,r1);                  
                                     fprintf(stderr," Writing to ONLINE from FIBER THREAD SUCCESSFUL\n");
                               } 
                            
                             c8fiberQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                      else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C08");
                           strcpy(a1->CMD.system_name,"fiber_optics");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C08 FIBER OPTICS MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C08 FIBER OPTICS MCM RESPONSE\n");shutdown(server_fd,SHUT_RDWR);
                                     close(server_fd);
                                     pthread_exit(NULL);  }
                             else if(n==0)
                            {
                              fprintf(stderr,"C08 FIBER OPTICS MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           {
                               write_shm(a1,r1);  
                            
                           } 
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* C08_front_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
 
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
      char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       c8frontQ.store = 0; c8frontQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c8frontQ.store)>(int)(c8frontQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = ( ANT_CMD*) c8_frontq_retrieve((int)c8frontQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"front_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C08 FRONT END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C08 FRONT END MCM RESPONSE\n"); 
                                    terminate_thread(server_fd);}
                               else if(n==0)
                              {
                                fprintf(stderr,"C08 FRONT END MCM closed it's Socket connection\n");
                                 terminate_thread(server_fd);
                              }
                              else
                              { printresp(r1); write_shm(a1,r1);  }
                           
                             c8frontQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       
                       }
                     else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C08");
                           strcpy(a1->CMD.system_name,"front_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                           strcpy(a1->CMD.timestamp,tstamp);
                           c1 = &a1->CMD;
                              
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C08 FRONT END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C08 FRONT END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"C08 FRONT END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1);  }
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* C08_backend_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
        char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       c8backQ.store = 0; c8backQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c8backQ.store)>(int)(c8backQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c8_backq_retrieve((int)c8backQ.retrieve);
                        pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"back_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to C08 BACK END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C08 BACK END MCM RESPONSE\n");
                                    terminate_thread(server_fd);}
                                else if(n==0)
                               {
                                 fprintf(stderr,"C08 BACK END MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              { printresp(r1);write_shm(a1,r1); } 
                           
                             c8backQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                      else
                         { // Periodic Monitoring in the background
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C08");
                           strcpy(a1->CMD.system_name,"back_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C08 BACK END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C08 Back END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"C08 BACK END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           { write_shm(a1,r1); }
                       
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* C08_self_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1= malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       c8selfQ.store = 0; c8selfQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c8selfQ.store)>(int)(c8selfQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c8_selfq_retrieve((int)c8selfQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"self_test"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                                     
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C08  SELF SYSTEM  MCM RESPONSE\n"); 
                                     terminate_thread(server_fd); }
                              else if(n==0)
                            {
                              fprintf(stderr,"C08  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd); 
                            }
                              else
                              { write_shm(a1,r1); } 
                           
                             c8selfQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                     else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C08");
                           strcpy(a1->CMD.system_name,"self_test");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C08 SELF SYSTEM  MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                            { fprintf(stderr," ERROR READING C08 Self Test MCM RESPONSE\n"); terminate_thread(server_fd);}
                             else if(n==0)
                            {
                              fprintf(stderr,"C08 SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1); } 
                           
                         }
                    }
  free(a1);
  free(r1);
  free(c1);
   return NULL;
}

/*************************************** C09 Antenna syste Thread functions here ******/
void* C09_fps_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
    
     resp *r1;
     r1 = malloc(sizeof(resp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       c9fpsQ.store = 0; c9fpsQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c9fpsQ.store)>(int)(c9fpsQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c9_fpsq_retrieve((int)c9fpsQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                              //  if(!strcasecmp(c1->system_name,"sentinel"))
                              if(!strcasecmp(c1->system_name,"fps"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C09 FPS MCM device\n"); }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "C09 FPS MCM TIMEOUT\n");
                                         terminate_thread(server_fd);
                                        
                                      }
                                      else
                                     { 
                                         printcmd(c1);
                                         bzero(c1,sizeof(cmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(3);
                                  bzero(r1,sizeof(resp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING C09 FPS MCM RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                  else if(n==0)
                                  {
                                     fprintf(stderr,"C09 FPS MCM closed it's Socket connection\n");
                                     terminate_thread(server_fd);
                                  }    
                                 else
                                 {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from FPS THREAD SUCCESSFUL\n");
                                 } 
                                c9fpsQ.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                     else
                         { // Periodic Monitoring in the background 
                          // sleep(5); // Sleep put as per CPK request Date 2/12/2014
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C09");
                           strcpy(a1->CMD.system_name,"fps");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"null");
                          //  strcpy(a1->CMD.op_name,"read_version");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                         
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C09 FPS MCM device\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C09 FPS MCM TIMEOUT #Perodic Monitoring\n");
                                terminate_thread(server_fd);
                             
                           }
                            else if(n==0)
                            {
                              fprintf(stderr,"C09 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(5);
                            bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C09 FPS 1 SECONDS MONITORING MCM RESPONSE\n");
                                   terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"C09 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              // printresp(r1);
                              write_shm(a1,r1); bzero(r1,sizeof(resp));
                            } 
                          } 
                
                    }

  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}
void* C09_sentinel_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       c9senQ.store = 0; c9senQ.retrieve = 0;
              for(;;)
              {
                   if((int)(c9senQ.store)>(int)(c9senQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c9_senq_retrieve((int)c9senQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                               // if(!strcasecmp(c1->system_name,"sentinel"))
                             if((!strcasecmp(c1->system_name,"sentinel"))||(!strcasecmp(c1->system_name,"fiber_optics")))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD C09 sentinel MCM device\n"); }
                                    else
                                   { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                        // bzero(c1,sizeof(cmd));   
                                         
                                    }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  usleep(500000);
                                 bzero(r1,sizeof(resp)); 
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING C09 sentinel MCM RESPONSE\n");  
                                     terminate_thread(server_fd); }
                               else if(n==0)
                                {
                                  fprintf(stderr,"C09 sentinel MCM closed it's Socket connection\n");
                                   terminate_thread(server_fd);
                                }     
                            else
                              {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from SENTINEL THREAD SUCCESSFUL\n");
                               } 
                             c9senQ.retrieve++; 
                                             
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                       else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C09");
                           strcpy(a1->CMD.system_name,"sentinel");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C09 sentinel MCM MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C09 Sentinel MCM RESPONSE\n"); terminate_thread(server_fd);  }
                            else if(n==0)
                            {
                              fprintf(stderr,"C09 sentinel MCM closed it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           else
                           {
                           
                                write_shm(a1,r1); 
                           } 
                         
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* C09_fiber_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
      char *tstamp;
     tstamp = malloc(25);
    
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       c9fiberQ.store = 0; c9fiberQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c9fiberQ.store)>(int)(c9fiberQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD*) c9_fiberq_retrieve((int)c9fiberQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"fiber_optics"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C09 FIBER OPTICS MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                       
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                    usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C09 FIBER OPTICS MCM RESPONSE\n"); terminate_thread(server_fd); }
                                else if(n==0)
                                {
                                 fprintf(stderr,"C09 FIBER OPTICS MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              {
                                     printresp(r1);
                                     write_shm(a1,r1);                  
                                     fprintf(stderr," Writing to ONLINE from FIBER THREAD SUCCESSFUL\n");
                               } 
                            
                             c9fiberQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                      else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C09");
                           strcpy(a1->CMD.system_name,"fiber_optics");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C09 FIBER OPTICS MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C09 FIBER OPTICS MCM RESPONSE\n");shutdown(server_fd,SHUT_RDWR);
                                     close(server_fd);
                                     pthread_exit(NULL);  }
                             else if(n==0)
                            {
                              fprintf(stderr,"C09 FIBER OPTICS MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           {
                             
                                write_shm(a1,r1);  
                            
                           } 
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* C09_front_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
 
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
      char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       c9frontQ.store = 0; c9frontQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c9frontQ.store)>(int)(c9frontQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = ( ANT_CMD*) c9_frontq_retrieve((int)c9frontQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"front_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C09 FRONT END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C07 FRONT END MCM RESPONSE\n"); 
                                    terminate_thread(server_fd);}
                               else if(n==0)
                              {
                                fprintf(stderr,"C09 FRONT END MCM closed it's Socket connection\n");
                                 terminate_thread(server_fd);
                              }
                              else
                              { printresp(r1); write_shm(a1,r1);  }
                           
                             c9frontQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       
                       }
                     else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C09");
                           strcpy(a1->CMD.system_name,"front_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                           strcpy(a1->CMD.timestamp,tstamp);
                           c1 = &a1->CMD;
                              
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C09 FRONT END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C09 FRONT END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"C09 FRONT END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1);  }
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* C09_backend_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
        char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       c9backQ.store = 0; c9backQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c9backQ.store)>(int)(c9backQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c9_backq_retrieve((int)c9backQ.retrieve);
                        pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"back_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to C09 BACK END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C09 BACK END MCM RESPONSE\n");
                                    terminate_thread(server_fd);}
                                else if(n==0)
                               {
                                 fprintf(stderr,"C09 BACK END MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              { printresp(r1);write_shm(a1,r1); } 
                           
                             c9backQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                      else
                         { // Periodic Monitoring in the background
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C09");
                           strcpy(a1->CMD.system_name,"back_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C09 BACK END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C09 Back END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"C07 BACK END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           { write_shm(a1,r1); }
                       
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* C09_self_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1= malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       c9selfQ.store = 0; c9selfQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c9selfQ.store)>(int)(c9selfQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c9_selfq_retrieve((int)c9selfQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"self_test"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                                     
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C09 SELF SYSTEM  MCM RESPONSE\n"); 
                                     terminate_thread(server_fd); }
                              else if(n==0)
                            {
                              fprintf(stderr,"C09 SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd); 
                            }
                              else
                              { write_shm(a1,r1); } 
                           
                             c9selfQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                     else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C09");
                           strcpy(a1->CMD.system_name,"self_test");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C09 SELF SYSTEM  MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                            { fprintf(stderr," ERROR READING C09 Self Test MCM RESPONSE\n"); terminate_thread(server_fd);}
                             else if(n==0)
                            {
                              fprintf(stderr,"C07 SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1); } 
                           
                         }
                    }
  free(a1);
  free(r1);
  free(c1);
   return NULL;
}

/*************************************** C10 Antenna syste Thread functions here ******/

void* C10_fps_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
    
     resp *r1;
     r1 = malloc(sizeof(resp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       c10fpsQ.store = 0; c10fpsQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c10fpsQ.store)>(int)(c10fpsQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c10_fpsq_retrieve((int)c10fpsQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                              //  if(!strcasecmp(c1->system_name,"sentinel"))
                              if(!strcasecmp(c1->system_name,"fps"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C10 FPS MCM device\n"); }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "C10 FPS MCM TIMEOUT\n");
                                         terminate_thread(server_fd);
                                        
                                      }
                                      else
                                     { 
                                         printcmd(c1);
                                         bzero(c1,sizeof(cmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(3);
                                  bzero(r1,sizeof(resp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING C00 FPS MCM RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                  else if(n==0)
                                  {
                                     fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                                     terminate_thread(server_fd);
                                  }    
                                 else
                                 {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from FPS THREAD SUCCESSFUL\n");
                                 } 
                                c10fpsQ.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                     else
                         { // Periodic Monitoring in the background 
                          // sleep(5); // Sleep put as per CPK request Date 2/12/2014
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C10");
                           strcpy(a1->CMD.system_name,"fps");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"null");
                          //  strcpy(a1->CMD.op_name,"read_version");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                         
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C10 FPS MCM device\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C00 FPS MCM TIMEOUT #Perodic Monitoring\n");
                                terminate_thread(server_fd);
                             
                           }
                            else if(n==0)
                            {
                              fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(5);
                            bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C10 FPS 1 SECONDS MONITORING MCM RESPONSE\n");
                                   terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"C10 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              // printresp(r1);
                              write_shm(a1,r1); bzero(r1,sizeof(resp));
                            } 
                          } 
                
                    }

  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}

void* C10_sentinel_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       c10senQ.store = 0; c10senQ.retrieve = 0;
              for(;;)
              {
                   if((int)(c10senQ.store)>(int)(c10senQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c10_senq_retrieve((int)c10senQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                              //  if(!strcasecmp(c1->system_name,"sentinel"))
                             if((!strcasecmp(c1->system_name,"sentinel"))||(!strcasecmp(c1->system_name,"fiber_optics")))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD C10 sentinel MCM device\n"); }
                                    else
                                   { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                        // bzero(c1,sizeof(cmd));   
                                         
                                    }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  usleep(500000);
                                 bzero(r1,sizeof(resp)); 
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING C10 sentinel MCM RESPONSE\n");  
                                     terminate_thread(server_fd); }
                               else if(n==0)
                                {
                                  fprintf(stderr,"C10 sentinel MCM closed it's Socket connection\n");
                                   terminate_thread(server_fd);
                                }     
                            else
                              {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from SENTINEL THREAD SUCCESSFUL\n");
                               } 
                             c10senQ.retrieve++; 
                                             
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                       else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C10");
                           strcpy(a1->CMD.system_name,"sentinel");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C10 sentinel MCM MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C10 Sentinel MCM RESPONSE\n"); terminate_thread(server_fd);  }
                            else if(n==0)
                            {
                              fprintf(stderr,"C10 sentinel MCM closed it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           else
                           {
                           
                                write_shm(a1,r1); 
                           } 
                         
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* C10_fiber_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
      char *tstamp;
     tstamp = malloc(25);
    
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       c10fiberQ.store = 0; c10fiberQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c10fiberQ.store)>(int)(c10fiberQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD*) c10_fiberq_retrieve((int)c10fiberQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"fiber_optics"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C10 FIBER OPTICS MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                       
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                    usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C10 FIBER OPTICS MCM RESPONSE\n"); terminate_thread(server_fd); }
                                else if(n==0)
                                {
                                 fprintf(stderr,"C10 FIBER OPTICS MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              {
                                     printresp(r1);
                                     write_shm(a1,r1);                  
                                     fprintf(stderr," Writing to ONLINE from FIBER THREAD SUCCESSFUL\n");
                               } 
                            
                             c10fiberQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                      else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C10");
                           strcpy(a1->CMD.system_name,"fiber_optics");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C10 FIBER OPTICS MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C10  FIBER OPTICS MCM RESPONSE\n");shutdown(server_fd,SHUT_RDWR);
                                     close(server_fd);
                                     pthread_exit(NULL);  }
                             else if(n==0)
                            {
                              fprintf(stderr,"C10 FIBER OPTICS MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           {
                             
                                write_shm(a1,r1);  
                            
                           } 
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* C10_front_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
 
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
      char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       c10frontQ.store = 0; c10frontQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c10frontQ.store)>(int)(c10frontQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = ( ANT_CMD*) c10_frontq_retrieve((int)c10frontQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"front_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C10 FRONT END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C10 FRONT END MCM RESPONSE\n"); 
                                    terminate_thread(server_fd);}
                               else if(n==0)
                              {
                                fprintf(stderr,"C10 FRONT END MCM closed it's Socket connection\n");
                                 terminate_thread(server_fd);
                              }
                              else
                              { printresp(r1); write_shm(a1,r1);  }
                           
                             c10frontQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       
                       }
                     else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C10");
                           strcpy(a1->CMD.system_name,"front_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                           strcpy(a1->CMD.timestamp,tstamp);
                           c1 = &a1->CMD;
                              
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C10 FRONT END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C10 FRONT END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"C10 FRONT END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1);  }
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* C10_backend_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
        char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       c10backQ.store = 0; c10backQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c10backQ.store)>(int)(c10backQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c10_backq_retrieve((int)c10backQ.retrieve);
                        pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"back_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to C10 BACK END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C10 BACK END MCM RESPONSE\n");
                                    terminate_thread(server_fd);}
                                else if(n==0)
                               {
                                 fprintf(stderr,"C10 BACK END MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              { printresp(r1);write_shm(a1,r1); } 
                           
                             c10backQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                      else
                         { // Periodic Monitoring in the background
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C10");
                           strcpy(a1->CMD.system_name,"back_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C10 BACK END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C10 Back END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"C10 BACK END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           { write_shm(a1,r1); }
                       
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* C10_self_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1= malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       c10selfQ.store = 0; c10selfQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c10selfQ.store)>(int)(c10selfQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c10_selfq_retrieve((int)c10selfQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"self_test"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                                     
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C10  SELF SYSTEM  MCM RESPONSE\n"); 
                                     terminate_thread(server_fd); }
                              else if(n==0)
                            {
                              fprintf(stderr,"C10  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd); 
                            }
                              else
                              { write_shm(a1,r1); } 
                           
                             c10selfQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                     else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C10");
                           strcpy(a1->CMD.system_name,"self_test");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C10  SELF SYSTEM  MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                            { fprintf(stderr," ERROR READING C10 Self Test MCM RESPONSE\n"); terminate_thread(server_fd);}
                             else if(n==0)
                            {
                              fprintf(stderr,"C10  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1); } 
                           
                         }
                    }
  free(a1);
  free(r1);
  free(c1);
   return NULL;
}

/*************************************** C11 Antenna syste Thread functions here ******/

void* C11_fps_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
    
     resp *r1;
     r1 = malloc(sizeof(resp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       c11fpsQ.store = 0; c11fpsQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c11fpsQ.store)>(int)(c11fpsQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c11_fpsq_retrieve((int)c11fpsQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                              //  if(!strcasecmp(c1->system_name,"sentinel"))
                              if(!strcasecmp(c1->system_name,"fps"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C11 FPS MCM device\n"); }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "C11 FPS MCM TIMEOUT\n");
                                         terminate_thread(server_fd);
                                        
                                      }
                                      else
                                     { 
                                         printcmd(c1);
                                         bzero(c1,sizeof(cmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(3);
                                  bzero(r1,sizeof(resp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING C00 FPS MCM RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                  else if(n==0)
                                  {
                                     fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                                     terminate_thread(server_fd);
                                  }    
                                 else
                                 {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from FPS THREAD SUCCESSFUL\n");
                                 } 
                                c11fpsQ.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                     else
                         { // Periodic Monitoring in the background 
                          // sleep(5); // Sleep put as per CPK request Date 2/12/2014
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C11");
                           strcpy(a1->CMD.system_name,"fps");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"null");
                          //  strcpy(a1->CMD.op_name,"read_version");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                         
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C11 FPS MCM device\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C00 FPS MCM TIMEOUT #Perodic Monitoring\n");
                                terminate_thread(server_fd);
                             
                           }
                            else if(n==0)
                            {
                              fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(5);
                            bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C11 FPS 1 SECONDS MONITORING MCM RESPONSE\n");
                                   terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"C11 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              // printresp(r1);
                              write_shm(a1,r1); bzero(r1,sizeof(resp));
                            } 
                          } 
                
                    }

  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}

void* C11_sentinel_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       c11senQ.store = 0; c11senQ.retrieve = 0;
              for(;;)
              {
                   if((int)(c11senQ.store)>(int)(c11senQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c11_senq_retrieve((int)c11senQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                               // if(!strcasecmp(c1->system_name,"sentinel"))
                              if((!strcasecmp(c1->system_name,"sentinel"))||(!strcasecmp(c1->system_name,"fiber_optics")))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD C11 sentinel MCM device\n"); }
                                    else
                                   { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                        // bzero(c1,sizeof(cmd));   
                                         
                                    }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  usleep(500000);
                                 bzero(r1,sizeof(resp)); 
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING C11 sentinel MCM RESPONSE\n");  
                                     terminate_thread(server_fd); }
                               else if(n==0)
                                {
                                  fprintf(stderr,"C11 sentinel MCM closed it's Socket connection\n");
                                   terminate_thread(server_fd);
                                }     
                            else
                              {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from SENTINEL THREAD SUCCESSFUL\n");
                               } 
                             c11senQ.retrieve++; 
                                             
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                       else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C11");
                           strcpy(a1->CMD.system_name,"sentinel");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C11 sentinel MCM MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C11 Sentinel MCM RESPONSE\n"); terminate_thread(server_fd);  }
                            else if(n==0)
                            {
                              fprintf(stderr,"C11 sentinel MCM closed it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           else
                           {
                           
                                write_shm(a1,r1); 
                           } 
                         
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* C11_fiber_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
      char *tstamp;
     tstamp = malloc(25);
    
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       c11fiberQ.store = 0; c11fiberQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c11fiberQ.store)>(int)(c11fiberQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD*) c11_fiberq_retrieve((int)c11fiberQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"fiber_optics"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C11 FIBER OPTICS MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                       
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                    usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C11 FIBER OPTICS MCM RESPONSE\n"); terminate_thread(server_fd); }
                                else if(n==0)
                                {
                                 fprintf(stderr,"C11 FIBER OPTICS MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              {
                                     printresp(r1);
                                     write_shm(a1,r1);                  
                                     fprintf(stderr," Writing to ONLINE from FIBER THREAD SUCCESSFUL\n");
                               } 
                            
                             c11fiberQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                      else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C11");
                           strcpy(a1->CMD.system_name,"fiber_optics");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C11 FIBER OPTICS MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C11  FIBER OPTICS MCM RESPONSE\n");shutdown(server_fd,SHUT_RDWR);
                                     close(server_fd);
                                     pthread_exit(NULL);  }
                             else if(n==0)
                            {
                              fprintf(stderr,"C11 FIBER OPTICS MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           {
                             
                                write_shm(a1,r1);  
                            
                           } 
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* C11_front_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
 
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
      char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       c11frontQ.store = 0; c11frontQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c11frontQ.store)>(int)(c11frontQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = ( ANT_CMD*) c11_frontq_retrieve((int)c11frontQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"front_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C11 FRONT END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C11 FRONT END MCM RESPONSE\n"); 
                                    terminate_thread(server_fd);}
                               else if(n==0)
                              {
                                fprintf(stderr,"C11 FRONT END MCM closed it's Socket connection\n");
                                 terminate_thread(server_fd);
                              }
                              else
                              { printresp(r1); write_shm(a1,r1);  }
                           
                             c11frontQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       
                       }
                     else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C11");
                           strcpy(a1->CMD.system_name,"front_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                           strcpy(a1->CMD.timestamp,tstamp);
                           c1 = &a1->CMD;
                              
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C11 FRONT END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C11 FRONT END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"C11 FRONT END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1);  }
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* C11_backend_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
        char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       c11backQ.store = 0; c11backQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c11backQ.store)>(int)(c11backQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c11_backq_retrieve((int)c11backQ.retrieve);
                        pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"back_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to C11 BACK END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C11 BACK END MCM RESPONSE\n");
                                    terminate_thread(server_fd);}
                                else if(n==0)
                               {
                                 fprintf(stderr,"C11 BACK END MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              { printresp(r1);write_shm(a1,r1); } 
                           
                             c11backQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                      else
                         { // Periodic Monitoring in the background
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C11");
                           strcpy(a1->CMD.system_name,"back_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C11 BACK END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C11 Back END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"C11 BACK END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           { write_shm(a1,r1); }
                       
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* C11_self_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1= malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       c11selfQ.store = 0; c11selfQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c11selfQ.store)>(int)(c11selfQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c11_selfq_retrieve((int)c11selfQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"self_test"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                                     
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C11  SELF SYSTEM  MCM RESPONSE\n"); 
                                     terminate_thread(server_fd); }
                              else if(n==0)
                            {
                              fprintf(stderr,"C11  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd); 
                            }
                              else
                              { write_shm(a1,r1); } 
                           
                             c11selfQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                     else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C11");
                           strcpy(a1->CMD.system_name,"self_test");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C11  SELF SYSTEM  MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                            { fprintf(stderr," ERROR READING C11 Self Test MCM RESPONSE\n"); terminate_thread(server_fd);}
                             else if(n==0)
                            {
                              fprintf(stderr,"C11  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1); } 
                           
                         }
                    }
  free(a1);
  free(r1);
  free(c1);
   return NULL;
}

/*************************************** C12 Antenna syste Thread functions here ******/

void* C12_fps_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
    
     resp *r1;
     r1 = malloc(sizeof(resp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       c12fpsQ.store = 0; c12fpsQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c12fpsQ.store)>(int)(c12fpsQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c12_fpsq_retrieve((int)c12fpsQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                              //  if(!strcasecmp(c1->system_name,"sentinel"))
                              if(!strcasecmp(c1->system_name,"fps"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C12 FPS MCM device\n"); }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "C12 FPS MCM TIMEOUT\n");
                                         terminate_thread(server_fd);
                                        
                                      }
                                      else
                                     { 
                                         printcmd(c1);
                                         bzero(c1,sizeof(cmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(3);
                                  bzero(r1,sizeof(resp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING C00 FPS MCM RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                  else if(n==0)
                                  {
                                     fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                                     terminate_thread(server_fd);
                                  }    
                                 else
                                 {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from FPS THREAD SUCCESSFUL\n");
                                 } 
                                c12fpsQ.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                     else
                         { // Periodic Monitoring in the background 
                          // sleep(5); // Sleep put as per CPK request Date 2/12/2014
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C12");
                           strcpy(a1->CMD.system_name,"fps");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"null");
                          //  strcpy(a1->CMD.op_name,"read_version");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                         
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to c12 FPS MCM device\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C00 FPS MCM TIMEOUT #Perodic Monitoring\n");
                                terminate_thread(server_fd);
                             
                           }
                            else if(n==0)
                            {
                              fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(5);
                            bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING c12 FPS 1 SECONDS MONITORING MCM RESPONSE\n");
                                   terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"c12 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              // printresp(r1);
                              write_shm(a1,r1); bzero(r1,sizeof(resp));
                            } 
                          } 
                
                    }

  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}

void* C12_sentinel_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       c12senQ.store = 0; c12senQ.retrieve = 0;
              for(;;)
              {
                   if((int)(c12senQ.store)>(int)(c12senQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c12_senq_retrieve((int)c12senQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                              //  if(!strcasecmp(c1->system_name,"sentinel"))
                             if((!strcasecmp(c1->system_name,"sentinel"))||(!strcasecmp(c1->system_name,"fiber_optics")))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD c12 sentinel MCM device\n"); }
                                    else
                                   { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                        // bzero(c1,sizeof(cmd));   
                                         
                                    }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  usleep(500000);
                                 bzero(r1,sizeof(resp)); 
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING c12 sentinel MCM RESPONSE\n");  
                                     terminate_thread(server_fd); }
                               else if(n==0)
                                {
                                  fprintf(stderr,"c12 sentinel MCM closed it's Socket connection\n");
                                   terminate_thread(server_fd);
                                }     
                            else
                              {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from SENTINEL THREAD SUCCESSFUL\n");
                               } 
                             c12senQ.retrieve++; 
                                             
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                       else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C12");
                           strcpy(a1->CMD.system_name,"sentinel");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to c12 sentinel MCM MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING c12 Sentinel MCM RESPONSE\n"); terminate_thread(server_fd);  }
                            else if(n==0)
                            {
                              fprintf(stderr,"c12 sentinel MCM closed it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           else
                           {
                           
                                write_shm(a1,r1); 
                           } 
                         
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* C12_fiber_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
      char *tstamp;
     tstamp = malloc(25);
    
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       c12fiberQ.store = 0; c12fiberQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c12fiberQ.store)>(int)(c12fiberQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD*) c12_fiberq_retrieve((int)c12fiberQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"fiber_optics"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to c12 FIBER OPTICS MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                       
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                    usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING c12 FIBER OPTICS MCM RESPONSE\n"); terminate_thread(server_fd); }
                                else if(n==0)
                                {
                                 fprintf(stderr,"c12 FIBER OPTICS MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              {
                                     printresp(r1);
                                     write_shm(a1,r1);                  
                                     fprintf(stderr," Writing to ONLINE from FIBER THREAD SUCCESSFUL\n");
                               } 
                            
                             c12fiberQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                      else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C12");
                           strcpy(a1->CMD.system_name,"fiber_optics");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to c12 FIBER OPTICS MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING c12  FIBER OPTICS MCM RESPONSE\n");shutdown(server_fd,SHUT_RDWR);
                                     close(server_fd);
                                     pthread_exit(NULL);  }
                             else if(n==0)
                            {
                              fprintf(stderr,"c12 FIBER OPTICS MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           {
                             
                                write_shm(a1,r1);  
                            
                           } 
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* C12_front_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
 
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
      char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       c12frontQ.store = 0; c12frontQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c12frontQ.store)>(int)(c12frontQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = ( ANT_CMD*) c12_frontq_retrieve((int)c12frontQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"front_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to c12 FRONT END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING c12 FRONT END MCM RESPONSE\n"); 
                                    terminate_thread(server_fd);}
                               else if(n==0)
                              {
                                fprintf(stderr,"c12 FRONT END MCM closed it's Socket connection\n");
                                 terminate_thread(server_fd);
                              }
                              else
                              { printresp(r1); write_shm(a1,r1);  }
                           
                             c12frontQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       
                       }
                     else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"c12");
                           strcpy(a1->CMD.system_name,"front_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                           strcpy(a1->CMD.timestamp,tstamp);
                           c1 = &a1->CMD;
                              
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to c12 FRONT END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING c12 FRONT END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"c12 FRONT END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1);  }
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* C12_backend_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
        char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       c12backQ.store = 0; c12backQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c12backQ.store)>(int)(c12backQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c12_backq_retrieve((int)c12backQ.retrieve);
                        pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"back_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to c12 BACK END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING c12 BACK END MCM RESPONSE\n");
                                    terminate_thread(server_fd);}
                                else if(n==0)
                               {
                                 fprintf(stderr,"c12 BACK END MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              { printresp(r1);write_shm(a1,r1); } 
                           
                             c12backQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                      else
                         { // Periodic Monitoring in the background
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C12");
                           strcpy(a1->CMD.system_name,"back_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to c12 BACK END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING c12 Back END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"c12 BACK END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           { write_shm(a1,r1); }
                       
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* C12_self_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1= malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       c12selfQ.store = 0; c12selfQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c12selfQ.store)>(int)(c12selfQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c12_selfq_retrieve((int)c12selfQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"self_test"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                                     
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING c12  SELF SYSTEM  MCM RESPONSE\n"); 
                                     terminate_thread(server_fd); }
                              else if(n==0)
                            {
                              fprintf(stderr,"c12  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd); 
                            }
                              else
                              { write_shm(a1,r1); } 
                           
                             c12selfQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                     else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C12");
                           strcpy(a1->CMD.system_name,"self_test");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to c12  SELF SYSTEM  MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                            { fprintf(stderr," ERROR READING c12 Self Test MCM RESPONSE\n"); terminate_thread(server_fd);}
                             else if(n==0)
                            {
                              fprintf(stderr,"c12  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1); } 
                           
                         }
                    }
  free(a1);
  free(r1);
  free(c1);
   return NULL;
}

/*************************************** C13 Antenna syste Thread functions here ******/

void* C13_fps_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
    
     resp *r1;
     r1 = malloc(sizeof(resp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       c13fpsQ.store = 0; c13fpsQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c13fpsQ.store)>(int)(c13fpsQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c13_fpsq_retrieve((int)c13fpsQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                              //  if(!strcasecmp(c1->system_name,"sentinel"))
                              if(!strcasecmp(c1->system_name,"fps"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C13 FPS MCM device\n"); }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "C13 FPS MCM TIMEOUT\n");
                                         terminate_thread(server_fd);
                                        
                                      }
                                      else
                                     { 
                                         printcmd(c1);
                                         bzero(c1,sizeof(cmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(3);
                                  bzero(r1,sizeof(resp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING C00 FPS MCM RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                  else if(n==0)
                                  {
                                     fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                                     terminate_thread(server_fd);
                                  }    
                                 else
                                 {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from FPS THREAD SUCCESSFUL\n");
                                 } 
                                c13fpsQ.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                     else
                         { // Periodic Monitoring in the background 
                          // sleep(5); // Sleep put as per CPK request Date 2/12/2014
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C13");
                           strcpy(a1->CMD.system_name,"fps");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"null");
                          //  strcpy(a1->CMD.op_name,"read_version");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                         
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C13 FPS MCM device\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C00 FPS MCM TIMEOUT #Perodic Monitoring\n");
                                terminate_thread(server_fd);
                             
                           }
                            else if(n==0)
                            {
                              fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(5);
                            bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C13 FPS 1 SECONDS MONITORING MCM RESPONSE\n");
                                   terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"C13 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              // printresp(r1);
                              write_shm(a1,r1); bzero(r1,sizeof(resp));
                            } 
                          } 
                
                    }

  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}

void* C13_sentinel_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       c13senQ.store = 0; c13senQ.retrieve = 0;
              for(;;)
              {
                   if((int)(c13senQ.store)>(int)(c13senQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c13_senq_retrieve((int)c13senQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                               // if(!strcasecmp(c1->system_name,"sentinel"))
                               if((!strcasecmp(c1->system_name,"sentinel"))||(!strcasecmp(c1->system_name,"fiber_optics")))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD C13 sentinel MCM device\n"); }
                                    else
                                   { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                        // bzero(c1,sizeof(cmd));   
                                         
                                    }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  usleep(500000);
                                 bzero(r1,sizeof(resp)); 
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING C13 sentinel MCM RESPONSE\n");  
                                     terminate_thread(server_fd); }
                               else if(n==0)
                                {
                                  fprintf(stderr,"C13 sentinel MCM closed it's Socket connection\n");
                                   terminate_thread(server_fd);
                                }     
                            else
                              {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from SENTINEL THREAD SUCCESSFUL\n");
                               } 
                             c13senQ.retrieve++; 
                                             
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                       else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C13");
                           strcpy(a1->CMD.system_name,"sentinel");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C13 sentinel MCM MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C13 Sentinel MCM RESPONSE\n"); terminate_thread(server_fd);  }
                            else if(n==0)
                            {
                              fprintf(stderr,"C13 sentinel MCM closed it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           else
                           {
                           
                                write_shm(a1,r1); 
                           } 
                         
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* C13_fiber_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
      char *tstamp;
     tstamp = malloc(25);
    
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       c13fiberQ.store = 0; c13fiberQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c13fiberQ.store)>(int)(c13fiberQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD*) c13_fiberq_retrieve((int)c13fiberQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"fiber_optics"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C13 FIBER OPTICS MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                       
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                    usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C13 FIBER OPTICS MCM RESPONSE\n"); terminate_thread(server_fd); }
                                else if(n==0)
                                {
                                 fprintf(stderr,"C13 FIBER OPTICS MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              {
                                     printresp(r1);
                                     write_shm(a1,r1);                  
                                     fprintf(stderr," Writing to ONLINE from FIBER THREAD SUCCESSFUL\n");
                               } 
                            
                             c13fiberQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                      else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C13");
                           strcpy(a1->CMD.system_name,"fiber_optics");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C13 FIBER OPTICS MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C13  FIBER OPTICS MCM RESPONSE\n");shutdown(server_fd,SHUT_RDWR);
                                     close(server_fd);
                                     pthread_exit(NULL);  }
                             else if(n==0)
                            {
                              fprintf(stderr,"C13 FIBER OPTICS MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           {
                             
                                write_shm(a1,r1);  
                            
                           } 
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* C13_front_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
 
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
      char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       c13frontQ.store = 0; c13frontQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c13frontQ.store)>(int)(c13frontQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = ( ANT_CMD*) c13_frontq_retrieve((int)c13frontQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"front_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C13 FRONT END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C13 FRONT END MCM RESPONSE\n"); 
                                    terminate_thread(server_fd);}
                               else if(n==0)
                              {
                                fprintf(stderr,"C13 FRONT END MCM closed it's Socket connection\n");
                                 terminate_thread(server_fd);
                              }
                              else
                              { printresp(r1); write_shm(a1,r1);  }
                           
                             c13frontQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       
                       }
                     else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C13");
                           strcpy(a1->CMD.system_name,"front_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                           strcpy(a1->CMD.timestamp,tstamp);
                           c1 = &a1->CMD;
                              
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C13 FRONT END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C13 FRONT END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"C13 FRONT END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1);  }
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* C13_backend_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
        char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       c13backQ.store = 0; c13backQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c13backQ.store)>(int)(c13backQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c13_backq_retrieve((int)c13backQ.retrieve);
                        pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"back_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to C13 BACK END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C13 BACK END MCM RESPONSE\n");
                                    terminate_thread(server_fd);}
                                else if(n==0)
                               {
                                 fprintf(stderr,"C13 BACK END MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              { printresp(r1);write_shm(a1,r1); } 
                           
                             c13backQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                      else
                         { // Periodic Monitoring in the background
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C13");
                           strcpy(a1->CMD.system_name,"back_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C13 BACK END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C13 Back END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"C13 BACK END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           { write_shm(a1,r1); }
                       
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* C13_self_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1= malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       c13selfQ.store = 0; c13selfQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c13selfQ.store)>(int)(c13selfQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c13_selfq_retrieve((int)c13selfQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"self_test"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                                     
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C13  SELF SYSTEM  MCM RESPONSE\n"); 
                                     terminate_thread(server_fd); }
                              else if(n==0)
                            {
                              fprintf(stderr,"C13  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd); 
                            }
                              else
                              { write_shm(a1,r1); } 
                           
                             c13selfQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                     else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C13");
                           strcpy(a1->CMD.system_name,"self_test");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C13  SELF SYSTEM  MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                            { fprintf(stderr," ERROR READING C13 Self Test MCM RESPONSE\n"); terminate_thread(server_fd);}
                             else if(n==0)
                            {
                              fprintf(stderr,"C13  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1); } 
                           
                         }
                    }
  free(a1);
  free(r1);
  free(c1);
   return NULL;
}

/*************************************** C14 Antenna syste Thread functions here ******/

void* C14_fps_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
    
     resp *r1;
     r1 = malloc(sizeof(resp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       c14fpsQ.store = 0; c14fpsQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c14fpsQ.store)>(int)(c14fpsQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c14_fpsq_retrieve((int)c14fpsQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                              //  if(!strcasecmp(c1->system_name,"sentinel"))
                              if(!strcasecmp(c1->system_name,"fps"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C14 FPS MCM device\n"); }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "C14 FPS MCM TIMEOUT\n");
                                         terminate_thread(server_fd);
                                        
                                      }
                                      else
                                     { 
                                         printcmd(c1);
                                         bzero(c1,sizeof(cmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(3);
                                  bzero(r1,sizeof(resp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING C00 FPS MCM RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                  else if(n==0)
                                  {
                                     fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                                     terminate_thread(server_fd);
                                  }    
                                 else
                                 {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from FPS THREAD SUCCESSFUL\n");
                                 } 
                                c14fpsQ.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                     else
                         { // Periodic Monitoring in the background 
                          // sleep(5); // Sleep put as per CPK request Date 2/12/2014
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C14");
                           strcpy(a1->CMD.system_name,"fps");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"null");
                          //  strcpy(a1->CMD.op_name,"read_version");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                         
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C14 FPS MCM device\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C00 FPS MCM TIMEOUT #Perodic Monitoring\n");
                                terminate_thread(server_fd);
                             
                           }
                            else if(n==0)
                            {
                              fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(5);
                            bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C14 FPS 1 SECONDS MONITORING MCM RESPONSE\n");
                                   terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"C14 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              // printresp(r1);
                              write_shm(a1,r1); bzero(r1,sizeof(resp));
                            } 
                          } 
                
                    }

  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}

void* C14_sentinel_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       c14senQ.store = 0; c14senQ.retrieve = 0;
              for(;;)
              {
                   if((int)(c14senQ.store)>(int)(c14senQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c14_senq_retrieve((int)c14senQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                              //  if(!strcasecmp(c1->system_name,"sentinel"))
                             if((!strcasecmp(c1->system_name,"sentinel"))||(!strcasecmp(c1->system_name,"fiber_optics")))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD C14 sentinel MCM device\n"); }
                                    else
                                   { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                        // bzero(c1,sizeof(cmd));   
                                         
                                    }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  usleep(500000);
                                 bzero(r1,sizeof(resp)); 
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING C14 sentinel MCM RESPONSE\n");  
                                     terminate_thread(server_fd); }
                               else if(n==0)
                                {
                                  fprintf(stderr,"C14 sentinel MCM closed it's Socket connection\n");
                                   terminate_thread(server_fd);
                                }     
                            else
                              {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from SENTINEL THREAD SUCCESSFUL\n");
                               } 
                             c14senQ.retrieve++; 
                                             
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                       else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C14");
                           strcpy(a1->CMD.system_name,"sentinel");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C14 sentinel MCM MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C14 Sentinel MCM RESPONSE\n"); terminate_thread(server_fd);  }
                            else if(n==0)
                            {
                              fprintf(stderr,"C14 sentinel MCM closed it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           else
                           {
                           
                                write_shm(a1,r1); 
                           } 
                         
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* C14_fiber_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
      char *tstamp;
     tstamp = malloc(25);
    
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       c14fiberQ.store = 0; c14fiberQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c14fiberQ.store)>(int)(c14fiberQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD*) c14_fiberq_retrieve((int)c14fiberQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"fiber_optics"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C14 FIBER OPTICS MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                       
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                    usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C14 FIBER OPTICS MCM RESPONSE\n"); terminate_thread(server_fd); }
                                else if(n==0)
                                {
                                 fprintf(stderr,"C14 FIBER OPTICS MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              {
                                     printresp(r1);
                                     write_shm(a1,r1);                  
                                     fprintf(stderr," Writing to ONLINE from FIBER THREAD SUCCESSFUL\n");
                               } 
                            
                             c14fiberQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                      else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C14");
                           strcpy(a1->CMD.system_name,"fiber_optics");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C14 FIBER OPTICS MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C14  FIBER OPTICS MCM RESPONSE\n");shutdown(server_fd,SHUT_RDWR);
                                     close(server_fd);
                                     pthread_exit(NULL);  }
                             else if(n==0)
                            {
                              fprintf(stderr,"C14 FIBER OPTICS MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           {
                             
                                write_shm(a1,r1);  
                            
                           } 
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* C14_front_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
 
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
      char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       c14frontQ.store = 0; c14frontQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c14frontQ.store)>(int)(c14frontQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = ( ANT_CMD*) c14_frontq_retrieve((int)c14frontQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"front_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C14 FRONT END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C14 FRONT END MCM RESPONSE\n"); 
                                    terminate_thread(server_fd);}
                               else if(n==0)
                              {
                                fprintf(stderr,"C14 FRONT END MCM closed it's Socket connection\n");
                                 terminate_thread(server_fd);
                              }
                              else
                              { printresp(r1); write_shm(a1,r1);  }
                           
                             c14frontQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       
                       }
                     else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C14");
                           strcpy(a1->CMD.system_name,"front_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                           strcpy(a1->CMD.timestamp,tstamp);
                           c1 = &a1->CMD;
                              
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C14 FRONT END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C14 FRONT END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"C14 FRONT END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1);  }
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* C14_backend_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
        char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       c14backQ.store = 0; c14backQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c14backQ.store)>(int)(c14backQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c14_backq_retrieve((int)c14backQ.retrieve);
                        pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"back_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to C14 BACK END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C14 BACK END MCM RESPONSE\n");
                                    terminate_thread(server_fd);}
                                else if(n==0)
                               {
                                 fprintf(stderr,"C14 BACK END MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              { printresp(r1);write_shm(a1,r1); } 
                           
                             c14backQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                      else
                         { // Periodic Monitoring in the background
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C14");
                           strcpy(a1->CMD.system_name,"back_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C14 BACK END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C14 Back END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"C14 BACK END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           { write_shm(a1,r1); }
                       
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* C14_self_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1= malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       c14selfQ.store = 0; c14selfQ.retrieve = 0;
              for(;;)
              {
                    if((int)(c14selfQ.store)>(int)(c14selfQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) c14_selfq_retrieve((int)c14selfQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"self_test"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                                     
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING C14  SELF SYSTEM  MCM RESPONSE\n"); 
                                     terminate_thread(server_fd); }
                              else if(n==0)
                            {
                              fprintf(stderr,"C14  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd); 
                            }
                              else
                              { write_shm(a1,r1); } 
                           
                             c14selfQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                     else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"C14");
                           strcpy(a1->CMD.system_name,"self_test");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to C14  SELF SYSTEM  MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                            { fprintf(stderr," ERROR READING C14 Self Test MCM RESPONSE\n"); terminate_thread(server_fd);}
                             else if(n==0)
                            {
                              fprintf(stderr,"C14  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1); } 
                           
                         }
                    }
  free(a1);
  free(r1);
  free(c1);
   return NULL;
}

/*************************************** E02 Antenna syste Thread functions here ******/

void* E02_fps_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
    
     resp *r1;
     r1 = malloc(sizeof(resp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       e2fpsQ.store = 0; e2fpsQ.retrieve = 0;
              for(;;)
              {
                    if((int)(e2fpsQ.store)>(int)(e2fpsQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) e2_fpsq_retrieve((int)e2fpsQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                              //  if(!strcasecmp(c1->system_name,"sentinel"))
                              if(!strcasecmp(c1->system_name,"fps"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to E02 FPS MCM device\n"); }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "E02 FPS MCM TIMEOUT\n");
                                         terminate_thread(server_fd);
                                        
                                      }
                                      else
                                     { 
                                         printcmd(c1);
                                         bzero(c1,sizeof(cmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(3);
                                  bzero(r1,sizeof(resp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING C00 FPS MCM RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                  else if(n==0)
                                  {
                                     fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                                     terminate_thread(server_fd);
                                  }    
                                 else
                                 {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from FPS THREAD SUCCESSFUL\n");
                                 } 
                                e2fpsQ.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                     else
                         { // Periodic Monitoring in the background 
                          // sleep(5); // Sleep put as per CPK request Date 2/12/2014
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"E02");
                           strcpy(a1->CMD.system_name,"fps");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"null");
                          //  strcpy(a1->CMD.op_name,"read_version");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                         
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to E02 FPS MCM device\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C00 FPS MCM TIMEOUT #Perodic Monitoring\n");
                                terminate_thread(server_fd);
                             
                           }
                            else if(n==0)
                            {
                              fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(5);
                            bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING E02 FPS 1 SECONDS MONITORING MCM RESPONSE\n");
                                   terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"E02 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              // printresp(r1);
                              write_shm(a1,r1); bzero(r1,sizeof(resp));
                            } 
                          } 
                
                    }

  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}

void* E02_sentinel_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       e2senQ.store = 0; e2senQ.retrieve = 0;
              for(;;)
              {
                   if((int)(e2senQ.store)>(int)(e2senQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) e2_senq_retrieve((int)e2senQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                               // if(!strcasecmp(c1->system_name,"sentinel"))
                               if((!strcasecmp(c1->system_name,"sentinel"))||(!strcasecmp(c1->system_name,"fiber_optics")))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD E02 sentinel MCM device\n"); }
                                    else
                                   { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                        // bzero(c1,sizeof(cmd));   
                                         
                                    }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  usleep(500000);
                                 bzero(r1,sizeof(resp)); 
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING E02 sentinel MCM RESPONSE\n");  
                                     terminate_thread(server_fd); }
                               else if(n==0)
                                {
                                  fprintf(stderr,"E02 sentinel MCM closed it's Socket connection\n");
                                   terminate_thread(server_fd);
                                }     
                            else
                              {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from SENTINEL THREAD SUCCESSFUL\n");
                               } 
                             e2senQ.retrieve++; 
                                             
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                       else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"E02");
                           strcpy(a1->CMD.system_name,"sentinel");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to E02 sentinel MCM MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING E02 Sentinel MCM RESPONSE\n"); terminate_thread(server_fd);  }
                            else if(n==0)
                            {
                              fprintf(stderr,"E02 sentinel MCM closed it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           else
                           {
                           
                                write_shm(a1,r1); 
                           } 
                         
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* E02_fiber_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
      char *tstamp;
     tstamp = malloc(25);
    
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       e2fiberQ.store = 0; e2fiberQ.retrieve = 0;
              for(;;)
              {
                    if((int)(e2fiberQ.store)>(int)(e2fiberQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD*) e2_fiberq_retrieve((int)e2fiberQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"fiber_optics"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to E02 FIBER OPTICS MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                       
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                    usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING E02 FIBER OPTICS MCM RESPONSE\n"); terminate_thread(server_fd); }
                                else if(n==0)
                                {
                                 fprintf(stderr,"E02 FIBER OPTICS MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              {
                                     printresp(r1);
                                     write_shm(a1,r1);                  
                                     fprintf(stderr," Writing to ONLINE from FIBER THREAD SUCCESSFUL\n");
                               } 
                            
                             e2fiberQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                      else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"E02");
                           strcpy(a1->CMD.system_name,"fiber_optics");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to E02 FIBER OPTICS MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING E02  FIBER OPTICS MCM RESPONSE\n");shutdown(server_fd,SHUT_RDWR);
                                     close(server_fd);
                                     pthread_exit(NULL);  }
                             else if(n==0)
                            {
                              fprintf(stderr,"E02 FIBER OPTICS MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           {
                             
                                write_shm(a1,r1);  
                            
                           } 
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* E02_front_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
 
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
      char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       e2frontQ.store = 0; e2frontQ.retrieve = 0;
              for(;;)
              {
                    if((int)(e2frontQ.store)>(int)(e2frontQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = ( ANT_CMD*) e2_frontq_retrieve((int)e2frontQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"front_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to E02 FRONT END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING E02 FRONT END MCM RESPONSE\n"); 
                                    terminate_thread(server_fd);}
                               else if(n==0)
                              {
                                fprintf(stderr,"E02 FRONT END MCM closed it's Socket connection\n");
                                 terminate_thread(server_fd);
                              }
                              else
                              { printresp(r1); write_shm(a1,r1);  }
                           
                             e2frontQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       
                       }
                     else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"E02");
                           strcpy(a1->CMD.system_name,"front_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                           strcpy(a1->CMD.timestamp,tstamp);
                           c1 = &a1->CMD;
                              
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to E02 FRONT END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING E02 FRONT END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"E02 FRONT END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1);  }
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* E02_backend_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
        char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       e2backQ.store = 0; e2backQ.retrieve = 0;
              for(;;)
              {
                    if((int)(e2backQ.store)>(int)(e2backQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) e2_backq_retrieve((int)e2backQ.retrieve);
                        pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"back_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to E02 BACK END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING E02 BACK END MCM RESPONSE\n");
                                    terminate_thread(server_fd);}
                                else if(n==0)
                               {
                                 fprintf(stderr,"E02 BACK END MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              { printresp(r1);write_shm(a1,r1); } 
                           
                             e2backQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                      else
                         { // Periodic Monitoring in the background
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"E02");
                           strcpy(a1->CMD.system_name,"back_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to E02 BACK END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING E02 Back END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"E02 BACK END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           { write_shm(a1,r1); }
                       
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* E02_self_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1= malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       e2selfQ.store = 0; e2selfQ.retrieve = 0;
              for(;;)
              {
                    if((int)(e2selfQ.store)>(int)(e2selfQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) e2_selfq_retrieve((int)e2selfQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"self_test"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                                     
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING E02  SELF SYSTEM  MCM RESPONSE\n"); 
                                     terminate_thread(server_fd); }
                              else if(n==0)
                            {
                              fprintf(stderr,"E02  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd); 
                            }
                              else
                              { write_shm(a1,r1); } 
                           
                             e2selfQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                     else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"E02");
                           strcpy(a1->CMD.system_name,"self_test");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to E02  SELF SYSTEM  MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                            { fprintf(stderr," ERROR READING E02 Self Test MCM RESPONSE\n"); terminate_thread(server_fd);}
                             else if(n==0)
                            {
                              fprintf(stderr,"E02  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1); } 
                           
                         }
                    }
  free(a1);
  free(r1);
  free(c1);
   return NULL;
}


/*************************************** E03 Antenna syste Thread functions here ******/

void* E03_fps_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
    
     resp *r1;
     r1 = malloc(sizeof(resp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       e3fpsQ.store = 0; e3fpsQ.retrieve = 0;
              for(;;)
              {
                    if((int)(e3fpsQ.store)>(int)(e3fpsQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) e3_fpsq_retrieve((int)e3fpsQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                              //  if(!strcasecmp(c1->system_name,"sentinel"))
                              if(!strcasecmp(c1->system_name,"fps"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to E03 FPS MCM device\n"); }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "E03 FPS MCM TIMEOUT\n");
                                         terminate_thread(server_fd);
                                        
                                      }
                                      else
                                     { 
                                         printcmd(c1);
                                         bzero(c1,sizeof(cmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(3);
                                  bzero(r1,sizeof(resp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING C00 FPS MCM RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                  else if(n==0)
                                  {
                                     fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                                     terminate_thread(server_fd);
                                  }    
                                 else
                                 {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from FPS THREAD SUCCESSFUL\n");
                                 } 
                                e3fpsQ.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                     else
                         { // Periodic Monitoring in the background 
                          // sleep(5); // Sleep put as per CPK request Date 2/12/2014
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"E03");
                           strcpy(a1->CMD.system_name,"fps");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"null");
                          //  strcpy(a1->CMD.op_name,"read_version");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                         
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to E03 FPS MCM device\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C00 FPS MCM TIMEOUT #Perodic Monitoring\n");
                                terminate_thread(server_fd);
                             
                           }
                            else if(n==0)
                            {
                              fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(5);
                            bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING E03 FPS 1 SECONDS MONITORING MCM RESPONSE\n");
                                   terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"E03 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              // printresp(r1);
                              write_shm(a1,r1); bzero(r1,sizeof(resp));
                            } 
                          } 
                
                    }

  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}

void* E03_sentinel_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       e3senQ.store = 0; e3senQ.retrieve = 0;
              for(;;)
              {
                   if((int)(e3senQ.store)>(int)(e3senQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) e3_senq_retrieve((int)e3senQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                              //  if(!strcasecmp(c1->system_name,"sentinel"))
                             if((!strcasecmp(c1->system_name,"sentinel"))||(!strcasecmp(c1->system_name,"fiber_optics")))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD E03 sentinel MCM device\n"); }
                                    else
                                   { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                        // bzero(c1,sizeof(cmd));   
                                         
                                    }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  usleep(500000);
                                 bzero(r1,sizeof(resp)); 
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING E03 sentinel MCM RESPONSE\n");  
                                     terminate_thread(server_fd); }
                               else if(n==0)
                                {
                                  fprintf(stderr,"E03 sentinel MCM closed it's Socket connection\n");
                                   terminate_thread(server_fd);
                                }     
                            else
                              {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from SENTINEL THREAD SUCCESSFUL\n");
                               } 
                             e3senQ.retrieve++; 
                                             
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                       else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"E03");
                           strcpy(a1->CMD.system_name,"sentinel");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to E03 sentinel MCM MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING E03 Sentinel MCM RESPONSE\n"); terminate_thread(server_fd);  }
                            else if(n==0)
                            {
                              fprintf(stderr,"E03 sentinel MCM closed it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           else
                           {
                           
                                write_shm(a1,r1); 
                           } 
                         
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* E03_fiber_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
      char *tstamp;
     tstamp = malloc(25);
    
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       e3fiberQ.store = 0; e3fiberQ.retrieve = 0;
              for(;;)
              {
                    if((int)(e3fiberQ.store)>(int)(e3fiberQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD*) e3_fiberq_retrieve((int)e3fiberQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"fiber_optics"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to E03 FIBER OPTICS MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                       
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                    usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING E03 FIBER OPTICS MCM RESPONSE\n"); terminate_thread(server_fd); }
                                else if(n==0)
                                {
                                 fprintf(stderr,"E03 FIBER OPTICS MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              {
                                     printresp(r1);
                                     write_shm(a1,r1);                  
                                     fprintf(stderr," Writing to ONLINE from FIBER THREAD SUCCESSFUL\n");
                               } 
                            
                             e3fiberQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                      else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"E03");
                           strcpy(a1->CMD.system_name,"fiber_optics");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to E03 FIBER OPTICS MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING E03  FIBER OPTICS MCM RESPONSE\n");shutdown(server_fd,SHUT_RDWR);
                                     close(server_fd);
                                     pthread_exit(NULL);  }
                             else if(n==0)
                            {
                              fprintf(stderr,"E03 FIBER OPTICS MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           {
                             
                                write_shm(a1,r1);  
                            
                           } 
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* E03_front_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
 
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
      char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       e3frontQ.store = 0; e3frontQ.retrieve = 0;
              for(;;)
              {
                    if((int)(e3frontQ.store)>(int)(e3frontQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = ( ANT_CMD*) e3_frontq_retrieve((int)e3frontQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"front_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to E03 FRONT END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING E03 FRONT END MCM RESPONSE\n"); 
                                    terminate_thread(server_fd);}
                               else if(n==0)
                              {
                                fprintf(stderr,"E03 FRONT END MCM closed it's Socket connection\n");
                                 terminate_thread(server_fd);
                              }
                              else
                              { printresp(r1); write_shm(a1,r1);  }
                           
                             e3frontQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       
                       }
                     else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"E03");
                           strcpy(a1->CMD.system_name,"front_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                           strcpy(a1->CMD.timestamp,tstamp);
                           c1 = &a1->CMD;
                              
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to E03 FRONT END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING E03 FRONT END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"E03 FRONT END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1);  }
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* E03_backend_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
        char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       e3backQ.store = 0; e3backQ.retrieve = 0;
              for(;;)
              {
                    if((int)(e3backQ.store)>(int)(e3backQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) e3_backq_retrieve((int)e3backQ.retrieve);
                        pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"back_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to E03 BACK END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING E03 BACK END MCM RESPONSE\n");
                                    terminate_thread(server_fd);}
                                else if(n==0)
                               {
                                 fprintf(stderr,"E03 BACK END MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              { printresp(r1);write_shm(a1,r1); } 
                           
                             e3backQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                      else
                         { // Periodic Monitoring in the background
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"E03");
                           strcpy(a1->CMD.system_name,"back_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to E03 BACK END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING E03 Back END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"E03 BACK END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           { write_shm(a1,r1); }
                       
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* E03_self_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1= malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       e3selfQ.store = 0; e3selfQ.retrieve = 0;
              for(;;)
              {
                    if((int)(e3selfQ.store)>(int)(e3selfQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) e3_selfq_retrieve((int)e3selfQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"self_test"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                                     
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING E03  SELF SYSTEM  MCM RESPONSE\n"); 
                                     terminate_thread(server_fd); }
                              else if(n==0)
                            {
                              fprintf(stderr,"E03  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd); 
                            }
                              else
                              { write_shm(a1,r1); } 
                           
                             e3selfQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                     else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"E03");
                           strcpy(a1->CMD.system_name,"self_test");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to E03  SELF SYSTEM  MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                            { fprintf(stderr," ERROR READING E03 Self Test MCM RESPONSE\n"); terminate_thread(server_fd);}
                             else if(n==0)
                            {
                              fprintf(stderr,"E03  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1); } 
                           
                         }
                    }
  free(a1);
  free(r1);
  free(c1);
   return NULL;
}

/*************************************** E04 Antenna syste Thread functions here ******/

void* E04_fps_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
    
     resp *r1;
     r1 = malloc(sizeof(resp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       e4fpsQ.store = 0; e4fpsQ.retrieve = 0;
              for(;;)
              {
                    if((int)(e4fpsQ.store)>(int)(e4fpsQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) e4_fpsq_retrieve((int)e4fpsQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                              //  if(!strcasecmp(c1->system_name,"sentinel"))
                              if(!strcasecmp(c1->system_name,"fps"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to E04 FPS MCM device\n"); }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "E04 FPS MCM TIMEOUT\n");
                                         terminate_thread(server_fd);
                                        
                                      }
                                      else
                                     { 
                                         printcmd(c1);
                                         bzero(c1,sizeof(cmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(3);
                                  bzero(r1,sizeof(resp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING C00 FPS MCM RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                  else if(n==0)
                                  {
                                     fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                                     terminate_thread(server_fd);
                                  }    
                                 else
                                 {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from FPS THREAD SUCCESSFUL\n");
                                 } 
                                e4fpsQ.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                     else
                         { // Periodic Monitoring in the background 
                          // sleep(5); // Sleep put as per CPK request Date 2/12/2014
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"E04");
                           strcpy(a1->CMD.system_name,"fps");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"null");
                          //  strcpy(a1->CMD.op_name,"read_version");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                         
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to E04 FPS MCM device\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C00 FPS MCM TIMEOUT #Perodic Monitoring\n");
                                terminate_thread(server_fd);
                             
                           }
                            else if(n==0)
                            {
                              fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(5);
                            bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING E04 FPS 1 SECONDS MONITORING MCM RESPONSE\n");
                                   terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"E04 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              // printresp(r1);
                              write_shm(a1,r1); bzero(r1,sizeof(resp));
                            } 
                          } 
                
                    }

  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}

void* E04_sentinel_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       e4senQ.store = 0; e4senQ.retrieve = 0;
              for(;;)
              {
                   if((int)(e4senQ.store)>(int)(e4senQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) e4_senq_retrieve((int)e4senQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                              //  if(!strcasecmp(c1->system_name,"sentinel"))
                             if((!strcasecmp(c1->system_name,"sentinel"))||(!strcasecmp(c1->system_name,"fiber_optics")))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD E04 sentinel MCM device\n"); }
                                    else
                                   { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                        // bzero(c1,sizeof(cmd));   
                                         
                                    }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  usleep(500000);
                                 bzero(r1,sizeof(resp)); 
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING E04 sentinel MCM RESPONSE\n");  
                                     terminate_thread(server_fd); }
                               else if(n==0)
                                {
                                  fprintf(stderr,"E04 sentinel MCM closed it's Socket connection\n");
                                   terminate_thread(server_fd);
                                }     
                            else
                              {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from SENTINEL THREAD SUCCESSFUL\n");
                               } 
                             e4senQ.retrieve++; 
                                             
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                       else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"E04");
                           strcpy(a1->CMD.system_name,"sentinel");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to E04 sentinel MCM MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING E04 Sentinel MCM RESPONSE\n"); terminate_thread(server_fd);  }
                            else if(n==0)
                            {
                              fprintf(stderr,"E04 sentinel MCM closed it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           else
                           {
                           
                                write_shm(a1,r1); 
                           } 
                         
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* E04_fiber_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
      char *tstamp;
     tstamp = malloc(25);
    
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       e4fiberQ.store = 0; e4fiberQ.retrieve = 0;
              for(;;)
              {
                    if((int)(e4fiberQ.store)>(int)(e4fiberQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD*) e4_fiberq_retrieve((int)e4fiberQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"fiber_optics"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to E04 FIBER OPTICS MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                       
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                    usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING E04 FIBER OPTICS MCM RESPONSE\n"); terminate_thread(server_fd); }
                                else if(n==0)
                                {
                                 fprintf(stderr,"E04 FIBER OPTICS MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              {
                                     printresp(r1);
                                     write_shm(a1,r1);                  
                                     fprintf(stderr," Writing to ONLINE from FIBER THREAD SUCCESSFUL\n");
                               } 
                            
                             e4fiberQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                      else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"E04");
                           strcpy(a1->CMD.system_name,"fiber_optics");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to E04 FIBER OPTICS MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING E04  FIBER OPTICS MCM RESPONSE\n");shutdown(server_fd,SHUT_RDWR);
                                     close(server_fd);
                                     pthread_exit(NULL);  }
                             else if(n==0)
                            {
                              fprintf(stderr,"E04 FIBER OPTICS MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           {
                             
                                write_shm(a1,r1);  
                            
                           } 
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* E04_front_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
 
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
      char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       e4frontQ.store = 0; e4frontQ.retrieve = 0;
              for(;;)
              {
                    if((int)(e4frontQ.store)>(int)(e4frontQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = ( ANT_CMD*) e4_frontq_retrieve((int)e4frontQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"front_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to E04 FRONT END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING E04 FRONT END MCM RESPONSE\n"); 
                                    terminate_thread(server_fd);}
                               else if(n==0)
                              {
                                fprintf(stderr,"E04 FRONT END MCM closed it's Socket connection\n");
                                 terminate_thread(server_fd);
                              }
                              else
                              { printresp(r1); write_shm(a1,r1);  }
                           
                             e4frontQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       
                       }
                     else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"E04");
                           strcpy(a1->CMD.system_name,"front_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                           strcpy(a1->CMD.timestamp,tstamp);
                           c1 = &a1->CMD;
                              
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to E04 FRONT END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING E04 FRONT END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"E04 FRONT END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1);  }
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* E04_backend_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
        char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       e4backQ.store = 0; e4backQ.retrieve = 0;
              for(;;)
              {
                    if((int)(e4backQ.store)>(int)(e4backQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) e4_backq_retrieve((int)e4backQ.retrieve);
                        pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"back_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to E04 BACK END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING E04 BACK END MCM RESPONSE\n");
                                    terminate_thread(server_fd);}
                                else if(n==0)
                               {
                                 fprintf(stderr,"E04 BACK END MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              { printresp(r1);write_shm(a1,r1); } 
                           
                             e4backQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                      else
                         { // Periodic Monitoring in the background
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"E04");
                           strcpy(a1->CMD.system_name,"back_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to E04 BACK END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING E04 Back END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"E04 BACK END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           { write_shm(a1,r1); }
                       
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* E04_self_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1= malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       e4selfQ.store = 0; e4selfQ.retrieve = 0;
              for(;;)
              {
                    if((int)(e4selfQ.store)>(int)(e4selfQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) e4_selfq_retrieve((int)e4selfQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"self_test"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                                     
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING E04  SELF SYSTEM  MCM RESPONSE\n"); 
                                     terminate_thread(server_fd); }
                              else if(n==0)
                            {
                              fprintf(stderr,"E04  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd); 
                            }
                              else
                              { write_shm(a1,r1); } 
                           
                             e4selfQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                     else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"E04");
                           strcpy(a1->CMD.system_name,"self_test");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to E04  SELF SYSTEM  MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                            { fprintf(stderr," ERROR READING E04 Self Test MCM RESPONSE\n"); terminate_thread(server_fd);}
                             else if(n==0)
                            {
                              fprintf(stderr,"E04  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1); } 
                           
                         }
                    }
  free(a1);
  free(r1);
  free(c1);
   return NULL;
}

/*************************************** E05 Antenna syste Thread functions here ******/

void* E05_fps_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
    
     resp *r1;
     r1 = malloc(sizeof(resp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       e5fpsQ.store = 0; e5fpsQ.retrieve = 0;
              for(;;)
              {
                    if((int)(e5fpsQ.store)>(int)(e5fpsQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) e5_fpsq_retrieve((int)e5fpsQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                              //  if(!strcasecmp(c1->system_name,"sentinel"))
                              if(!strcasecmp(c1->system_name,"fps"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to E05 FPS MCM device\n"); }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "E05 FPS MCM TIMEOUT\n");
                                         terminate_thread(server_fd);
                                        
                                      }
                                      else
                                     { 
                                         printcmd(c1);
                                         bzero(c1,sizeof(cmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(3);
                                  bzero(r1,sizeof(resp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING C00 FPS MCM RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                  else if(n==0)
                                  {
                                     fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                                     terminate_thread(server_fd);
                                  }    
                                 else
                                 {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from FPS THREAD SUCCESSFUL\n");
                                 } 
                                e5fpsQ.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                     else
                         { // Periodic Monitoring in the background 
                          // sleep(5); // Sleep put as per CPK request Date 2/12/2014
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"E05");
                           strcpy(a1->CMD.system_name,"fps");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"null");
                          //  strcpy(a1->CMD.op_name,"read_version");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                         
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to E05 FPS MCM device\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C00 FPS MCM TIMEOUT #Perodic Monitoring\n");
                                terminate_thread(server_fd);
                             
                           }
                            else if(n==0)
                            {
                              fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(5);
                            bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING E05 FPS 1 SECONDS MONITORING MCM RESPONSE\n");
                                   terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"E05 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              // printresp(r1);
                              write_shm(a1,r1); bzero(r1,sizeof(resp));
                            } 
                          } 
                
                    }

  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}

void* E05_sentinel_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       e5senQ.store = 0; e5senQ.retrieve = 0;
              for(;;)
              {
                   if((int)(e5senQ.store)>(int)(e5senQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) e5_senq_retrieve((int)e5senQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                              //  if(!strcasecmp(c1->system_name,"sentinel"))
                              if((!strcasecmp(c1->system_name,"sentinel"))||(!strcasecmp(c1->system_name,"fiber_optics")))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD E05 sentinel MCM device\n"); }
                                    else
                                   { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                        // bzero(c1,sizeof(cmd));   
                                         
                                    }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  usleep(500000);
                                 bzero(r1,sizeof(resp)); 
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING E05 sentinel MCM RESPONSE\n");  
                                     terminate_thread(server_fd); }
                               else if(n==0)
                                {
                                  fprintf(stderr,"E05 sentinel MCM closed it's Socket connection\n");
                                   terminate_thread(server_fd);
                                }     
                            else
                              {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from SENTINEL THREAD SUCCESSFUL\n");
                               } 
                             e5senQ.retrieve++; 
                                             
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                       else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"E05");
                           strcpy(a1->CMD.system_name,"sentinel");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to E05 sentinel MCM MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING E05 Sentinel MCM RESPONSE\n"); terminate_thread(server_fd);  }
                            else if(n==0)
                            {
                              fprintf(stderr,"E05 sentinel MCM closed it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           else
                           {
                           
                                write_shm(a1,r1); 
                           } 
                         
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* E05_fiber_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
      char *tstamp;
     tstamp = malloc(25);
    
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       e5fiberQ.store = 0; e5fiberQ.retrieve = 0;
              for(;;)
              {
                    if((int)(e5fiberQ.store)>(int)(e5fiberQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD*) e5_fiberq_retrieve((int)e5fiberQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"fiber_optics"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to E05 FIBER OPTICS MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                       
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                    usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING E05 FIBER OPTICS MCM RESPONSE\n"); terminate_thread(server_fd); }
                                else if(n==0)
                                {
                                 fprintf(stderr,"E05 FIBER OPTICS MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              {
                                     printresp(r1);
                                     write_shm(a1,r1);                  
                                     fprintf(stderr," Writing to ONLINE from FIBER THREAD SUCCESSFUL\n");
                               } 
                            
                             e5fiberQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                      else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"E05");
                           strcpy(a1->CMD.system_name,"fiber_optics");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to E05 FIBER OPTICS MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING E05  FIBER OPTICS MCM RESPONSE\n");shutdown(server_fd,SHUT_RDWR);
                                     close(server_fd);
                                     pthread_exit(NULL);  }
                             else if(n==0)
                            {
                              fprintf(stderr,"E05 FIBER OPTICS MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           {
                             
                                write_shm(a1,r1);  
                            
                           } 
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* E05_front_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
 
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
      char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       e5frontQ.store = 0; e5frontQ.retrieve = 0;
              for(;;)
              {
                    if((int)(e5frontQ.store)>(int)(e5frontQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = ( ANT_CMD*) e5_frontq_retrieve((int)e5frontQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"front_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to E05 FRONT END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING E05 FRONT END MCM RESPONSE\n"); 
                                    terminate_thread(server_fd);}
                               else if(n==0)
                              {
                                fprintf(stderr,"E05 FRONT END MCM closed it's Socket connection\n");
                                 terminate_thread(server_fd);
                              }
                              else
                              { printresp(r1); write_shm(a1,r1);  }
                           
                             e5frontQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       
                       }
                     else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"E05");
                           strcpy(a1->CMD.system_name,"front_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                           strcpy(a1->CMD.timestamp,tstamp);
                           c1 = &a1->CMD;
                              
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to E05 FRONT END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING E05 FRONT END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"E05 FRONT END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1);  }
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* E05_backend_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
        char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       e5backQ.store = 0; e5backQ.retrieve = 0;
              for(;;)
              {
                    if((int)(e5backQ.store)>(int)(e5backQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) e5_backq_retrieve((int)e5backQ.retrieve);
                        pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"back_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to E05 BACK END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING E05 BACK END MCM RESPONSE\n");
                                    terminate_thread(server_fd);}
                                else if(n==0)
                               {
                                 fprintf(stderr,"E05 BACK END MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              { printresp(r1);write_shm(a1,r1); } 
                           
                             e5backQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                      else
                         { // Periodic Monitoring in the background
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"E05");
                           strcpy(a1->CMD.system_name,"back_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to E05 BACK END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING E05 Back END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"E05 BACK END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           { write_shm(a1,r1); }
                       
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* E05_self_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1= malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       e5selfQ.store = 0; e5selfQ.retrieve = 0;
              for(;;)
              {
                    if((int)(e5selfQ.store)>(int)(e5selfQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) e5_selfq_retrieve((int)e5selfQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"self_test"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                                     
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING E05  SELF SYSTEM  MCM RESPONSE\n"); 
                                     terminate_thread(server_fd); }
                              else if(n==0)
                            {
                              fprintf(stderr,"E05  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd); 
                            }
                              else
                              { write_shm(a1,r1); } 
                           
                             e5selfQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                     else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"E05");
                           strcpy(a1->CMD.system_name,"self_test");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to E05  SELF SYSTEM  MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                            { fprintf(stderr," ERROR READING E05 Self Test MCM RESPONSE\n"); terminate_thread(server_fd);}
                             else if(n==0)
                            {
                              fprintf(stderr,"E05  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1); } 
                           
                         }
                    }
  free(a1);
  free(r1);
  free(c1);
   return NULL;
}

/*************************************** E06 Antenna syste Thread functions here ******/

void* E06_fps_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
    
     resp *r1;
     r1 = malloc(sizeof(resp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       e6fpsQ.store = 0; e6fpsQ.retrieve = 0;
              for(;;)
              {
                    if((int)(e6fpsQ.store)>(int)(e6fpsQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) e6_fpsq_retrieve((int)e6fpsQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                              //  if(!strcasecmp(c1->system_name,"sentinel"))
                              if(!strcasecmp(c1->system_name,"fps"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to E06 FPS MCM device\n"); }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "E06 FPS MCM TIMEOUT\n");
                                         terminate_thread(server_fd);
                                        
                                      }
                                      else
                                     { 
                                         printcmd(c1);
                                         bzero(c1,sizeof(cmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(3);
                                  bzero(r1,sizeof(resp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING C00 FPS MCM RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                  else if(n==0)
                                  {
                                     fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                                     terminate_thread(server_fd);
                                  }    
                                 else
                                 {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from FPS THREAD SUCCESSFUL\n");
                                 } 
                                e6fpsQ.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                     else
                         { // Periodic Monitoring in the background 
                          // sleep(5); // Sleep put as per CPK request Date 2/12/2014
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"E06");
                           strcpy(a1->CMD.system_name,"fps");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"null");
                          //  strcpy(a1->CMD.op_name,"read_version");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                         
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to E06 FPS MCM device\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C00 FPS MCM TIMEOUT #Perodic Monitoring\n");
                                terminate_thread(server_fd);
                             
                           }
                            else if(n==0)
                            {
                              fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(5);
                            bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING E06 FPS 1 SECONDS MONITORING MCM RESPONSE\n");
                                   terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"E06 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              // printresp(r1);
                              write_shm(a1,r1); bzero(r1,sizeof(resp));
                            } 
                          } 
                
                    }

  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}

void* E06_sentinel_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       e6senQ.store = 0; e6senQ.retrieve = 0;
              for(;;)
              {
                   if((int)(e6senQ.store)>(int)(e6senQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) e6_senq_retrieve((int)e6senQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                               // if(!strcasecmp(c1->system_name,"sentinel"))
                              if((!strcasecmp(c1->system_name,"sentinel"))||(!strcasecmp(c1->system_name,"fiber_optics")))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD E06 sentinel MCM device\n"); }
                                    else
                                   { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                        // bzero(c1,sizeof(cmd));   
                                         
                                    }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  usleep(500000);
                                 bzero(r1,sizeof(resp)); 
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING E06 sentinel MCM RESPONSE\n");  
                                     terminate_thread(server_fd); }
                               else if(n==0)
                                {
                                  fprintf(stderr,"E06 sentinel MCM closed it's Socket connection\n");
                                   terminate_thread(server_fd);
                                }     
                            else
                              {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from SENTINEL THREAD SUCCESSFUL\n");
                               } 
                             e6senQ.retrieve++; 
                                             
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                       else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"E06");
                           strcpy(a1->CMD.system_name,"sentinel");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to E06 sentinel MCM MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING E06 Sentinel MCM RESPONSE\n"); terminate_thread(server_fd);  }
                            else if(n==0)
                            {
                              fprintf(stderr,"E06 sentinel MCM closed it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           else
                           {
                           
                                write_shm(a1,r1); 
                           } 
                         
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* E06_fiber_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
      char *tstamp;
     tstamp = malloc(25);
    
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       e6fiberQ.store = 0; e6fiberQ.retrieve = 0;
              for(;;)
              {
                    if((int)(e6fiberQ.store)>(int)(e6fiberQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD*) e6_fiberq_retrieve((int)e6fiberQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"fiber_optics"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to E06 FIBER OPTICS MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                       
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                    usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING E06 FIBER OPTICS MCM RESPONSE\n"); terminate_thread(server_fd); }
                                else if(n==0)
                                {
                                 fprintf(stderr,"E06 FIBER OPTICS MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              {
                                     printresp(r1);
                                     write_shm(a1,r1);                  
                                     fprintf(stderr," Writing to ONLINE from FIBER THREAD SUCCESSFUL\n");
                               } 
                            
                             e6fiberQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                      else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"E06");
                           strcpy(a1->CMD.system_name,"fiber_optics");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to E06 FIBER OPTICS MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING E06  FIBER OPTICS MCM RESPONSE\n");shutdown(server_fd,SHUT_RDWR);
                                     close(server_fd);
                                     pthread_exit(NULL);  }
                             else if(n==0)
                            {
                              fprintf(stderr,"E06 FIBER OPTICS MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           {
                             
                                write_shm(a1,r1);  
                            
                           } 
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* E06_front_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
 
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
      char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       e6frontQ.store = 0; e6frontQ.retrieve = 0;
              for(;;)
              {
                    if((int)(e6frontQ.store)>(int)(e6frontQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = ( ANT_CMD*) e6_frontq_retrieve((int)e6frontQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"front_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to E06 FRONT END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING E06 FRONT END MCM RESPONSE\n"); 
                                    terminate_thread(server_fd);}
                               else if(n==0)
                              {
                                fprintf(stderr,"E06 FRONT END MCM closed it's Socket connection\n");
                                 terminate_thread(server_fd);
                              }
                              else
                              { printresp(r1); write_shm(a1,r1);  }
                           
                             e6frontQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       
                       }
                     else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"E06");
                           strcpy(a1->CMD.system_name,"front_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                           strcpy(a1->CMD.timestamp,tstamp);
                           c1 = &a1->CMD;
                              
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to E06 FRONT END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING E06 FRONT END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"E06 FRONT END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1);  }
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* E06_backend_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
        char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       e6backQ.store = 0; e6backQ.retrieve = 0;
              for(;;)
              {
                    if((int)(e6backQ.store)>(int)(e6backQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) e6_backq_retrieve((int)e6backQ.retrieve);
                        pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"back_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to E06 BACK END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING E06 BACK END MCM RESPONSE\n");
                                    terminate_thread(server_fd);}
                                else if(n==0)
                               {
                                 fprintf(stderr,"E06 BACK END MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              { printresp(r1);write_shm(a1,r1); } 
                           
                             e6backQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                      else
                         { // Periodic Monitoring in the background
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"E06");
                           strcpy(a1->CMD.system_name,"back_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to E06 BACK END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING E06 Back END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"E06 BACK END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           { write_shm(a1,r1); }
                       
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* E06_self_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1= malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       e6selfQ.store = 0; e6selfQ.retrieve = 0;
              for(;;)
              {
                    if((int)(e6selfQ.store)>(int)(e6selfQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) e6_selfq_retrieve((int)e6selfQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"self_test"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                                     
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING E06  SELF SYSTEM  MCM RESPONSE\n"); 
                                     terminate_thread(server_fd); }
                              else if(n==0)
                            {
                              fprintf(stderr,"E06  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd); 
                            }
                              else
                              { write_shm(a1,r1); } 
                           
                             e6selfQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                     else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"E06");
                           strcpy(a1->CMD.system_name,"self_test");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to E06  SELF SYSTEM  MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                            { fprintf(stderr," ERROR READING E06 Self Test MCM RESPONSE\n"); terminate_thread(server_fd);}
                             else if(n==0)
                            {
                              fprintf(stderr,"E06  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1); } 
                           
                         }
                    }
  free(a1);
  free(r1);
  free(c1);
   return NULL;
}

/*************************************** S01 Antenna syste Thread functions here ******/

void* S01_fps_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
    
     resp *r1;
     r1 = malloc(sizeof(resp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       s1fpsQ.store = 0; s1fpsQ.retrieve = 0;
              for(;;)
              {
                    if((int)(s1fpsQ.store)>(int)(s1fpsQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) s1_fpsq_retrieve((int)s1fpsQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                              //  if(!strcasecmp(c1->system_name,"sentinel"))
                              if(!strcasecmp(c1->system_name,"fps"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to S01 FPS MCM device\n"); }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "S01 FPS MCM TIMEOUT\n");
                                         terminate_thread(server_fd);
                                        
                                      }
                                      else
                                     { 
                                         printcmd(c1);
                                         bzero(c1,sizeof(cmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(3);
                                  bzero(r1,sizeof(resp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING C00 FPS MCM RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                  else if(n==0)
                                  {
                                     fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                                     terminate_thread(server_fd);
                                  }    
                                 else
                                 {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from FPS THREAD SUCCESSFUL\n");
                                 } 
                                s1fpsQ.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                     else
                         { // Periodic Monitoring in the background 
                          // sleep(5); // Sleep put as per CPK request Date 2/12/2014
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"S01");
                           strcpy(a1->CMD.system_name,"fps");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"null");
                          //  strcpy(a1->CMD.op_name,"read_version");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                         
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to S01 FPS MCM device\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C00 FPS MCM TIMEOUT #Perodic Monitoring\n");
                                terminate_thread(server_fd);
                             
                           }
                            else if(n==0)
                            {
                              fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(5);
                            bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING S01 FPS 1 SECONDS MONITORING MCM RESPONSE\n");
                                   terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"S01 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              // printresp(r1);
                              write_shm(a1,r1); bzero(r1,sizeof(resp));
                            } 
                          } 
                
                    }

  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}

void* S01_sentinel_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       s1senQ.store = 0; s1senQ.retrieve = 0;
              for(;;)
              {
                   if((int)(s1senQ.store)>(int)(s1senQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) s1_senq_retrieve((int)s1senQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                               // if(!strcasecmp(c1->system_name,"sentinel"))
                             if((!strcasecmp(c1->system_name,"sentinel"))||(!strcasecmp(c1->system_name,"fiber_optics")))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD S01 sentinel MCM device\n"); }
                                    else
                                   { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                        // bzero(c1,sizeof(cmd));   
                                         
                                    }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  usleep(500000);
                                 bzero(r1,sizeof(resp)); 
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING S01 sentinel MCM RESPONSE\n");  
                                     terminate_thread(server_fd); }
                               else if(n==0)
                                {
                                  fprintf(stderr,"S01 sentinel MCM closed it's Socket connection\n");
                                   terminate_thread(server_fd);
                                }     
                            else
                              {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from SENTINEL THREAD SUCCESSFUL\n");
                               } 
                             s1senQ.retrieve++; 
                                             
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                       else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"S01");
                           strcpy(a1->CMD.system_name,"sentinel");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to S01 sentinel MCM MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING S01 Sentinel MCM RESPONSE\n"); terminate_thread(server_fd);  }
                            else if(n==0)
                            {
                              fprintf(stderr,"S01 sentinel MCM closed it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           else
                           {
                           
                                write_shm(a1,r1); 
                           } 
                         
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* S01_fiber_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
      char *tstamp;
     tstamp = malloc(25);
    
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       s1fiberQ.store = 0; s1fiberQ.retrieve = 0;
              for(;;)
              {
                    if((int)(s1fiberQ.store)>(int)(s1fiberQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD*) s1_fiberq_retrieve((int)s1fiberQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"fiber_optics"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to S01 FIBER OPTICS MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                       
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                    usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING S01 FIBER OPTICS MCM RESPONSE\n"); terminate_thread(server_fd); }
                                else if(n==0)
                                {
                                 fprintf(stderr,"S01 FIBER OPTICS MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              {
                                     printresp(r1);
                                     write_shm(a1,r1);                  
                                     fprintf(stderr," Writing to ONLINE from FIBER THREAD SUCCESSFUL\n");
                               } 
                            
                             s1fiberQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                      else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"S01");
                           strcpy(a1->CMD.system_name,"fiber_optics");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to S01 FIBER OPTICS MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING S01  FIBER OPTICS MCM RESPONSE\n");shutdown(server_fd,SHUT_RDWR);
                                     close(server_fd);
                                     pthread_exit(NULL);  }
                             else if(n==0)
                            {
                              fprintf(stderr,"S01 FIBER OPTICS MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           {
                             
                                write_shm(a1,r1);  
                            
                           } 
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* S01_front_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
 
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
      char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       s1frontQ.store = 0; s1frontQ.retrieve = 0;
              for(;;)
              {
                    if((int)(s1frontQ.store)>(int)(s1frontQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = ( ANT_CMD*) s1_frontq_retrieve((int)s1frontQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"front_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to S01 FRONT END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING S01 FRONT END MCM RESPONSE\n"); 
                                    terminate_thread(server_fd);}
                               else if(n==0)
                              {
                                fprintf(stderr,"S01 FRONT END MCM closed it's Socket connection\n");
                                 terminate_thread(server_fd);
                              }
                              else
                              { printresp(r1); write_shm(a1,r1);  }
                           
                             s1frontQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       
                       }
                     else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"S01");
                           strcpy(a1->CMD.system_name,"front_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                           strcpy(a1->CMD.timestamp,tstamp);
                           c1 = &a1->CMD;
                              
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to S01 FRONT END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING S01 FRONT END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"S01 FRONT END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1);  }
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* S01_backend_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
        char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       s1backQ.store = 0; s1backQ.retrieve = 0;
              for(;;)
              {
                    if((int)(s1backQ.store)>(int)(s1backQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) s1_backq_retrieve((int)s1backQ.retrieve);
                        pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"back_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to S01 BACK END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING S01 BACK END MCM RESPONSE\n");
                                    terminate_thread(server_fd);}
                                else if(n==0)
                               {
                                 fprintf(stderr,"S01 BACK END MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              { printresp(r1);write_shm(a1,r1); } 
                           
                             s1backQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                      else
                         { // Periodic Monitoring in the background
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"S01");
                           strcpy(a1->CMD.system_name,"back_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to S01 BACK END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING S01 Back END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"S01 BACK END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           { write_shm(a1,r1); }
                       
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* S01_self_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1= malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       s1selfQ.store = 0; s1selfQ.retrieve = 0;
              for(;;)
              {
                    if((int)(s1selfQ.store)>(int)(s1selfQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) s1_selfq_retrieve((int)s1selfQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"self_test"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                                     
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING S01  SELF SYSTEM  MCM RESPONSE\n"); 
                                     terminate_thread(server_fd); }
                              else if(n==0)
                            {
                              fprintf(stderr,"S01  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd); 
                            }
                              else
                              { write_shm(a1,r1); } 
                           
                             s1selfQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                     else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"S01");
                           strcpy(a1->CMD.system_name,"self_test");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to S01  SELF SYSTEM  MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                            { fprintf(stderr," ERROR READING S01 Self Test MCM RESPONSE\n"); terminate_thread(server_fd);}
                             else if(n==0)
                            {
                              fprintf(stderr,"S01  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1); } 
                           
                         }
                    }
  free(a1);
  free(r1);
  free(c1);
   return NULL;
}

/*************************************** S02 Antenna syste Thread functions here ******/

void* S02_fps_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
    
     resp *r1;
     r1 = malloc(sizeof(resp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       s2fpsQ.store = 0; s2fpsQ.retrieve = 0;
              for(;;)
              {
                    if((int)(s2fpsQ.store)>(int)(s2fpsQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) s2_fpsq_retrieve((int)s2fpsQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                              //  if(!strcasecmp(c1->system_name,"sentinel"))
                              if(!strcasecmp(c1->system_name,"fps"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to S02 FPS MCM device\n"); }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "S02 FPS MCM TIMEOUT\n");
                                         terminate_thread(server_fd);
                                        
                                      }
                                      else
                                     { 
                                         printcmd(c1);
                                         bzero(c1,sizeof(cmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(3);
                                  bzero(r1,sizeof(resp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING C00 FPS MCM RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                  else if(n==0)
                                  {
                                     fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                                     terminate_thread(server_fd);
                                  }    
                                 else
                                 {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from FPS THREAD SUCCESSFUL\n");
                                 } 
                                s2fpsQ.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                     else
                         { // Periodic Monitoring in the background 
                          // sleep(5); // Sleep put as per CPK request Date 2/12/2014
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"S02");
                           strcpy(a1->CMD.system_name,"fps");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"null");
                          //  strcpy(a1->CMD.op_name,"read_version");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                         
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to S02 FPS MCM device\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C00 FPS MCM TIMEOUT #Perodic Monitoring\n");
                                terminate_thread(server_fd);
                             
                           }
                            else if(n==0)
                            {
                              fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(5);
                            bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING S02 FPS 1 SECONDS MONITORING MCM RESPONSE\n");
                                   terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"S02 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              // printresp(r1);
                              write_shm(a1,r1); bzero(r1,sizeof(resp));
                            } 
                          } 
                
                    }

  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}

void* S02_sentinel_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       s2senQ.store = 0; s2senQ.retrieve = 0;
              for(;;)
              {
                   if((int)(s2senQ.store)>(int)(s2senQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) s2_senq_retrieve((int)s2senQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                             //   if(!strcasecmp(c1->system_name,"sentinel"))
                                 if((!strcasecmp(c1->system_name,"sentinel"))||(!strcasecmp(c1->system_name,"fiber_optics")))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD S02 sentinel MCM device\n"); }
                                    else
                                   { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                        // bzero(c1,sizeof(cmd));   
                                         
                                    }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  usleep(500000);
                                 bzero(r1,sizeof(resp)); 
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING S02 sentinel MCM RESPONSE\n");  
                                     terminate_thread(server_fd); }
                               else if(n==0)
                                {
                                  fprintf(stderr,"S02 sentinel MCM closed it's Socket connection\n");
                                   terminate_thread(server_fd);
                                }     
                            else
                              {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from SENTINEL THREAD SUCCESSFUL\n");
                               } 
                             s2senQ.retrieve++; 
                                             
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                       else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"S02");
                           strcpy(a1->CMD.system_name,"sentinel");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to S02 sentinel MCM MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING S02 Sentinel MCM RESPONSE\n"); terminate_thread(server_fd);  }
                            else if(n==0)
                            {
                              fprintf(stderr,"S02 sentinel MCM closed it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           else
                           {
                           
                                write_shm(a1,r1); 
                           } 
                         
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* S02_fiber_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
      char *tstamp;
     tstamp = malloc(25);
    
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       s2fiberQ.store = 0; s2fiberQ.retrieve = 0;
              for(;;)
              {
                    if((int)(s2fiberQ.store)>(int)(s2fiberQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD*) s2_fiberq_retrieve((int)s2fiberQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"fiber_optics"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to S02 FIBER OPTICS MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                       
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                    usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING S02 FIBER OPTICS MCM RESPONSE\n"); terminate_thread(server_fd); }
                                else if(n==0)
                                {
                                 fprintf(stderr,"S02 FIBER OPTICS MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              {
                                     printresp(r1);
                                     write_shm(a1,r1);                  
                                     fprintf(stderr," Writing to ONLINE from FIBER THREAD SUCCESSFUL\n");
                               } 
                            
                             s2fiberQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                      else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"S02");
                           strcpy(a1->CMD.system_name,"fiber_optics");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to S02 FIBER OPTICS MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING S02  FIBER OPTICS MCM RESPONSE\n");shutdown(server_fd,SHUT_RDWR);
                                     close(server_fd);
                                     pthread_exit(NULL);  }
                             else if(n==0)
                            {
                              fprintf(stderr,"S02 FIBER OPTICS MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           {
                             
                                write_shm(a1,r1);  
                            
                           } 
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* S02_front_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
 
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
      char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       s2frontQ.store = 0; s2frontQ.retrieve = 0;
              for(;;)
              {
                    if((int)(s2frontQ.store)>(int)(s3frontQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = ( ANT_CMD*) s2_frontq_retrieve((int)s2frontQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"front_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to S02 FRONT END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING S02 FRONT END MCM RESPONSE\n"); 
                                    terminate_thread(server_fd);}
                               else if(n==0)
                              {
                                fprintf(stderr,"S02 FRONT END MCM closed it's Socket connection\n");
                                 terminate_thread(server_fd);
                              }
                              else
                              { printresp(r1); write_shm(a1,r1);  }
                           
                             s2frontQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       
                       }
                     else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"S02");
                           strcpy(a1->CMD.system_name,"front_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                           strcpy(a1->CMD.timestamp,tstamp);
                           c1 = &a1->CMD;
                              
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to S02 FRONT END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING S02 FRONT END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"S02 FRONT END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1);  }
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* S02_backend_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
        char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       s2backQ.store = 0; s2backQ.retrieve = 0;
              for(;;)
              {
                    if((int)(s2backQ.store)>(int)(s2backQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) s2_backq_retrieve((int)s2backQ.retrieve);
                        pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"back_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to S02 BACK END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING S02 BACK END MCM RESPONSE\n");
                                    terminate_thread(server_fd);}
                                else if(n==0)
                               {
                                 fprintf(stderr,"S02 BACK END MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              { printresp(r1);write_shm(a1,r1); } 
                           
                             s2backQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                      else
                         { // Periodic Monitoring in the background
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"S02");
                           strcpy(a1->CMD.system_name,"back_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to S02 BACK END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING S02 Back END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"S02 BACK END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           { write_shm(a1,r1); }
                       
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* S02_self_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1= malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       s2selfQ.store = 0; s2selfQ.retrieve = 0;
              for(;;)
              {
                    if((int)(s2selfQ.store)>(int)(s2selfQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) s2_selfq_retrieve((int)s2selfQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"self_test"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                                     
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING S02  SELF SYSTEM  MCM RESPONSE\n"); 
                                     terminate_thread(server_fd); }
                              else if(n==0)
                            {
                              fprintf(stderr,"S02  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd); 
                            }
                              else
                              { write_shm(a1,r1); } 
                           
                             s2selfQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                     else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"S02");
                           strcpy(a1->CMD.system_name,"self_test");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to S02  SELF SYSTEM  MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                            { fprintf(stderr," ERROR READING S02 Self Test MCM RESPONSE\n"); terminate_thread(server_fd);}
                             else if(n==0)
                            {
                              fprintf(stderr,"S02  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1); } 
                           
                         }
                    }
  free(a1);
  free(r1);
  free(c1);
   return NULL;
}

/*************************************** S03 Antenna syste Thread functions here ******/

void* S03_fps_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
    
     resp *r1;
     r1 = malloc(sizeof(resp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       s3fpsQ.store = 0; s3fpsQ.retrieve = 0;
              for(;;)
              {
                    if((int)(s3fpsQ.store)>(int)(s3fpsQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) s3_fpsq_retrieve((int)s3fpsQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                              //  if(!strcasecmp(c1->system_name,"sentinel"))
                              if(!strcasecmp(c1->system_name,"fps"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to S03 FPS MCM device\n"); }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "S03 FPS MCM TIMEOUT\n");
                                         terminate_thread(server_fd);
                                        
                                      }
                                      else
                                     { 
                                         printcmd(c1);
                                         bzero(c1,sizeof(cmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(3);
                                  bzero(r1,sizeof(resp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING C00 FPS MCM RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                  else if(n==0)
                                  {
                                     fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                                     terminate_thread(server_fd);
                                  }    
                                 else
                                 {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from FPS THREAD SUCCESSFUL\n");
                                 } 
                                s3fpsQ.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                     else
                         { // Periodic Monitoring in the background 
                          // sleep(5); // Sleep put as per CPK request Date 2/12/2014
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"S03");
                           strcpy(a1->CMD.system_name,"fps");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"null");
                          //  strcpy(a1->CMD.op_name,"read_version");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                         
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to S03 FPS MCM device\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C00 FPS MCM TIMEOUT #Perodic Monitoring\n");
                                terminate_thread(server_fd);
                             
                           }
                            else if(n==0)
                            {
                              fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(5);
                            bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING S03 FPS 1 SECONDS MONITORING MCM RESPONSE\n");
                                   terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"S03 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              // printresp(r1);
                              write_shm(a1,r1); bzero(r1,sizeof(resp));
                            } 
                          } 
                
                    }

  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}

void* S03_sentinel_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       s3senQ.store = 0; s3senQ.retrieve = 0;
              for(;;)
              {
                   if((int)(s3senQ.store)>(int)(s3senQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) s3_senq_retrieve((int)s3senQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                               // if(!strcasecmp(c1->system_name,"sentinel"))
                               if((!strcasecmp(c1->system_name,"sentinel"))||(!strcasecmp(c1->system_name,"fiber_optics")))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD S03 sentinel MCM device\n"); }
                                    else
                                   { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                        // bzero(c1,sizeof(cmd));   
                                         
                                    }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  usleep(500000);
                                 bzero(r1,sizeof(resp)); 
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING S03 sentinel MCM RESPONSE\n");  
                                     terminate_thread(server_fd); }
                               else if(n==0)
                                {
                                  fprintf(stderr,"S03 sentinel MCM closed it's Socket connection\n");
                                   terminate_thread(server_fd);
                                }     
                            else
                              {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from SENTINEL THREAD SUCCESSFUL\n");
                               } 
                             s3senQ.retrieve++; 
                                             
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                       else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"S03");
                           strcpy(a1->CMD.system_name,"sentinel");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to S03 sentinel MCM MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING S03 Sentinel MCM RESPONSE\n"); terminate_thread(server_fd);  }
                            else if(n==0)
                            {
                              fprintf(stderr,"S03 sentinel MCM closed it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           else
                           {
                           
                                write_shm(a1,r1); 
                           } 
                         
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* S03_fiber_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
      char *tstamp;
     tstamp = malloc(25);
    
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       s3fiberQ.store = 0; s3fiberQ.retrieve = 0;
              for(;;)
              {
                    if((int)(s3fiberQ.store)>(int)(s3fiberQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD*) s3_fiberq_retrieve((int)s3fiberQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"fiber_optics"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to S03 FIBER OPTICS MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                       
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                    usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING S03 FIBER OPTICS MCM RESPONSE\n"); terminate_thread(server_fd); }
                                else if(n==0)
                                {
                                 fprintf(stderr,"S03 FIBER OPTICS MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              {
                                     printresp(r1);
                                     write_shm(a1,r1);                  
                                     fprintf(stderr," Writing to ONLINE from FIBER THREAD SUCCESSFUL\n");
                               } 
                            
                             s3fiberQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                      else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"S03");
                           strcpy(a1->CMD.system_name,"fiber_optics");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to S03 FIBER OPTICS MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING S03  FIBER OPTICS MCM RESPONSE\n");shutdown(server_fd,SHUT_RDWR);
                                     close(server_fd);
                                     pthread_exit(NULL);  }
                             else if(n==0)
                            {
                              fprintf(stderr,"S03 FIBER OPTICS MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           {
                             
                                write_shm(a1,r1);  
                            
                           } 
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* S03_front_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
 
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
      char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       s3frontQ.store = 0; s3frontQ.retrieve = 0;
              for(;;)
              {
                    if((int)(s3frontQ.store)>(int)(s3frontQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = ( ANT_CMD*) s3_frontq_retrieve((int)s3frontQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"front_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to S03 FRONT END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING S03 FRONT END MCM RESPONSE\n"); 
                                    terminate_thread(server_fd);}
                               else if(n==0)
                              {
                                fprintf(stderr,"S03 FRONT END MCM closed it's Socket connection\n");
                                 terminate_thread(server_fd);
                              }
                              else
                              { printresp(r1); write_shm(a1,r1);  }
                           
                             s3frontQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       
                       }
                     else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"S03");
                           strcpy(a1->CMD.system_name,"front_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                           strcpy(a1->CMD.timestamp,tstamp);
                           c1 = &a1->CMD;
                              
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to S03 FRONT END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING S03 FRONT END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"S03 FRONT END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1);  }
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* S03_backend_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
        char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       s3backQ.store = 0; s3backQ.retrieve = 0;
              for(;;)
              {
                    if((int)(s3backQ.store)>(int)(s3backQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) s3_backq_retrieve((int)s3backQ.retrieve);
                        pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"back_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to S03 BACK END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING S03 BACK END MCM RESPONSE\n");
                                    terminate_thread(server_fd);}
                                else if(n==0)
                               {
                                 fprintf(stderr,"S03 BACK END MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              { printresp(r1);write_shm(a1,r1); } 
                           
                             s3backQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                      else
                         { // Periodic Monitoring in the background
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"S03");
                           strcpy(a1->CMD.system_name,"back_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to S03 BACK END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING S03 Back END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"S03 BACK END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           { write_shm(a1,r1); }
                       
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* S03_self_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1= malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       s3selfQ.store = 0; s3selfQ.retrieve = 0;
              for(;;)
              {
                    if((int)(s3selfQ.store)>(int)(s3selfQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) s3_selfq_retrieve((int)s3selfQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"self_test"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                                     
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING S03  SELF SYSTEM  MCM RESPONSE\n"); 
                                     terminate_thread(server_fd); }
                              else if(n==0)
                            {
                              fprintf(stderr,"S03  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd); 
                            }
                              else
                              { write_shm(a1,r1); } 
                           
                             s3selfQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                     else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"S03");
                           strcpy(a1->CMD.system_name,"self_test");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to S03  SELF SYSTEM  MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                            { fprintf(stderr," ERROR READING S03 Self Test MCM RESPONSE\n"); terminate_thread(server_fd);}
                             else if(n==0)
                            {
                              fprintf(stderr,"S03  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1); } 
                           
                         }
                    }
  free(a1);
  free(r1);
  free(c1);
   return NULL;
}

/*************************************** S04 Antenna syste Thread functions here ******/

void* S04_fps_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
    
     resp *r1;
     r1 = malloc(sizeof(resp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       s4fpsQ.store = 0; s4fpsQ.retrieve = 0;
              for(;;)
              {
                    if((int)(s4fpsQ.store)>(int)(s4fpsQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) s4_fpsq_retrieve((int)s4fpsQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                              //  if(!strcasecmp(c1->system_name,"sentinel"))
                              if(!strcasecmp(c1->system_name,"fps"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to S04 FPS MCM device\n"); }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "S04 FPS MCM TIMEOUT\n");
                                         terminate_thread(server_fd);
                                        
                                      }
                                      else
                                     { 
                                         printcmd(c1);
                                         bzero(c1,sizeof(cmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(3);
                                  bzero(r1,sizeof(resp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING C00 FPS MCM RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                  else if(n==0)
                                  {
                                     fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                                     terminate_thread(server_fd);
                                  }    
                                 else
                                 {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from FPS THREAD SUCCESSFUL\n");
                                 } 
                                s4fpsQ.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                     else
                         { // Periodic Monitoring in the background 
                          // sleep(5); // Sleep put as per CPK request Date 2/12/2014
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"S04");
                           strcpy(a1->CMD.system_name,"fps");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"null");
                          //  strcpy(a1->CMD.op_name,"read_version");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                         
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to S04 FPS MCM device\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C00 FPS MCM TIMEOUT #Perodic Monitoring\n");
                                terminate_thread(server_fd);
                             
                           }
                            else if(n==0)
                            {
                              fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(5);
                            bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING S04 FPS 1 SECONDS MONITORING MCM RESPONSE\n");
                                   terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"S04 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              // printresp(r1);
                              write_shm(a1,r1); bzero(r1,sizeof(resp));
                            } 
                          } 
                
                    }

  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}

void* S04_sentinel_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       s4senQ.store = 0; s4senQ.retrieve = 0;
              for(;;)
              {
                   if((int)(s4senQ.store)>(int)(s4senQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) s4_senq_retrieve((int)s4senQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                              //  if(!strcasecmp(c1->system_name,"sentinel"))
                             if((!strcasecmp(c1->system_name,"sentinel"))||(!strcasecmp(c1->system_name,"fiber_optics")))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD S04 sentinel MCM device\n"); }
                                    else
                                   { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                        // bzero(c1,sizeof(cmd));   
                                         
                                    }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  usleep(500000);
                                 bzero(r1,sizeof(resp)); 
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING S04 sentinel MCM RESPONSE\n");  
                                     terminate_thread(server_fd); }
                               else if(n==0)
                                {
                                  fprintf(stderr,"S04 sentinel MCM closed it's Socket connection\n");
                                   terminate_thread(server_fd);
                                }     
                            else
                              {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from SENTINEL THREAD SUCCESSFUL\n");
                               } 
                             s4senQ.retrieve++; 
                                             
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                       else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"S04");
                           strcpy(a1->CMD.system_name,"sentinel");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to S04 sentinel MCM MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING S04 Sentinel MCM RESPONSE\n"); terminate_thread(server_fd);  }
                            else if(n==0)
                            {
                              fprintf(stderr,"S04 sentinel MCM closed it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           else
                           {
                           
                                write_shm(a1,r1); 
                           } 
                         
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* S04_fiber_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
      char *tstamp;
     tstamp = malloc(25);
    
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       s4fiberQ.store = 0; s4fiberQ.retrieve = 0;
              for(;;)
              {
                    if((int)(s4fiberQ.store)>(int)(s4fiberQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD*) s4_fiberq_retrieve((int)s4fiberQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"fiber_optics"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to S04 FIBER OPTICS MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                       
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                    usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING S04 FIBER OPTICS MCM RESPONSE\n"); terminate_thread(server_fd); }
                                else if(n==0)
                                {
                                 fprintf(stderr,"S04 FIBER OPTICS MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              {
                                     printresp(r1);
                                     write_shm(a1,r1);                  
                                     fprintf(stderr," Writing to ONLINE from FIBER THREAD SUCCESSFUL\n");
                               } 
                            
                             s4fiberQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                      else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"S04");
                           strcpy(a1->CMD.system_name,"fiber_optics");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to S04 FIBER OPTICS MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING S04  FIBER OPTICS MCM RESPONSE\n");shutdown(server_fd,SHUT_RDWR);
                                     close(server_fd);
                                     pthread_exit(NULL);  }
                             else if(n==0)
                            {
                              fprintf(stderr,"S04 FIBER OPTICS MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           {
                             
                                write_shm(a1,r1);  
                            
                           } 
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* S04_front_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
 
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
      char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       s4frontQ.store = 0; s4frontQ.retrieve = 0;
              for(;;)
              {
                    if((int)(s4frontQ.store)>(int)(s4frontQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = ( ANT_CMD*) s4_frontq_retrieve((int)s4frontQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"front_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to S04 FRONT END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING S04 FRONT END MCM RESPONSE\n"); 
                                    terminate_thread(server_fd);}
                               else if(n==0)
                              {
                                fprintf(stderr,"S04 FRONT END MCM closed it's Socket connection\n");
                                 terminate_thread(server_fd);
                              }
                              else
                              { printresp(r1); write_shm(a1,r1);  }
                           
                             s4frontQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       
                       }
                     else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"S04");
                           strcpy(a1->CMD.system_name,"front_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                           strcpy(a1->CMD.timestamp,tstamp);
                           c1 = &a1->CMD;
                              
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to S04 FRONT END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING S04 FRONT END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"S04 FRONT END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1);  }
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* S04_backend_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
        char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       s4backQ.store = 0; s4backQ.retrieve = 0;
              for(;;)
              {
                    if((int)(s4backQ.store)>(int)(s4backQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) s4_backq_retrieve((int)s4backQ.retrieve);
                        pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"back_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to S04 BACK END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING S04 BACK END MCM RESPONSE\n");
                                    terminate_thread(server_fd);}
                                else if(n==0)
                               {
                                 fprintf(stderr,"S04 BACK END MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              { printresp(r1);write_shm(a1,r1); } 
                           
                             s4backQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                      else
                         { // Periodic Monitoring in the background
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"S04");
                           strcpy(a1->CMD.system_name,"back_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to S04 BACK END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING S04 Back END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"S04 BACK END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           { write_shm(a1,r1); }
                       
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* S04_self_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1= malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       s4selfQ.store = 0; s4selfQ.retrieve = 0;
              for(;;)
              {
                    if((int)(s4selfQ.store)>(int)(s4selfQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) s4_selfq_retrieve((int)s4selfQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"self_test"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                                     
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING S04  SELF SYSTEM  MCM RESPONSE\n"); 
                                     terminate_thread(server_fd); }
                              else if(n==0)
                            {
                              fprintf(stderr,"S04  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd); 
                            }
                              else
                              { write_shm(a1,r1); } 
                           
                             s4selfQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                     else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"S04");
                           strcpy(a1->CMD.system_name,"self_test");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to S04  SELF SYSTEM  MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                            { fprintf(stderr," ERROR READING S04 Self Test MCM RESPONSE\n"); terminate_thread(server_fd);}
                             else if(n==0)
                            {
                              fprintf(stderr,"S04  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1); } 
                           
                         }
                    }
  free(a1);
  free(r1);
  free(c1);
   return NULL;
}

/*************************************** S06 Antenna syste Thread functions here ******/

void* S06_fps_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
    
     resp *r1;
     r1 = malloc(sizeof(resp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       s6fpsQ.store = 0; s6fpsQ.retrieve = 0;
              for(;;)
              {
                    if((int)(s6fpsQ.store)>(int)(s6fpsQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) s6_fpsq_retrieve((int)s6fpsQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                              //  if(!strcasecmp(c1->system_name,"sentinel"))
                              if(!strcasecmp(c1->system_name,"fps"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to S06 FPS MCM device\n"); }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "S06 FPS MCM TIMEOUT\n");
                                         terminate_thread(server_fd);
                                        
                                      }
                                      else
                                     { 
                                         printcmd(c1);
                                         bzero(c1,sizeof(cmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(3);
                                  bzero(r1,sizeof(resp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING C00 FPS MCM RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                  else if(n==0)
                                  {
                                     fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                                     terminate_thread(server_fd);
                                  }    
                                 else
                                 {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from FPS THREAD SUCCESSFUL\n");
                                 } 
                                s6fpsQ.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                     else
                         { // Periodic Monitoring in the background 
                          // sleep(5); // Sleep put as per CPK request Date 2/12/2014
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"S06");
                           strcpy(a1->CMD.system_name,"fps");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"null");
                          //  strcpy(a1->CMD.op_name,"read_version");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                         
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to S06 FPS MCM device\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C00 FPS MCM TIMEOUT #Perodic Monitoring\n");
                                terminate_thread(server_fd);
                             
                           }
                            else if(n==0)
                            {
                              fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(5);
                            bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING S06 FPS 1 SECONDS MONITORING MCM RESPONSE\n");
                                   terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"S06 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              // printresp(r1);
                              write_shm(a1,r1); bzero(r1,sizeof(resp));
                            } 
                          } 
                
                    }

  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}

void* S06_sentinel_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       s6senQ.store = 0; s6senQ.retrieve = 0;
              for(;;)
              {
                   if((int)(s6senQ.store)>(int)(s6senQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) s6_senq_retrieve((int)s6senQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                               // if(!strcasecmp(c1->system_name,"sentinel"))
                               if((!strcasecmp(c1->system_name,"sentinel"))||(!strcasecmp(c1->system_name,"fiber_optics")))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD S06 sentinel MCM device\n"); }
                                    else
                                   { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                        // bzero(c1,sizeof(cmd));   
                                         
                                    }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  usleep(500000);
                                 bzero(r1,sizeof(resp)); 
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING S06 sentinel MCM RESPONSE\n");  
                                     terminate_thread(server_fd); }
                               else if(n==0)
                                {
                                  fprintf(stderr,"S06 sentinel MCM closed it's Socket connection\n");
                                   terminate_thread(server_fd);
                                }     
                            else
                              {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from SENTINEL THREAD SUCCESSFUL\n");
                               } 
                             s6senQ.retrieve++; 
                                             
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                       else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"S06");
                           strcpy(a1->CMD.system_name,"sentinel");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to S06 sentinel MCM MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING S06 Sentinel MCM RESPONSE\n"); terminate_thread(server_fd);  }
                            else if(n==0)
                            {
                              fprintf(stderr,"S06 sentinel MCM closed it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           else
                           {
                           
                                write_shm(a1,r1); 
                           } 
                         
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* S06_fiber_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
      char *tstamp;
     tstamp = malloc(25);
    
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       s6fiberQ.store = 0; s6fiberQ.retrieve = 0;
              for(;;)
              {
                    if((int)(s6fiberQ.store)>(int)(s6fiberQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD*) s6_fiberq_retrieve((int)s6fiberQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"fiber_optics"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to S06 FIBER OPTICS MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                       
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                    usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING S06 FIBER OPTICS MCM RESPONSE\n"); terminate_thread(server_fd); }
                                else if(n==0)
                                {
                                 fprintf(stderr,"S06 FIBER OPTICS MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              {
                                     printresp(r1);
                                     write_shm(a1,r1);                  
                                     fprintf(stderr," Writing to ONLINE from FIBER THREAD SUCCESSFUL\n");
                               } 
                            
                             s6fiberQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                      else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"S06");
                           strcpy(a1->CMD.system_name,"fiber_optics");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to S06 FIBER OPTICS MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING S06  FIBER OPTICS MCM RESPONSE\n");shutdown(server_fd,SHUT_RDWR);
                                     close(server_fd);
                                     pthread_exit(NULL);  }
                             else if(n==0)
                            {
                              fprintf(stderr,"S06 FIBER OPTICS MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           {
                             
                                write_shm(a1,r1);  
                            
                           } 
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* S06_front_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
 
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
      char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       s6frontQ.store = 0; s6frontQ.retrieve = 0;
              for(;;)
              {
                    if((int)(s6frontQ.store)>(int)(s6frontQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = ( ANT_CMD*) s6_frontq_retrieve((int)s6frontQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"front_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to S06 FRONT END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING S06 FRONT END MCM RESPONSE\n"); 
                                    terminate_thread(server_fd);}
                               else if(n==0)
                              {
                                fprintf(stderr,"S06 FRONT END MCM closed it's Socket connection\n");
                                 terminate_thread(server_fd);
                              }
                              else
                              { printresp(r1); write_shm(a1,r1);  }
                           
                             s6frontQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       
                       }
                     else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"S06");
                           strcpy(a1->CMD.system_name,"front_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                           strcpy(a1->CMD.timestamp,tstamp);
                           c1 = &a1->CMD;
                              
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to S06 FRONT END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING S06 FRONT END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"S06 FRONT END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1);  }
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* S06_backend_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
        char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       s6backQ.store = 0; s6backQ.retrieve = 0;
              for(;;)
              {
                    if((int)(s6backQ.store)>(int)(s6backQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) s6_backq_retrieve((int)s6backQ.retrieve);
                        pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"back_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to S06 BACK END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING S06 BACK END MCM RESPONSE\n");
                                    terminate_thread(server_fd);}
                                else if(n==0)
                               {
                                 fprintf(stderr,"S06 BACK END MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              { printresp(r1);write_shm(a1,r1); } 
                           
                             s6backQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                      else
                         { // Periodic Monitoring in the background
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"S06");
                           strcpy(a1->CMD.system_name,"back_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to S06 BACK END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING S06 Back END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"S06 BACK END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           { write_shm(a1,r1); }
                       
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* S06_self_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1= malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       s6selfQ.store = 0; s6selfQ.retrieve = 0;
              for(;;)
              {
                    if((int)(s6selfQ.store)>(int)(s6selfQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) s6_selfq_retrieve((int)s6selfQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"self_test"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                                     
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING S06  SELF SYSTEM  MCM RESPONSE\n"); 
                                     terminate_thread(server_fd); }
                              else if(n==0)
                            {
                              fprintf(stderr,"S06  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd); 
                            }
                              else
                              { write_shm(a1,r1); } 
                           
                             s6selfQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                     else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"S06");
                           strcpy(a1->CMD.system_name,"self_test");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to S06  SELF SYSTEM  MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                            { fprintf(stderr," ERROR READING S06 Self Test MCM RESPONSE\n"); terminate_thread(server_fd);}
                             else if(n==0)
                            {
                              fprintf(stderr,"S06  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1); } 
                           
                         }
                    }
  free(a1);
  free(r1);
  free(c1);
   return NULL;
}


/*************************************** W01 Antenna syste Thread functions here ******/

void* W01_fps_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
    
     resp *r1;
     r1 = malloc(sizeof(resp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       w1fpsQ.store = 0; w1fpsQ.retrieve = 0;
              for(;;)
              {
                    if((int)(w1fpsQ.store)>(int)(w1fpsQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) w1_fpsq_retrieve((int)w1fpsQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                              //  if(!strcasecmp(c1->system_name,"sentinel"))
                              if(!strcasecmp(c1->system_name,"fps"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to W01 FPS MCM device\n"); }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "W01 FPS MCM TIMEOUT\n");
                                         terminate_thread(server_fd);
                                        
                                      }
                                      else
                                     { 
                                         printcmd(c1);
                                         bzero(c1,sizeof(cmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(3);
                                  bzero(r1,sizeof(resp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING C00 FPS MCM RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                  else if(n==0)
                                  {
                                     fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                                     terminate_thread(server_fd);
                                  }    
                                 else
                                 {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from FPS THREAD SUCCESSFUL\n");
                                 } 
                                w1fpsQ.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                     else
                         { // Periodic Monitoring in the background 
                          // sleep(5); // Sleep put as per CPK request Date 2/12/2014
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"W01");
                           strcpy(a1->CMD.system_name,"fps");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"null");
                          //  strcpy(a1->CMD.op_name,"read_version");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                         
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to W01 FPS MCM device\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C00 FPS MCM TIMEOUT #Perodic Monitoring\n");
                                terminate_thread(server_fd);
                             
                           }
                            else if(n==0)
                            {
                              fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(5);
                            bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING W01 FPS 1 SECONDS MONITORING MCM RESPONSE\n");
                                   terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"W01 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              // printresp(r1);
                              write_shm(a1,r1); bzero(r1,sizeof(resp));
                            } 
                          } 
                
                    }

  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}

void* W01_sentinel_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       w1senQ.store = 0; w1senQ.retrieve = 0;
              for(;;)
              {
                   if((int)(w1senQ.store)>(int)(w1senQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) w1_senq_retrieve((int)w1senQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                //if(!strcasecmp(c1->system_name,"sentinel"))
                              if((!strcasecmp(c1->system_name,"sentinel"))||(!strcasecmp(c1->system_name,"fiber_optics")))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD W01 sentinel MCM device\n"); }
                                    else
                                   { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                        // bzero(c1,sizeof(cmd));   
                                         
                                    }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  usleep(500000);
                                 bzero(r1,sizeof(resp)); 
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING W01 sentinel MCM RESPONSE\n");  
                                     terminate_thread(server_fd); }
                               else if(n==0)
                                {
                                  fprintf(stderr,"W01 sentinel MCM closed it's Socket connection\n");
                                   terminate_thread(server_fd);
                                }     
                            else
                              {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from SENTINEL THREAD SUCCESSFUL\n");
                               } 
                             w1senQ.retrieve++; 
                                             
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                       else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"W01");
                           strcpy(a1->CMD.system_name,"sentinel");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to W01 sentinel MCM MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING W01 Sentinel MCM RESPONSE\n"); terminate_thread(server_fd);  }
                            else if(n==0)
                            {
                              fprintf(stderr,"W01 sentinel MCM closed it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           else
                           {
                           
                                write_shm(a1,r1); 
                           } 
                         
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* W01_fiber_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
      char *tstamp;
     tstamp = malloc(25);
    
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       w1fiberQ.store = 0; w1fiberQ.retrieve = 0;
              for(;;)
              {
                    if((int)(w1fiberQ.store)>(int)(w1fiberQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD*) w1_fiberq_retrieve((int)w1fiberQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"fiber_optics"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to W01 FIBER OPTICS MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                       
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                    usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING W01 FIBER OPTICS MCM RESPONSE\n"); terminate_thread(server_fd); }
                                else if(n==0)
                                {
                                 fprintf(stderr,"W01 FIBER OPTICS MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              {
                                     printresp(r1);
                                     write_shm(a1,r1);                  
                                     fprintf(stderr," Writing to ONLINE from FIBER THREAD SUCCESSFUL\n");
                               } 
                            
                             w1fiberQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                      else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"W01");
                           strcpy(a1->CMD.system_name,"fiber_optics");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to W01 FIBER OPTICS MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING W01  FIBER OPTICS MCM RESPONSE\n");shutdown(server_fd,SHUT_RDWR);
                                     close(server_fd);
                                     pthread_exit(NULL);  }
                             else if(n==0)
                            {
                              fprintf(stderr,"W01 FIBER OPTICS MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           {
                             
                                write_shm(a1,r1);  
                            
                           } 
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* W01_front_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
 
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
      char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       w1frontQ.store = 0; w1frontQ.retrieve = 0;
              for(;;)
              {
                    if((int)(w1frontQ.store)>(int)(w1frontQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = ( ANT_CMD*) w1_frontq_retrieve((int)w1frontQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"front_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to W01 FRONT END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING W01 FRONT END MCM RESPONSE\n"); 
                                    terminate_thread(server_fd);}
                               else if(n==0)
                              {
                                fprintf(stderr,"W01 FRONT END MCM closed it's Socket connection\n");
                                 terminate_thread(server_fd);
                              }
                              else
                              { printresp(r1); write_shm(a1,r1);  }
                           
                             w1frontQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       
                       }
                     else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"W01");
                           strcpy(a1->CMD.system_name,"front_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                           strcpy(a1->CMD.timestamp,tstamp);
                           c1 = &a1->CMD;
                              
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to W01 FRONT END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING W01 FRONT END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"W01 FRONT END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1);  }
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* W01_backend_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
        char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       w1backQ.store = 0; w1backQ.retrieve = 0;
              for(;;)
              {
                    if((int)(w1backQ.store)>(int)(w1backQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) w1_backq_retrieve((int)w1backQ.retrieve);
                        pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"back_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to W01 BACK END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING W01 BACK END MCM RESPONSE\n");
                                    terminate_thread(server_fd);}
                                else if(n==0)
                               {
                                 fprintf(stderr,"W01 BACK END MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              { printresp(r1);write_shm(a1,r1); } 
                           
                             w1backQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                      else
                         { // Periodic Monitoring in the background
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"W01");
                           strcpy(a1->CMD.system_name,"back_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to W01 BACK END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING W01 Back END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"W01 BACK END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           { write_shm(a1,r1); }
                       
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* W01_self_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1= malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       w1selfQ.store = 0; w1selfQ.retrieve = 0;
              for(;;)
              {
                    if((int)(w1selfQ.store)>(int)(w1selfQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) w1_selfq_retrieve((int)w1selfQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"self_test"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                                     
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING W01  SELF SYSTEM  MCM RESPONSE\n"); 
                                     terminate_thread(server_fd); }
                              else if(n==0)
                            {
                              fprintf(stderr,"W01  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd); 
                            }
                              else
                              { write_shm(a1,r1); } 
                           
                             w1selfQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                     else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"W01");
                           strcpy(a1->CMD.system_name,"self_test");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to W01  SELF SYSTEM  MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                            { fprintf(stderr," ERROR READING W01 Self Test MCM RESPONSE\n"); terminate_thread(server_fd);}
                             else if(n==0)
                            {
                              fprintf(stderr,"W01  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1); } 
                           
                         }
                    }
  free(a1);
  free(r1);
  free(c1);
   return NULL;
}

/*************************************** W02 Antenna syste Thread functions here ******/

void* W02_fps_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
    
     resp *r1;
     r1 = malloc(sizeof(resp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       w2fpsQ.store = 0; w2fpsQ.retrieve = 0;
              for(;;)
              {
                    if((int)(w2fpsQ.store)>(int)(w2fpsQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) w2_fpsq_retrieve((int)w2fpsQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                              //  if(!strcasecmp(c1->system_name,"sentinel"))
                              if(!strcasecmp(c1->system_name,"fps"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to W02 FPS MCM device\n"); }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "W02 FPS MCM TIMEOUT\n");
                                         terminate_thread(server_fd);
                                        
                                      }
                                      else
                                     { 
                                         printcmd(c1);
                                         bzero(c1,sizeof(cmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(3);
                                  bzero(r1,sizeof(resp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING C00 FPS MCM RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                  else if(n==0)
                                  {
                                     fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                                     terminate_thread(server_fd);
                                  }    
                                 else
                                 {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from FPS THREAD SUCCESSFUL\n");
                                 } 
                                w2fpsQ.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                     else
                         { // Periodic Monitoring in the background 
                          // sleep(5); // Sleep put as per CPK request Date 2/12/2014
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"W02");
                           strcpy(a1->CMD.system_name,"fps");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"null");
                          //  strcpy(a1->CMD.op_name,"read_version");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                         
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to W02 FPS MCM device\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C00 FPS MCM TIMEOUT #Perodic Monitoring\n");
                                terminate_thread(server_fd);
                             
                           }
                            else if(n==0)
                            {
                              fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(5);
                            bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING W02 FPS 1 SECONDS MONITORING MCM RESPONSE\n");
                                   terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"W02 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              // printresp(r1);
                              write_shm(a1,r1); bzero(r1,sizeof(resp));
                            } 
                          } 
                
                    }

  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}

void* W02_sentinel_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       w2senQ.store = 0; w2senQ.retrieve = 0;
              for(;;)
              {
                   if((int)(w2senQ.store)>(int)(w2senQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) w2_senq_retrieve((int)w2senQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                              //  if(!strcasecmp(c1->system_name,"sentinel"))
                               if((!strcasecmp(c1->system_name,"sentinel"))||(!strcasecmp(c1->system_name,"fiber_optics")))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD W02 sentinel MCM device\n"); }
                                    else
                                   { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                        // bzero(c1,sizeof(cmd));   
                                         
                                    }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  usleep(500000);
                                 bzero(r1,sizeof(resp)); 
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING W02 sentinel MCM RESPONSE\n");  
                                     terminate_thread(server_fd); }
                               else if(n==0)
                                {
                                  fprintf(stderr,"W02 sentinel MCM closed it's Socket connection\n");
                                   terminate_thread(server_fd);
                                }     
                            else
                              {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from SENTINEL THREAD SUCCESSFUL\n");
                               } 
                             w2senQ.retrieve++; 
                                             
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                       else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"W02");
                           strcpy(a1->CMD.system_name,"sentinel");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to W02 sentinel MCM MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING W02 Sentinel MCM RESPONSE\n"); terminate_thread(server_fd);  }
                            else if(n==0)
                            {
                              fprintf(stderr,"W02 sentinel MCM closed it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           else
                           {
                           
                                write_shm(a1,r1); 
                           } 
                         
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* W02_fiber_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
      char *tstamp;
     tstamp = malloc(25);
    
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       w2fiberQ.store = 0; w2fiberQ.retrieve = 0;
              for(;;)
              {
                    if((int)(w2fiberQ.store)>(int)(w2fiberQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD*) w2_fiberq_retrieve((int)w2fiberQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"fiber_optics"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to W02 FIBER OPTICS MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                       
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                    usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING W02 FIBER OPTICS MCM RESPONSE\n"); terminate_thread(server_fd); }
                                else if(n==0)
                                {
                                 fprintf(stderr,"W02 FIBER OPTICS MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              {
                                     printresp(r1);
                                     write_shm(a1,r1);                  
                                     fprintf(stderr," Writing to ONLINE from FIBER THREAD SUCCESSFUL\n");
                               } 
                            
                             w2fiberQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                      else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"W02");
                           strcpy(a1->CMD.system_name,"fiber_optics");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to W02 FIBER OPTICS MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING W02  FIBER OPTICS MCM RESPONSE\n");shutdown(server_fd,SHUT_RDWR);
                                     close(server_fd);
                                     pthread_exit(NULL);  }
                             else if(n==0)
                            {
                              fprintf(stderr,"W02 FIBER OPTICS MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           {
                             
                                write_shm(a1,r1);  
                            
                           } 
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* W02_front_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
 
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
      char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       w2frontQ.store = 0; w2frontQ.retrieve = 0;
              for(;;)
              {
                    if((int)(w2frontQ.store)>(int)(w2frontQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = ( ANT_CMD*) w2_frontq_retrieve((int)w2frontQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"front_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to W02 FRONT END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING W02 FRONT END MCM RESPONSE\n"); 
                                    terminate_thread(server_fd);}
                               else if(n==0)
                              {
                                fprintf(stderr,"W02 FRONT END MCM closed it's Socket connection\n");
                                 terminate_thread(server_fd);
                              }
                              else
                              { printresp(r1); write_shm(a1,r1);  }
                           
                             w2frontQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       
                       }
                     else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"W02");
                           strcpy(a1->CMD.system_name,"front_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                           strcpy(a1->CMD.timestamp,tstamp);
                           c1 = &a1->CMD;
                              
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to W02 FRONT END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING W02 FRONT END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"W02 FRONT END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1);  }
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* W02_backend_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
        char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       w2backQ.store = 0; w2backQ.retrieve = 0;
              for(;;)
              {
                    if((int)(w2backQ.store)>(int)(w2backQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) w2_backq_retrieve((int)w2backQ.retrieve);
                        pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"back_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to W02 BACK END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING W02 BACK END MCM RESPONSE\n");
                                    terminate_thread(server_fd);}
                                else if(n==0)
                               {
                                 fprintf(stderr,"W02 BACK END MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              { printresp(r1);write_shm(a1,r1); } 
                           
                             w2backQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                      else
                         { // Periodic Monitoring in the background
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"W02");
                           strcpy(a1->CMD.system_name,"back_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to W02 BACK END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING W02 Back END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"W02 BACK END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           { write_shm(a1,r1); }
                       
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* W02_self_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1= malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       w2selfQ.store = 0; w2selfQ.retrieve = 0;
              for(;;)
              {
                    if((int)(w2selfQ.store)>(int)(w2selfQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) w2_selfq_retrieve((int)w2selfQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"self_test"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                                     
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING W02  SELF SYSTEM  MCM RESPONSE\n"); 
                                     terminate_thread(server_fd); }
                              else if(n==0)
                            {
                              fprintf(stderr,"W02  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd); 
                            }
                              else
                              { write_shm(a1,r1); } 
                           
                             w2selfQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                     else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"W02");
                           strcpy(a1->CMD.system_name,"self_test");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to W02  SELF SYSTEM  MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                            { fprintf(stderr," ERROR READING W02 Self Test MCM RESPONSE\n"); terminate_thread(server_fd);}
                             else if(n==0)
                            {
                              fprintf(stderr,"W02  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1); } 
                           
                         }
                    }
  free(a1);
  free(r1);
  free(c1);
   return NULL;
}

/*************************************** W03 Antenna syste Thread functions here ******/

void* W03_fps_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
    
     resp *r1;
     r1 = malloc(sizeof(resp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       w3fpsQ.store = 0; w3fpsQ.retrieve = 0;
              for(;;)
              {
                    if((int)(w3fpsQ.store)>(int)(w3fpsQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) w3_fpsq_retrieve((int)w3fpsQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                              //  if(!strcasecmp(c1->system_name,"sentinel"))
                              if(!strcasecmp(c1->system_name,"fps"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to W03 FPS MCM device\n"); }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "W03 FPS MCM TIMEOUT\n");
                                         terminate_thread(server_fd);
                                        
                                      }
                                      else
                                     { 
                                         printcmd(c1);
                                         bzero(c1,sizeof(cmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(3);
                                  bzero(r1,sizeof(resp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING C00 FPS MCM RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                  else if(n==0)
                                  {
                                     fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                                     terminate_thread(server_fd);
                                  }    
                                 else
                                 {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from FPS THREAD SUCCESSFUL\n");
                                 } 
                                w3fpsQ.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                     else
                         { // Periodic Monitoring in the background 
                          // sleep(5); // Sleep put as per CPK request Date 2/12/2014
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"W03");
                           strcpy(a1->CMD.system_name,"fps");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"null");
                          //  strcpy(a1->CMD.op_name,"read_version");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                         
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to W03 FPS MCM device\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C00 FPS MCM TIMEOUT #Perodic Monitoring\n");
                                terminate_thread(server_fd);
                             
                           }
                            else if(n==0)
                            {
                              fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(5);
                            bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING W03 FPS 1 SECONDS MONITORING MCM RESPONSE\n");
                                   terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"W03 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              // printresp(r1);
                              write_shm(a1,r1); bzero(r1,sizeof(resp));
                            } 
                          } 
                
                    }

  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}

void* W03_sentinel_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       w3senQ.store = 0; w3senQ.retrieve = 0;
              for(;;)
              {
                   if((int)(w3senQ.store)>(int)(w3senQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) w3_senq_retrieve((int)w3senQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                               // if(!strcasecmp(c1->system_name,"sentinel"))
                             if((!strcasecmp(c1->system_name,"sentinel"))||(!strcasecmp(c1->system_name,"fiber_optics")))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD W03 sentinel MCM device\n"); }
                                    else
                                   { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                        // bzero(c1,sizeof(cmd));   
                                         
                                    }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  usleep(500000);
                                 bzero(r1,sizeof(resp)); 
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING W03 sentinel MCM RESPONSE\n");  
                                     terminate_thread(server_fd); }
                               else if(n==0)
                                {
                                  fprintf(stderr,"W03 sentinel MCM closed it's Socket connection\n");
                                   terminate_thread(server_fd);
                                }     
                            else
                              {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from SENTINEL THREAD SUCCESSFUL\n");
                               } 
                             w3senQ.retrieve++; 
                                             
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                       else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"W03");
                           strcpy(a1->CMD.system_name,"sentinel");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to W03 sentinel MCM MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING W03 Sentinel MCM RESPONSE\n"); terminate_thread(server_fd);  }
                            else if(n==0)
                            {
                              fprintf(stderr,"W03 sentinel MCM closed it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           else
                           {
                           
                                write_shm(a1,r1); 
                           } 
                         
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* W03_fiber_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
      char *tstamp;
     tstamp = malloc(25);
    
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       w3fiberQ.store = 0; w3fiberQ.retrieve = 0;
              for(;;)
              {
                    if((int)(w3fiberQ.store)>(int)(w3fiberQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD*) w3_fiberq_retrieve((int)w3fiberQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"fiber_optics"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to W03 FIBER OPTICS MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                       
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                    usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING W03 FIBER OPTICS MCM RESPONSE\n"); terminate_thread(server_fd); }
                                else if(n==0)
                                {
                                 fprintf(stderr,"W03 FIBER OPTICS MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              {
                                     printresp(r1);
                                     write_shm(a1,r1);                  
                                     fprintf(stderr," Writing to ONLINE from FIBER THREAD SUCCESSFUL\n");
                               } 
                            
                             w3fiberQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                      else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"W03");
                           strcpy(a1->CMD.system_name,"fiber_optics");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to W03 FIBER OPTICS MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING W03  FIBER OPTICS MCM RESPONSE\n");shutdown(server_fd,SHUT_RDWR);
                                     close(server_fd);
                                     pthread_exit(NULL);  }
                             else if(n==0)
                            {
                              fprintf(stderr,"W03 FIBER OPTICS MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           {
                             
                                write_shm(a1,r1);  
                            
                           } 
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* W03_front_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
 
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
      char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       w3frontQ.store = 0; w3frontQ.retrieve = 0;
              for(;;)
              {
                    if((int)(w3frontQ.store)>(int)(w3frontQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = ( ANT_CMD*) w3_frontq_retrieve((int)w3frontQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"front_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to W03 FRONT END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING W03 FRONT END MCM RESPONSE\n"); 
                                    terminate_thread(server_fd);}
                               else if(n==0)
                              {
                                fprintf(stderr,"W03 FRONT END MCM closed it's Socket connection\n");
                                 terminate_thread(server_fd);
                              }
                              else
                              { printresp(r1); write_shm(a1,r1);  }
                           
                             w3frontQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       
                       }
                     else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"W03");
                           strcpy(a1->CMD.system_name,"front_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                           strcpy(a1->CMD.timestamp,tstamp);
                           c1 = &a1->CMD;
                              
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to W03 FRONT END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING W03 FRONT END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"W03 FRONT END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1);  }
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* W03_backend_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
        char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       w3backQ.store = 0; w3backQ.retrieve = 0;
              for(;;)
              {
                    if((int)(w3backQ.store)>(int)(w3backQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) w3_backq_retrieve((int)w3backQ.retrieve);
                        pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"back_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to W03 BACK END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING W03 BACK END MCM RESPONSE\n");
                                    terminate_thread(server_fd);}
                                else if(n==0)
                               {
                                 fprintf(stderr,"W03 BACK END MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              { printresp(r1);write_shm(a1,r1); } 
                           
                             w3backQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                      else
                         { // Periodic Monitoring in the background
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"W03");
                           strcpy(a1->CMD.system_name,"back_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to W03 BACK END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING W03 Back END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"W03 BACK END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           { write_shm(a1,r1); }
                       
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* W03_self_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1= malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       w3selfQ.store = 0; w3selfQ.retrieve = 0;
              for(;;)
              {
                    if((int)(w3selfQ.store)>(int)(w3selfQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) w3_selfq_retrieve((int)w3selfQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"self_test"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                                     
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING W03  SELF SYSTEM  MCM RESPONSE\n"); 
                                     terminate_thread(server_fd); }
                              else if(n==0)
                            {
                              fprintf(stderr,"W03  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd); 
                            }
                              else
                              { write_shm(a1,r1); } 
                           
                             w3selfQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                     else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"W03");
                           strcpy(a1->CMD.system_name,"self_test");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to W03  SELF SYSTEM  MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                            { fprintf(stderr," ERROR READING W03 Self Test MCM RESPONSE\n"); terminate_thread(server_fd);}
                             else if(n==0)
                            {
                              fprintf(stderr,"W03  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1); } 
                           
                         }
                    }
  free(a1);
  free(r1);
  free(c1);
   return NULL;
}

/*************************************** W04 Antenna syste Thread functions here ******/

void* W04_fps_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
    
     resp *r1;
     r1 = malloc(sizeof(resp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       w4fpsQ.store = 0; w4fpsQ.retrieve = 0;
              for(;;)
              {
                    if((int)(w4fpsQ.store)>(int)(w4fpsQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) w4_fpsq_retrieve((int)w4fpsQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                              //  if(!strcasecmp(c1->system_name,"sentinel"))
                              if(!strcasecmp(c1->system_name,"fps"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to W04 FPS MCM device\n"); }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "W04 FPS MCM TIMEOUT\n");
                                         terminate_thread(server_fd);
                                        
                                      }
                                      else
                                     { 
                                         printcmd(c1);
                                         bzero(c1,sizeof(cmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(3);
                                  bzero(r1,sizeof(resp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING C00 FPS MCM RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                  else if(n==0)
                                  {
                                     fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                                     terminate_thread(server_fd);
                                  }    
                                 else
                                 {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from FPS THREAD SUCCESSFUL\n");
                                 } 
                                w4fpsQ.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                     else
                         { // Periodic Monitoring in the background 
                          // sleep(5); // Sleep put as per CPK request Date 2/12/2014
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"W04");
                           strcpy(a1->CMD.system_name,"fps");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"null");
                          //  strcpy(a1->CMD.op_name,"read_version");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                         
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to W04 FPS MCM device\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C00 FPS MCM TIMEOUT #Perodic Monitoring\n");
                                terminate_thread(server_fd);
                             
                           }
                            else if(n==0)
                            {
                              fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(5);
                            bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING W04 FPS 1 SECONDS MONITORING MCM RESPONSE\n");
                                   terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"W04 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              // printresp(r1);
                              write_shm(a1,r1); bzero(r1,sizeof(resp));
                            } 
                          } 
                
                    }

  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}

void* W04_sentinel_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       w4senQ.store = 0; w4senQ.retrieve = 0;
              for(;;)
              {
                   if((int)(w4senQ.store)>(int)(w4senQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) w4_senq_retrieve((int)w4senQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                               // if(!strcasecmp(c1->system_name,"sentinel"))
                              if((!strcasecmp(c1->system_name,"sentinel"))||(!strcasecmp(c1->system_name,"fiber_optics")))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD W04 sentinel MCM device\n"); }
                                    else
                                   { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                        // bzero(c1,sizeof(cmd));   
                                         
                                    }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  usleep(500000);
                                 bzero(r1,sizeof(resp)); 
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING W04 sentinel MCM RESPONSE\n");  
                                     terminate_thread(server_fd); }
                               else if(n==0)
                                {
                                  fprintf(stderr,"W04 sentinel MCM closed it's Socket connection\n");
                                   terminate_thread(server_fd);
                                }     
                            else
                              {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from SENTINEL THREAD SUCCESSFUL\n");
                               } 
                             w4senQ.retrieve++; 
                                             
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                       else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"W04");
                           strcpy(a1->CMD.system_name,"sentinel");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to W04 sentinel MCM MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING W04 Sentinel MCM RESPONSE\n"); terminate_thread(server_fd);  }
                            else if(n==0)
                            {
                              fprintf(stderr,"W04 sentinel MCM closed it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           else
                           {
                           
                                write_shm(a1,r1); 
                           } 
                         
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* W04_fiber_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
      char *tstamp;
     tstamp = malloc(25);
    
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       w4fiberQ.store = 0; w4fiberQ.retrieve = 0;
              for(;;)
              {
                    if((int)(w4fiberQ.store)>(int)(w4fiberQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD*) w4_fiberq_retrieve((int)w4fiberQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"fiber_optics"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to W04 FIBER OPTICS MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                       
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                    usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING W04 FIBER OPTICS MCM RESPONSE\n"); terminate_thread(server_fd); }
                                else if(n==0)
                                {
                                 fprintf(stderr,"W04 FIBER OPTICS MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              {
                                     printresp(r1);
                                     write_shm(a1,r1);                  
                                     fprintf(stderr," Writing to ONLINE from FIBER THREAD SUCCESSFUL\n");
                               } 
                            
                             w4fiberQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                      else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"W04");
                           strcpy(a1->CMD.system_name,"fiber_optics");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to W04 FIBER OPTICS MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING W04  FIBER OPTICS MCM RESPONSE\n");shutdown(server_fd,SHUT_RDWR);
                                     close(server_fd);
                                     pthread_exit(NULL);  }
                             else if(n==0)
                            {
                              fprintf(stderr,"W04 FIBER OPTICS MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           {
                             
                                write_shm(a1,r1);  
                            
                           } 
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* W04_front_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
 
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
      char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       w4frontQ.store = 0; w4frontQ.retrieve = 0;
              for(;;)
              {
                    if((int)(w4frontQ.store)>(int)(w4frontQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = ( ANT_CMD*) w4_frontq_retrieve((int)w4frontQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"front_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to W04 FRONT END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING W04 FRONT END MCM RESPONSE\n"); 
                                    terminate_thread(server_fd);}
                               else if(n==0)
                              {
                                fprintf(stderr,"W04 FRONT END MCM closed it's Socket connection\n");
                                 terminate_thread(server_fd);
                              }
                              else
                              { printresp(r1); write_shm(a1,r1);  }
                           
                             w4frontQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       
                       }
                     else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"W04");
                           strcpy(a1->CMD.system_name,"front_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                           strcpy(a1->CMD.timestamp,tstamp);
                           c1 = &a1->CMD;
                              
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to W04 FRONT END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING W04 FRONT END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"W04 FRONT END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1);  }
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* W04_backend_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
        char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       w4backQ.store = 0; w4backQ.retrieve = 0;
              for(;;)
              {
                    if((int)(w4backQ.store)>(int)(w4backQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) w4_backq_retrieve((int)w4backQ.retrieve);
                        pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"back_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to W04 BACK END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING W04 BACK END MCM RESPONSE\n");
                                    terminate_thread(server_fd);}
                                else if(n==0)
                               {
                                 fprintf(stderr,"W04 BACK END MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              { printresp(r1);write_shm(a1,r1); } 
                           
                             w4backQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                      else
                         { // Periodic Monitoring in the background
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"W04");
                           strcpy(a1->CMD.system_name,"back_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to W04 BACK END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING W04 Back END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"W04 BACK END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           { write_shm(a1,r1); }
                       
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* W04_self_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1= malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       w4selfQ.store = 0; w4selfQ.retrieve = 0;
              for(;;)
              {
                    if((int)(w4selfQ.store)>(int)(w4selfQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) w4_selfq_retrieve((int)w4selfQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"self_test"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                                     
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING W04  SELF SYSTEM  MCM RESPONSE\n"); 
                                     terminate_thread(server_fd); }
                              else if(n==0)
                            {
                              fprintf(stderr,"W04  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd); 
                            }
                              else
                              { write_shm(a1,r1); } 
                           
                             w4selfQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                     else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"W04");
                           strcpy(a1->CMD.system_name,"self_test");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to W04  SELF SYSTEM  MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                            { fprintf(stderr," ERROR READING W04 Self Test MCM RESPONSE\n"); terminate_thread(server_fd);}
                             else if(n==0)
                            {
                              fprintf(stderr,"W04  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1); } 
                           
                         }
                    }
  free(a1);
  free(r1);
  free(c1);
   return NULL;
}

/*************************************** W05 Antenna syste Thread functions here ******/

void* W05_fps_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
    
     resp *r1;
     r1 = malloc(sizeof(resp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       w5fpsQ.store = 0; w5fpsQ.retrieve = 0;
              for(;;)
              {
                    if((int)(w5fpsQ.store)>(int)(w5fpsQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) w5_fpsq_retrieve((int)w5fpsQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                              //  if(!strcasecmp(c1->system_name,"sentinel"))
                              if(!strcasecmp(c1->system_name,"fps"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to W05 FPS MCM device\n"); }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "W05 FPS MCM TIMEOUT\n");
                                         terminate_thread(server_fd);
                                        
                                      }
                                      else
                                     { 
                                         printcmd(c1);
                                         bzero(c1,sizeof(cmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(3);
                                  bzero(r1,sizeof(resp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING C00 FPS MCM RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                  else if(n==0)
                                  {
                                     fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                                     terminate_thread(server_fd);
                                  }    
                                 else
                                 {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from FPS THREAD SUCCESSFUL\n");
                                 } 
                                w5fpsQ.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                     else
                         { // Periodic Monitoring in the background 
                          // sleep(5); // Sleep put as per CPK request Date 2/12/2014
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"W05");
                           strcpy(a1->CMD.system_name,"fps");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"null");
                          //  strcpy(a1->CMD.op_name,"read_version");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                         
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to W05 FPS MCM device\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C00 FPS MCM TIMEOUT #Perodic Monitoring\n");
                                terminate_thread(server_fd);
                             
                           }
                            else if(n==0)
                            {
                              fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(5);
                            bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING W05 FPS 1 SECONDS MONITORING MCM RESPONSE\n");
                                   terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"W05 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              // printresp(r1);
                              write_shm(a1,r1); bzero(r1,sizeof(resp));
                            } 
                          } 
                
                    }

  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}

void* W05_sentinel_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       w5senQ.store = 0; w5senQ.retrieve = 0;
              for(;;)
              {
                   if((int)(w5senQ.store)>(int)(w5senQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) w5_senq_retrieve((int)w5senQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                              //  if(!strcasecmp(c1->system_name,"sentinel"))
                               if((!strcasecmp(c1->system_name,"sentinel"))||(!strcasecmp(c1->system_name,"fiber_optics")))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD W05 sentinel MCM device\n"); }
                                    else
                                   { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                        // bzero(c1,sizeof(cmd));   
                                         
                                    }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  usleep(500000);
                                 bzero(r1,sizeof(resp)); 
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING W05 sentinel MCM RESPONSE\n");  
                                     terminate_thread(server_fd); }
                               else if(n==0)
                                {
                                  fprintf(stderr,"W05 sentinel MCM closed it's Socket connection\n");
                                   terminate_thread(server_fd);
                                }     
                            else
                              {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from SENTINEL THREAD SUCCESSFUL\n");
                               } 
                             w5senQ.retrieve++; 
                                             
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                       else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"W05");
                           strcpy(a1->CMD.system_name,"sentinel");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to W05 sentinel MCM MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING W05 Sentinel MCM RESPONSE\n"); terminate_thread(server_fd);  }
                            else if(n==0)
                            {
                              fprintf(stderr,"W05 sentinel MCM closed it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           else
                           {
                           
                                write_shm(a1,r1); 
                           } 
                         
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* W05_fiber_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
      char *tstamp;
     tstamp = malloc(25);
    
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       w5fiberQ.store = 0; w5fiberQ.retrieve = 0;
              for(;;)
              {
                    if((int)(w5fiberQ.store)>(int)(w5fiberQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD*) w5_fiberq_retrieve((int)w5fiberQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"fiber_optics"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to W05 FIBER OPTICS MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                       
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                    usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING W05 FIBER OPTICS MCM RESPONSE\n"); terminate_thread(server_fd); }
                                else if(n==0)
                                {
                                 fprintf(stderr,"W05 FIBER OPTICS MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              {
                                     printresp(r1);
                                     write_shm(a1,r1);                  
                                     fprintf(stderr," Writing to ONLINE from FIBER THREAD SUCCESSFUL\n");
                               } 
                            
                             w5fiberQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                      else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"W05");
                           strcpy(a1->CMD.system_name,"fiber_optics");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to W05 FIBER OPTICS MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING W05  FIBER OPTICS MCM RESPONSE\n");shutdown(server_fd,SHUT_RDWR);
                                     close(server_fd);
                                     pthread_exit(NULL);  }
                             else if(n==0)
                            {
                              fprintf(stderr,"W05 FIBER OPTICS MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           {
                             
                                write_shm(a1,r1);  
                            
                           } 
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* W05_front_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
 
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
      char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       w5frontQ.store = 0; w5frontQ.retrieve = 0;
              for(;;)
              {
                    if((int)(w5frontQ.store)>(int)(w5frontQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = ( ANT_CMD*) w5_frontq_retrieve((int)w5frontQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"front_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to W05 FRONT END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING W05 FRONT END MCM RESPONSE\n"); 
                                    terminate_thread(server_fd);}
                               else if(n==0)
                              {
                                fprintf(stderr,"W05 FRONT END MCM closed it's Socket connection\n");
                                 terminate_thread(server_fd);
                              }
                              else
                              { printresp(r1); write_shm(a1,r1);  }
                           
                             w5frontQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       
                       }
                     else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"W05");
                           strcpy(a1->CMD.system_name,"front_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                           strcpy(a1->CMD.timestamp,tstamp);
                           c1 = &a1->CMD;
                              
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to W05 FRONT END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING W05 FRONT END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"W05 FRONT END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1);  }
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* W05_backend_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
        char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       w5backQ.store = 0; w5backQ.retrieve = 0;
              for(;;)
              {
                    if((int)(w5backQ.store)>(int)(w5backQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) w5_backq_retrieve((int)w5backQ.retrieve);
                        pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"back_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to W05 BACK END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING W05 BACK END MCM RESPONSE\n");
                                    terminate_thread(server_fd);}
                                else if(n==0)
                               {
                                 fprintf(stderr,"W05 BACK END MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              { printresp(r1);write_shm(a1,r1); } 
                           
                             w5backQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                      else
                         { // Periodic Monitoring in the background
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"W05");
                           strcpy(a1->CMD.system_name,"back_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to W05 BACK END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING W05 Back END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"W05 BACK END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           { write_shm(a1,r1); }
                       
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* W05_self_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1= malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       w5selfQ.store = 0; w5selfQ.retrieve = 0;
              for(;;)
              {
                    if((int)(w5selfQ.store)>(int)(w5selfQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) w5_selfq_retrieve((int)w5selfQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"self_test"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                                     
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING W05  SELF SYSTEM  MCM RESPONSE\n"); 
                                     terminate_thread(server_fd); }
                              else if(n==0)
                            {
                              fprintf(stderr,"W05  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd); 
                            }
                              else
                              { write_shm(a1,r1); } 
                           
                             w5selfQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                     else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"W05");
                           strcpy(a1->CMD.system_name,"self_test");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to W05  SELF SYSTEM  MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                            { fprintf(stderr," ERROR READING W05 Self Test MCM RESPONSE\n"); terminate_thread(server_fd);}
                             else if(n==0)
                            {
                              fprintf(stderr,"W05  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1); } 
                           
                         }
                    }
  free(a1);
  free(r1);
  free(c1);
   return NULL;
}

/*************************************** W06 Antenna syste Thread functions here ******/

void* W06_fps_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
    
     resp *r1;
     r1 = malloc(sizeof(resp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       w6fpsQ.store = 0; w6fpsQ.retrieve = 0;
              for(;;)
              {
                    if((int)(w6fpsQ.store)>(int)(w6fpsQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) w6_fpsq_retrieve((int)w6fpsQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                              //  if(!strcasecmp(c1->system_name,"sentinel"))
                              if(!strcasecmp(c1->system_name,"fps"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to W06 FPS MCM device\n"); }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "W06 FPS MCM TIMEOUT\n");
                                         terminate_thread(server_fd);
                                        
                                      }
                                      else
                                     { 
                                         printcmd(c1);
                                         bzero(c1,sizeof(cmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(3);
                                  bzero(r1,sizeof(resp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING C00 FPS MCM RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                  else if(n==0)
                                  {
                                     fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                                     terminate_thread(server_fd);
                                  }    
                                 else
                                 {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from FPS THREAD SUCCESSFUL\n");
                                 } 
                                w6fpsQ.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                     else
                         { // Periodic Monitoring in the background 
                          // sleep(5); // Sleep put as per CPK request Date 2/12/2014
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"W06");
                           strcpy(a1->CMD.system_name,"fps");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"null");
                          //  strcpy(a1->CMD.op_name,"read_version");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                         
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to W06 FPS MCM device\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C00 FPS MCM TIMEOUT #Perodic Monitoring\n");
                                terminate_thread(server_fd);
                             
                           }
                            else if(n==0)
                            {
                              fprintf(stderr,"C00 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(5);
                            bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING W06 FPS 1 SECONDS MONITORING MCM RESPONSE\n");
                                   terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"W06 FPS MCM closed it's Socket connection\n");
                              terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              // printresp(r1);
                              write_shm(a1,r1); bzero(r1,sizeof(resp));
                            } 
                          } 
                
                    }

  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}

void* W06_sentinel_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       w6senQ.store = 0; w6senQ.retrieve = 0;
              for(;;)
              {
                   if((int)(w6senQ.store)>(int)(w6senQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) w6_senq_retrieve((int)w6senQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1 = &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                              //  if(!strcasecmp(c1->system_name,"sentinel"))
                             if((!strcasecmp(c1->system_name,"sentinel"))||(!strcasecmp(c1->system_name,"fiber_optics")))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD W06 sentinel MCM device\n"); }
                                    else
                                   { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                        // bzero(c1,sizeof(cmd));   
                                         
                                    }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  usleep(500000);
                                 bzero(r1,sizeof(resp)); 
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING W06 sentinel MCM RESPONSE\n");  
                                     terminate_thread(server_fd); }
                               else if(n==0)
                                {
                                  fprintf(stderr,"W06 sentinel MCM closed it's Socket connection\n");
                                   terminate_thread(server_fd);
                                }     
                            else
                              {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from SENTINEL THREAD SUCCESSFUL\n");
                               } 
                             w6senQ.retrieve++; 
                                             
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                       else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"W06");
                           strcpy(a1->CMD.system_name,"sentinel");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to W06 sentinel MCM MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING W06 Sentinel MCM RESPONSE\n"); terminate_thread(server_fd);  }
                            else if(n==0)
                            {
                              fprintf(stderr,"W06 sentinel MCM closed it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           else
                           {
                           
                                write_shm(a1,r1); 
                           } 
                         
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* W06_fiber_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
      char *tstamp;
     tstamp = malloc(25);
    
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       w6fiberQ.store = 0; w6fiberQ.retrieve = 0;
              for(;;)
              {
                    if((int)(w6fiberQ.store)>(int)(w6fiberQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD*) w6_fiberq_retrieve((int)w6fiberQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"fiber_optics"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to W06 FIBER OPTICS MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                       
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                    usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING W06 FIBER OPTICS MCM RESPONSE\n"); terminate_thread(server_fd); }
                                else if(n==0)
                                {
                                 fprintf(stderr,"W06 FIBER OPTICS MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              {
                                     printresp(r1);
                                     write_shm(a1,r1);                  
                                     fprintf(stderr," Writing to ONLINE from FIBER THREAD SUCCESSFUL\n");
                               } 
                            
                             w6fiberQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                      else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"W06");
                           strcpy(a1->CMD.system_name,"fiber_optics");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to W06 FIBER OPTICS MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING W06  FIBER OPTICS MCM RESPONSE\n");shutdown(server_fd,SHUT_RDWR);
                                     close(server_fd);
                                     pthread_exit(NULL);  }
                             else if(n==0)
                            {
                              fprintf(stderr,"W06 FIBER OPTICS MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           {
                             
                                write_shm(a1,r1);  
                            
                           } 
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}

void* W06_front_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
 
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
      char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
 
       w6frontQ.store = 0; w6frontQ.retrieve = 0;
              for(;;)
              {
                    if((int)(w6frontQ.store)>(int)(w6frontQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = ( ANT_CMD*) w6_frontq_retrieve((int)w6frontQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                         c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"front_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to W06 FRONT END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);  bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING W06 FRONT END MCM RESPONSE\n"); 
                                    terminate_thread(server_fd);}
                               else if(n==0)
                              {
                                fprintf(stderr,"W06 FRONT END MCM closed it's Socket connection\n");
                                 terminate_thread(server_fd);
                              }
                              else
                              { printresp(r1); write_shm(a1,r1);  }
                           
                             w6frontQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       
                       }
                     else
                         { // Periodic Monitoring in the background 
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"W06");
                           strcpy(a1->CMD.system_name,"front_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                           tstamp = tp(tstamp);
                           strcpy(a1->CMD.timestamp,tstamp);
                           c1 = &a1->CMD;
                              
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to W06 FRONT END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING W06 FRONT END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"W06 FRONT END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1);  }
                          
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* W06_backend_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   
     cmd *c1;
     c1 = malloc(sizeof(cmd));
   
        char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       w6backQ.store = 0; w6backQ.retrieve = 0;
              for(;;)
              {
                    if((int)(w6backQ.store)>(int)(w6backQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) w6_backq_retrieve((int)w6backQ.retrieve);
                        pthread_mutex_unlock(&lock);
                        
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"back_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to W06 BACK END MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING W06 BACK END MCM RESPONSE\n");
                                    terminate_thread(server_fd);}
                                else if(n==0)
                               {
                                 fprintf(stderr,"W06 BACK END MCM closed it's Socket connection\n");
                                  terminate_thread(server_fd);
                               } 
                              else
                              { printresp(r1);write_shm(a1,r1); } 
                           
                             w6backQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                      else
                         { // Periodic Monitoring in the background
                            bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"W06");
                           strcpy(a1->CMD.system_name,"back_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to W06 BACK END MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING W06 Back END MCM RESPONSE\n"); terminate_thread(server_fd); }
                             else if(n==0)
                            {
                              fprintf(stderr,"W06 BACK END MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            } 
                           else
                           { write_shm(a1,r1); }
                       
                         }
                    }
     free(a1);
  free(r1);
  free(c1);
   return NULL;
}


void* W06_self_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1= malloc(sizeof(ANT_CMD));
  
     cmd *c1;
     c1 = malloc(sizeof(cmd));
  
     char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  
       w6selfQ.store = 0; w6selfQ.retrieve = 0;
              for(;;)
              {
                    if((int)(w6selfQ.store)>(int)(w6selfQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       a1 = (ANT_CMD *) w6_selfq_retrieve((int)w6selfQ.retrieve);
                       pthread_mutex_unlock(&lock);
                       
                        tstamp = tp(tstamp);
                        strcpy(a1->CMD.timestamp,tstamp);
                        c1= &a1->CMD;
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"self_test"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1); bzero(c1,sizeof(cmd));
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                                     
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING W06  SELF SYSTEM  MCM RESPONSE\n"); 
                                     terminate_thread(server_fd); }
                              else if(n==0)
                            {
                              fprintf(stderr,"W06  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd); 
                            }
                              else
                              { write_shm(a1,r1); } 
                           
                             w6selfQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                     else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(cmd));
                           strcpy(a1->antenna_name,"W06");
                           strcpy(a1->CMD.system_name,"self_test");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to W06  SELF SYSTEM  MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                             sleep(1);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                            { fprintf(stderr," ERROR READING W06 Self Test MCM RESPONSE\n"); terminate_thread(server_fd);}
                             else if(n==0)
                            {
                              fprintf(stderr,"W06  SELF SYSTEM MCM closed it's Socket connection\n");
                               terminate_thread(server_fd);
                            }
                           else
                           { write_shm(a1,r1); } 
                           
                         }
                    }
  free(a1);
  free(r1);
  free(c1);
   return NULL;
}












