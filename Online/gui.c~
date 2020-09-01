#include"gui.h"
#include"server.h"
#include"queue.h"
#include"socket.h"

void* gui_interface( void* parameters)
{

      ANT_CMD *e1;
     e1 = malloc(sizeof(ANT_CMD));
     
      ACK *a1;
      a1 = malloc(sizeof(ACK));
  
    /* int sofd, sfd1,yes=1;
     socklen_t clilen;
     struct sockaddr_in serv_addr, cli_addr;
           
     sofd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
       fprintf(stderr,"ERROR opening socket\n");
    if(setsockopt(sofd, SOL_SOCKET , SO_REUSEADDR, &yes, sizeof(int)) == -1)
    {
          fprintf(stderr," SOCKET REUSEADDR Error\n");
    } 
     bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(PORT_G);

     if (bind(sofd, (struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
              { 
               fprintf(stderr,"ERROR binding socket\n");
              }

     listen(sofd,5); */
    
      int sofd ,sfd1;

       
     sofd=init_server(PORT_G);
      if(sofd == -1 )
     {
       fprintf(stderr," ####### GUI SERVER NOT OPENED ##########\n");
     }
     clilen = sizeof(cli_addr); 
     
        
     while(1)
     {
        fprintf(stderr,"### SERVER WANTING FOR GUI CLIENT TO CONNECT #####\n");
        sfd1 = accept(sofd,(struct sockaddr *) &cli_addr,&clilen);
        fprintf(stderr,"#### Client=> %s Port %d\n",inet_ntoa(cli_addr.sin_addr),ntohs(cli_addr.sin_port));
       
           bzero(e1,sizeof(ANT_CMD));
            read(sfd1,e1,sizeof(ANT_CMD));
           if(!strcmp(e1->antenna_name,"C00"))
            {
               //if(!strcasecmp(e1->CMD.system_name,"sentinel"))
               if((!strcasecmp(e1->CMD.system_name,"sentinel"))||(!strcasecmp(e1->CMD.system_name,"fiber_optics")))
                {
                    pthread_mutex_lock(&lock);
                    senq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }
              /* else if(!strcasecmp(e1->CMD.system_name,"fiber_optics"))
                {
                 
                    pthread_mutex_lock(&lock);
                    fiberq_store(*e1); 
                    pthread_mutex_unlock(&lock);
                }*/
              else if(!strcasecmp(e1->CMD.system_name,"front_end"))
               {
                
                 pthread_mutex_lock(&lock);
                 frontq_store(*e1); 
                 pthread_mutex_unlock(&lock);
               }
             else if(!strcasecmp(e1->CMD.system_name,"back_end"))
              { 
                 
                   pthread_mutex_lock(&lock);
                   backq_store(*e1); 
                   pthread_mutex_unlock(&lock);
                 
              }
             else if(!strcasecmp(e1->CMD.system_name,"self_test"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  selfq_store(*e1); 
                  pthread_mutex_unlock(&lock);
               }
             }

            else if(!strcmp(e1->antenna_name,"C01"))
            {
              // if(!strcasecmp(e1->CMD.system_name,"sentinel"))
                if((!strcasecmp(e1->CMD.system_name,"sentinel"))||(!strcasecmp(e1->CMD.system_name,"fiber_optics")))
                {
                  
                   pthread_mutex_lock(&lock);
                    c1_senq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }
              /* else if(!strcasecmp(e1->CMD.system_name,"fiber_optics"))
                {
                 
                    pthread_mutex_lock(&lock);
                    c1_fiberq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }*/
              else if(!strcasecmp(e1->CMD.system_name,"front_end"))
               {
                
                  pthread_mutex_lock(&lock);
                  c1_frontq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             else if(!strcasecmp(e1->CMD.system_name,"back_end"))
              { 
                 
                   pthread_mutex_lock(&lock);
                   c1_backq_store(*e1); 
                   pthread_mutex_unlock(&lock);
                 
              }
             else if(!strcasecmp(e1->CMD.system_name,"self_test"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  c1_selfq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             }
               else if(!strcmp(e1->antenna_name,"C02"))
            {
              // if(!strcasecmp(e1->CMD.system_name,"sentinel"))
                 if((!strcasecmp(e1->CMD.system_name,"sentinel"))||(!strcasecmp(e1->CMD.system_name,"fiber_optics")))
                {
                  
                   pthread_mutex_lock(&lock);
                    c2_senq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }
              /* else if(!strcasecmp(e1->CMD.system_name,"fiber_optics"))
                {
                 
                    pthread_mutex_lock(&lock);
                    c2_fiberq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }*/
              else if(!strcasecmp(e1->CMD.system_name,"front_end"))
               {
                
                  pthread_mutex_lock(&lock);
                  c2_frontq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             else if(!strcasecmp(e1->CMD.system_name,"back_end"))
              { 
                 
                   pthread_mutex_lock(&lock);
                   c2_backq_store(*e1); 
                   pthread_mutex_unlock(&lock);
                 
              }
             else if(!strcasecmp(e1->CMD.system_name,"self_test"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  c2_selfq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             }
               else if(!strcmp(e1->antenna_name,"C03"))
            {
               //if(!strcasecmp(e1->CMD.system_name,"sentinel"))
                 if((!strcasecmp(e1->CMD.system_name,"sentinel"))||(!strcasecmp(e1->CMD.system_name,"fiber_optics")))
                {
                  
                   pthread_mutex_lock(&lock);
                    c3_senq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }
              /* else if(!strcasecmp(e1->CMD.system_name,"fiber_optics"))
                {
                 
                    pthread_mutex_lock(&lock);
                    c3_fiberq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }*/
              else if(!strcasecmp(e1->CMD.system_name,"front_end"))
               {
                
                  pthread_mutex_lock(&lock);
                  c3_frontq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             else if(!strcasecmp(e1->CMD.system_name,"back_end"))
              { 
                 
                   pthread_mutex_lock(&lock);
                   c3_backq_store(*e1); 
                   pthread_mutex_unlock(&lock);
                 
              }
             else if(!strcasecmp(e1->CMD.system_name,"self_test"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  c3_selfq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             }
               else if(!strcmp(e1->antenna_name,"C04"))
            {
              // if(!strcasecmp(e1->CMD.system_name,"sentinel"))
                 if((!strcasecmp(e1->CMD.system_name,"sentinel"))||(!strcasecmp(e1->CMD.system_name,"fiber_optics")))
                {
                  
                   pthread_mutex_lock(&lock);
                    c4_senq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }
              /* else if(!strcasecmp(e1->CMD.system_name,"fiber_optics"))
                {
                 
                    pthread_mutex_lock(&lock);
                    c4_fiberq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }*/
              else if(!strcasecmp(e1->CMD.system_name,"front_end"))
               {
                
                  pthread_mutex_lock(&lock);
                  c4_frontq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             else if(!strcasecmp(e1->CMD.system_name,"back_end"))
              { 
                 
                   pthread_mutex_lock(&lock);
                   c4_backq_store(*e1); 
                   pthread_mutex_unlock(&lock);
                 
              }
             else if(!strcasecmp(e1->CMD.system_name,"self_test"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  c4_selfq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             }
               else if(!strcmp(e1->antenna_name,"C05"))
            {
              // if(!strcasecmp(e1->CMD.system_name,"sentinel"))
                 if((!strcasecmp(e1->CMD.system_name,"sentinel"))||(!strcasecmp(e1->CMD.system_name,"fiber_optics")))
                {
                  
                   pthread_mutex_lock(&lock);
                    c5_senq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }
             /*  else if(!strcasecmp(e1->CMD.system_name,"fiber_optics"))
                {
                 
                    pthread_mutex_lock(&lock);
                    c5_fiberq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }*/
              else if(!strcasecmp(e1->CMD.system_name,"front_end"))
               {
                
                  pthread_mutex_lock(&lock);
                  c5_frontq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             else if(!strcasecmp(e1->CMD.system_name,"back_end"))
              { 
                 
                   pthread_mutex_lock(&lock);
                   c5_backq_store(*e1); 
                   pthread_mutex_unlock(&lock);
                 
              }
             else if(!strcasecmp(e1->CMD.system_name,"self_test"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  c5_selfq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             }
               else if(!strcmp(e1->antenna_name,"C06"))
            {
              // if(!strcasecmp(e1->CMD.system_name,"sentinel"))
                 if((!strcasecmp(e1->CMD.system_name,"sentinel"))||(!strcasecmp(e1->CMD.system_name,"fiber_optics")))
                {
                  
                   pthread_mutex_lock(&lock);
                    c6_senq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }
              /* else if(!strcasecmp(e1->CMD.system_name,"fiber_optics"))
                {
                 
                    pthread_mutex_lock(&lock);
                    c6_fiberq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }*/
              else if(!strcasecmp(e1->CMD.system_name,"front_end"))
               {
                
                  pthread_mutex_lock(&lock);
                  c6_frontq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             else if(!strcasecmp(e1->CMD.system_name,"back_end"))
              { 
                 
                   pthread_mutex_lock(&lock);
                   c6_backq_store(*e1); 
                   pthread_mutex_unlock(&lock);
                 
              }
             else if(!strcasecmp(e1->CMD.system_name,"self_test"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  c6_selfq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             }  
              else if(!strcmp(e1->antenna_name,"C09"))
            {
              // if(!strcasecmp(e1->CMD.system_name,"sentinel"))
                 if((!strcasecmp(e1->CMD.system_name,"sentinel"))||(!strcasecmp(e1->CMD.system_name,"fiber_optics")))
                {
                  
                   pthread_mutex_lock(&lock);
                    c9_senq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }
              /* else if(!strcasecmp(e1->CMD.system_name,"fiber_optics"))
                {
                 
                    pthread_mutex_lock(&lock);
                    c9_fiberq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }*/
              else if(!strcasecmp(e1->CMD.system_name,"front_end"))
               {
                
                  pthread_mutex_lock(&lock);
                  c9_frontq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             else if(!strcasecmp(e1->CMD.system_name,"back_end"))
              { 
                 
                   pthread_mutex_lock(&lock);
                   c9_backq_store(*e1); 
                   pthread_mutex_unlock(&lock);
                 
              }
             else if(!strcasecmp(e1->CMD.system_name,"self_test"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  c9_selfq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             }
               else if(!strcmp(e1->antenna_name,"C08"))
            {
              // if(!strcasecmp(e1->CMD.system_name,"sentinel"))
                 if((!strcasecmp(e1->CMD.system_name,"sentinel"))||(!strcasecmp(e1->CMD.system_name,"fiber_optics")))
                {
                  
                   pthread_mutex_lock(&lock);
                    c8_senq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }
             /*  else if(!strcasecmp(e1->CMD.system_name,"fiber_optics"))
                {
                 
                    pthread_mutex_lock(&lock);
                    c8_fiberq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }*/
              else if(!strcasecmp(e1->CMD.system_name,"front_end"))
               {
                
                  pthread_mutex_lock(&lock);
                  c8_frontq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             else if(!strcasecmp(e1->CMD.system_name,"back_end"))
              { 
                 
                   pthread_mutex_lock(&lock);
                   c8_backq_store(*e1); 
                   pthread_mutex_unlock(&lock);
                 
              }
             else if(!strcasecmp(e1->CMD.system_name,"self_test"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  c8_selfq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             }
              else if(!strcmp(e1->antenna_name,"C10"))
            {
              // if(!strcasecmp(e1->CMD.system_name,"sentinel"))
                 if((!strcasecmp(e1->CMD.system_name,"sentinel"))||(!strcasecmp(e1->CMD.system_name,"fiber_optics")))
                {
                  
                   pthread_mutex_lock(&lock);
                    c10_senq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }
             /*  else if(!strcasecmp(e1->CMD.system_name,"fiber_optics"))
                {
                 
                    pthread_mutex_lock(&lock);
                    c10_fiberq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }*/
              else if(!strcasecmp(e1->CMD.system_name,"front_end"))
               {
                
                  pthread_mutex_lock(&lock);
                  c10_frontq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             else if(!strcasecmp(e1->CMD.system_name,"back_end"))
              { 
                 
                   pthread_mutex_lock(&lock);
                   c8_backq_store(*e1); 
                   pthread_mutex_unlock(&lock);
                 
              }
             else if(!strcasecmp(e1->CMD.system_name,"self_test"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  c10_selfq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             }
              else if(!strcmp(e1->antenna_name,"C11"))
            {
              // if(!strcasecmp(e1->CMD.system_name,"sentinel"))
                 if((!strcasecmp(e1->CMD.system_name,"sentinel"))||(!strcasecmp(e1->CMD.system_name,"fiber_optics")))
                {
                  
                   pthread_mutex_lock(&lock);
                    c11_senq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }
              /* else if(!strcasecmp(e1->CMD.system_name,"fiber_optics"))
                {
                 
                    pthread_mutex_lock(&lock);
                    c11_fiberq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }*/
              else if(!strcasecmp(e1->CMD.system_name,"front_end"))
               {
                
                  pthread_mutex_lock(&lock);
                  c11_frontq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             else if(!strcasecmp(e1->CMD.system_name,"back_end"))
              { 
                 
                   pthread_mutex_lock(&lock);
                   c11_backq_store(*e1); 
                   pthread_mutex_unlock(&lock);
                 
              }
             else if(!strcasecmp(e1->CMD.system_name,"self_test"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  c11_selfq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             }
              else if(!strcmp(e1->antenna_name,"C12"))
            {
              // if(!strcasecmp(e1->CMD.system_name,"sentinel"))
                if((!strcasecmp(e1->CMD.system_name,"sentinel"))||(!strcasecmp(e1->CMD.system_name,"fiber_optics")))
                {
                  
                   pthread_mutex_lock(&lock);
                    c12_senq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }
              /* else if(!strcasecmp(e1->CMD.system_name,"fiber_optics"))
                {
                 
                    pthread_mutex_lock(&lock);
                    c12_fiberq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }*/
              else if(!strcasecmp(e1->CMD.system_name,"front_end"))
               {
                
                  pthread_mutex_lock(&lock);
                  c12_frontq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             else if(!strcasecmp(e1->CMD.system_name,"back_end"))
              { 
                 
                   pthread_mutex_lock(&lock);
                   c12_backq_store(*e1); 
                   pthread_mutex_unlock(&lock);
                 
              }
             else if(!strcasecmp(e1->CMD.system_name,"self_test"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  c12_selfq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             }
              else if(!strcmp(e1->antenna_name,"C13"))
            {
               //if(!strcasecmp(e1->CMD.system_name,"sentinel"))
                 if((!strcasecmp(e1->CMD.system_name,"sentinel"))||(!strcasecmp(e1->CMD.system_name,"fiber_optics")))
                {
                  
                   pthread_mutex_lock(&lock);
                    c13_senq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }
             /*  else if(!strcasecmp(e1->CMD.system_name,"fiber_optics"))
                {
                 
                    pthread_mutex_lock(&lock);
                    c13_fiberq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }*/
              else if(!strcasecmp(e1->CMD.system_name,"front_end"))
               {
                
                  pthread_mutex_lock(&lock);
                  c13_frontq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             else if(!strcasecmp(e1->CMD.system_name,"back_end"))
              { 
                 
                   pthread_mutex_lock(&lock);
                   c13_backq_store(*e1); 
                   pthread_mutex_unlock(&lock);
                 
              }
             else if(!strcasecmp(e1->CMD.system_name,"self_test"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  c13_selfq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             }
              else if(!strcmp(e1->antenna_name,"C14"))
            {
              // if(!strcasecmp(e1->CMD.system_name,"sentinel"))
                 if((!strcasecmp(e1->CMD.system_name,"sentinel"))||(!strcasecmp(e1->CMD.system_name,"fiber_optics")))
                {
                  
                   pthread_mutex_lock(&lock);
                    c14_senq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }
             /*  else if(!strcasecmp(e1->CMD.system_name,"fiber_optics"))
                {
                 
                    pthread_mutex_lock(&lock);
                    c14_fiberq_store(*e1);
                    pthread_mutex_unlock(&lock);
                } */
              else if(!strcasecmp(e1->CMD.system_name,"front_end"))
               {
                
                  pthread_mutex_lock(&lock);
                  c14_frontq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             else if(!strcasecmp(e1->CMD.system_name,"back_end"))
              { 
                 
                   pthread_mutex_lock(&lock);
                   c14_backq_store(*e1); 
                   pthread_mutex_unlock(&lock);
                 
              }
             else if(!strcasecmp(e1->CMD.system_name,"self_test"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  c14_selfq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             }
              else if(!strcmp(e1->antenna_name,"E02"))
            {
             //  if(!strcasecmp(e1->CMD.system_name,"sentinel"))
                 if((!strcasecmp(e1->CMD.system_name,"sentinel"))||(!strcasecmp(e1->CMD.system_name,"fiber_optics")))
                {
                  
                   pthread_mutex_lock(&lock);
                    e2_senq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }
              /* else if(!strcasecmp(e1->CMD.system_name,"fiber_optics"))
                {
                 
                    pthread_mutex_lock(&lock);
                    e2_fiberq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }*/
              else if(!strcasecmp(e1->CMD.system_name,"front_end"))
               {
                
                  pthread_mutex_lock(&lock);
                  e2_frontq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             else if(!strcasecmp(e1->CMD.system_name,"back_end"))
              { 
                 
                   pthread_mutex_lock(&lock);
                   e2_backq_store(*e1); 
                   pthread_mutex_unlock(&lock);
                 
              }
             else if(!strcasecmp(e1->CMD.system_name,"self_test"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  e2_selfq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             }
               else if(!strcmp(e1->antenna_name,"E03"))
            {
              // if(!strcasecmp(e1->CMD.system_name,"sentinel"))
                 if((!strcasecmp(e1->CMD.system_name,"sentinel"))||(!strcasecmp(e1->CMD.system_name,"fiber_optics")))
                {
                  
                   pthread_mutex_lock(&lock);
                    e3_senq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }
              /* else if(!strcasecmp(e1->CMD.system_name,"fiber_optics"))
                {
                 
                    pthread_mutex_lock(&lock);
                    e3_fiberq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }*/
              else if(!strcasecmp(e1->CMD.system_name,"front_end"))
               {
                
                  pthread_mutex_lock(&lock);
                  e3_frontq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             else if(!strcasecmp(e1->CMD.system_name,"back_end"))
              { 
                 
                   pthread_mutex_lock(&lock);
                   e3_backq_store(*e1); 
                   pthread_mutex_unlock(&lock);
                 
              }
             else if(!strcasecmp(e1->CMD.system_name,"self_test"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  e3_selfq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             }
               else if(!strcmp(e1->antenna_name,"E04"))
            {
               //if(!strcasecmp(e1->CMD.system_name,"sentinel"))
                 if((!strcasecmp(e1->CMD.system_name,"sentinel"))||(!strcasecmp(e1->CMD.system_name,"fiber_optics")))
                {
                  
                   pthread_mutex_lock(&lock);
                    e4_senq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }
              /* else if(!strcasecmp(e1->CMD.system_name,"fiber_optics"))
                {
                 
                    pthread_mutex_lock(&lock);
                    e4_fiberq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }*/
              else if(!strcasecmp(e1->CMD.system_name,"front_end"))
               {
                
                  pthread_mutex_lock(&lock);
                  e4_frontq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             else if(!strcasecmp(e1->CMD.system_name,"back_end"))
              { 
                 
                   pthread_mutex_lock(&lock);
                   e4_backq_store(*e1); 
                   pthread_mutex_unlock(&lock);
                 
              }
             else if(!strcasecmp(e1->CMD.system_name,"self_test"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  e4_selfq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             }
               else if(!strcmp(e1->antenna_name,"E05"))
            {
               //if(!strcasecmp(e1->CMD.system_name,"sentinel"))
                 if((!strcasecmp(e1->CMD.system_name,"sentinel"))||(!strcasecmp(e1->CMD.system_name,"fiber_optics")))
                {
                  
                   pthread_mutex_lock(&lock);
                    e5_senq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }
              /* else if(!strcasecmp(e1->CMD.system_name,"fiber_optics"))
                {
                 
                    pthread_mutex_lock(&lock);
                    e5_fiberq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }*/
              else if(!strcasecmp(e1->CMD.system_name,"front_end"))
               {
                
                  pthread_mutex_lock(&lock);
                  e5_frontq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             else if(!strcasecmp(e1->CMD.system_name,"back_end"))
              { 
                 
                   pthread_mutex_lock(&lock);
                   e5_backq_store(*e1); 
                   pthread_mutex_unlock(&lock);
                 
              }
             else if(!strcasecmp(e1->CMD.system_name,"self_test"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  e5_selfq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             }
               else if(!strcmp(e1->antenna_name,"E06"))
            {
              // if(!strcasecmp(e1->CMD.system_name,"sentinel"))
                 if((!strcasecmp(e1->CMD.system_name,"sentinel"))||(!strcasecmp(e1->CMD.system_name,"fiber_optics")))
                {
                  
                   pthread_mutex_lock(&lock);
                    e6_senq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }
              /* else if(!strcasecmp(e1->CMD.system_name,"fiber_optics"))
                {
                 
                    pthread_mutex_lock(&lock);
                    e6_fiberq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }*/
              else if(!strcasecmp(e1->CMD.system_name,"front_end"))
               {
                
                  pthread_mutex_lock(&lock);
                  e6_frontq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             else if(!strcasecmp(e1->CMD.system_name,"back_end"))
              { 
                 
                   pthread_mutex_lock(&lock);
                   e6_backq_store(*e1); 
                   pthread_mutex_unlock(&lock);
                 
              }
             else if(!strcasecmp(e1->CMD.system_name,"self_test"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  e6_selfq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             }
               else if(!strcmp(e1->antenna_name,"S01"))
            {
              // if(!strcasecmp(e1->CMD.system_name,"sentinel"))
                 if((!strcasecmp(e1->CMD.system_name,"sentinel"))||(!strcasecmp(e1->CMD.system_name,"fiber_optics")))
                {
                  
                   pthread_mutex_lock(&lock);
                    s1_senq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }
             /*  else if(!strcasecmp(e1->CMD.system_name,"fiber_optics"))
                {
                 
                    pthread_mutex_lock(&lock);
                    s1_fiberq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }*/
              else if(!strcasecmp(e1->CMD.system_name,"front_end"))
               {
                
                  pthread_mutex_lock(&lock);
                  s1_frontq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             else if(!strcasecmp(e1->CMD.system_name,"back_end"))
              { 
                 
                   pthread_mutex_lock(&lock);
                   s1_backq_store(*e1); 
                   pthread_mutex_unlock(&lock);
                 
              }
             else if(!strcasecmp(e1->CMD.system_name,"self_test"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  s1_selfq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             }
             else if(!strcmp(e1->antenna_name,"S02"))
            {
              // if(!strcasecmp(e1->CMD.system_name,"sentinel"))
                 if((!strcasecmp(e1->CMD.system_name,"sentinel"))||(!strcasecmp(e1->CMD.system_name,"fiber_optics")))
                {
                  
                   pthread_mutex_lock(&lock);
                    s2_senq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }
             /*  else if(!strcasecmp(e1->CMD.system_name,"fiber_optics"))
                {
                 
                    pthread_mutex_lock(&lock);
                    s2_fiberq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }*/
              else if(!strcasecmp(e1->CMD.system_name,"front_end"))
               {
                
                  pthread_mutex_lock(&lock);
                  s2_frontq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             else if(!strcasecmp(e1->CMD.system_name,"back_end"))
              { 
                 
                   pthread_mutex_lock(&lock);
                   s2_backq_store(*e1); 
                   pthread_mutex_unlock(&lock);
                 
              }
             else if(!strcasecmp(e1->CMD.system_name,"self_test"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  s2_selfq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             }
             else if(!strcmp(e1->antenna_name,"S03"))
            {
              // if(!strcasecmp(e1->CMD.system_name,"sentinel"))
                if((!strcasecmp(e1->CMD.system_name,"sentinel"))||(!strcasecmp(e1->CMD.system_name,"fiber_optics")))
                {
                  
                   pthread_mutex_lock(&lock);
                    s3_senq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }
              /* else if(!strcasecmp(e1->CMD.system_name,"fiber_optics"))
                {
                 
                    pthread_mutex_lock(&lock);
                    s3_fiberq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }*/
              else if(!strcasecmp(e1->CMD.system_name,"front_end"))
               {
                
                  pthread_mutex_lock(&lock);
                  s3_frontq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             else if(!strcasecmp(e1->CMD.system_name,"back_end"))
              { 
                 
                   pthread_mutex_lock(&lock);
                   s3_backq_store(*e1); 
                   pthread_mutex_unlock(&lock);
                 
              }
             else if(!strcasecmp(e1->CMD.system_name,"self_test"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  s3_selfq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             }
             else if(!strcmp(e1->antenna_name,"S04"))
            {
              // if(!strcasecmp(e1->CMD.system_name,"sentinel"))
                if((!strcasecmp(e1->CMD.system_name,"sentinel"))||(!strcasecmp(e1->CMD.system_name,"fiber_optics")))
                {
                  
                   pthread_mutex_lock(&lock);
                    s4_senq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }
             /*  else if(!strcasecmp(e1->CMD.system_name,"fiber_optics"))
                {
                 
                    pthread_mutex_lock(&lock);
                    s4_fiberq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }*/
              else if(!strcasecmp(e1->CMD.system_name,"front_end"))
               {
                
                  pthread_mutex_lock(&lock);
                  s4_frontq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             else if(!strcasecmp(e1->CMD.system_name,"back_end"))
              { 
                 
                   pthread_mutex_lock(&lock);
                   s4_backq_store(*e1); 
                   pthread_mutex_unlock(&lock);
                 
              }
             else if(!strcasecmp(e1->CMD.system_name,"self_test"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  s4_selfq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             }
             else if(!strcmp(e1->antenna_name,"S06"))
            {
              // if(!strcasecmp(e1->CMD.system_name,"sentinel"))
                 if((!strcasecmp(e1->CMD.system_name,"sentinel"))||(!strcasecmp(e1->CMD.system_name,"fiber_optics")))
                {
                  
                   pthread_mutex_lock(&lock);
                    s6_senq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }
              /* else if(!strcasecmp(e1->CMD.system_name,"fiber_optics"))
                {
                 
                    pthread_mutex_lock(&lock);
                    s6_fiberq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }*/
              else if(!strcasecmp(e1->CMD.system_name,"front_end"))
               {
                
                  pthread_mutex_lock(&lock);
                  s6_frontq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             else if(!strcasecmp(e1->CMD.system_name,"back_end"))
              { 
                 
                   pthread_mutex_lock(&lock);
                   s6_backq_store(*e1); 
                   pthread_mutex_unlock(&lock);
                 
              }
             else if(!strcasecmp(e1->CMD.system_name,"self_test"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  s6_selfq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             }
             else if(!strcmp(e1->antenna_name,"W01"))
            {
              // if(!strcasecmp(e1->CMD.system_name,"sentinel"))
                 if((!strcasecmp(e1->CMD.system_name,"sentinel"))||(!strcasecmp(e1->CMD.system_name,"fiber_optics")))
                {
                  
                   pthread_mutex_lock(&lock);
                    w1_senq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }
              /* else if(!strcasecmp(e1->CMD.system_name,"fiber_optics"))
                {
                 
                    pthread_mutex_lock(&lock);
                    w1_fiberq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }*/
              else if(!strcasecmp(e1->CMD.system_name,"front_end"))
               {
                
                  pthread_mutex_lock(&lock);
                  w1_frontq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             else if(!strcasecmp(e1->CMD.system_name,"back_end"))
              { 
                 
                   pthread_mutex_lock(&lock);
                   w1_backq_store(*e1); 
                   pthread_mutex_unlock(&lock);
                 
              }
             else if(!strcasecmp(e1->CMD.system_name,"self_test"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  w1_selfq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             }
              else if(!strcmp(e1->antenna_name,"W02"))
            {
               //if(!strcasecmp(e1->CMD.system_name,"sentinel"))
                 if((!strcasecmp(e1->CMD.system_name,"sentinel"))||(!strcasecmp(e1->CMD.system_name,"fiber_optics")))
                {
                  
                   pthread_mutex_lock(&lock);
                    w2_senq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }
              /* else if(!strcasecmp(e1->CMD.system_name,"fiber_optics"))
                {
                 
                    pthread_mutex_lock(&lock);
                    w2_fiberq_store(*e1);
                    pthread_mutex_unlock(&lock);
                } */
              else if(!strcasecmp(e1->CMD.system_name,"front_end"))
               {
                
                  pthread_mutex_lock(&lock);
                  w2_frontq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             else if(!strcasecmp(e1->CMD.system_name,"back_end"))
              { 
                 
                   pthread_mutex_lock(&lock);
                   w2_backq_store(*e1); 
                   pthread_mutex_unlock(&lock);
                 
              }
             else if(!strcasecmp(e1->CMD.system_name,"self_test"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  w2_selfq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             }
              else if(!strcmp(e1->antenna_name,"W03"))
            {
              // if(!strcasecmp(e1->CMD.system_name,"sentinel"))
                 if((!strcasecmp(e1->CMD.system_name,"sentinel"))||(!strcasecmp(e1->CMD.system_name,"fiber_optics")))
                {
                  
                   pthread_mutex_lock(&lock);
                    w3_senq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }
             /*  else if(!strcasecmp(e1->CMD.system_name,"fiber_optics"))
                {
                 
                    pthread_mutex_lock(&lock);
                    w3_fiberq_store(*e1);
                    pthread_mutex_unlock(&lock);
                } */
              else if(!strcasecmp(e1->CMD.system_name,"front_end"))
               {
                
                  pthread_mutex_lock(&lock);
                  w3_frontq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             else if(!strcasecmp(e1->CMD.system_name,"back_end"))
              { 
                 
                   pthread_mutex_lock(&lock);
                   w3_backq_store(*e1); 
                   pthread_mutex_unlock(&lock);
                 
              }
             else if(!strcasecmp(e1->CMD.system_name,"self_test"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  w3_selfq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             }
              else if(!strcmp(e1->antenna_name,"W04"))
            {
               //if(!strcasecmp(e1->CMD.system_name,"sentinel"))
                 if((!strcasecmp(e1->CMD.system_name,"sentinel"))||(!strcasecmp(e1->CMD.system_name,"fiber_optics")))
                {
                  
                   pthread_mutex_lock(&lock);
                    w4_senq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }
              /* else if(!strcasecmp(e1->CMD.system_name,"fiber_optics"))
                {
                 
                    pthread_mutex_lock(&lock);
                    w4_fiberq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }*/
              else if(!strcasecmp(e1->CMD.system_name,"front_end"))
               {
                
                  pthread_mutex_lock(&lock);
                  w4_frontq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             else if(!strcasecmp(e1->CMD.system_name,"back_end"))
              { 
                 
                   pthread_mutex_lock(&lock);
                   w4_backq_store(*e1); 
                   pthread_mutex_unlock(&lock);
                 
              }
             else if(!strcasecmp(e1->CMD.system_name,"self_test"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  w4_selfq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             }
              else if(!strcmp(e1->antenna_name,"W05"))
            {
              // if(!strcasecmp(e1->CMD.system_name,"sentinel"))
                  if((!strcasecmp(e1->CMD.system_name,"sentinel"))||(!strcasecmp(e1->CMD.system_name,"fiber_optics")))
                  {
                  
                   pthread_mutex_lock(&lock);
                    w5_senq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }
              /* else if(!strcasecmp(e1->CMD.system_name,"fiber_optics"))
                {
                 
                    pthread_mutex_lock(&lock);
                    w5_fiberq_store(*e1);
                    pthread_mutex_unlock(&lock);
                } */
              else if(!strcasecmp(e1->CMD.system_name,"front_end"))
               {
                
                  pthread_mutex_lock(&lock);
                  w5_frontq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             else if(!strcasecmp(e1->CMD.system_name,"back_end"))
              { 
                 
                   pthread_mutex_lock(&lock);
                   w5_backq_store(*e1); 
                   pthread_mutex_unlock(&lock);
                 
              }
             else if(!strcasecmp(e1->CMD.system_name,"self_test"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  w5_selfq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             }
              else if(!strcmp(e1->antenna_name,"W06"))
            {
              // if(!strcasecmp(e1->CMD.system_name,"sentinel"))
                 if((!strcasecmp(e1->CMD.system_name,"sentinel"))||(!strcasecmp(e1->CMD.system_name,"fiber_optics")))
                {
                  
                   pthread_mutex_lock(&lock);
                    w6_senq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }
              /* else if(!strcasecmp(e1->CMD.system_name,"fiber_optics"))
                {
                 
                    pthread_mutex_lock(&lock);
                    w6_fiberq_store(*e1);
                    pthread_mutex_unlock(&lock);
                }*/
              else if(!strcasecmp(e1->CMD.system_name,"front_end"))
               {
                
                  pthread_mutex_lock(&lock);
                  w6_frontq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             else if(!strcasecmp(e1->CMD.system_name,"back_end"))
              { 
                 
                   pthread_mutex_lock(&lock);
                   w6_backq_store(*e1); 
                   pthread_mutex_unlock(&lock);
                 
              }
             else if(!strcasecmp(e1->CMD.system_name,"self_test"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  w6_selfq_store(*e1);
                  pthread_mutex_unlock(&lock);
               }
             }
             else
              { fprintf(stderr,"###### Antenna name doesn't match\n"); }
                 
          /* fprintf(stderr,"Size of Command structure is %d\n",sizeof(ANT_CMD));
           fprintf(stderr,"Antenna Name is %s\n",e1->antenna_name);
           fprintf(stderr,"Operation Name is %s\n",e1->CMD.op_name);
           c = &e1->CMD;
            printcmd(c); */
         
         if (sfd1 < 0) 
            fprintf(stderr,"ERROR Accept socket\n");

           strcpy(a1->ant_name,e1->antenna_name);
           strcpy(a1->sys_name,e1->CMD.system_name);
           write(sfd1,a1,sizeof(ACK));
        
         /*  if (n < 0)
                fprintf(stderr,"ERROR writing socket\n");
            else
            printf("we wrote on the socket %s %s\n",a1->ant_name,a1->sys_name); */
            close(sfd1);
      }
        close(sofd);
}
