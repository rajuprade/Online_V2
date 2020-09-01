/*
 * FPS shared memory client - client program to demonstrate shared memory.
 */

#include"shm.h"
#include"user1.h"
printcmd(cmd *c1)
{
   int i;

       printf("############################ COMMAND SENT FROM SERVER #################\n");
       printf("SEQ => %d\t TIMESTAMP =>%s\t SYSTEM NAME => %s\t OPERATION NAME=> %s\n",c1->seq,c1->timestamp,c1->system_name,c1->op_name);
       
        for(i=0;i<c1->number_param;i++)
        {
          printf("PARAMETER NAME=> %s\tARGUMENT CH1=> %s\tARGUMENT CH2=> %s\n",c1->parameter_name[i],c1->Argument_Ch1[i],c1->Argument_Ch2[i]);
        } 
           
}

printresp(resp *r1)
{
   int i;
 
         printf("############ RESPONSE RECIEVED ROM CLIENT ######\n");
         printf("RESPONSE TYPE => %d\tSEQUENCE=> %d\tTIMESTAMP=> %s\tSYSTEM NAME=> %s\n",r1->response_type,r1->seq,r1->timestamp,r1->system_name);
         printf("#####################MONITORING SUMMARY#####################\n");
         for(i=0; i<32;i++)
          {
             printf("%s\t",r1->Mon_sum[i]);
          }
 
        printf("\n#######################   MONITORING RAW ###############################\n");
          for(i=0; i<64;i++)
          {
             printf("%s\t",r1->Mon_raw[i]);
          }
          printf("\n############################ RESPONSE MESSAGES FROM MCM  ##############\n");
          for(i=0; i<r1->num_resp_msg;i++)
          {
            printf("RESPONSE MESSAGES FROM MCM=> %s\n",r1->response_message[i]);
          }
      //  printf("\n==============================================================================\n");
}
int main()
{
    int shmid1,shmid2, shmid3,shmid4;
    key_t key1,key2,key3,key4;
     int i=0,j,k,m,flag=0;
      cmd *c2,*c1;
      resp *r2,*r1;
       setdata *s1;
       ANT_CMD *a1;
      c1 = (cmd *)malloc(sizeof(cmd));
      r1 = (resp *)malloc(sizeof(resp));

      
      key1 = 5800;
      key2 = 5801;
     
       char *das;
      das = (char *)malloc(sizeof(20));
      key4 = 4999;  // For DAS Server message
   
    
   if( (shmid4 = shmget(key4,20,IPC_CREAT | 0777)) < 0 )
       {
         printf("shmget");
         exit(1);
       }
    
       if ( (das = (char *)shmat(shmid4,NULL,0)) == sizeof(das) -1)
   
         {
           printf("shmat");
           exit(1);
         }

      
/*** C00 Shared Memory ****/
   if ((shmid1 = shmget(key1, SHMSZ1,0777)) < 0) {
        perror("shmget");
        exit(1);
    }

  

    if ((a1 =(ANT_CMD*) shmat(shmid1,NULL, 0)) == (ANT_CMD *) -1) {
        printf("shmat");
        exit(1);
    }
    
   if( (shmid2 = shmget(key2,SHMSZ2,0777)) < 0 )
       {
         printf("shmget");
         exit(1);
       }

     if ( (r2 = (resp *)shmat(shmid2,NULL,0)) == (resp *) -1)
   
         {
           printf("shmat");
           exit(1);
         }


       while(1)
       {

          if(!strcmp(a1->antenna_name,"C00"))
           {
            // fprintf(stderr," ##### C00 Command & Response for [[[[ %s ]]]]\n",a1->antenna_name);
               if(!strcmp(r2->system_name,"fps"))
                {
                // fprintf(stderr,"########## FPS System ########\n");
                // fprintf(stderr,"***************************************************\n");
                  printresp(r2);
                // fprintf(stderr,"**************************************************\n");
                }
               usleep(5000);
              c2 = &a1->CMD;
              memcpy(c2, &a1->CMD, sizeof(cmd));
              if(!strcmp(c2->system_name,"fps"))
              {
                printcmd(c2);
              }
           }
         else if(!strcmp(a1->antenna_name,"C01"))
           {
            // fprintf(stderr," ##### C00 Command & Response for [[[[ %s ]]]]\n",a1->antenna_name);
               if(!strcmp(r2->system_name,"fps"))
                {
                // fprintf(stderr,"########## FPS System ########\n");
                // fprintf(stderr,"***************************************************\n");
                  printresp(r2);
                // fprintf(stderr,"**************************************************\n");
                }
               usleep(5000);
              c2 = &a1->CMD;
              memcpy(c2, &a1->CMD, sizeof(cmd));
              if(!strcmp(c2->system_name,"fps"))
              {
                printcmd(c2);
              }
           }
        else if(!strcmp(a1->antenna_name,"C02"))
           {
            // fprintf(stderr," ##### C00 Command & Response for [[[[ %s ]]]]\n",a1->antenna_name);
               if(!strcmp(r2->system_name,"fps"))
                {
                // fprintf(stderr,"########## FPS System ########\n");
                // fprintf(stderr,"***************************************************\n");
                  printresp(r2);
                // fprintf(stderr,"**************************************************\n");
                }
               usleep(5000);
              c2 = &a1->CMD;
              memcpy(c2, &a1->CMD, sizeof(cmd));
              if(!strcmp(c2->system_name,"fps"))
              {
                printcmd(c2);
              }
           }
      else if(!strcmp(a1->antenna_name,"C03"))
           {
            // fprintf(stderr," ##### C00 Command & Response for [[[[ %s ]]]]\n",a1->antenna_name);
               if(!strcmp(r2->system_name,"fps"))
                {
                // fprintf(stderr,"########## FPS System ########\n");
                // fprintf(stderr,"***************************************************\n");
                  printresp(r2);
                // fprintf(stderr,"**************************************************\n");
                }
               usleep(5000);
              c2 = &a1->CMD;
              memcpy(c2, &a1->CMD, sizeof(cmd));
              if(!strcmp(c2->system_name,"fps"))
              {
                printcmd(c2);
              }
           }
           else if(!strcmp(a1->antenna_name,"C05"))
           {
            // fprintf(stderr," ##### C00 Command & Response for [[[[ %s ]]]]\n",a1->antenna_name);
               if(!strcmp(r2->system_name,"fps"))
                {
                // fprintf(stderr,"########## FPS System ########\n");
                // fprintf(stderr,"***************************************************\n");
                  printresp(r2);
                // fprintf(stderr,"**************************************************\n");
                }
               usleep(5000);
              c2 = &a1->CMD;
              memcpy(c2, &a1->CMD, sizeof(cmd));
              if(!strcmp(c2->system_name,"fps"))
              {
                printcmd(c2);
              }
           }
           else if(!strcmp(a1->antenna_name,"C06"))
           {
            // fprintf(stderr," ##### C00 Command & Response for [[[[ %s ]]]]\n",a1->antenna_name);
               if(!strcmp(r2->system_name,"fps"))
                {
                // fprintf(stderr,"########## FPS System ########\n");
                // fprintf(stderr,"***************************************************\n");
                  printresp(r2);
                // fprintf(stderr,"**************************************************\n");
                }
               usleep(5000);
              c2 = &a1->CMD;
              memcpy(c2, &a1->CMD, sizeof(cmd));
              if(!strcmp(c2->system_name,"fps"))
              {
                printcmd(c2);
              }
           }
           else
            { 
              //fprintf(stderr,".");
            }
            }
        
     
        return 0;
}
