#include"servo.h"
#include"socket.h"
#include"ssclink.h"

void AskAx(SRVANT_CMD *a1)
{
  /* unsigned char c;
   fprintf(stderr,"Enter the AXIS (A/E/B) :\n");
   scanf("%c",&c);
   fprintf(stderr,"Entered Axis is %c\n",c); */
   strcpy(a1->SRVCMD.para_name[0],"ax");
   strcpy(a1->SRVCMD.para_value[0],"B");
  // sprintf(a1->SRVCMD.para_value[0],"%c\0",c);
}

void AskAng(SRVANT_CMD *a1)
{ 
  char buff[11];
  fprintf(stderr,"Enter the Ang(+/-ddd:mm:ss) :\n");
  scanf("%s",buff);
}

void AskTime(SRVANT_CMD *a1)
{
   char buf[9];
   fprintf(stderr,"Enter the Time (hh:mm:ss) :\n");
   scanf("%s",buf);
}

void printservocmd(servocmd *c1)
{
   int i;
        printf("we wrote on the socket %d %s %s %s\n",c1->seq,c1->timestamp,c1->system_name,c1->op_name);
       
        for(i=0;i<c1->number_param;i++)
        {
          printf("%s %s\n",c1->para_name[i],c1->para_value[i]);
        } 
        printf(" Size of Struct is ######## %d\n",sizeof(servocmd));
     
}


