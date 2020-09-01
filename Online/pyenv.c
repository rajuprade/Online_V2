#include"pyenv.h"
#include"server.h"
#include"servo.h"
#include"servo_queue.h"
#include"queue.h"
#include"socket.h"

void* pyenv_interface( void* parameters)
{
  
      PYS *py;
      py = malloc(sizeof(PYS));
      char buff[2048];
      ANT_CMD *e1;
      e1 = malloc(sizeof(ANT_CMD));
     
      PYACK *a1;
      a1 = malloc(sizeof(PYACK));
    
      SRVANT_CMD *s1;
      s1 = malloc(sizeof(SRVANT_CMD));

      int i,j,no_element,n,sofd,sfd1,m;
      char *token,*del=" ",cmd1[10][20];
     
             
      sofd=init_server(PORT_PYENV);
      if(sofd == -1 )
     {
       fprintf(stderr,"=> PYTHON ENVIRONMENT SERVER NOT OPENED =>\n");
     }
     clilen = sizeof(cli_addr); 
     
        
     while(1)
    {
        fprintf(stderr,"$$$ SERVER WANTING FOR PYTHON ENVIRONMENT CLIENT TO CONNECT $$$$\n");
        sfd1 = accept(sofd,(struct sockaddr *) &cli_addr,&clilen);
        fprintf(stderr,"#### Client=> %s Port %d\n",inet_ntoa(cli_addr.sin_addr),ntohs(cli_addr.sin_port));
       
        while(1)
         {
              // bzero(py,sizeof(PYS));
                 bzero(py,2048);
              n = read( sfd1,py,sizeof(PYS));
              if(n)
                  {
                    fprintf(stderr,"====>Size of read is %d\n",n);
                  }
              //memcpy(py, buff, sizeof(buff));
              //if((n=read(sfd1,py,sizeof(PYS)))!=sizeof(PYS))
               /* if(read(sfd1,py,sizeof(PYS)))             
                {
                   fprintf(stderr,"ERROR READING COMMAND FROM PY ENV\n"); 
                   perror(n);
                   close(sfd1);
                   break;
                } */
                else if(n==0)
                {
                  fprintf(stderr," PYTHON Socket connection CLOSED\n");
                   close(sfd1);
                   break;
                }

              else
               { fprintf(stderr," PYTHON #########\n"); } 
             //read(sfd1,py,sizeof(PYS));
            for(i=0;i<py->no_of_antennas;i++)
             {
               fprintf(stderr,"PYTHON ANTENNA name %s\n",py->antenna_list[i]);
               fprintf(stderr,"PYTHON SYSTEM name %s\n",py->system_name);
               //fprintf(stderr,"PYTHON SYSTEM name %s\n",py->cmd_name);
                
                strcpy(e1->antenna_name,py->antenna_list[i]);
                strcpy(e1->CMD.system_name,py->system_name);
                // for servo
               if(!strcasecmp(py->system_name,"servo")) {
                strcpy(s1->SRVCMD.system_name,py->system_name);
                memcpy(&s1->SRVCMD, py->buffer_cmd, sizeof(s1->SRVCMD));
                for(m=0;m<s1->SRVCMD.number_param;m++) {
                fprintf(stderr," para name  %s:",s1->SRVCMD.para_name[m]);
                fprintf(stderr," para value: %s",s1->SRVCMD.para_value[m]);
                }
               }

                /*token=strtok(py->cmd_name,del);
                 j=0;
                while(token !=NULL)
                 { 
                        // i=0;
                   strcpy(cmd1[j],token);
                   fprintf(stderr," CMD[%d] => %s\n",j,cmd1[j]);
                   j++; 
                   no_element = j;
                  //fprintf(stderr," Number of Element is %d\n",no_element);
                    token =  strtok(NULL," ");
                 }
                
                strcpy(e1->CMD.op_name,cmd1[0]);
                e1->CMD.number_param=1;
                strcpy(e1->CMD.parameter_name[0],cmd1[1]);
                strcpy(e1->CMD.Argument_Ch1[0],cmd1[2]);
                strcpy(e1->CMD.Argument_Ch2[0],cmd1[3]); */
                memcpy(&e1->CMD, py->buffer_cmd, sizeof(e1->CMD));
                fprintf(stderr," param_number %d\n",e1->CMD.number_param);
               if(strcasecmp(py->system_name,"servo")) {
                for(m=0;m<e1->CMD.number_param;m++) {
                fprintf(stderr," para name  %s:",e1->CMD.parameter_name[m]);
                fprintf(stderr," argument ch1: %s",e1->CMD.Argument_Ch1[m]);
                fprintf(stderr," argument ch2: %s\n",e1->CMD.Argument_Ch2[m]);
                }
                }
 
                if(!strcmp(e1->antenna_name,"C00"))
            {
              if(!strcasecmp(py->system_name,"servo"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  C00srv_store(*s1); 
                  pthread_mutex_unlock(&lock);
               }
             else 
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
             else if(!strcasecmp(e1->CMD.system_name,"fps"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  fpsq_store(*e1); 
                  pthread_mutex_unlock(&lock);
               }
             }

            else if(!strcmp(e1->antenna_name,"C01"))
            {
              // if(!strcasecmp(e1->CMD.system_name,"sentinel"))
              if(!strcasecmp(py->system_name,"servo"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  C01srv_store(*s1); 
                  pthread_mutex_unlock(&lock);
               }
             else 
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
             else if(!strcasecmp(e1->CMD.system_name,"fps"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  c1_fpsq_store(*e1); 
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
              if(!strcasecmp(py->system_name,"servo"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  C02srv_store(*s1); 
                  pthread_mutex_unlock(&lock);
               }
             else 
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
             else if(!strcasecmp(e1->CMD.system_name,"fps"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  c2_fpsq_store(*e1); 
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
              if(!strcasecmp(py->system_name,"servo"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  C03srv_store(*s1); 
                  pthread_mutex_unlock(&lock);
               }
             else 
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
             else if(!strcasecmp(e1->CMD.system_name,"fps"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  c3_fpsq_store(*e1); 
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
              if(!strcasecmp(py->system_name,"servo"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  C04srv_store(*s1); 
                  pthread_mutex_unlock(&lock);
               }
             else 
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
             else if(!strcasecmp(e1->CMD.system_name,"fps"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  c4_fpsq_store(*e1); 
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
              if(!strcasecmp(py->system_name,"servo"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  C05srv_store(*s1); 
                  pthread_mutex_unlock(&lock);
               }
             else 
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
             else if(!strcasecmp(e1->CMD.system_name,"fps"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  c5_fpsq_store(*e1); 
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
              if(!strcasecmp(py->system_name,"servo"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  C06srv_store(*s1); 
                  pthread_mutex_unlock(&lock);
               }
             else 
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
             else if(!strcasecmp(e1->CMD.system_name,"fps"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  c6_fpsq_store(*e1); 
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
              if(!strcasecmp(py->system_name,"servo"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  C01srv_store(*s1); 
                  pthread_mutex_unlock(&lock);
               }
             else 
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
             else if(!strcasecmp(e1->CMD.system_name,"fps"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  c9_fpsq_store(*e1); 
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
              if(!strcasecmp(py->system_name,"servo"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  C08srv_store(*s1); 
                  pthread_mutex_unlock(&lock);
               }
             else 
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
             else if(!strcasecmp(e1->CMD.system_name,"fps"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  c8_fpsq_store(*e1); 
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
              if(!strcasecmp(py->system_name,"servo"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  C10srv_store(*s1); 
                  pthread_mutex_unlock(&lock);
               }
             else 
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
                   c10_backq_store(*e1); 
                   pthread_mutex_unlock(&lock);
                 
              }
             else if(!strcasecmp(e1->CMD.system_name,"fps"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  c10_fpsq_store(*e1); 
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
              if(!strcasecmp(py->system_name,"servo"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  C11srv_store(*s1); 
                  pthread_mutex_unlock(&lock);
               }
             else 
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
             else if(!strcasecmp(e1->CMD.system_name,"fps"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  c11_fpsq_store(*e1); 
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
              if(!strcasecmp(py->system_name,"servo"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  C12srv_store(*s1); 
                  pthread_mutex_unlock(&lock);
               }
             else 
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
             else if(!strcasecmp(e1->CMD.system_name,"fps"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  c12_fpsq_store(*e1); 
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
              if(!strcasecmp(py->system_name,"servo"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  C13srv_store(*s1); 
                  pthread_mutex_unlock(&lock);
               }
             else 
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
             else if(!strcasecmp(e1->CMD.system_name,"fps"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  c13_fpsq_store(*e1); 
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
              if(!strcasecmp(py->system_name,"servo"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  C14srv_store(*s1); 
                  pthread_mutex_unlock(&lock);
               }
             else 
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
             else if(!strcasecmp(e1->CMD.system_name,"fps"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  c14_fpsq_store(*e1); 
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
              if(!strcasecmp(py->system_name,"servo"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  E02srv_store(*s1); 
                  pthread_mutex_unlock(&lock);
               }
             else 
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
             else if(!strcasecmp(e1->CMD.system_name,"fps"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  e2_fpsq_store(*e1); 
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
              if(!strcasecmp(py->system_name,"servo"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  E03srv_store(*s1); 
                  pthread_mutex_unlock(&lock);
               }
             else 
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
             else if(!strcasecmp(e1->CMD.system_name,"fps"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  e3_fpsq_store(*e1); 
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
              if(!strcasecmp(py->system_name,"servo"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  E04srv_store(*s1); 
                  pthread_mutex_unlock(&lock);
               }
             else 
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
             else if(!strcasecmp(e1->CMD.system_name,"fps"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  e4_fpsq_store(*e1); 
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
              if(!strcasecmp(py->system_name,"servo"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  E05srv_store(*s1); 
                  pthread_mutex_unlock(&lock);
               }
             else 
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
             else if(!strcasecmp(e1->CMD.system_name,"fps"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  e5_fpsq_store(*e1); 
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
              if(!strcasecmp(py->system_name,"servo"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  E06srv_store(*s1); 
                  pthread_mutex_unlock(&lock);
               }
             else 
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
             else if(!strcasecmp(e1->CMD.system_name,"fps"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  e6_fpsq_store(*e1); 
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
              if(!strcasecmp(py->system_name,"servo"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  S01srv_store(*s1); 
                  pthread_mutex_unlock(&lock);
               }
             else 
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
             else if(!strcasecmp(e1->CMD.system_name,"fps"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  s1_fpsq_store(*e1); 
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
              if(!strcasecmp(py->system_name,"servo"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  S02srv_store(*s1); 
                  pthread_mutex_unlock(&lock);
               }
             else 
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
             else if(!strcasecmp(e1->CMD.system_name,"fps"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  s2_fpsq_store(*e1); 
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
              if(!strcasecmp(py->system_name,"servo"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  S03srv_store(*s1); 
                  pthread_mutex_unlock(&lock);
               }
             else 
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
             else if(!strcasecmp(e1->CMD.system_name,"fps"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  s3_fpsq_store(*e1); 
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
              if(!strcasecmp(py->system_name,"servo"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  S04srv_store(*s1); 
                  pthread_mutex_unlock(&lock);
               }
             else 
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
             else if(!strcasecmp(e1->CMD.system_name,"fps"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  s4_fpsq_store(*e1); 
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
              if(!strcasecmp(py->system_name,"servo"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  S06srv_store(*s1); 
                  pthread_mutex_unlock(&lock);
               }
             else 
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
             else if(!strcasecmp(e1->CMD.system_name,"fps"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  s6_fpsq_store(*e1); 
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
              if(!strcasecmp(py->system_name,"servo"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  W01srv_store(*s1); 
                  pthread_mutex_unlock(&lock);
               }
             else 
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
             else if(!strcasecmp(e1->CMD.system_name,"fps"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  w1_fpsq_store(*e1); 
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
              if(!strcasecmp(py->system_name,"servo"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  W02srv_store(*s1); 
                  pthread_mutex_unlock(&lock);
               }
             else 
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
             else if(!strcasecmp(e1->CMD.system_name,"fps"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  w2_fpsq_store(*e1); 
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
              if(!strcasecmp(py->system_name,"servo"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  W03srv_store(*s1); 
                  pthread_mutex_unlock(&lock);
               }
             else 
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
             else if(!strcasecmp(e1->CMD.system_name,"fps"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  w3_fpsq_store(*e1); 
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
              if(!strcasecmp(py->system_name,"servo"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  W04srv_store(*s1); 
                  pthread_mutex_unlock(&lock);
               }
             else 
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
             else if(!strcasecmp(e1->CMD.system_name,"fps"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  w4_fpsq_store(*e1); 
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
              if(!strcasecmp(py->system_name,"servo"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  W05srv_store(*s1); 
                  pthread_mutex_unlock(&lock);
               }
             else 
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
             else if(!strcasecmp(e1->CMD.system_name,"fps"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  w5_fpsq_store(*e1); 
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
              if(!strcasecmp(py->system_name,"servo"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  W06srv_store(*s1); 
                  pthread_mutex_unlock(&lock);
               }
             else 
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
             else if(!strcasecmp(e1->CMD.system_name,"fps"))
              {
                 
                  pthread_mutex_lock(&lock); 
                  w6_fpsq_store(*e1); 
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
            }
      
          }
      }
        close(sofd);
}
