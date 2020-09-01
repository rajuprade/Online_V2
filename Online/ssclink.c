#include"ssclink.h"
#include"servo.h"
#include"servo_queue.h"
#include"socket.h"
#include"server.h"

void* C00_servo( void* parameters)
{    
     int server_fd;
     ssize_t n;

     SRVANT_CMD *a1;
     a1 = malloc(sizeof(SRVANT_CMD));
  
     servocmd *c1;
     c1 = malloc(sizeof(servocmd));
    
     servoresp *r1;
     r1 = malloc(sizeof(servoresp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       C00srvq.store = 0; C00srvq.retrieve = 0;
              for(;;)
              {
                    if((int)(C00srvq.store)>(int)(C00srvq.retrieve))
                     {
                       pthread_mutex_lock(&locks);
                       a1 = (SRVANT_CMD *) C00srv_retrieve((int)C00srvq.retrieve);
                       pthread_mutex_unlock(&locks);
                        tstamp = tp(tstamp);
                        strcpy(a1->SRVCMD.timestamp,tstamp);
                        c1 = &a1->SRVCMD;
                         if((servocmd *)c1 != (servocmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"servo"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C00 servo system\n");
                                         terminate_thread(server_fd);
                                     }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "C00 servo timeout\n");
                                         terminate_thread(server_fd);
                                      }
                               
                                      else
                                     { 
                                         printservocmd(c1);
                                         bzero(c1,sizeof(servocmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(2);
                                  bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING C00 servo Intermidate RESPONSE\n");
                                     terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing IMMEDIATE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                 sleep(2);
                                 bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING C00 servo FINAL RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing FINAL RESPONSE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                C00srvq.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                   /*   else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(servocmd));
                           strcpy(a1->antenna_name,"C00");
                           strcpy(a1->SRVCMD.system_name,"servo");
                           a1->SRVCMD.seq= 10;
                           strcpy(a1->SRVCMD.op_name,"mon");
                           a1->SRVCMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->SRVCMD.timestamp,tstamp);
                            c1 = &a1->SRVCMD;
                          
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                            {  fprintf(stderr," ERROR Sending CMD to C00 Servo system\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C00 Servo system #Perodic Monitoring\n");
                             
                           }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(1);
                            bzero(r1,sizeof(servoresp));
                            if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                           { fprintf(stderr," ERROR READING C00 Servo system RESPONSE\n");
                                     terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"C00 servo system it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              //write_shm(a1,r1); 
                            } 
                          } */
                
                    }
  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}

// C01 servo antenna thread

void* C01_servo( void* parameters)
{    
     int server_fd;
     ssize_t n;

     SRVANT_CMD *a1;
     a1 = malloc(sizeof(SRVANT_CMD));
  
     servocmd *c1;
     c1 = malloc(sizeof(servocmd));
    
     servoresp *r1;
     r1 = malloc(sizeof(servoresp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       C01srvq.store = 0; C01srvq.retrieve = 0;
              for(;;)
              {
                    if((int)(C01srvq.store)>(int)(C01srvq.retrieve))
                     {
                       pthread_mutex_lock(&locks);
                       a1 = (SRVANT_CMD *) C01srv_retrieve((int)C01srvq.retrieve);
                       pthread_mutex_unlock(&locks);
                        tstamp = tp(tstamp);
                        strcpy(a1->SRVCMD.timestamp,tstamp);
                        c1 = &a1->SRVCMD;
                         if((servocmd *)c1 != (servocmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"servo"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C01 servo system\n");
                                         terminate_thread(server_fd);
                                     }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "C01 servo timeout\n");
                                         terminate_thread(server_fd);
                                      }
                               
                                      else
                                     { 
                                         printservocmd(c1);
                                         bzero(c1,sizeof(servocmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(2);
                                  bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING C01 servo Intermidate RESPONSE\n");
                                     terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing IMMEDIATE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                 sleep(2);
                                 bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING C01 servo FINAL RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing FINAL RESPONSE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                C01srvq.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                   /*   else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(servocmd));
                           strcpy(a1->antenna_name,"C01");
                           strcpy(a1->SRVCMD.system_name,"servo");
                           a1->SRVCMD.seq= 10;
                           strcpy(a1->SRVCMD.op_name,"mon");
                           a1->SRVCMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->SRVCMD.timestamp,tstamp);
                            c1 = &a1->SRVCMD;
                          
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                            {  fprintf(stderr," ERROR Sending CMD to C01 Servo system\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C01 Servo system #Perodic Monitoring\n");
                             
                           }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(1);
                            bzero(r1,sizeof(servoresp));
                            if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                           { fprintf(stderr," ERROR READING C01 Servo system RESPONSE\n");
                                     terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"C01 servo system it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              //write_shm(a1,r1); 
                            } 
                          } */
                
                    }
  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}


// C02 servo antenna thread

void* C02_servo( void* parameters)
{    
     int server_fd;
     ssize_t n;

     SRVANT_CMD *a1;
     a1 = malloc(sizeof(SRVANT_CMD));
  
     servocmd *c1;
     c1 = malloc(sizeof(servocmd));
    
     servoresp *r1;
     r1 = malloc(sizeof(servoresp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       C02srvq.store = 0; C02srvq.retrieve = 0;
              for(;;)
              {
                    if((int)(C02srvq.store)>(int)(C02srvq.retrieve))
                     {
                       pthread_mutex_lock(&locks);
                       a1 = (SRVANT_CMD *) C02srv_retrieve((int)C02srvq.retrieve);
                       pthread_mutex_unlock(&locks);
                        tstamp = tp(tstamp);
                        strcpy(a1->SRVCMD.timestamp,tstamp);
                        c1 = &a1->SRVCMD;
                         if((servocmd *)c1 != (servocmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"servo"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C02 servo system\n");
                                         terminate_thread(server_fd);
                                     }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "C02 servo timeout\n");
                                         terminate_thread(server_fd);
                                      }
                               
                                      else
                                     { 
                                         printservocmd(c1);
                                         bzero(c1,sizeof(servocmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(2);
                                  bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING C02 servo Intermidate RESPONSE\n");
                                     terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing IMMEDIATE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                 sleep(2);
                                 bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING C02 servo FINAL RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing FINAL RESPONSE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                C02srvq.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                   /*   else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(servocmd));
                           strcpy(a1->antenna_name,"C02");
                           strcpy(a1->SRVCMD.system_name,"servo");
                           a1->SRVCMD.seq= 10;
                           strcpy(a1->SRVCMD.op_name,"mon");
                           a1->SRVCMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->SRVCMD.timestamp,tstamp);
                            c1 = &a1->SRVCMD;
                          
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                            {  fprintf(stderr," ERROR Sending CMD to C02 Servo system\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C02 Servo system #Perodic Monitoring\n");
                             
                           }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(1);
                            bzero(r1,sizeof(servoresp));
                            if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                           { fprintf(stderr," ERROR READING C02 Servo system RESPONSE\n");
                                     terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"C02 servo system it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              //write_shm(a1,r1); 
                            } 
                          } */
                
                    }
  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}

// C03 servo antenna thread

void* C03_servo( void* parameters)
{    
     int server_fd;
     ssize_t n;

     SRVANT_CMD *a1;
     a1 = malloc(sizeof(SRVANT_CMD));
  
     servocmd *c1;
     c1 = malloc(sizeof(servocmd));
    
     servoresp *r1;
     r1 = malloc(sizeof(servoresp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       C03srvq.store = 0; C03srvq.retrieve = 0;
              for(;;)
              {
                    if((int)(C03srvq.store)>(int)(C03srvq.retrieve))
                     {
                       pthread_mutex_lock(&locks);
                       a1 = (SRVANT_CMD *) C03srv_retrieve((int)C03srvq.retrieve);
                       pthread_mutex_unlock(&locks);
                        tstamp = tp(tstamp);
                        strcpy(a1->SRVCMD.timestamp,tstamp);
                        c1 = &a1->SRVCMD;
                         if((servocmd *)c1 != (servocmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"servo"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C03 servo system\n");
                                         terminate_thread(server_fd);
                                     }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "C03 servo timeout\n");
                                         terminate_thread(server_fd);
                                      }
                               
                                      else
                                     { 
                                         printservocmd(c1);
                                         bzero(c1,sizeof(servocmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(2);
                                  bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING C03 servo Intermidate RESPONSE\n");
                                     terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing IMMEDIATE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                 sleep(2);
                                 bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING C03 servo FINAL RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing FINAL RESPONSE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                C03srvq.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                   /*   else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(servocmd));
                           strcpy(a1->antenna_name,"C03");
                           strcpy(a1->SRVCMD.system_name,"servo");
                           a1->SRVCMD.seq= 10;
                           strcpy(a1->SRVCMD.op_name,"mon");
                           a1->SRVCMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->SRVCMD.timestamp,tstamp);
                            c1 = &a1->SRVCMD;
                          
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                            {  fprintf(stderr," ERROR Sending CMD to C03 Servo system\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C03 Servo system #Perodic Monitoring\n");
                             
                           }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(1);
                            bzero(r1,sizeof(servoresp));
                            if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                           { fprintf(stderr," ERROR READING C03 Servo system RESPONSE\n");
                                     terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"C03 servo system it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              //write_shm(a1,r1); 
                            } 
                          } */
                
                    }
  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}

// C04 servo antenna thread

void* C04_servo( void* parameters)
{    
     int server_fd;
     ssize_t n;

     SRVANT_CMD *a1;
     a1 = malloc(sizeof(SRVANT_CMD));
  
     servocmd *c1;
     c1 = malloc(sizeof(servocmd));
    
     servoresp *r1;
     r1 = malloc(sizeof(servoresp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       C04srvq.store = 0; C04srvq.retrieve = 0;
              for(;;)
              {
                    if((int)(C04srvq.store)>(int)(C04srvq.retrieve))
                     {
                       pthread_mutex_lock(&locks);
                       a1 = (SRVANT_CMD *) C04srv_retrieve((int)C04srvq.retrieve);
                       pthread_mutex_unlock(&locks);
                        tstamp = tp(tstamp);
                        strcpy(a1->SRVCMD.timestamp,tstamp);
                        c1 = &a1->SRVCMD;
                         if((servocmd *)c1 != (servocmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"servo"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C04 servo system\n");
                                         terminate_thread(server_fd);
                                     }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "C04 servo timeout\n");
                                         terminate_thread(server_fd);
                                      }
                               
                                      else
                                     { 
                                         printservocmd(c1);
                                         bzero(c1,sizeof(servocmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(2);
                                  bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING C04 servo Intermidate RESPONSE\n");
                                     terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing IMMEDIATE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                 sleep(2);
                                 bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING C04 servo FINAL RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing FINAL RESPONSE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                C04srvq.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                   /*   else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(servocmd));
                           strcpy(a1->antenna_name,"C04");
                           strcpy(a1->SRVCMD.system_name,"servo");
                           a1->SRVCMD.seq= 10;
                           strcpy(a1->SRVCMD.op_name,"mon");
                           a1->SRVCMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->SRVCMD.timestamp,tstamp);
                            c1 = &a1->SRVCMD;
                          
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                            {  fprintf(stderr," ERROR Sending CMD to C04 Servo system\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C04 Servo system #Perodic Monitoring\n");
                             
                           }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(1);
                            bzero(r1,sizeof(servoresp));
                            if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                           { fprintf(stderr," ERROR READING C04 Servo system RESPONSE\n");
                                     terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"C04 servo system it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              //write_shm(a1,r1); 
                            } 
                          } */
                
                    }
  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}

// C05 servo antenna thread

void* C05_servo( void* parameters)
{    
     int server_fd;
     ssize_t n;

     SRVANT_CMD *a1;
     a1 = malloc(sizeof(SRVANT_CMD));
  
     servocmd *c1;
     c1 = malloc(sizeof(servocmd));
    
     servoresp *r1;
     r1 = malloc(sizeof(servoresp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       C05srvq.store = 0; C05srvq.retrieve = 0;
              for(;;)
              {
                    if((int)(C05srvq.store)>(int)(C05srvq.retrieve))
                     {
                       pthread_mutex_lock(&locks);
                       a1 = (SRVANT_CMD *) C05srv_retrieve((int)C05srvq.retrieve);
                       pthread_mutex_unlock(&locks);
                        tstamp = tp(tstamp);
                        strcpy(a1->SRVCMD.timestamp,tstamp);
                        c1 = &a1->SRVCMD;
                         if((servocmd *)c1 != (servocmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"servo"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C05 servo system\n");
                                         terminate_thread(server_fd);
                                     }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "C05 servo timeout\n");
                                         terminate_thread(server_fd);
                                      }
                               
                                      else
                                     { 
                                         printservocmd(c1);
                                         bzero(c1,sizeof(servocmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(2);
                                  bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING C05 servo Intermidate RESPONSE\n");
                                     terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing IMMEDIATE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                 sleep(2);
                                 bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING C05 servo FINAL RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing FINAL RESPONSE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                C05srvq.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                   /*   else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(servocmd));
                           strcpy(a1->antenna_name,"C05");
                           strcpy(a1->SRVCMD.system_name,"servo");
                           a1->SRVCMD.seq= 10;
                           strcpy(a1->SRVCMD.op_name,"mon");
                           a1->SRVCMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->SRVCMD.timestamp,tstamp);
                            c1 = &a1->SRVCMD;
                          
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                            {  fprintf(stderr," ERROR Sending CMD to C05 Servo system\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C05 Servo system #Perodic Monitoring\n");
                             
                           }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(1);
                            bzero(r1,sizeof(servoresp));
                            if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                           { fprintf(stderr," ERROR READING C05 Servo system RESPONSE\n");
                                     terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"C05 servo system it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              //write_shm(a1,r1); 
                            } 
                          } */
                
                    }
  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}

// C06 servo antenna thread

void* C06_servo( void* parameters)
{    
     int server_fd;
     ssize_t n;

     SRVANT_CMD *a1;
     a1 = malloc(sizeof(SRVANT_CMD));
  
     servocmd *c1;
     c1 = malloc(sizeof(servocmd));
    
     servoresp *r1;
     r1 = malloc(sizeof(servoresp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       C06srvq.store = 0; C06srvq.retrieve = 0;
              for(;;)
              {
                    if((int)(C06srvq.store)>(int)(C06srvq.retrieve))
                     {
                       pthread_mutex_lock(&locks);
                       a1 = (SRVANT_CMD *) C06srv_retrieve((int)C06srvq.retrieve);
                       pthread_mutex_unlock(&locks);
                        tstamp = tp(tstamp);
                        strcpy(a1->SRVCMD.timestamp,tstamp);
                        c1 = &a1->SRVCMD;
                         if((servocmd *)c1 != (servocmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"servo"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C06 servo system\n");
                                         terminate_thread(server_fd);
                                     }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "C06 servo timeout\n");
                                         terminate_thread(server_fd);
                                      }
                               
                                      else
                                     { 
                                         printservocmd(c1);
                                         bzero(c1,sizeof(servocmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(2);
                                  bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING C06 servo Intermidate RESPONSE\n");
                                     terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing IMMEDIATE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                 sleep(2);
                                 bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING C06 servo FINAL RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing FINAL RESPONSE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                C06srvq.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                   /*   else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(servocmd));
                           strcpy(a1->antenna_name,"C06");
                           strcpy(a1->SRVCMD.system_name,"servo");
                           a1->SRVCMD.seq= 10;
                           strcpy(a1->SRVCMD.op_name,"mon");
                           a1->SRVCMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->SRVCMD.timestamp,tstamp);
                            c1 = &a1->SRVCMD;
                          
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                            {  fprintf(stderr," ERROR Sending CMD to C06 Servo system\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C06 Servo system #Perodic Monitoring\n");
                             
                           }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(1);
                            bzero(r1,sizeof(servoresp));
                            if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                           { fprintf(stderr," ERROR READING C06 Servo system RESPONSE\n");
                                     terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"C06 servo system it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              //write_shm(a1,r1); 
                            } 
                          } */
                
                    }
  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}

// C08 servo antenna thread

void* C08_servo( void* parameters)
{    
     int server_fd;
     ssize_t n;

     SRVANT_CMD *a1;
     a1 = malloc(sizeof(SRVANT_CMD));
  
     servocmd *c1;
     c1 = malloc(sizeof(servocmd));
    
     servoresp *r1;
     r1 = malloc(sizeof(servoresp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       C08srvq.store = 0; C08srvq.retrieve = 0;
              for(;;)
              {
                    if((int)(C08srvq.store)>(int)(C08srvq.retrieve))
                     {
                       pthread_mutex_lock(&locks);
                       a1 = (SRVANT_CMD *) C08srv_retrieve((int)C08srvq.retrieve);
                       pthread_mutex_unlock(&locks);
                        tstamp = tp(tstamp);
                        strcpy(a1->SRVCMD.timestamp,tstamp);
                        c1 = &a1->SRVCMD;
                         if((servocmd *)c1 != (servocmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"servo"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C08 servo system\n");
                                         terminate_thread(server_fd);
                                     }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "C08 servo timeout\n");
                                         terminate_thread(server_fd);
                                      }
                               
                                      else
                                     { 
                                         printservocmd(c1);
                                         bzero(c1,sizeof(servocmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(2);
                                  bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING C08 servo Intermidate RESPONSE\n");
                                     terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing IMMEDIATE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                 sleep(2);
                                 bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING C08 servo FINAL RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing FINAL RESPONSE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                C08srvq.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                   /*   else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(servocmd));
                           strcpy(a1->antenna_name,"C08");
                           strcpy(a1->SRVCMD.system_name,"servo");
                           a1->SRVCMD.seq= 10;
                           strcpy(a1->SRVCMD.op_name,"mon");
                           a1->SRVCMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->SRVCMD.timestamp,tstamp);
                            c1 = &a1->SRVCMD;
                          
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                            {  fprintf(stderr," ERROR Sending CMD to C08 Servo system\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C08 Servo system #Perodic Monitoring\n");
                             
                           }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(1);
                            bzero(r1,sizeof(servoresp));
                            if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                           { fprintf(stderr," ERROR READING C08 Servo system RESPONSE\n");
                                     terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"C08 servo system it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              //write_shm(a1,r1); 
                            } 
                          } */
                
                    }
  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}

// C09 servo antenna thread

void* C09_servo( void* parameters)
{    
     int server_fd;
     ssize_t n;

     SRVANT_CMD *a1;
     a1 = malloc(sizeof(SRVANT_CMD));
  
     servocmd *c1;
     c1 = malloc(sizeof(servocmd));
    
     servoresp *r1;
     r1 = malloc(sizeof(servoresp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       C09srvq.store = 0; C09srvq.retrieve = 0;
              for(;;)
              {
                    if((int)(C09srvq.store)>(int)(C09srvq.retrieve))
                     {
                       pthread_mutex_lock(&locks);
                       a1 = (SRVANT_CMD *) C09srv_retrieve((int)C09srvq.retrieve);
                       pthread_mutex_unlock(&locks);
                        tstamp = tp(tstamp);
                        strcpy(a1->SRVCMD.timestamp,tstamp);
                        c1 = &a1->SRVCMD;
                         if((servocmd *)c1 != (servocmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"servo"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C09 servo system\n");
                                         terminate_thread(server_fd);
                                     }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "C09 servo timeout\n");
                                         terminate_thread(server_fd);
                                      }
                               
                                      else
                                     { 
                                         printservocmd(c1);
                                         bzero(c1,sizeof(servocmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(2);
                                  bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING C09 servo Intermidate RESPONSE\n");
                                     terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing IMMEDIATE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                 sleep(2);
                                 bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING C09 servo FINAL RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing FINAL RESPONSE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                C09srvq.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                   /*   else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(servocmd));
                           strcpy(a1->antenna_name,"C09");
                           strcpy(a1->SRVCMD.system_name,"servo");
                           a1->SRVCMD.seq= 10;
                           strcpy(a1->SRVCMD.op_name,"mon");
                           a1->SRVCMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->SRVCMD.timestamp,tstamp);
                            c1 = &a1->SRVCMD;
                          
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                            {  fprintf(stderr," ERROR Sending CMD to C09 Servo system\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C09 Servo system #Perodic Monitoring\n");
                             
                           }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(1);
                            bzero(r1,sizeof(servoresp));
                            if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                           { fprintf(stderr," ERROR READING C09 Servo system RESPONSE\n");
                                     terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"C09 servo system it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              //write_shm(a1,r1); 
                            } 
                          } */
                
                    }
  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}

// C10 servo antenna thread

void* C10_servo( void* parameters)
{    
     int server_fd;
     ssize_t n;

     SRVANT_CMD *a1;
     a1 = malloc(sizeof(SRVANT_CMD));
  
     servocmd *c1;
     c1 = malloc(sizeof(servocmd));
    
     servoresp *r1;
     r1 = malloc(sizeof(servoresp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       C10srvq.store = 0; C10srvq.retrieve = 0;
              for(;;)
              {
                    if((int)(C10srvq.store)>(int)(C10srvq.retrieve))
                     {
                       pthread_mutex_lock(&locks);
                       a1 = (SRVANT_CMD *) C10srv_retrieve((int)C10srvq.retrieve);
                       pthread_mutex_unlock(&locks);
                        tstamp = tp(tstamp);
                        strcpy(a1->SRVCMD.timestamp,tstamp);
                        c1 = &a1->SRVCMD;
                         if((servocmd *)c1 != (servocmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"servo"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C10 servo system\n");
                                         terminate_thread(server_fd);
                                     }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "C10 servo timeout\n");
                                         terminate_thread(server_fd);
                                      }
                               
                                      else
                                     { 
                                         printservocmd(c1);
                                         bzero(c1,sizeof(servocmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(2);
                                  bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING C10 servo Intermidate RESPONSE\n");
                                     terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing IMMEDIATE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                 sleep(2);
                                 bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING C10 servo FINAL RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing FINAL RESPONSE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                C10srvq.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                   /*   else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(servocmd));
                           strcpy(a1->antenna_name,"C10");
                           strcpy(a1->SRVCMD.system_name,"servo");
                           a1->SRVCMD.seq= 10;
                           strcpy(a1->SRVCMD.op_name,"mon");
                           a1->SRVCMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->SRVCMD.timestamp,tstamp);
                            c1 = &a1->SRVCMD;
                          
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                            {  fprintf(stderr," ERROR Sending CMD to C10 Servo system\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C10 Servo system #Perodic Monitoring\n");
                             
                           }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(1);
                            bzero(r1,sizeof(servoresp));
                            if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                           { fprintf(stderr," ERROR READING C10 Servo system RESPONSE\n");
                                     terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"C10 servo system it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              //write_shm(a1,r1); 
                            } 
                          } */
                
                    }
  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}

// C11 servo antenna thread

void* C11_servo( void* parameters)
{    
     int server_fd;
     ssize_t n;

     SRVANT_CMD *a1;
     a1 = malloc(sizeof(SRVANT_CMD));
  
     servocmd *c1;
     c1 = malloc(sizeof(servocmd));
    
     servoresp *r1;
     r1 = malloc(sizeof(servoresp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       C11srvq.store = 0; C11srvq.retrieve = 0;
              for(;;)
              {
                    if((int)(C11srvq.store)>(int)(C11srvq.retrieve))
                     {
                       pthread_mutex_lock(&locks);
                       a1 = (SRVANT_CMD *) C11srv_retrieve((int)C11srvq.retrieve);
                       pthread_mutex_unlock(&locks);
                        tstamp = tp(tstamp);
                        strcpy(a1->SRVCMD.timestamp,tstamp);
                        c1 = &a1->SRVCMD;
                         if((servocmd *)c1 != (servocmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"servo"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C11 servo system\n");
                                         terminate_thread(server_fd);
                                     }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "C11 servo timeout\n");
                                         terminate_thread(server_fd);
                                      }
                               
                                      else
                                     { 
                                         printservocmd(c1);
                                         bzero(c1,sizeof(servocmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(2);
                                  bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING C11 servo Intermidate RESPONSE\n");
                                     terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing IMMEDIATE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                 sleep(2);
                                 bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING C11 servo FINAL RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing FINAL RESPONSE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                C11srvq.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                   /*   else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(servocmd));
                           strcpy(a1->antenna_name,"C11");
                           strcpy(a1->SRVCMD.system_name,"servo");
                           a1->SRVCMD.seq= 10;
                           strcpy(a1->SRVCMD.op_name,"mon");
                           a1->SRVCMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->SRVCMD.timestamp,tstamp);
                            c1 = &a1->SRVCMD;
                          
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                            {  fprintf(stderr," ERROR Sending CMD to C11 Servo system\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C11 Servo system #Perodic Monitoring\n");
                             
                           }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(1);
                            bzero(r1,sizeof(servoresp));
                            if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                           { fprintf(stderr," ERROR READING C11 Servo system RESPONSE\n");
                                     terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"C11 servo system it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              //write_shm(a1,r1); 
                            } 
                          } */
                
                    }
  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}

// C12 servo antenna thread

void* C12_servo( void* parameters)
{    
     int server_fd;
     ssize_t n;

     SRVANT_CMD *a1;
     a1 = malloc(sizeof(SRVANT_CMD));
  
     servocmd *c1;
     c1 = malloc(sizeof(servocmd));
    
     servoresp *r1;
     r1 = malloc(sizeof(servoresp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       C12srvq.store = 0; C12srvq.retrieve = 0;
              for(;;)
              {
                    if((int)(C12srvq.store)>(int)(C12srvq.retrieve))
                     {
                       pthread_mutex_lock(&locks);
                       a1 = (SRVANT_CMD *) C12srv_retrieve((int)C12srvq.retrieve);
                       pthread_mutex_unlock(&locks);
                        tstamp = tp(tstamp);
                        strcpy(a1->SRVCMD.timestamp,tstamp);
                        c1 = &a1->SRVCMD;
                         if((servocmd *)c1 != (servocmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"servo"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C12 servo system\n");
                                         terminate_thread(server_fd);
                                     }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "C12 servo timeout\n");
                                         terminate_thread(server_fd);
                                      }
                               
                                      else
                                     { 
                                         printservocmd(c1);
                                         bzero(c1,sizeof(servocmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(2);
                                  bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING C12 servo Intermidate RESPONSE\n");
                                     terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing IMMEDIATE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                 sleep(2);
                                 bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING C12 servo FINAL RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing FINAL RESPONSE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                C12srvq.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                   /*   else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(servocmd));
                           strcpy(a1->antenna_name,"C12");
                           strcpy(a1->SRVCMD.system_name,"servo");
                           a1->SRVCMD.seq= 10;
                           strcpy(a1->SRVCMD.op_name,"mon");
                           a1->SRVCMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->SRVCMD.timestamp,tstamp);
                            c1 = &a1->SRVCMD;
                          
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                            {  fprintf(stderr," ERROR Sending CMD to C12 Servo system\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C12 Servo system #Perodic Monitoring\n");
                             
                           }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(1);
                            bzero(r1,sizeof(servoresp));
                            if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                           { fprintf(stderr," ERROR READING C12 Servo system RESPONSE\n");
                                     terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"C12 servo system it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              //write_shm(a1,r1); 
                            } 
                          } */
                
                    }
  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}

// C13 servo antenna thread

void* C13_servo( void* parameters)
{    
     int server_fd;
     ssize_t n;

     SRVANT_CMD *a1;
     a1 = malloc(sizeof(SRVANT_CMD));
  
     servocmd *c1;
     c1 = malloc(sizeof(servocmd));
    
     servoresp *r1;
     r1 = malloc(sizeof(servoresp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       C13srvq.store = 0; C13srvq.retrieve = 0;
              for(;;)
              {
                    if((int)(C13srvq.store)>(int)(C13srvq.retrieve))
                     {
                       pthread_mutex_lock(&locks);
                       a1 = (SRVANT_CMD *) C13srv_retrieve((int)C13srvq.retrieve);
                       pthread_mutex_unlock(&locks);
                        tstamp = tp(tstamp);
                        strcpy(a1->SRVCMD.timestamp,tstamp);
                        c1 = &a1->SRVCMD;
                         if((servocmd *)c1 != (servocmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"servo"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C13 servo system\n");
                                         terminate_thread(server_fd);
                                     }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "C13 servo timeout\n");
                                         terminate_thread(server_fd);
                                      }
                               
                                      else
                                     { 
                                         printservocmd(c1);
                                         bzero(c1,sizeof(servocmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(2);
                                  bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING C13 servo Intermidate RESPONSE\n");
                                     terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing IMMEDIATE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                 sleep(2);
                                 bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING C13 servo FINAL RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing FINAL RESPONSE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                C13srvq.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                   /*   else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(servocmd));
                           strcpy(a1->antenna_name,"C13");
                           strcpy(a1->SRVCMD.system_name,"servo");
                           a1->SRVCMD.seq= 10;
                           strcpy(a1->SRVCMD.op_name,"mon");
                           a1->SRVCMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->SRVCMD.timestamp,tstamp);
                            c1 = &a1->SRVCMD;
                          
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                            {  fprintf(stderr," ERROR Sending CMD to C13 Servo system\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C13 Servo system #Perodic Monitoring\n");
                             
                           }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(1);
                            bzero(r1,sizeof(servoresp));
                            if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                           { fprintf(stderr," ERROR READING C13 Servo system RESPONSE\n");
                                     terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"C13 servo system it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              //write_shm(a1,r1); 
                            } 
                          } */
                
                    }
  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}

// C14 servo antenna thread

void* C14_servo( void* parameters)
{    
     int server_fd;
     ssize_t n;

     SRVANT_CMD *a1;
     a1 = malloc(sizeof(SRVANT_CMD));
  
     servocmd *c1;
     c1 = malloc(sizeof(servocmd));
    
     servoresp *r1;
     r1 = malloc(sizeof(servoresp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       C14srvq.store = 0; C14srvq.retrieve = 0;
              for(;;)
              {
                    if((int)(C14srvq.store)>(int)(C14srvq.retrieve))
                     {
                       pthread_mutex_lock(&locks);
                       a1 = (SRVANT_CMD *) C14srv_retrieve((int)C14srvq.retrieve);
                       pthread_mutex_unlock(&locks);
                        tstamp = tp(tstamp);
                        strcpy(a1->SRVCMD.timestamp,tstamp);
                        c1 = &a1->SRVCMD;
                         if((servocmd *)c1 != (servocmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"servo"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                                     {  fprintf(stderr," ERROR Sending CMD to C14 servo system\n");
                                         terminate_thread(server_fd);
                                     }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "C14 servo timeout\n");
                                         terminate_thread(server_fd);
                                      }
                               
                                      else
                                     { 
                                         printservocmd(c1);
                                         bzero(c1,sizeof(servocmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(2);
                                  bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING C14 servo Intermidate RESPONSE\n");
                                     terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing IMMEDIATE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                 sleep(2);
                                 bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING C14 servo FINAL RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing FINAL RESPONSE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                C14srvq.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                   /*   else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(servocmd));
                           strcpy(a1->antenna_name,"C14");
                           strcpy(a1->SRVCMD.system_name,"servo");
                           a1->SRVCMD.seq= 10;
                           strcpy(a1->SRVCMD.op_name,"mon");
                           a1->SRVCMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->SRVCMD.timestamp,tstamp);
                            c1 = &a1->SRVCMD;
                          
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                            {  fprintf(stderr," ERROR Sending CMD to C14 Servo system\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C14 Servo system #Perodic Monitoring\n");
                             
                           }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(1);
                            bzero(r1,sizeof(servoresp));
                            if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                           { fprintf(stderr," ERROR READING C14 Servo system RESPONSE\n");
                                     terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"C14 servo system it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              //write_shm(a1,r1); 
                            } 
                          } */
                
                    }
  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}

// S01 servo antenna thread

void* S01_servo( void* parameters)
{    
     int server_fd;
     ssize_t n;

     SRVANT_CMD *a1;
     a1 = malloc(sizeof(SRVANT_CMD));
  
     servocmd *c1;
     c1 = malloc(sizeof(servocmd));
    
     servoresp *r1;
     r1 = malloc(sizeof(servoresp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       S01srvq.store = 0; S01srvq.retrieve = 0;
              for(;;)
              {
                    if((int)(S01srvq.store)>(int)(S01srvq.retrieve))
                     {
                       pthread_mutex_lock(&locks);
                       a1 = (SRVANT_CMD *) S01srv_retrieve((int)S01srvq.retrieve);
                       pthread_mutex_unlock(&locks);
                        tstamp = tp(tstamp);
                        strcpy(a1->SRVCMD.timestamp,tstamp);
                        c1 = &a1->SRVCMD;
                         if((servocmd *)c1 != (servocmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"servo"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                                     {  fprintf(stderr," ERROR Sending CMD to S01 servo system\n");
                                         terminate_thread(server_fd);
                                     }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "S01 servo timeout\n");
                                         terminate_thread(server_fd);
                                      }
                               
                                      else
                                     { 
                                         printservocmd(c1);
                                         bzero(c1,sizeof(servocmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(2);
                                  bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING S01 servo Intermidate RESPONSE\n");
                                     terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing IMMEDIATE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                 sleep(2);
                                 bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING S01 servo FINAL RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing FINAL RESPONSE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                S01srvq.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                   /*   else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(servocmd));
                           strcpy(a1->antenna_name,"S01");
                           strcpy(a1->SRVCMD.system_name,"servo");
                           a1->SRVCMD.seq= 10;
                           strcpy(a1->SRVCMD.op_name,"mon");
                           a1->SRVCMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->SRVCMD.timestamp,tstamp);
                            c1 = &a1->SRVCMD;
                          
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                            {  fprintf(stderr," ERROR Sending CMD to S01 Servo system\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "S01 Servo system #Perodic Monitoring\n");
                             
                           }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(1);
                            bzero(r1,sizeof(servoresp));
                            if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                           { fprintf(stderr," ERROR READING S01 Servo system RESPONSE\n");
                                     terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"S01 servo system it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              //write_shm(a1,r1); 
                            } 
                          } */
                
                    }
  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}


// S02 servo antenna thread

void* S02_servo( void* parameters)
{    
     int server_fd;
     ssize_t n;

     SRVANT_CMD *a1;
     a1 = malloc(sizeof(SRVANT_CMD));
  
     servocmd *c1;
     c1 = malloc(sizeof(servocmd));
    
     servoresp *r1;
     r1 = malloc(sizeof(servoresp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       S02srvq.store = 0; S02srvq.retrieve = 0;
              for(;;)
              {
                    if((int)(S02srvq.store)>(int)(S02srvq.retrieve))
                     {
                       pthread_mutex_lock(&locks);
                       a1 = (SRVANT_CMD *) S02srv_retrieve((int)S02srvq.retrieve);
                       pthread_mutex_unlock(&locks);
                        tstamp = tp(tstamp);
                        strcpy(a1->SRVCMD.timestamp,tstamp);
                        c1 = &a1->SRVCMD;
                         if((servocmd *)c1 != (servocmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"servo"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                                     {  fprintf(stderr," ERROR Sending CMD to S02 servo system\n");
                                         terminate_thread(server_fd);
                                     }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "S02 servo timeout\n");
                                         terminate_thread(server_fd);
                                      }
                               
                                      else
                                     { 
                                         printservocmd(c1);
                                         bzero(c1,sizeof(servocmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(2);
                                  bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING S02 servo Intermidate RESPONSE\n");
                                     terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing IMMEDIATE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                 sleep(2);
                                 bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING S02 servo FINAL RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing FINAL RESPONSE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                S02srvq.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                   /*   else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(servocmd));
                           strcpy(a1->antenna_name,"S02");
                           strcpy(a1->SRVCMD.system_name,"servo");
                           a1->SRVCMD.seq= 10;
                           strcpy(a1->SRVCMD.op_name,"mon");
                           a1->SRVCMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->SRVCMD.timestamp,tstamp);
                            c1 = &a1->SRVCMD;
                          
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                            {  fprintf(stderr," ERROR Sending CMD to S02 Servo system\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "S02 Servo system #Perodic Monitoring\n");
                             
                           }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(1);
                            bzero(r1,sizeof(servoresp));
                            if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                           { fprintf(stderr," ERROR READING S02 Servo system RESPONSE\n");
                                     terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"S02 servo system it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              //write_shm(a1,r1); 
                            } 
                          } */
                
                    }
  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}


// S03 servo antenna thread

void* S03_servo( void* parameters)
{    
     int server_fd;
     ssize_t n;

     SRVANT_CMD *a1;
     a1 = malloc(sizeof(SRVANT_CMD));
  
     servocmd *c1;
     c1 = malloc(sizeof(servocmd));
    
     servoresp *r1;
     r1 = malloc(sizeof(servoresp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       S03srvq.store = 0; S03srvq.retrieve = 0;
              for(;;)
              {
                    if((int)(S03srvq.store)>(int)(S03srvq.retrieve))
                     {
                       pthread_mutex_lock(&locks);
                       a1 = (SRVANT_CMD *) S03srv_retrieve((int)S03srvq.retrieve);
                       pthread_mutex_unlock(&locks);
                        tstamp = tp(tstamp);
                        strcpy(a1->SRVCMD.timestamp,tstamp);
                        c1 = &a1->SRVCMD;
                         if((servocmd *)c1 != (servocmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"servo"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                                     {  fprintf(stderr," ERROR Sending CMD to S03 servo system\n");
                                         terminate_thread(server_fd);
                                     }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "S03 servo timeout\n");
                                         terminate_thread(server_fd);
                                      }
                               
                                      else
                                     { 
                                         printservocmd(c1);
                                         bzero(c1,sizeof(servocmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(2);
                                  bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING S03 servo Intermidate RESPONSE\n");
                                     terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing IMMEDIATE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                 sleep(2);
                                 bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING S03 servo FINAL RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing FINAL RESPONSE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                S03srvq.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                   /*   else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(servocmd));
                           strcpy(a1->antenna_name,"S03");
                           strcpy(a1->SRVCMD.system_name,"servo");
                           a1->SRVCMD.seq= 10;
                           strcpy(a1->SRVCMD.op_name,"mon");
                           a1->SRVCMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->SRVCMD.timestamp,tstamp);
                            c1 = &a1->SRVCMD;
                          
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                            {  fprintf(stderr," ERROR Sending CMD to S03 Servo system\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "S03 Servo system #Perodic Monitoring\n");
                             
                           }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(1);
                            bzero(r1,sizeof(servoresp));
                            if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                           { fprintf(stderr," ERROR READING S03 Servo system RESPONSE\n");
                                     terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"S03 servo system it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              //write_shm(a1,r1); 
                            } 
                          } */
                
                    }
  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}


// S04 servo antenna thread

void* S04_servo( void* parameters)
{    
     int server_fd;
     ssize_t n;

     SRVANT_CMD *a1;
     a1 = malloc(sizeof(SRVANT_CMD));
  
     servocmd *c1;
     c1 = malloc(sizeof(servocmd));
    
     servoresp *r1;
     r1 = malloc(sizeof(servoresp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       S04srvq.store = 0; S04srvq.retrieve = 0;
              for(;;)
              {
                    if((int)(S04srvq.store)>(int)(S04srvq.retrieve))
                     {
                       pthread_mutex_lock(&locks);
                       a1 = (SRVANT_CMD *) S04srv_retrieve((int)S04srvq.retrieve);
                       pthread_mutex_unlock(&locks);
                        tstamp = tp(tstamp);
                        strcpy(a1->SRVCMD.timestamp,tstamp);
                        c1 = &a1->SRVCMD;
                         if((servocmd *)c1 != (servocmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"servo"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                                     {  fprintf(stderr," ERROR Sending CMD to S04 servo system\n");
                                         terminate_thread(server_fd);
                                     }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "S04 servo timeout\n");
                                         terminate_thread(server_fd);
                                      }
                               
                                      else
                                     { 
                                         printservocmd(c1);
                                         bzero(c1,sizeof(servocmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(2);
                                  bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING S04 servo Intermidate RESPONSE\n");
                                     terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing IMMEDIATE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                 sleep(2);
                                 bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING S04 servo FINAL RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing FINAL RESPONSE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                S04srvq.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                   /*   else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(servocmd));
                           strcpy(a1->antenna_name,"S04");
                           strcpy(a1->SRVCMD.system_name,"servo");
                           a1->SRVCMD.seq= 10;
                           strcpy(a1->SRVCMD.op_name,"mon");
                           a1->SRVCMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->SRVCMD.timestamp,tstamp);
                            c1 = &a1->SRVCMD;
                          
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                            {  fprintf(stderr," ERROR Sending CMD to S04 Servo system\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "S04 Servo system #Perodic Monitoring\n");
                             
                           }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(1);
                            bzero(r1,sizeof(servoresp));
                            if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                           { fprintf(stderr," ERROR READING S04 Servo system RESPONSE\n");
                                     terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"S04 servo system it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              //write_shm(a1,r1); 
                            } 
                          } */
                
                    }
  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}



// S06 servo antenna thread

void* S06_servo( void* parameters)
{    
     int server_fd;
     ssize_t n;

     SRVANT_CMD *a1;
     a1 = malloc(sizeof(SRVANT_CMD));
  
     servocmd *c1;
     c1 = malloc(sizeof(servocmd));
    
     servoresp *r1;
     r1 = malloc(sizeof(servoresp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       S06srvq.store = 0; S06srvq.retrieve = 0;
              for(;;)
              {
                    if((int)(S06srvq.store)>(int)(S06srvq.retrieve))
                     {
                       pthread_mutex_lock(&locks);
                       a1 = (SRVANT_CMD *) S06srv_retrieve((int)S06srvq.retrieve);
                       pthread_mutex_unlock(&locks);
                        tstamp = tp(tstamp);
                        strcpy(a1->SRVCMD.timestamp,tstamp);
                        c1 = &a1->SRVCMD;
                         if((servocmd *)c1 != (servocmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"servo"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                                     {  fprintf(stderr," ERROR Sending CMD to S06 servo system\n");
                                         terminate_thread(server_fd);
                                     }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "S06 servo timeout\n");
                                         terminate_thread(server_fd);
                                      }
                               
                                      else
                                     { 
                                         printservocmd(c1);
                                         bzero(c1,sizeof(servocmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(2);
                                  bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING S06 servo Intermidate RESPONSE\n");
                                     terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing IMMEDIATE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                 sleep(2);
                                 bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING S06 servo FINAL RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing FINAL RESPONSE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                S06srvq.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                   /*   else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(servocmd));
                           strcpy(a1->antenna_name,"S06");
                           strcpy(a1->SRVCMD.system_name,"servo");
                           a1->SRVCMD.seq= 10;
                           strcpy(a1->SRVCMD.op_name,"mon");
                           a1->SRVCMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->SRVCMD.timestamp,tstamp);
                            c1 = &a1->SRVCMD;
                          
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                            {  fprintf(stderr," ERROR Sending CMD to S06 Servo system\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "S06 Servo system #Perodic Monitoring\n");
                             
                           }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(1);
                            bzero(r1,sizeof(servoresp));
                            if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                           { fprintf(stderr," ERROR READING S06 Servo system RESPONSE\n");
                                     terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"S06 servo system it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              //write_shm(a1,r1); 
                            } 
                          } */
                
                    }
  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}


// E02 servo antenna thread

void* E02_servo( void* parameters)
{    
     int server_fd;
     ssize_t n;

     SRVANT_CMD *a1;
     a1 = malloc(sizeof(SRVANT_CMD));
  
     servocmd *c1;
     c1 = malloc(sizeof(servocmd));
    
     servoresp *r1;
     r1 = malloc(sizeof(servoresp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       E02srvq.store = 0; E02srvq.retrieve = 0;
              for(;;)
              {
                    if((int)(E02srvq.store)>(int)(E02srvq.retrieve))
                     {
                       pthread_mutex_lock(&locks);
                       a1 = (SRVANT_CMD *) E02srv_retrieve((int)E02srvq.retrieve);
                       pthread_mutex_unlock(&locks);
                        tstamp = tp(tstamp);
                        strcpy(a1->SRVCMD.timestamp,tstamp);
                        c1 = &a1->SRVCMD;
                         if((servocmd *)c1 != (servocmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"servo"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                                     {  fprintf(stderr," ERROR Sending CMD to E02 servo system\n");
                                         terminate_thread(server_fd);
                                     }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "E02 servo timeout\n");
                                         terminate_thread(server_fd);
                                      }
                               
                                      else
                                     { 
                                         printservocmd(c1);
                                         bzero(c1,sizeof(servocmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(2);
                                  bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING E02 servo Intermidate RESPONSE\n");
                                     terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing IMMEDIATE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                 sleep(2);
                                 bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING E02 servo FINAL RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing FINAL RESPONSE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                E02srvq.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                   /*   else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(servocmd));
                           strcpy(a1->antenna_name,"E02");
                           strcpy(a1->SRVCMD.system_name,"servo");
                           a1->SRVCMD.seq= 10;
                           strcpy(a1->SRVCMD.op_name,"mon");
                           a1->SRVCMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->SRVCMD.timestamp,tstamp);
                            c1 = &a1->SRVCMD;
                          
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                            {  fprintf(stderr," ERROR Sending CMD to E02 Servo system\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "E02 Servo system #Perodic Monitoring\n");
                             
                           }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(1);
                            bzero(r1,sizeof(servoresp));
                            if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                           { fprintf(stderr," ERROR READING E02 Servo system RESPONSE\n");
                                     terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"E02 servo system it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              //write_shm(a1,r1); 
                            } 
                          } */
                
                    }
  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}


// E03 servo antenna thread

void* E03_servo( void* parameters)
{    
     int server_fd;
     ssize_t n;

     SRVANT_CMD *a1;
     a1 = malloc(sizeof(SRVANT_CMD));
  
     servocmd *c1;
     c1 = malloc(sizeof(servocmd));
    
     servoresp *r1;
     r1 = malloc(sizeof(servoresp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       E03srvq.store = 0; E03srvq.retrieve = 0;
              for(;;)
              {
                    if((int)(E03srvq.store)>(int)(E03srvq.retrieve))
                     {
                       pthread_mutex_lock(&locks);
                       a1 = (SRVANT_CMD *) E03srv_retrieve((int)E03srvq.retrieve);
                       pthread_mutex_unlock(&locks);
                        tstamp = tp(tstamp);
                        strcpy(a1->SRVCMD.timestamp,tstamp);
                        c1 = &a1->SRVCMD;
                         if((servocmd *)c1 != (servocmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"servo"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                                     {  fprintf(stderr," ERROR Sending CMD to E03 servo system\n");
                                         terminate_thread(server_fd);
                                     }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "E03 servo timeout\n");
                                         terminate_thread(server_fd);
                                      }
                               
                                      else
                                     { 
                                         printservocmd(c1);
                                         bzero(c1,sizeof(servocmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(2);
                                  bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING E03 servo Intermidate RESPONSE\n");
                                     terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing IMMEDIATE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                 sleep(2);
                                 bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING E03 servo FINAL RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing FINAL RESPONSE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                E03srvq.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                   /*   else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(servocmd));
                           strcpy(a1->antenna_name,"E03");
                           strcpy(a1->SRVCMD.system_name,"servo");
                           a1->SRVCMD.seq= 10;
                           strcpy(a1->SRVCMD.op_name,"mon");
                           a1->SRVCMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->SRVCMD.timestamp,tstamp);
                            c1 = &a1->SRVCMD;
                          
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                            {  fprintf(stderr," ERROR Sending CMD to E03 Servo system\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "E03 Servo system #Perodic Monitoring\n");
                             
                           }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(1);
                            bzero(r1,sizeof(servoresp));
                            if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                           { fprintf(stderr," ERROR READING E03 Servo system RESPONSE\n");
                                     terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"E03 servo system it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              //write_shm(a1,r1); 
                            } 
                          } */
                
                    }
  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}

// E04 servo antenna thread

void* E04_servo( void* parameters)
{    
     int server_fd;
     ssize_t n;

     SRVANT_CMD *a1;
     a1 = malloc(sizeof(SRVANT_CMD));
  
     servocmd *c1;
     c1 = malloc(sizeof(servocmd));
    
     servoresp *r1;
     r1 = malloc(sizeof(servoresp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       E04srvq.store = 0; E04srvq.retrieve = 0;
              for(;;)
              {
                    if((int)(E04srvq.store)>(int)(E04srvq.retrieve))
                     {
                       pthread_mutex_lock(&locks);
                       a1 = (SRVANT_CMD *) E04srv_retrieve((int)E04srvq.retrieve);
                       pthread_mutex_unlock(&locks);
                        tstamp = tp(tstamp);
                        strcpy(a1->SRVCMD.timestamp,tstamp);
                        c1 = &a1->SRVCMD;
                         if((servocmd *)c1 != (servocmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"servo"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                                     {  fprintf(stderr," ERROR Sending CMD to E04 servo system\n");
                                         terminate_thread(server_fd);
                                     }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "E04 servo timeout\n");
                                         terminate_thread(server_fd);
                                      }
                               
                                      else
                                     { 
                                         printservocmd(c1);
                                         bzero(c1,sizeof(servocmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(2);
                                  bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING E04 servo Intermidate RESPONSE\n");
                                     terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing IMMEDIATE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                 sleep(2);
                                 bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING E04 servo FINAL RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing FINAL RESPONSE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                E04srvq.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                   /*   else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(servocmd));
                           strcpy(a1->antenna_name,"E04");
                           strcpy(a1->SRVCMD.system_name,"servo");
                           a1->SRVCMD.seq= 10;
                           strcpy(a1->SRVCMD.op_name,"mon");
                           a1->SRVCMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->SRVCMD.timestamp,tstamp);
                            c1 = &a1->SRVCMD;
                          
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                            {  fprintf(stderr," ERROR Sending CMD to E04 Servo system\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "E04 Servo system #Perodic Monitoring\n");
                             
                           }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(1);
                            bzero(r1,sizeof(servoresp));
                            if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                           { fprintf(stderr," ERROR READING E04 Servo system RESPONSE\n");
                                     terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"E04 servo system it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              //write_shm(a1,r1); 
                            } 
                          } */
                
                    }
  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}


// E06 servo antenna thread

void* E06_servo( void* parameters)
{    
     int server_fd;
     ssize_t n;

     SRVANT_CMD *a1;
     a1 = malloc(sizeof(SRVANT_CMD));
  
     servocmd *c1;
     c1 = malloc(sizeof(servocmd));
    
     servoresp *r1;
     r1 = malloc(sizeof(servoresp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       E06srvq.store = 0; E06srvq.retrieve = 0;
              for(;;)
              {
                    if((int)(E06srvq.store)>(int)(E06srvq.retrieve))
                     {
                       pthread_mutex_lock(&locks);
                       a1 = (SRVANT_CMD *) E06srv_retrieve((int)E06srvq.retrieve);
                       pthread_mutex_unlock(&locks);
                        tstamp = tp(tstamp);
                        strcpy(a1->SRVCMD.timestamp,tstamp);
                        c1 = &a1->SRVCMD;
                         if((servocmd *)c1 != (servocmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"servo"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                                     {  fprintf(stderr," ERROR Sending CMD to E06 servo system\n");
                                         terminate_thread(server_fd);
                                     }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "E06 servo timeout\n");
                                         terminate_thread(server_fd);
                                      }
                               
                                      else
                                     { 
                                         printservocmd(c1);
                                         bzero(c1,sizeof(servocmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(2);
                                  bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING E06 servo Intermidate RESPONSE\n");
                                     terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing IMMEDIATE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                 sleep(2);
                                 bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING E06 servo FINAL RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing FINAL RESPONSE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                E06srvq.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                   /*   else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(servocmd));
                           strcpy(a1->antenna_name,"E06");
                           strcpy(a1->SRVCMD.system_name,"servo");
                           a1->SRVCMD.seq= 10;
                           strcpy(a1->SRVCMD.op_name,"mon");
                           a1->SRVCMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->SRVCMD.timestamp,tstamp);
                            c1 = &a1->SRVCMD;
                          
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                            {  fprintf(stderr," ERROR Sending CMD to E06 Servo system\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "E06 Servo system #Perodic Monitoring\n");
                             
                           }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(1);
                            bzero(r1,sizeof(servoresp));
                            if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                           { fprintf(stderr," ERROR READING E06 Servo system RESPONSE\n");
                                     terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"E06 servo system it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              //write_shm(a1,r1); 
                            } 
                          } */
                
                    }
  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}

// W01 servo antenna thread

void* W01_servo( void* parameters)
{    
     int server_fd;
     ssize_t n;

     SRVANT_CMD *a1;
     a1 = malloc(sizeof(SRVANT_CMD));
  
     servocmd *c1;
     c1 = malloc(sizeof(servocmd));
    
     servoresp *r1;
     r1 = malloc(sizeof(servoresp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       W01srvq.store = 0; W01srvq.retrieve = 0;
              for(;;)
              {
                    if((int)(W01srvq.store)>(int)(W01srvq.retrieve))
                     {
                       pthread_mutex_lock(&locks);
                       a1 = (SRVANT_CMD *) W01srv_retrieve((int)W01srvq.retrieve);
                       pthread_mutex_unlock(&locks);
                        tstamp = tp(tstamp);
                        strcpy(a1->SRVCMD.timestamp,tstamp);
                        c1 = &a1->SRVCMD;
                         if((servocmd *)c1 != (servocmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"servo"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                                     {  fprintf(stderr," ERROR Sending CMD to W01 servo system\n");
                                         terminate_thread(server_fd);
                                     }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "W01 servo timeout\n");
                                         terminate_thread(server_fd);
                                      }
                               
                                      else
                                     { 
                                         printservocmd(c1);
                                         bzero(c1,sizeof(servocmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(2);
                                  bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING W01 servo Intermidate RESPONSE\n");
                                     terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing IMMEDIATE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                 sleep(2);
                                 bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING W01 servo FINAL RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing FINAL RESPONSE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                W01srvq.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                   /*   else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(servocmd));
                           strcpy(a1->antenna_name,"W01");
                           strcpy(a1->SRVCMD.system_name,"servo");
                           a1->SRVCMD.seq= 10;
                           strcpy(a1->SRVCMD.op_name,"mon");
                           a1->SRVCMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->SRVCMD.timestamp,tstamp);
                            c1 = &a1->SRVCMD;
                          
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                            {  fprintf(stderr," ERROR Sending CMD to W01 Servo system\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "W01 Servo system #Perodic Monitoring\n");
                             
                           }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(1);
                            bzero(r1,sizeof(servoresp));
                            if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                           { fprintf(stderr," ERROR READING W01 Servo system RESPONSE\n");
                                     terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"W01 servo system it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              //write_shm(a1,r1); 
                            } 
                          } */
                
                    }
  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}

// W02 servo antenna thread

void* W02_servo( void* parameters)
{    
     int server_fd;
     ssize_t n;

     SRVANT_CMD *a1;
     a1 = malloc(sizeof(SRVANT_CMD));
  
     servocmd *c1;
     c1 = malloc(sizeof(servocmd));
    
     servoresp *r1;
     r1 = malloc(sizeof(servoresp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       W02srvq.store = 0; W02srvq.retrieve = 0;
              for(;;)
              {
                    if((int)(W02srvq.store)>(int)(W02srvq.retrieve))
                     {
                       pthread_mutex_lock(&locks);
                       a1 = (SRVANT_CMD *) W02srv_retrieve((int)W02srvq.retrieve);
                       pthread_mutex_unlock(&locks);
                        tstamp = tp(tstamp);
                        strcpy(a1->SRVCMD.timestamp,tstamp);
                        c1 = &a1->SRVCMD;
                         if((servocmd *)c1 != (servocmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"servo"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                                     {  fprintf(stderr," ERROR Sending CMD to W02 servo system\n");
                                         terminate_thread(server_fd);
                                     }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "W02 servo timeout\n");
                                         terminate_thread(server_fd);
                                      }
                               
                                      else
                                     { 
                                         printservocmd(c1);
                                         bzero(c1,sizeof(servocmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(2);
                                  bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING W02 servo Intermidate RESPONSE\n");
                                     terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing IMMEDIATE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                 sleep(2);
                                 bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING W02 servo FINAL RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing FINAL RESPONSE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                W02srvq.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                   /*   else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(servocmd));
                           strcpy(a1->antenna_name,"W02");
                           strcpy(a1->SRVCMD.system_name,"servo");
                           a1->SRVCMD.seq= 10;
                           strcpy(a1->SRVCMD.op_name,"mon");
                           a1->SRVCMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->SRVCMD.timestamp,tstamp);
                            c1 = &a1->SRVCMD;
                          
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                            {  fprintf(stderr," ERROR Sending CMD to W02 Servo system\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "W02 Servo system #Perodic Monitoring\n");
                             
                           }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(1);
                            bzero(r1,sizeof(servoresp));
                            if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                           { fprintf(stderr," ERROR READING W02 Servo system RESPONSE\n");
                                     terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"W02 servo system it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              //write_shm(a1,r1); 
                            } 
                          } */
                
                    }
  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}

// W03 servo antenna thread

void* W03_servo( void* parameters)
{    
     int server_fd;
     ssize_t n;

     SRVANT_CMD *a1;
     a1 = malloc(sizeof(SRVANT_CMD));
  
     servocmd *c1;
     c1 = malloc(sizeof(servocmd));
    
     servoresp *r1;
     r1 = malloc(sizeof(servoresp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       W03srvq.store = 0; W03srvq.retrieve = 0;
              for(;;)
              {
                    if((int)(W03srvq.store)>(int)(W03srvq.retrieve))
                     {
                       pthread_mutex_lock(&locks);
                       a1 = (SRVANT_CMD *) W03srv_retrieve((int)W03srvq.retrieve);
                       pthread_mutex_unlock(&locks);
                        tstamp = tp(tstamp);
                        strcpy(a1->SRVCMD.timestamp,tstamp);
                        c1 = &a1->SRVCMD;
                         if((servocmd *)c1 != (servocmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"servo"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                                     {  fprintf(stderr," ERROR Sending CMD to W03 servo system\n");
                                         terminate_thread(server_fd);
                                     }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "W03 servo timeout\n");
                                         terminate_thread(server_fd);
                                      }
                               
                                      else
                                     { 
                                         printservocmd(c1);
                                         bzero(c1,sizeof(servocmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(2);
                                  bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING W03 servo Intermidate RESPONSE\n");
                                     terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing IMMEDIATE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                 sleep(2);
                                 bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING W03 servo FINAL RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing FINAL RESPONSE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                W03srvq.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                   /*   else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(servocmd));
                           strcpy(a1->antenna_name,"W03");
                           strcpy(a1->SRVCMD.system_name,"servo");
                           a1->SRVCMD.seq= 10;
                           strcpy(a1->SRVCMD.op_name,"mon");
                           a1->SRVCMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->SRVCMD.timestamp,tstamp);
                            c1 = &a1->SRVCMD;
                          
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                            {  fprintf(stderr," ERROR Sending CMD to W03 Servo system\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "W03 Servo system #Perodic Monitoring\n");
                             
                           }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(1);
                            bzero(r1,sizeof(servoresp));
                            if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                           { fprintf(stderr," ERROR READING W03 Servo system RESPONSE\n");
                                     terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"W03 servo system it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              //write_shm(a1,r1); 
                            } 
                          } */
                
                    }
  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}

// W04 servo antenna thread

void* W04_servo( void* parameters)
{    
     int server_fd;
     ssize_t n;

     SRVANT_CMD *a1;
     a1 = malloc(sizeof(SRVANT_CMD));
  
     servocmd *c1;
     c1 = malloc(sizeof(servocmd));
    
     servoresp *r1;
     r1 = malloc(sizeof(servoresp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       W04srvq.store = 0; W04srvq.retrieve = 0;
              for(;;)
              {
                    if((int)(W04srvq.store)>(int)(W04srvq.retrieve))
                     {
                       pthread_mutex_lock(&locks);
                       a1 = (SRVANT_CMD *) W04srv_retrieve((int)W04srvq.retrieve);
                       pthread_mutex_unlock(&locks);
                        tstamp = tp(tstamp);
                        strcpy(a1->SRVCMD.timestamp,tstamp);
                        c1 = &a1->SRVCMD;
                         if((servocmd *)c1 != (servocmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"servo"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                                     {  fprintf(stderr," ERROR Sending CMD to W04 servo system\n");
                                         terminate_thread(server_fd);
                                     }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "W04 servo timeout\n");
                                         terminate_thread(server_fd);
                                      }
                               
                                      else
                                     { 
                                         printservocmd(c1);
                                         bzero(c1,sizeof(servocmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(2);
                                  bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING W04 servo Intermidate RESPONSE\n");
                                     terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing IMMEDIATE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                 sleep(2);
                                 bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING W04 servo FINAL RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing FINAL RESPONSE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                W04srvq.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                   /*   else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(servocmd));
                           strcpy(a1->antenna_name,"W04");
                           strcpy(a1->SRVCMD.system_name,"servo");
                           a1->SRVCMD.seq= 10;
                           strcpy(a1->SRVCMD.op_name,"mon");
                           a1->SRVCMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->SRVCMD.timestamp,tstamp);
                            c1 = &a1->SRVCMD;
                          
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                            {  fprintf(stderr," ERROR Sending CMD to W04 Servo system\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "W04 Servo system #Perodic Monitoring\n");
                             
                           }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(1);
                            bzero(r1,sizeof(servoresp));
                            if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                           { fprintf(stderr," ERROR READING W04 Servo system RESPONSE\n");
                                     terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"W04 servo system it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              //write_shm(a1,r1); 
                            } 
                          } */
                
                    }
  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}

// W05 servo antenna thread

void* W05_servo( void* parameters)
{    
     int server_fd;
     ssize_t n;

     SRVANT_CMD *a1;
     a1 = malloc(sizeof(SRVANT_CMD));
  
     servocmd *c1;
     c1 = malloc(sizeof(servocmd));
    
     servoresp *r1;
     r1 = malloc(sizeof(servoresp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       W05srvq.store = 0; W05srvq.retrieve = 0;
              for(;;)
              {
                    if((int)(W05srvq.store)>(int)(W05srvq.retrieve))
                     {
                       pthread_mutex_lock(&locks);
                       a1 = (SRVANT_CMD *) W05srv_retrieve((int)W05srvq.retrieve);
                       pthread_mutex_unlock(&locks);
                        tstamp = tp(tstamp);
                        strcpy(a1->SRVCMD.timestamp,tstamp);
                        c1 = &a1->SRVCMD;
                         if((servocmd *)c1 != (servocmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"servo"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                                     {  fprintf(stderr," ERROR Sending CMD to W05 servo system\n");
                                         terminate_thread(server_fd);
                                     }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "W05 servo timeout\n");
                                         terminate_thread(server_fd);
                                      }
                               
                                      else
                                     { 
                                         printservocmd(c1);
                                         bzero(c1,sizeof(servocmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(2);
                                  bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING W05 servo Intermidate RESPONSE\n");
                                     terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing IMMEDIATE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                 sleep(2);
                                 bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING W05 servo FINAL RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing FINAL RESPONSE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                W05srvq.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                   /*   else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(servocmd));
                           strcpy(a1->antenna_name,"W05");
                           strcpy(a1->SRVCMD.system_name,"servo");
                           a1->SRVCMD.seq= 10;
                           strcpy(a1->SRVCMD.op_name,"mon");
                           a1->SRVCMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->SRVCMD.timestamp,tstamp);
                            c1 = &a1->SRVCMD;
                          
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                            {  fprintf(stderr," ERROR Sending CMD to W05 Servo system\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "W05 Servo system #Perodic Monitoring\n");
                             
                           }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(1);
                            bzero(r1,sizeof(servoresp));
                            if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                           { fprintf(stderr," ERROR READING W05 Servo system RESPONSE\n");
                                     terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"W05 servo system it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              //write_shm(a1,r1); 
                            } 
                          } */
                
                    }
  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}

// W06 servo antenna thread

void* W06_servo( void* parameters)
{    
     int server_fd;
     ssize_t n;

     SRVANT_CMD *a1;
     a1 = malloc(sizeof(SRVANT_CMD));
  
     servocmd *c1;
     c1 = malloc(sizeof(servocmd));
    
     servoresp *r1;
     r1 = malloc(sizeof(servoresp));
     server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
  
       W06srvq.store = 0; W06srvq.retrieve = 0;
              for(;;)
              {
                    if((int)(W06srvq.store)>(int)(W06srvq.retrieve))
                     {
                       pthread_mutex_lock(&locks);
                       a1 = (SRVANT_CMD *) W06srv_retrieve((int)W06srvq.retrieve);
                       pthread_mutex_unlock(&locks);
                        tstamp = tp(tstamp);
                        strcpy(a1->SRVCMD.timestamp,tstamp);
                        c1 = &a1->SRVCMD;
                         if((servocmd *)c1 != (servocmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"servo"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                                     {  fprintf(stderr," ERROR Sending CMD to W06 servo system\n");
                                         terminate_thread(server_fd);
                                     }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "W06 servo timeout\n");
                                         terminate_thread(server_fd);
                                      }
                               
                                      else
                                     { 
                                         printservocmd(c1);
                                         bzero(c1,sizeof(servocmd));
                                                                             
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  sleep(2);
                                  bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING W06 servo Intermidate RESPONSE\n");
                                     terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing IMMEDIATE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                 sleep(2);
                                 bzero(r1,sizeof(servoresp)); 
                             
                               if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                                  { fprintf(stderr," ERROR READING W06 servo FINAL RESPONSE\n");
                                    terminate_thread(server_fd);
                                  }
                                 else
                                 {
                                    printservoresp(r1);
                                    //write_shm(a1,r1); 
                                    bzero(r1,sizeof(servoresp));
                                   fprintf(stderr," Writing FINAL RESPONSE to ONLINE from SERVO THREAD SUCCESSFUL\n");
                                 } 
                                W06srvq.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                   /*   else
                         { // Periodic Monitoring in the background 
                           bzero(c1,sizeof(servocmd));
                           strcpy(a1->antenna_name,"W06");
                           strcpy(a1->SRVCMD.system_name,"servo");
                           a1->SRVCMD.seq= 10;
                           strcpy(a1->SRVCMD.op_name,"mon");
                           a1->SRVCMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->SRVCMD.timestamp,tstamp);
                            c1 = &a1->SRVCMD;
                          
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(servocmd)))!=sizeof(servocmd))
                            {  fprintf(stderr," ERROR Sending CMD to W06 Servo system\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "W06 Servo system #Perodic Monitoring\n");
                             
                           }
                            else
                             {
                               // printcmd(c1);
                             }
                              
                             sleep(1);
                            bzero(r1,sizeof(servoresp));
                            if((n=readn(server_fd,r1,sizeof(servoresp)))!=sizeof(servoresp))
                           { fprintf(stderr," ERROR READING W06 Servo system RESPONSE\n");
                                     terminate_thread(server_fd);
                           }
                           
                           else if(n==0)
                            {
                              fprintf(stderr,"W06 servo system it's Socket connection\n");
                                terminate_thread(server_fd);
                            }
                           
                           else
                           {
                              //write_shm(a1,r1); 
                            } 
                          } */
                
                    }
  free(a1);
  free(r1);
  free(c1);
     
   return NULL;
}