void printservoresp(servoresp *r1)
{
   int i;
   fprintf(stderr," Size of Response Struct is ######## %d\n",sizeof(servoresp));
   fprintf(stderr,"SEQ number is %d\n",r1->seq);
   fprintf(stderr,"Timestamp is %s\n",r1->timestamp);
   fprintf(stderr,"System name is %s\n",r1->system_name);
   fprintf(stderr,"Response code is %d\n",r1->response_code);
   fprintf(stderr,"Response type is %d\n",r1->response_type);
     fprintf(stderr,"%s\n",r1->response_msg);
   if(r1->response_code == 1 )
     fprintf(stderr,"%s\n",r1->response_msg);
    else if(r1->response_code == 2 && r1->response_type == 1)
             fprintf(stderr,"%s\n",r1->response_msg);
    else if(r1->response_code == 2 && r1->response_type == 2)
            fprintf(stderr,"%s\n",r1->response_msg);
    else if(r1->response_code == 3)
        fprintf(stderr,"%s\n",r1->response_msg);
    else if(r1->response_code == 4)
          {
             for(i=0; i<r1->num_resp_msg;i++)
            {
              fprintf(stderr,"%s\n",r1->para_name[i]);
              fprintf(stderr,"%s\n",r1->para_value[i]);
            }
           }
   else
    fprintf(stderr,"No Response from Servo system\n");

}
void servo_cmd_list(int cmd,SRVANT_CMD *a1)
{
    unsigned char c;
    char buf[11];
    char buff[9];
      switch(cmd)
     {
       case COLDSTART: a1->SRVCMD.seq= 10;
                      strcpy(a1->SRVCMD.op_name,"coldstart");    // Command ID 40
                     // sprintf(a1->SRVCMD.SRVCMD_code,"%s","0x40"); 
                      a1->SRVCMD.number_param=0;
                      fprintf(stderr,"********** %s\n",a1->SRVCMD.op_name);
                       break;
      case TRACK:  a1->SRVCMD.seq= 11;
                   strcpy(a1->SRVCMD.op_name,"track"); 
                  //  sprintf(a1->SRVCMD.SRVCMD_code,"%s","0x44");// Command ID 44
                   a1->SRVCMD.number_param=4;
                   // strcpy(a1->SRVCMD.para_name[0],"ax");
                    AskAx(a1); //fprintf(stderr,"Entered Axis is %c\n",c);
                  // fprintf(stderr,"Enter the Axis(A/E/B):\n");
                  // scanf("%c",&c);
                  // strcpy(a1->SRVCMD.para_value[0],"B");
                //   sprintf(a1->SRVCMD.para_value[0],"%c\0",c);
                   strcpy(a1->SRVCMD.para_name[1],"time"); // Duration for tracking the source
                   // fprintf(stderr,"Enter the Time in hh:mm:ss:\n");
                  // scanf("%s",buf);
                   //sprintf(a1->SRVCMD.para_value[1],"%s",buff);
                    strcpy(a1->SRVCMD.para_value[1],"19:00:00");
                  // strcpy(a1->SRVCMD.para_value[1],"16:00:00");
                  
                   strcpy(a1->SRVCMD.para_name[2],"ang1");
                   strcpy(a1->SRVCMD.para_value[2],"115:00:00");
                   strcpy(a1->SRVCMD.para_name[3],"ang2");
                   strcpy(a1->SRVCMD.para_value[3],"90:00:00");
                   fprintf(stderr,"********** %s\n",a1->SRVCMD.op_name); 
                    break;
      case HOLD:  a1->SRVCMD.seq= 12;
                  strcpy(a1->SRVCMD.op_name,"hold"); // Command ID 46
                 // sprintf(a1->SRVCMD.SRVCMD_code,"%s","0x46");
                  a1->SRVCMD.number_param=1;
                   AskAx(a1);
                  //strcpy(a1->SRVCMD.para_name[0],"ax");
                  //strcpy(a1->SRVCMD.para_value[0],"B");
                  fprintf(stderr,"********** %s\n",a1->SRVCMD.op_name); 
                  break;
      case POSITION: a1->SRVCMD.seq= 13;
                     strcpy(a1->SRVCMD.op_name,"position"); // Command ID 42
                  //  sprintf(a1->SRVCMD.SRVCMD_code,"%s","0x42");
                     a1->SRVCMD.number_param=3;
                    // strcpy(a1->SRVCMD.para_name[0],"ax");
                    // strcpy(a1->SRVCMD.para_value[0],"B");
                        AskAx(a1);
                     strcpy(a1->SRVCMD.para_name[1],"ang1");
                     strcpy(a1->SRVCMD.para_value[1],"100:00:00");
                   
                     strcpy(a1->SRVCMD.para_name[2],"ang2");
                     strcpy(a1->SRVCMD.para_value[2],"45:00:00");
                     fprintf(stderr,"********** %s\n",a1->SRVCMD.op_name); 
                      break;
       case STOP:  a1->SRVCMD.seq= 14;
                  strcpy(a1->SRVCMD.op_name,"stop");          // Command ID 48
                 // sprintf(a1->SRVCMD.SRVCMD_code,"%s","0x48");
                  a1->SRVCMD.number_param=1;
                      AskAx(a1);
                   //strcpy(a1->SRVCMD.para_name[0],"ax");
                  // strcpy(a1->SRVCMD.para_value[0],"B");
                   fprintf(stderr,"********** %s\n",a1->SRVCMD.op_name);
                  break;  
       case CLOSE:  a1->SRVCMD.seq= 15;
                   strcpy(a1->SRVCMD.op_name,"close");   // Command ID 4a
                  //sprintf(a1->SRVCMD.SRVCMD_code,"%s","0x4a");
                   a1->SRVCMD.number_param=0;fprintf(stderr,"********** %s\n",a1->SRVCMD.op_name);
                   break; 
       case STOW:  a1->SRVCMD.seq= 16;
                  strcpy(a1->SRVCMD.op_name,"stow");   // Command ID 4c
                //  sprintf(a1->SRVCMD.SRVCMD_code,"%s","0x4c");
                  a1->SRVCMD.number_param=1;
                   AskAx(a1);
                  // strcpy(a1->SRVCMD.para_name[0],"ax");
                  // strcpy(a1->SRVCMD.para_value[0],"B");
                   fprintf(stderr,"********** %s\n",a1->SRVCMD.op_name);
                  break;
      case STOWRELEASE:  a1->SRVCMD.seq= 17;
                  strcpy(a1->SRVCMD.op_name,"stow_release"); // Command ID 4e
                 // sprintf(a1->SRVCMD.SRVCMD_code,"%s","0x4e");
                  a1->SRVCMD.number_param=1;AskAx(a1);
                 // strcpy(a1->SRVCMD.para_name[0],"ax");
                 // strcpy(a1->SRVCMD.para_value[0],"B");
                  fprintf(stderr,"********** %s\n",a1->SRVCMD.op_name);
                  break;
      case ABORT:  a1->SRVCMD.seq= 18;
                   strcpy(a1->SRVCMD.op_name,"abort");// Command ID 50
                  // sprintf(a1->SRVCMD.SRVCMD_code,"%s","0x50");
                   a1->SRVCMD.number_param=0;fprintf(stderr,"%s\n",a1->SRVCMD.op_name);
                   break; 
         
      case RESETHW: a1->SRVCMD.seq= 19;
                   strcpy(a1->SRVCMD.op_name,"resethw");// Command ID 6e
                  // sprintf(a1->SRVCMD.SRVCMD_code,"%s","0x6e"); 
                   a1->SRVCMD.number_param=0; fprintf(stderr,"%s\n",a1->SRVCMD.op_name);
                   break; 
      case READANGLES:a1->SRVCMD.seq= 20;
                   strcpy(a1->SRVCMD.op_name,"readangles"); // command ID 30 in present Online
                //   sprintf(a1->SRVCMD.SRVCMD_code,"%s","0x30");
                   a1->SRVCMD.number_param=0;
                   fprintf(stderr,"%s\n",a1->SRVCMD.op_name);
                    break;
      case READANAVAR:a1->SRVCMD.seq= 21;
                   strcpy(a1->SRVCMD.op_name,"readanavar"); // Command ID 32 
                   //sprintf(a1->SRVCMD.SRVCMD_code,"%s","0x32");
                   a1->SRVCMD.number_param=0; 
                   fprintf(stderr,"%s\n",a1->SRVCMD.op_name);
                    break;
      case READDIGVAR:a1->SRVCMD.seq= 22;
                   strcpy(a1->SRVCMD.op_name,"readdigvar"); // Command ID 34 
                 //  sprintf(a1->SRVCMD.SRVCMD_code,"%s","0x34");
                   a1->SRVCMD.number_param=0; 
                   fprintf(stderr,"%s\n",a1->SRVCMD.op_name);
                    break;
     case READSETPARA:a1->SRVCMD.seq= 23;
                   strcpy(a1->SRVCMD.op_name,"readsetpara"); // Command ID 36 
                   //sprintf(a1->SRVCMD.SRVCMD_code,"%s","0x36");
                   a1->SRVCMD.number_param=0; 
                   fprintf(stderr,"%s\n",a1->SRVCMD.op_name);
                    break;
     case READANTSTATUS:a1->SRVCMD.seq= 24;
                   strcpy(a1->SRVCMD.op_name,"readantstatus"); // Command ID 38
                 //  sprintf(a1->SRVCMD.SRVCMD_code,"%s","0x38");
                   a1->SRVCMD.number_param=0; 
                   fprintf(stderr,"%s\n",a1->SRVCMD.op_name);
                    break;
     case READVERSION:a1->SRVCMD.seq= 25;
                   strcpy(a1->SRVCMD.op_name,"readversion"); // Command ID 3a 
                 //  sprintf(a1->SRVCMD.SRVCMD_code,"%s","0x3a") ;
                   a1->SRVCMD.number_param=0; 
                   fprintf(stderr,"%s\n",a1->SRVCMD.op_name);
                    break;
    // Present Online Sub array Controller commands.
  //  case SENDSACSRC:   //send source coords to subarray controller modified to send trk/posn,TMAX
                        //sscanf(ra0, "%fh%fm%fs", &ra[0], &ra[1], &ra[2]);
                       // sscanf(dec0, "%fd%f\'%f\"", &dec[0], &dec[1], &dec[2]);
                       //cout << "test: " << ra0 << " " << dec0 << endl;
                        // rarad = (ra[0] + ra[1]/60. + ra[2]/3600.)*M_PI/12.;           // 12 h - PI rad - 180 deg
                        // decrad = (dec[0] + dec[1]/60. + dec[2]/3600.)*M_PI/180.;
                         //fprintf(stderr,"RD DEC values %f %f\n",rarad,decrad);
                         // RArad = rarad;
                         // DECrad = decrad;
    //                      break;
   // case TRKSACSRC : //request subarray controller to track source
   // case STPSACTRK : // request SAC to stop tracking source
 
   // case GOSACOUT :  //    request SAC to track on outer track
   // case GOSACINN :  //   request SAC to track on inner track

  /*  case TRKELOFF :   // track elevation offset by IPA 
                      // Close previous track command issue new track command.
                      // Set Track parameter 
    case TRKAZOFF :   // track azimuth offset by IPA
                       // Close previous track command issue new track command. // Set New Track parameter 
    case TRKANTOFF:   // track azimuth, elevation offset by JPA,IPA
                      // Close previous track command issue new track command. // Set New Track parameter 
    case TRKRAOFF :   // track right ascension offset by IPA
                      // Close previous track command issue new track command. // Set New Track parameter 
    case TRKDECOFF:   // track declination offset by IPA
                      // Close previous track command issue new track command. // Set New Track parameter 
    case SCANELSRC :  // scan src in el with derv=ipa,ptime=jpa
                       // Close previous track command issue new track command. // Set New Track parameter 
    case SCANAZSRC :  // scan src in az with derv=ipa,ptime=jpa
                       // Close previous track command issue new track command. // Set New  Track parameter 
    case SCANRASRC :  // scan src in ra with derv=ipa,ptime=jpa
                      // Close previous track command issue new track command. // Set New Track parameter 
    case SCANDEC :    //scan src in dec with derv=ipa,ptime=jpa 
                     // Close previous track command issue new track command. // Set New Track parameter 
    
// Commands in TELESET 
   
    1. sv trkset trkset.dat // Azimuth offset, Elevation offset, Antenna longitude,Antenna Latitude
    2. sv trkaz in // Set Azimuth out or in
    3. sv trkrate // Enter Ra rate, DEc rate & Time reference t0
    4. sv trkon track.dat // track.dat => Source name, Right ascension,Declinasion
    5. sv trkoff // Stop tracking 

*/
    }
     
}

