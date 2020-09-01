#include"mcm_thread.h"

void* sentinel_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *ant_cmd;
     ant_cmd = malloc(sizeof(ANT_CMD));
     ANT_RESP *ant_resp;
     ant_resp = malloc(sizeof(ANT_RESP));
     cmd *c1;//,*temp;
     c1 = malloc(sizeof(cmd));
    // temp = malloc(sizeof(cmd));
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
    //fprintf(stderr," ######### =====>  SenTinel THREAD ========> \n");
       senQ.store = 0; senQ.retrieve = 0;
              for(;;)
              {
                    while((int)(senQ.store)>(int)(senQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       c1 = (cmd *) senq_retrieve((int)senQ.retrieve);
                       pthread_mutex_unlock(&lock);
                        // if((c1= &ant_cmd->CMD[0])!=(cmd *)NULL)
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"sentinel"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to MCM device\n");}
                                       else
                                      { 
                                        fprintf(stderr," SUCEESSFUL\n");
                                         bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                             //  printcmd(c1);
                               //sleep(1);
                                 usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING MCM RESPONSE\n"); }
                              else
                              {
                                    printresp(r1);
                                     pthread_mutex_lock(&lock);
                                     rq_store(*r1);
                                      pthread_mutex_unlock(&lock); 
                                   usleep(500000); 
                                  if((n= writen(sfd,(unsigned char *)r1,sizeof(resp)))!=sizeof(resp))
                                  {fprintf(stderr," Writing to ONLINE device Failed \n");}  
                                  else
                                   {
                                      bzero(r1,sizeof(resp));
                                     fprintf(stderr," Writing to ONLINE from SENTINEL THREAD SUCCESSFUL\n");
                                   }   
                                                                                    
                               } 
                             senQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        //pthread_mutex_unlock(&lock);
                       }
                
                    }
     
   return NULL;
}

void* fiber_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *ant_cmd;
     ant_cmd = malloc(sizeof(ANT_CMD));
     ANT_RESP *ant_resp;
     ant_resp = malloc(sizeof(ANT_RESP));
     cmd *c1;//,*temp;
     c1 = malloc(sizeof(cmd));
    // temp = malloc(sizeof(cmd));
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
   // fprintf(stderr," ######### =====>  Fiber Optics  ========> \n");
       fiberQ.store = 0; fiberQ.retrieve = 0;
              for(;;)
              {
                    while((int)(fiberQ.store)>(int)(fiberQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       c1 = (cmd *) fiberq_retrieve((int)fiberQ.retrieve);
                        pthread_mutex_unlock(&lock);
                        // if((c1= &ant_cmd->CMD[0])!=(cmd *)NULL)
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"fiber_optics"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to MCM device\n");}
                                       else
                                      { 
                                        fprintf(stderr," SUCEESSFUL\n");
                                         bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                             //  printcmd(c1);
                                 //sleep(1);
                               usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING MCM RESPONSE\n"); }
                              else
                              {
                                    printresp(r1);
                                     pthread_mutex_lock(&lock);
                                     rq_store(*r1);
                                     pthread_mutex_unlock(&lock); 
                                      usleep(500000); 
                                  if((n= writen(sfd,(unsigned char *)r1,sizeof(resp)))!=sizeof(resp))
                                  {fprintf(stderr," Writing to ONLINE device Failed \n");}  
                                  else
                                   {
                                      bzero(r1,sizeof(resp));
                                     fprintf(stderr," Writing to ONLINE from FIBER THREAD SUCCESSFUL\n");
                                   }   
                                                                                    
                               } 
                             fiberQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        //pthread_mutex_unlock(&lock);
                       }
                
                    }
     
   return NULL;
}

void* front_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *ant_cmd;
     ant_cmd = malloc(sizeof(ANT_CMD));
     ANT_RESP *ant_resp;
     ant_resp = malloc(sizeof(ANT_RESP));
     cmd *c1;//,*temp;
     c1 = malloc(sizeof(cmd));
    // temp = malloc(sizeof(cmd));
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
  //  fprintf(stderr," ######### =====>  FRONT END THREAD ========> \n");
       Q.store = 0; Q.retrieve = 0;
              for(;;)
              {
                    while((int)(Q.store)>(int)(Q.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       c1 = (cmd *) q_retrieve((int)Q.retrieve);
                        pthread_mutex_unlock(&lock);
                        // if((c1= &ant_cmd->CMD[0])!=(cmd *)NULL)
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"front_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to MCM device\n");}
                                       else
                                      { 
                                        fprintf(stderr," SUCEESSFUL\n");
                                         bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                             //  printcmd(c1);
                                // sleep(1);
                               usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING MCM RESPONSE\n"); }
                              else
                              {
                                    printresp(r1);
                                    pthread_mutex_lock(&lock);
                                     rq_store(*r1);
                                     pthread_mutex_unlock(&lock); 
                                    usleep(500000); 
                                  if((n= writen(sfd,(unsigned char *)r1,sizeof(resp)))!=sizeof(resp))
                                  {fprintf(stderr," Writing to ONLINE device Failed \n");}  
                                  else
                                   {
                                      bzero(r1,sizeof(resp));
                                     fprintf(stderr," Writing to ONLINE from FRONT END SUCCESSFUL\n");
                                   }   
                                                                                    
                               } 
                             Q.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        //pthread_mutex_unlock(&lock);
                       }
                
                    }
     
   return NULL;
}


void* backend_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *ant_cmd;
     ant_cmd = malloc(sizeof(ANT_CMD));
     ANT_RESP *ant_resp;
     ant_resp = malloc(sizeof(ANT_RESP));
     cmd *c1;//,*temp;
     c1 = malloc(sizeof(cmd));
    // temp = malloc(sizeof(cmd));
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
   // fprintf(stderr," ######### =====>  Backend THREAD ========> \n");
       backQ.store = 0; backQ.retrieve = 0;
              for(;;)
              {
                    while((int)(backQ.store)>(int)(backQ.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       c1 = (cmd *) backq_retrieve((int)backQ.retrieve);
                        pthread_mutex_unlock(&lock);
                        // if((c1= &ant_cmd->CMD[0])!=(cmd *)NULL)
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"back_end"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to MCM device\n");}
                                       else
                                      { 
                                        fprintf(stderr," SUCEESSFUL\n");
                                         bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                             //  printcmd(c1);
                                 //sleep(1);
                               usleep(500000);
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING MCM RESPONSE\n"); }
                              else
                              {
                                    printresp(r1);
                                    pthread_mutex_lock(&lock);
                                     rq_store(*r1);
                                     pthread_mutex_unlock(&lock);
                                    usleep(500000);  
                                  if((n= writen(sfd,(unsigned char *)r1,sizeof(resp)))!=sizeof(resp))
                                  {fprintf(stderr," Writing to ONLINE device Failed \n");}  
                                  else
                                   {
                                      bzero(r1,sizeof(resp));
                                     fprintf(stderr," Writing to ONLINE from BACKEND THREAD SUCCESSFUL\n");
                                   }   
                                                                                    
                               } 
                             backQ.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        //pthread_mutex_unlock(&lock);
                       }
                
                    }
     
   return NULL;
}


void* self_thread( void* parameters)
{    
     int server_fd;
     ssize_t n;
     ANT_CMD *ant_cmd;
     ant_cmd = malloc(sizeof(ANT_CMD));
     ANT_RESP *ant_resp;
     ant_resp = malloc(sizeof(ANT_RESP));
     cmd *c1;//,*temp;
     c1 = malloc(sizeof(cmd));
    // temp = malloc(sizeof(cmd));
     resp *r1;
    r1 = malloc(sizeof(resp));
    server_fd = *(int*)parameters;
   // fprintf(stderr," ######### =====>  SELF TEST THREAD ========> \n");
       Q.store = 0; Q.retrieve = 0;
              for(;;)
              {
                    while((int)(Q.store)>(int)(Q.retrieve))
                     {
                       pthread_mutex_lock(&lock);
                       c1 = (cmd *) q_retrieve((int)Q.retrieve);
                        pthread_mutex_unlock(&lock);
                        // if((c1= &ant_cmd->CMD[0])!=(cmd *)NULL)
                         if((cmd *)c1 != (cmd *)NULL)
                           {  
                                if(!strcasecmp(c1->system_name,"self_test"))
                                 {
                                         
                                    if((n= writen(server_fd,(unsigned char *)c1,sizeof(cmd)))!=sizeof(cmd))
                                     {  fprintf(stderr," Sending CMD to MCM device\n");}
                                       else
                                      { 
                                        fprintf(stderr," SUCEESSFUL\n");
                                         bzero(c1,sizeof(cmd));
                                      }
                                  }
                                  else
                                  { fprintf(stderr,"SYSTEM NAME doesn't MATCHES\n");}
                        
                             //  printcmd(c1);
                                 //sleep(1);
                   
                                   bzero(r1,sizeof(resp));               
                              if((n=readn(server_fd,r1,sizeof(resp)))!=sizeof(resp))
                                  { fprintf(stderr,"ERROR READING MCM RESPONSE\n"); }
                              else
                              {
                                    printresp(r1);
                                     pthread_mutex_lock(&lock);
                                     rq_store(*r1);
                                     pthread_mutex_unlock(&lock);  
                                  if((n= writen(sfd,(unsigned char *)r1,sizeof(resp)))!=sizeof(resp))
                                  {fprintf(stderr," Writing to ONLINE device Failed \n");}  
                                  else
                                   {
                                      bzero(r1,sizeof(resp));
                                     fprintf(stderr," Writing to ONLINE SUCCESSFUL\n");
                                   }   
                                                                                    
                               } 
                             Q.retrieve++;                      
                         }
                         else
                         { fprintf(stderr," COMMAND is NULL in the QUEUE\n"); }
                        //pthread_mutex_unlock(&lock);
                       }
                
                    }
     
   return NULL;
}
