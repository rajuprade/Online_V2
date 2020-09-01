#include"mcm_thread.h"

void* sentinel_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   /*  ANT_RESP *ant_resp;
     ant_resp = malloc(sizeof(ANT_RESP));*/
     cmd *c1;//,*temp;
     c1 = malloc(sizeof(cmd));
    // temp = malloc(sizeof(cmd));
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
   // fprintf(stderr," ######### =====>  SenTinel THREAD ========> \n");
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
                                if(!strcasecmp(c1->system_name,"sentinel"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to MCM device\n"); }
            
                                     else if (readable_timeo(server_fd,2) == 0)
                                      {
                                         fprintf(stderr, "C00 Sentinel MCM TIMEOUT\n");
                                         //close(sfd);
                                        //break;
                                       }
                                      else
                                     { 
                                         printcmd(c1);
                                        // bzero(c1,sizeof(cmd));   
                                         
                                     }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  usleep(50000);
                                  bzero(r1,sizeof(resp)); 
                                 read(server_fd,r1,sizeof(resp));
                                  printresp(r1);
                                  write_shm(a1,r1);        
                             /*  if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING MCM RESPONSE\n"); }
                                    
                                else
                               {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from SENTINEL THREAD SUCCESSFUL\n");
                                } */
                              //pthread_mutex_unlock(&lock);
                             senQ.retrieve++; 
                                                
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                      else
                         { // Periodic Monitoring in the background 
                           //pthread_mutex_lock(&lock);
                           strcpy(a1->antenna_name,"C00");
                           strcpy(a1->CMD.system_name,"sentinel");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                            //pthread_mutex_lock(&lock);
                             //usleep(5000);
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to MCM device\n"); }
                            else if (readable_timeo(server_fd,5) == 0)
                           {
                             fprintf(stderr, "C00 Sentinel MCM TIMEOUT #Perodic Monitoring\n");
                              //close(sfd);
                             //break;
                           }
                            else
                            {// printcmd(c1);
                            }
                                sleep(1);
                                 bzero(r1,sizeof(resp)); 
                                 read(server_fd,r1,sizeof(resp));
                                 // printresp(r1);
                                  write_shm(a1,r1);  
                           /*  sleep(2);
                            bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING MCM RESPONSE\n"); }
                           
                           else if (n==0)
                           fprintf(stderr,"C00 sentinel MCM closed it's Socket connection\n");
                           
                           else
                           {
                             //printresp(r1);
                              write_shm(a1,r1); 
                             // bzero(r1,sizeof(resp));
                            //fprintf(stderr," Writing to the Periodic Monitoring SENTINEL SYSTEM\n");
                           } */
                           //pthread_mutex_unlock(&lock); 
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
    /* ANT_RESP *ant_resp;
     ant_resp = malloc(sizeof(ANT_RESP)); */
     cmd *c1;//,*temp;
     c1 = malloc(sizeof(cmd));
      char *tstamp;
     tstamp = malloc(25);
    // temp = malloc(sizeof(cmd));
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  //  fprintf(stderr," ######### =====>  Fiber Optics  ========> \n");
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
                                     {  fprintf(stderr," ERROR Sending CMD to MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);
                                        // bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                    usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING MCM RESPONSE\n"); }
                              else
                              {
                                     printresp(r1);
                                     write_shm(a1,r1);                  
                                     fprintf(stderr," Writing to ONLINE from FIBER THREAD SUCCESSFUL\n");
                               } 
                             //pthread_mutex_unlock(&lock);
                             fiberQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                       else
                         { // Periodic Monitoring in the background 
                           //pthread_mutex_lock(&lock);
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
                                 read(server_fd,r1,sizeof(resp));
                                 // printresp(r1);
                                  write_shm(a1,r1);  
                          /*   sleep(2);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C00 FIBER MCM RESPONSE\n"); }
                           
                           else
                           {
                             //printresp(r1);
                              write_shm(a1,r1); 
                             // bzero(r1,sizeof(resp));
                            //fprintf(stderr," Writing to the Periodic Monitoring SENTINEL SYSTEM\n");
                           } */
                           //pthread_mutex_unlock(&lock);
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
    /* ANT_RESP *ant_resp;
     ant_resp = malloc(sizeof(ANT_RESP)); */
     cmd *c1;//,*temp;
     c1 = malloc(sizeof(cmd));
    // temp = malloc(sizeof(cmd));
      char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  //  fprintf(stderr," ######### =====>  FRONT END THREAD ========> \n");
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
                                     {  fprintf(stderr," ERROR Sending CMD to MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING MCM RESPONSE\n"); }
                              else
                              {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from FRONT END SUCCESSFUL\n");
                                  
                               } 
                             // pthread_mutex_unlock(&lock);
                             frontQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       
                       }
                       
                      else
                         { // Periodic Monitoring in the background
                           //pthread_mutex_lock(&lock); 
                           strcpy(a1->antenna_name,"C00");
                           strcpy(a1->CMD.system_name,"front_end");
                           a1->CMD.seq= 10;
                           strcpy(a1->CMD.op_name,"mon");
                           a1->CMD.number_param=0;
                            tstamp = tp(tstamp);
                            strcpy(a1->CMD.timestamp,tstamp);
                            c1 = &a1->CMD;
                           // pthread_mutex_lock(&lock); 
                            if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                            {  fprintf(stderr," ERROR Sending CMD to MCM device\n"); }
                            else
                            {// printcmd(c1);
                            }
                                 sleep(1);
                                 bzero(r1,sizeof(resp)); 
                                 read(server_fd,r1,sizeof(resp));
                                 // printresp(r1);
                                  write_shm(a1,r1);  
                           /*  sleep(2);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C00 FRONTEND MCM RESPONSE\n"); }
                          
                           else
                           {
                             //printresp(r1);
                              write_shm(a1,r1); 
                             // bzero(r1,sizeof(resp));
                            //fprintf(stderr," Writing to the Periodic Monitoring SENTINEL SYSTEM\n");
                           }*/
                           //pthread_mutex_unlock(&lock); 
                         }
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
   /*  ANT_RESP *ant_resp;
     ant_resp = malloc(sizeof(ANT_RESP)); */
     cmd *c1;//,*temp;
     c1 = malloc(sizeof(cmd));
    // temp = malloc(sizeof(cmd));
        char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
   // fprintf(stderr," ######### =====>  Backend THREAD ========> \n");
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
                                     {  fprintf(stderr," Sending CMD to MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING MCM RESPONSE\n"); }
                              else
                              {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                    fprintf(stderr," Writing to ONLINE from BACKEND THREAD SUCCESSFUL\n");
                              } 
                            // pthread_mutex_unlock(&lock);
                             backQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        //pthread_mutex_unlock(&lock);
                       }
                       else
                         { // Periodic Monitoring in the background
                            //  pthread_mutex_lock(&lock); 
                            strcpy(a1->antenna_name,"C00");
                           strcpy(a1->CMD.system_name,"back_end");
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
                                 read(server_fd,r1,sizeof(resp));
                                 // printresp(r1);
                                  write_shm(a1,r1);  
                            /* sleep(2);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C00 back END MCM RESPONSE\n"); }
                          
                           else
                           {
                             //printresp(r1);
                              write_shm(a1,r1); 
                             // bzero(r1,sizeof(resp));
                            //fprintf(stderr," Writing to the Periodic Monitoring SENTINEL SYSTEM\n");
                           } */
                            //pthread_mutex_unlock(&lock);
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
  /*   ANT_RESP *ant_resp;
     ant_resp = malloc(sizeof(ANT_RESP)); */
     cmd *c1;//,*temp;
     c1 = malloc(sizeof(cmd));
    // temp = malloc(sizeof(cmd));
        char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
   // fprintf(stderr," ######### =====>  SELF TEST THREAD ========> \n");
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
                                     {  fprintf(stderr," Sending CMD to MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                                     
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING MCM RESPONSE\n"); }
                              else
                              {
                                    printresp(r1);
                                    write_shm(a1,r1); 
                                      bzero(r1,sizeof(resp));
                                     fprintf(stderr," Writing to ONLINE SUCCESSFUL\n");
                                   
                                                                                    
                               }
                             // pthread_mutex_unlock(&lock); 
                             selfQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                       else
                         { // Periodic Monitoring in the background 
                             //pthread_mutex_lock(&lock);
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
                                 read(server_fd,r1,sizeof(resp));
                                 // printresp(r1);
                                  write_shm(a1,r1);  
                           /*  sleep(2);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING MCM RESPONSE\n"); }
                           
                           else
                           {
                             //printresp(r1);
                              write_shm(a1,r1); 
                             // bzero(r1,sizeof(resp));
                            //fprintf(stderr," Writing to the Periodic Monitoring SENTINEL SYSTEM\n");
                           }*/
                           //pthread_mutex_unlock(&lock); 
                         }
                    }
  free(a1);
  free(r1);
  free(c1);
   return NULL;
}

/*************************************** C01 Antenna syste Thread functions here ******/

void* C01_sentinel_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *a1;
     a1 = malloc(sizeof(ANT_CMD));
   /*  ANT_RESP *ant_resp;
     ant_resp = malloc(sizeof(ANT_RESP)); */
     cmd *c1;//,*temp;
     c1 = malloc(sizeof(cmd));
    // temp = malloc(sizeof(cmd));
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
     char *tstamp;
     tstamp = malloc(25);
   // fprintf(stderr," ######### =====>  SenTinel THREAD ========> \n");
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
                                if(!strcasecmp(c1->system_name,"sentinel"))
                                 {
                                    
                                    if((n=writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," ERROR Sending CMD to MCM device\n"); }
                                    else
                                   { 
                                         printcmd(c1);
                                        // bzero(c1,sizeof(cmd));   
                                         
                                    }
                                  } 
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                  usleep(500000);
                                 bzero(r1,sizeof(resp)); 
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr," ERROR READING MCM RESPONSE\n"); }
                                    
                            else
                              {
                                    printresp(r1);
                                    //write_shm_C01(a1,r1); 
                                      write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                   fprintf(stderr," Writing to ONLINE from SENTINEL THREAD SUCCESSFUL\n");
                               } 
                             c1senQ.retrieve++; 
                          // pthread_mutex_unlock(&lock);                     
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        
                       }
                       else
                         { // Periodic Monitoring in the background 
                          // pthread_mutex_lock(&lock);
                           strcpy(a1->antenna_name,"C01");
                           strcpy(a1->CMD.system_name,"sentinel");
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
                                 read(server_fd,r1,sizeof(resp));
                                 // printresp(r1);
                                  write_shm(a1,r1);  
                           /*  sleep(2);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C01 Sentinel MCM RESPONSE\n"); }
                           
                           else
                           {
                             //printresp(r1);
                             // write_shm_C01(a1,r1); 
                                write_shm(a1,r1); 
                             // bzero(r1,sizeof(resp));
                            //fprintf(stderr," Writing to the Periodic Monitoring SENTINEL SYSTEM\n");
                           } */
                          //pthread_mutex_unlock(&lock); 
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
    /* ANT_RESP *ant_resp;
     ant_resp = malloc(sizeof(ANT_RESP)); */
     cmd *c1;//,*temp;
     c1 = malloc(sizeof(cmd));
      char *tstamp;
     tstamp = malloc(25);
    // temp = malloc(sizeof(cmd));
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  //  fprintf(stderr," ######### =====>  Fiber Optics  ========> \n");
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
                                     {  fprintf(stderr," ERROR Sending CMD to MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);
                                        // bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                    usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING MCM RESPONSE\n"); }
                              else
                              {
                                     printresp(r1);
                                     //write_shm_C01(a1,r1); 
                                       write_shm(a1,r1);                  
                                     fprintf(stderr," Writing to ONLINE from FIBER THREAD SUCCESSFUL\n");
                               } 
                             //   pthread_mutex_unlock(&lock);
                             c1fiberQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                      else
                         { // Periodic Monitoring in the background 
                           // pthread_mutex_lock(&lock);
                           strcpy(a1->antenna_name,"C01");
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
                                 read(server_fd,r1,sizeof(resp));
                                 // printresp(r1);
                                  write_shm(a1,r1);  
                           /*  sleep(2);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C01  FIBER OPTICS MCM RESPONSE\n"); }
                            
                           else
                           {
                             //printresp(r1);
                             // write_shm_C01(a1,r1);
                                write_shm(a1,r1);  
                             // bzero(r1,sizeof(resp));
                            //fprintf(stderr," Writing to the Periodic Monitoring SENTINEL SYSTEM\n");
                           } */
                          // pthread_mutex_unlock(&lock); 
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
  /*   ANT_RESP *ant_resp;
     ant_resp = malloc(sizeof(ANT_RESP)); */
     cmd *c1;//,*temp;
     c1 = malloc(sizeof(cmd));
    // temp = malloc(sizeof(cmd));
      char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  //  fprintf(stderr," ######### =====>  FRONT END THREAD ========> \n");
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
                                     {  fprintf(stderr," ERROR Sending CMD to MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING MCM RESPONSE\n"); }
                              else
                              {
                                    printresp(r1);
                                   // write_shm_C01(a1,r1);
                                      write_shm(a1,r1);  
                                    bzero(r1,sizeof(resp));
                                     fprintf(stderr," Writing to ONLINE from FRONT END SUCCESSFUL\n");
                                    
                               } 
                             //   pthread_mutex_unlock(&lock);
                             c1frontQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       
                       }
                     else
                         { // Periodic Monitoring in the background 
                           //pthread_mutex_lock(&lock);
                           strcpy(a1->antenna_name,"C01");
                           strcpy(a1->CMD.system_name,"front_end");
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
                                 read(server_fd,r1,sizeof(resp));
                                 // printresp(r1);
                                  write_shm(a1,r1);  
                           /*  sleep(2);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C01 FRONT END MCM RESPONSE\n"); }
                           
                           else
                           {
                             //printresp(r1);
                             // write_shm_C01(a1,r1); 
                                write_shm(a1,r1); 
                             // bzero(r1,sizeof(resp));
                            //fprintf(stderr," Writing to the Periodic Monitoring SENTINEL SYSTEM\n");
                           }*/
                          // pthread_mutex_unlock(&lock); 
                         }
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
   /*  ANT_RESP *ant_resp;
     ant_resp = malloc(sizeof(ANT_RESP)); */
     cmd *c1;//,*temp;
     c1 = malloc(sizeof(cmd));
    // temp = malloc(sizeof(cmd));
        char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
   // fprintf(stderr," ######### =====>  Backend THREAD ========> \n");
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
                                     {  fprintf(stderr," Sending CMD to MCM device\n");}
                                       else
                                      { 
                                         printcmd(c1);
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                                   usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING MCM RESPONSE\n"); }
                              else
                              {
                                    printresp(r1);
                                    //write_shm_C01(a1,r1); 
                                      write_shm(a1,r1); 
                                    bzero(r1,sizeof(resp));
                                    fprintf(stderr," Writing to ONLINE from BACKEND THREAD SUCCESSFUL\n");
                              } 
                             //  pthread_mutex_unlock(&lock);
                             c1backQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        //pthread_mutex_unlock(&lock);
                       }
                      else
                         { // Periodic Monitoring in the background
                           // pthread_mutex_lock(&lock);
                           strcpy(a1->antenna_name,"C01");
                           strcpy(a1->CMD.system_name,"back_end");
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
                                 read(server_fd,r1,sizeof(resp));
                                 // printresp(r1);
                                  write_shm(a1,r1);  
                            /* sleep(2);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C01 Back END MCM RESPONSE\n"); }
                            
                           else
                           {
                             //printresp(r1);
                              //write_shm_C01(a1,r1); 
                                write_shm(a1,r1); 
                             // bzero(r1,sizeof(resp));
                            //fprintf(stderr," Writing to the Periodic Monitoring SENTINEL SYSTEM\n");
                           }*/
                         // pthread_mutex_unlock(&lock); 
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
   /*  ANT_RESP *ant_resp;
     ant_resp = malloc(sizeof(ANT_RESP)); */
     cmd *c1;//,*temp;
     c1 = malloc(sizeof(cmd));
    // temp = malloc(sizeof(cmd));
        char *tstamp;
     tstamp = malloc(25);
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
   // fprintf(stderr," ######### =====>  SELF TEST THREAD ========> \n");
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
                                         printcmd(c1);
                                         //bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                                     
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING MCM RESPONSE\n"); }
                              else
                              {
                                      printresp(r1);
                                  //  write_shm_C01(a1,r1); 
                                        write_shm(a1,r1); 
                                      bzero(r1,sizeof(resp));
                                     fprintf(stderr," Writing to ONLINE SUCCESSFUL\n");
                                   
                                                                                    
                               } 
                             // pthread_mutex_unlock(&lock);
                             c1selfQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                       }
                     else
                         { // Periodic Monitoring in the background 
                            //pthread_mutex_lock(&lock);
                           strcpy(a1->antenna_name,"C01");
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
                                 read(server_fd,r1,sizeof(resp));
                                 // printresp(r1);
                                  write_shm(a1,r1);  
                            /* sleep(2);
                             bzero(r1,sizeof(resp));
                            if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                           { fprintf(stderr," ERROR READING C01 Self Test MCM RESPONSE\n"); }
                          
                           else
                           {
                             //printresp(r1);
                             // write_shm_C01(a1,r1); 
                                write_shm(a1,r1); 
                             // bzero(r1,sizeof(resp));
                            //fprintf(stderr," Writing to the Periodic Monitoring SENTINEL SYSTEM\n");
                           } */
                            // pthread_mutex_unlock(&lock); 
                         }
                    }
  free(a1);
  free(r1);
  free(c1);
   return NULL;
}


