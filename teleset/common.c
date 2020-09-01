#include"server.h"

void *connection_handler(void *socket_desc)
{
     int sfd=0,n;
     ssize_t bytes=-1;
     ANS *Antenna_data;
     Antenna_data = (ANS *)socket_desc;
     ANT_CMD *a1;
     a1= malloc(sizeof(ANT_CMD));
    
     ANT_RESP *b1;
     b1= malloc(sizeof(ANT_RESP));
      
     ACK *ack;
     ack = malloc(sizeof(ACK));
 
     cmd *c1;
     c1 = malloc(sizeof(cmd));
     resp *r1;
     r1 = malloc(sizeof(resp));
     char *tstamp;
     tstamp = malloc(25);
     strcpy(a1->antenna_name,Antenna_data->aname); // copy the first antenna name from file/user input 
     //memcpy(sfd,Antenna_data->sockfd,sizeof(Antenna_data->sockfd));
      sfd = Antenna_data->sockfd;
     fprintf(stderr," Antenna name is %s %s\n",a1->antenna_name,Antenna_data->aname);
     fprintf(stderr," SOCK FD is %d\n",sfd);
           for(;;)
           {
             printf("\n\nEnter the system number from the list\n");
             printf("0.sentinal\n");
             printf("1.front_end\n");
             printf("2:fiber_optics\n");
             printf("3:back_end\n");
             printf("4:self_test\n\n");                                                  
             scanf("%d",&n); 
             // n =0;
              exec_cmd(n,a1);
                  
             tstamp = tp(tstamp);
             strcpy(a1->CMD[0].timestamp,tstamp);
             if((bytes = writen(sfd,(unsigned char *)a1,sizeof(ANT_CMD)))!=sizeof(ANT_CMD))
              {fprintf(stderr," ERROR Writing COMMAND to DISPACTHER \n"); }
              else
              { //fprintf(stderr," ##### ANTENNNA Name is %s #####\n",a1->antenna_name); 
                   c1 = &a1->CMD[0];
                 // printcmd(c1);
               }
                 if (readable_timeo(sfd,2) == 0)
                 {
                   fprintf(stderr, "SOCKET TIMEOUT\n");
                   //close(sfd);
                   //break;
                  }
                  else
                  {   usleep(500000);
                      if ((bytes = read_ack(sfd,(unsigned char *)ack,sizeof(ACK)))!=sizeof(ACK))
                     { fprintf(stderr,"ACK REading Failed !!!!!!\n");}
                    else
                     {fprintf(stderr,"########## ACK from ABC of %s ANTEANNA ####### %s \n",ack->Ant_name,ack->Resp_msg);}
                   }
             // sleep(1);
             // fprintf(stderr,"########## Waiting for the Final Response ###### \n");
            /*  c1 = &a1->CMD[0];
              printcmd(c1);*/
                 sleep(1);
                if((bytes = readn(sfd,(unsigned char *)r1,sizeof(resp)))!=sizeof(resp))
                  {fprintf(stderr,"ANT RESPONSE REAding Failed !!!!\n") ;} 
                  else
                  {
                   // r1= &b1->RESP[0]; 
                     // {fprintf(stderr,"=====> GOT ANT RESPONSE (((((())))))))\n"); }
                     printresp(r1);
                     write_shm(c1,r1); 
                    //write_command_xml(c1);
                    //write_response_xml(r1);        
                  }
               }
        
    return 0;
} 
char* tp(char *tstamp)
{

 char stamp1[26], stamp2[21];
 time_t t1;
   time(&t1);
   ctime_r(&t1, stamp1);
 //  fprintf(stderr,"%s\n",stamp1);
   stamp2[0] = stamp1[8];
   stamp2[1] = stamp1[9];
   stamp2[2] = '-';
   stamp2[3] = stamp1[4]; 
   stamp2[4] = stamp1[5]; 
   stamp2[5] = stamp1[6];
   stamp2[6] = '-'; 
   stamp2[7] = stamp1[20];
   stamp2[8] = stamp1[21];
   stamp2[9] = stamp1[22];
   stamp2[10] = stamp1[23];
   stamp2[11]= ' ';
   stamp2[12] = stamp1[11];
   stamp2[13] = stamp1[12];
   stamp2[14] = stamp1[13];
   stamp2[15] = stamp1[14];
   stamp2[16] = stamp1[15];
   stamp2[17] = stamp1[16];
   stamp2[18] = stamp1[17];
   stamp2[19] = stamp1[18];
   stamp2[20] = '\0'; 
   strcpy(tstamp,stamp2);
 // fprintf(stderr,"%s\n",stamp2);
  return (tstamp);
}


void printcmd(cmd *c1)
{
   int i;
        printf("we wrote on the socket %d %s %s %s\n",c1->seq,c1->timestamp,c1->system_name,c1->op_name);
       
        for(i=0;i<c1->number_param;i++)
        {
          printf("%s %s %s\n",c1->parameter_name[i],c1->Argument_Ch1[i],c1->Argument_Ch2[i]);
        } 
        printf(" Size of Struct is ######## %d\n",sizeof(cmd));
     
}

void printresp(resp *r1)
{
   int i;
   printf(" Size of Response Struct is ######## %d\n",sizeof(resp));
         printf("$$$$$$$$$$$$$$$$$ got from Client\n");
         printf("##############Response Message from MCM setting##########\n %d\n %d\n %s\n %s\n ",r1->response_type,r1->seq,r1->timestamp,r1->system_name);
 
         for(i=0; i<32;i++)
          {
             printf("%s ",r1->Mon_sum[i]);
          }
 
        for(i=0; i<64;i++)
          {
             printf("%s ",r1->Mon_raw[i]);
          }
        
        for(i=0; i<r1->num_resp_msg;i++)
          {
            printf(" %s\n",r1->response_message[i]);
          }

}

/* Write-Read ****/
void write_read(int newsockfd,cmd *c1, resp *r1)
{
      
         write(newsockfd,c1,sizeof(cmd));
         printcmd(c1);
         sleep(1);
         if (readable_timeo(newsockfd, 5) == 0)
          {
               fprintf(stderr, "socket timeout\n");
               close(newsockfd);
         }
       else 
          {
             read(newsockfd,r1,sizeof(resp));
             printresp(r1);
          }

}
int readable_timeo(int fd, int sec)
{
     fd_set rset;
     struct timeval tv;

      FD_ZERO(&rset);
      FD_SET(fd, &rset);

      tv.tv_sec = sec;
      tv.tv_usec = 0;

     return (select(fd + 1, &rset, NULL, NULL, &tv));
        /* > 0 if descriptor is readable */
}