void* servosystem( void* parameters)
{   
     int server_fd, *new_sock,Ret,sockfd,i;
     pthread_t servo_th;
    
      pthread_mutex_init(&locks,NULL);
      sockfd=init_server(PORT_SERVO);
      if(sockfd == -1)
      {
       fprintf(stderr," ####### SERV0 Socket opening failed ##########\n");
      }
     clilen = sizeof(cli_addr);
       fprintf(stderr,"==> SERVO SERVER WANTING FOR CLIENT CONNECTION ===>"); 
         while(1)
         {  
            i=0;
            server_fd = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen); 
            if(!strcmp(inet_ntoa(cli_addr.sin_addr),C00_SERVO_IP))
                     { 
                        new_sock = malloc(1);
                        *new_sock = server_fd;
                        fprintf(stderr," ACCEPTED CONNECTION C00 Servo System %s\n",inet_ntoa(cli_addr.sin_addr));
                         Ret= pthread_create(&servo_th,NULL,&C00_servo,(void *)new_sock); 
                          if(Ret)
                           { 
                             fprintf(stderr,"Error in Opening SERVO thread %d\n",Ret);
                           }
                          else 
                          {
                            fprintf(stderr,"SERVO thread opened succesfully=> %d\n",Ret); 
                         }
                     }
             else if(!strcmp(inet_ntoa(cli_addr.sin_addr),C01_SERVO_IP))
                     { 
                        new_sock = malloc(1);
                        *new_sock = server_fd;
                        fprintf(stderr," ACCEPTED CONNECTION C01 Servo System %s\n",inet_ntoa(cli_addr.sin_addr));
                         Ret= pthread_create(&servo_th,NULL,&C01_servo,(void *)new_sock); 
                          if(Ret)
                           { 
                             fprintf(stderr,"Error in Opening SERVO thread %d\n",Ret);
                           }
                          else 
                          {
                            fprintf(stderr,"SERVO thread opened succesfully=> %d\n",Ret); 
                         }
                     }
             else if(!strcmp(inet_ntoa(cli_addr.sin_addr),C02_SERVO_IP))
                     { 
                        new_sock = malloc(1);
                        *new_sock = server_fd;
                        fprintf(stderr," ACCEPTED CONNECTION C02 Servo System %s\n",inet_ntoa(cli_addr.sin_addr));
                         Ret= pthread_create(&servo_th,NULL,&C02_servo,(void *)new_sock); 
                          if(Ret)
                           { 
                             fprintf(stderr,"Error in Opening SERVO thread %d\n",Ret);
                           }
                          else 
                          {
                            fprintf(stderr,"SERVO thread opened succesfully=> %d\n",Ret); 
                         }
                     }
             else if(!strcmp(inet_ntoa(cli_addr.sin_addr),C03_SERVO_IP))
                     { 
                        new_sock = malloc(1);
                        *new_sock = server_fd;
                        fprintf(stderr," ACCEPTED CONNECTION C03 Servo System %s\n",inet_ntoa(cli_addr.sin_addr));
                         Ret= pthread_create(&servo_th,NULL,&C03_servo,(void *)new_sock); 
                          if(Ret)
                           { 
                             fprintf(stderr,"Error in Opening SERVO thread %d\n",Ret);
                           }
                          else 
                          {
                            fprintf(stderr,"SERVO thread opened succesfully=> %d\n",Ret); 
                         }
                     }
              else if(!strcmp(inet_ntoa(cli_addr.sin_addr),C04_SERVO_IP))
                     { 
                        new_sock = malloc(1);
                        *new_sock = server_fd;
                        fprintf(stderr," ACCEPTED CONNECTION C04 Servo System %s\n",inet_ntoa(cli_addr.sin_addr));
                         Ret= pthread_create(&servo_th,NULL,&C04_servo,(void *)new_sock); 
                          if(Ret)
                           { 
                             fprintf(stderr,"Error in Opening SERVO thread %d\n",Ret);
                           }
                          else 
                          {
                            fprintf(stderr,"SERVO thread opened succesfully=> %d\n",Ret); 
                         }
                     }
               else if(!strcmp(inet_ntoa(cli_addr.sin_addr),C05_SERVO_IP))
                     { 
                        new_sock = malloc(1);
                        *new_sock = server_fd;
                        fprintf(stderr," ACCEPTED CONNECTION C05 Servo System %s\n",inet_ntoa(cli_addr.sin_addr));
                         Ret= pthread_create(&servo_th,NULL,&C05_servo,(void *)new_sock); 
                          if(Ret)
                           { 
                             fprintf(stderr,"Error in Opening SERVO thread %d\n",Ret);
                           }
                          else 
                          {
                            fprintf(stderr,"SERVO thread opened succesfully=> %d\n",Ret); 
                         }
                     }
               else if(!strcmp(inet_ntoa(cli_addr.sin_addr),C06_SERVO_IP))
                     { 
                        new_sock = malloc(1);
                        *new_sock = server_fd;
                        fprintf(stderr," ACCEPTED CONNECTION C06 Servo System %s\n",inet_ntoa(cli_addr.sin_addr));
                         Ret= pthread_create(&servo_th,NULL,&C06_servo,(void *)new_sock); 
                          if(Ret)
                           { 
                             fprintf(stderr,"Error in Opening SERVO thread %d\n",Ret);
                           }
                          else 
                          {
                            fprintf(stderr,"SERVO thread opened succesfully=> %d\n",Ret); 
                         }
                     }
               else if(!strcmp(inet_ntoa(cli_addr.sin_addr),C08_SERVO_IP))
                     { 
                        new_sock = malloc(1);
                        *new_sock = server_fd;
                        fprintf(stderr," ACCEPTED CONNECTION C08 Servo System %s\n",inet_ntoa(cli_addr.sin_addr));
                         Ret= pthread_create(&servo_th,NULL,&C08_servo,(void *)new_sock); 
                          if(Ret)
                           { 
                             fprintf(stderr,"Error in Opening SERVO thread %d\n",Ret);
                           }
                          else 
                          {
                            fprintf(stderr,"SERVO thread opened succesfully=> %d\n",Ret); 
                         }
                     }
               else if(!strcmp(inet_ntoa(cli_addr.sin_addr),C09_SERVO_IP))
                     { 
                        new_sock = malloc(1);
                        *new_sock = server_fd;
                        fprintf(stderr," ACCEPTED CONNECTION C09 Servo System %s\n",inet_ntoa(cli_addr.sin_addr));
                         Ret= pthread_create(&servo_th,NULL,&C09_servo,(void *)new_sock); 
                          if(Ret)
                           { 
                             fprintf(stderr,"Error in Opening SERVO thread %d\n",Ret);
                           }
                          else 
                          {
                            fprintf(stderr,"SERVO thread opened succesfully=> %d\n",Ret); 
                         }
                     }
              else if(!strcmp(inet_ntoa(cli_addr.sin_addr),C10_SERVO_IP))
                     { 
                        new_sock = malloc(1);
                        *new_sock = server_fd;
                        fprintf(stderr," ACCEPTED CONNECTION C10 Servo System %s\n",inet_ntoa(cli_addr.sin_addr));
                         Ret= pthread_create(&servo_th,NULL,&C10_servo,(void *)new_sock); 
                          if(Ret)
                           { 
                             fprintf(stderr,"Error in Opening SERVO thread %d\n",Ret);
                           }
                          else 
                          {
                            fprintf(stderr,"SERVO thread opened succesfully=> %d\n",Ret); 
                         }
                     }
               else if(!strcmp(inet_ntoa(cli_addr.sin_addr),C11_SERVO_IP))
                     { 
                        new_sock = malloc(1);
                        *new_sock = server_fd;
                        fprintf(stderr," ACCEPTED CONNECTION C11 Servo System %s\n",inet_ntoa(cli_addr.sin_addr));
                         Ret= pthread_create(&servo_th,NULL,&C11_servo,(void *)new_sock); 
                          if(Ret)
                           { 
                             fprintf(stderr,"Error in Opening SERVO thread %d\n",Ret);
                           }
                          else 
                          {
                            fprintf(stderr,"SERVO thread opened succesfully=> %d\n",Ret); 
                         }
                     }
                    else if(!strcmp(inet_ntoa(cli_addr.sin_addr),C12_SERVO_IP))
                     { 
                        new_sock = malloc(1);
                        *new_sock = server_fd;
                        fprintf(stderr," ACCEPTED CONNECTION C12 Servo System %s\n",inet_ntoa(cli_addr.sin_addr));
                         Ret= pthread_create(&servo_th,NULL,&C12_servo,(void *)new_sock); 
                          if(Ret)
                           { 
                             fprintf(stderr,"Error in Opening SERVO thread %d\n",Ret);
                           }
                          else 
                          {
                            fprintf(stderr,"SERVO thread opened succesfully=> %d\n",Ret); 
                         }
                     }
                    else if(!strcmp(inet_ntoa(cli_addr.sin_addr),C13_SERVO_IP))
                     { 
                        new_sock = malloc(1);
                        *new_sock = server_fd;
                        fprintf(stderr," ACCEPTED CONNECTION C13 Servo System %s\n",inet_ntoa(cli_addr.sin_addr));
                         Ret= pthread_create(&servo_th,NULL,&C13_servo,(void *)new_sock); 
                          if(Ret)
                           { 
                             fprintf(stderr,"Error in Opening SERVO thread %d\n",Ret);
                           }
                          else 
                          {
                            fprintf(stderr,"SERVO thread opened succesfully=> %d\n",Ret); 
                         }
                     }
                   else if(!strcmp(inet_ntoa(cli_addr.sin_addr),C14_SERVO_IP))
                     { 
                        new_sock = malloc(1);
                        *new_sock = server_fd;
                        fprintf(stderr," ACCEPTED CONNECTION C14 Servo System %s\n",inet_ntoa(cli_addr.sin_addr));
                         Ret= pthread_create(&servo_th,NULL,&C14_servo,(void *)new_sock); 
                          if(Ret)
                           { 
                             fprintf(stderr,"Error in Opening SERVO thread %d\n",Ret);
                           }
                          else 
                          {
                            fprintf(stderr,"SERVO thread opened succesfully=> %d\n",Ret); 
                         }
                     }
                   else if(!strcmp(inet_ntoa(cli_addr.sin_addr),E02_SERVO_IP))
                     { 
                        new_sock = malloc(1);
                        *new_sock = server_fd;
                        fprintf(stderr," ACCEPTED CONNECTION E02 Servo System %s\n",inet_ntoa(cli_addr.sin_addr));
                         Ret= pthread_create(&servo_th,NULL,&E02_servo,(void *)new_sock); 
                          if(Ret)
                           { 
                             fprintf(stderr,"Error in Opening SERVO thread %d\n",Ret);
                           }
                          else 
                          {
                            fprintf(stderr,"SERVO thread opened succesfully=> %d\n",Ret); 
                         }
                     }
                  else if(!strcmp(inet_ntoa(cli_addr.sin_addr),E03_SERVO_IP))
                     { 
                        new_sock = malloc(1);
                        *new_sock = server_fd;
                        fprintf(stderr," ACCEPTED CONNECTION E03 Servo System %s\n",inet_ntoa(cli_addr.sin_addr));
                         Ret= pthread_create(&servo_th,NULL,&E03_servo,(void *)new_sock); 
                          if(Ret)
                           { 
                             fprintf(stderr,"Error in Opening SERVO thread %d\n",Ret);
                           }
                          else 
                          {
                            fprintf(stderr,"SERVO thread opened succesfully=> %d\n",Ret); 
                         }
                     }
                   else if(!strcmp(inet_ntoa(cli_addr.sin_addr),E04_SERVO_IP))
                     { 
                        new_sock = malloc(1);
                        *new_sock = server_fd;
                        fprintf(stderr," ACCEPTED CONNECTION E04 Servo System %s\n",inet_ntoa(cli_addr.sin_addr));
                         Ret= pthread_create(&servo_th,NULL,&E04_servo,(void *)new_sock); 
                          if(Ret)
                           { 
                             fprintf(stderr,"Error in Opening SERVO thread %d\n",Ret);
                           }
                          else 
                          {
                            fprintf(stderr,"SERVO thread opened succesfully=> %d\n",Ret); 
                         }
                     }
                  
                     else if(!strcmp(inet_ntoa(cli_addr.sin_addr),E06_SERVO_IP))
                     { 
                        new_sock = malloc(1);
                        *new_sock = server_fd;
                        fprintf(stderr," ACCEPTED CONNECTION E06 Servo System %s\n",inet_ntoa(cli_addr.sin_addr));
                         Ret= pthread_create(&servo_th,NULL,&E06_servo,(void *)new_sock); 
                          if(Ret)
                           { 
                             fprintf(stderr,"Error in Opening SERVO thread %d\n",Ret);
                           }
                          else 
                          {
                            fprintf(stderr,"SERVO thread opened succesfully=> %d\n",Ret); 
                         }
                     }
                   else if(!strcmp(inet_ntoa(cli_addr.sin_addr),S01_SERVO_IP))
                     { 
                        new_sock = malloc(1);
                        *new_sock = server_fd;
                        fprintf(stderr," ACCEPTED CONNECTION S01 Servo System %s\n",inet_ntoa(cli_addr.sin_addr));
                         Ret= pthread_create(&servo_th,NULL,&S01_servo,(void *)new_sock); 
                          if(Ret)
                           { 
                             fprintf(stderr,"Error in Opening SERVO thread %d\n",Ret);
                           }
                          else 
                          {
                            fprintf(stderr,"SERVO thread opened succesfully=> %d\n",Ret); 
                         }
                     }
                    else if(!strcmp(inet_ntoa(cli_addr.sin_addr),S02_SERVO_IP))
                     { 
                        new_sock = malloc(1);
                        *new_sock = server_fd;
                        fprintf(stderr," ACCEPTED CONNECTION S02 Servo System %s\n",inet_ntoa(cli_addr.sin_addr));
                         Ret= pthread_create(&servo_th,NULL,&S02_servo,(void *)new_sock); 
                          if(Ret)
                           { 
                             fprintf(stderr,"Error in Opening SERVO thread %d\n",Ret);
                           }
                          else 
                          {
                            fprintf(stderr,"SERVO thread opened succesfully=> %d\n",Ret); 
                         }
                     }
                   else if(!strcmp(inet_ntoa(cli_addr.sin_addr),S03_SERVO_IP))
                     { 
                        new_sock = malloc(1);
                        *new_sock = server_fd;
                        fprintf(stderr," ACCEPTED CONNECTION S03 Servo System %s\n",inet_ntoa(cli_addr.sin_addr));
                         Ret= pthread_create(&servo_th,NULL,&S03_servo,(void *)new_sock); 
                          if(Ret)
                           { 
                             fprintf(stderr,"Error in Opening SERVO thread %d\n",Ret);
                           }
                          else 
                          {
                            fprintf(stderr,"SERVO thread opened succesfully=> %d\n",Ret); 
                         }
                     }
                     else if(!strcmp(inet_ntoa(cli_addr.sin_addr),S04_SERVO_IP))
                     { 
                        new_sock = malloc(1);
                        *new_sock = server_fd;
                        fprintf(stderr," ACCEPTED CONNECTION S04 Servo System %s\n",inet_ntoa(cli_addr.sin_addr));
                         Ret= pthread_create(&servo_th,NULL,&S04_servo,(void *)new_sock); 
                          if(Ret)
                           { 
                             fprintf(stderr,"Error in Opening SERVO thread %d\n",Ret);
                           }
                          else 
                          {
                            fprintf(stderr,"SERVO thread opened succesfully=> %d\n",Ret); 
                         }
                     }
                      else if(!strcmp(inet_ntoa(cli_addr.sin_addr),S06_SERVO_IP))
                     { 
                        new_sock = malloc(1);
                        *new_sock = server_fd;
                        fprintf(stderr," ACCEPTED CONNECTION S06 Servo System %s\n",inet_ntoa(cli_addr.sin_addr));
                         Ret= pthread_create(&servo_th,NULL,&S06_servo,(void *)new_sock); 
                          if(Ret)
                           { 
                             fprintf(stderr,"Error in Opening SERVO thread %d\n",Ret);
                           }
                          else 
                          {
                            fprintf(stderr,"SERVO thread opened succesfully=> %d\n",Ret); 
                         }
                     }
                   else if(!strcmp(inet_ntoa(cli_addr.sin_addr),W01_SERVO_IP))
                     { 
                        new_sock = malloc(1);
                        *new_sock = server_fd;
                        fprintf(stderr," ACCEPTED CONNECTION W01 Servo System %s\n",inet_ntoa(cli_addr.sin_addr));
                         Ret= pthread_create(&servo_th,NULL,&W01_servo,(void *)new_sock); 
                          if(Ret)
                           { 
                             fprintf(stderr,"Error in Opening SERVO thread %d\n",Ret);
                           }
                          else 
                          {
                            fprintf(stderr,"SERVO thread opened succesfully=> %d\n",Ret); 
                         }
                     }
                    else if(!strcmp(inet_ntoa(cli_addr.sin_addr),W02_SERVO_IP))
                     { 
                        new_sock = malloc(1);
                        *new_sock = server_fd;
                        fprintf(stderr," ACCEPTED CONNECTION W02 Servo System %s\n",inet_ntoa(cli_addr.sin_addr));
                         Ret= pthread_create(&servo_th,NULL,&W02_servo,(void *)new_sock); 
                          if(Ret)
                           { 
                             fprintf(stderr,"Error in Opening SERVO thread %d\n",Ret);
                           }
                          else 
                          {
                            fprintf(stderr,"SERVO thread opened succesfully=> %d\n",Ret); 
                         }
                     }
                     else if(!strcmp(inet_ntoa(cli_addr.sin_addr),W03_SERVO_IP))
                     { 
                        new_sock = malloc(1);
                        *new_sock = server_fd;
                        fprintf(stderr," ACCEPTED CONNECTION W03 Servo System %s\n",inet_ntoa(cli_addr.sin_addr));
                         Ret= pthread_create(&servo_th,NULL,&W03_servo,(void *)new_sock); 
                          if(Ret)
                           { 
                             fprintf(stderr,"Error in Opening SERVO thread %d\n",Ret);
                           }
                          else 
                          {
                            fprintf(stderr,"SERVO thread opened succesfully=> %d\n",Ret); 
                         }
                     }
                     else if(!strcmp(inet_ntoa(cli_addr.sin_addr),W04_SERVO_IP))
                     { 
                        new_sock = malloc(1);
                        *new_sock = server_fd;
                        fprintf(stderr," ACCEPTED CONNECTION W04 Servo System %s\n",inet_ntoa(cli_addr.sin_addr));
                         Ret= pthread_create(&servo_th,NULL,&W04_servo,(void *)new_sock); 
                          if(Ret)
                           { 
                             fprintf(stderr,"Error in Opening SERVO thread %d\n",Ret);
                           }
                          else 
                          {
                            fprintf(stderr,"SERVO thread opened succesfully=> %d\n",Ret); 
                         }
                     }
                      else if(!strcmp(inet_ntoa(cli_addr.sin_addr),W05_SERVO_IP))
                     { 
                        new_sock = malloc(1);
                        *new_sock = server_fd;
                        fprintf(stderr," ACCEPTED CONNECTION W05 Servo System %s\n",inet_ntoa(cli_addr.sin_addr));
                         Ret= pthread_create(&servo_th,NULL,&W05_servo,(void *)new_sock); 
                          if(Ret)
                           { 
                             fprintf(stderr,"Error in Opening SERVO thread %d\n",Ret);
                           }
                          else 
                          {
                            fprintf(stderr,"SERVO thread opened succesfully=> %d\n",Ret); 
                         }
                     }
                       else if(!strcmp(inet_ntoa(cli_addr.sin_addr),W06_SERVO_IP))
                     { 
                        new_sock = malloc(1);
                        *new_sock = server_fd;
                        fprintf(stderr," ACCEPTED CONNECTION W06 Servo System %s\n",inet_ntoa(cli_addr.sin_addr));
                         Ret= pthread_create(&servo_th,NULL,&W06_servo,(void *)new_sock); 
                          if(Ret)
                           { 
                             fprintf(stderr,"Error in Opening SERVO thread %d\n",Ret);
                           }
                          else 
                          {
                            fprintf(stderr,"SERVO thread opened succesfully=> %d\n",Ret); 
                         }
                     }
            else
             { //fprintf(stderr,"UNAuthorized Connection=> %d\n",Ret); 

             } 
       }


}




