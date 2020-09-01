/*
 * shm-client - client program to demonstrate shared memory.
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
    int shmid1,shmid2, shmid3,shmid4,shmid5;
    key_t key1,key2,key3,key4,key5;
     int i=0,j,k,m,flag=0;
      cmd *c2,*c1,*c3;
      resp *r2,*r1,*r3,*r4;
       setdata *s1;
       ANT_CMD *a1,*a2;
      c1 = (cmd *)malloc(sizeof(cmd));
      r1 = (resp *)malloc(sizeof(resp));

      c3 = (cmd *)malloc(sizeof(cmd));
      r3 = (resp *)malloc(sizeof(resp));
      key1 = 5800;
      key2 = 5801;
      key3 = 9100; 
      key4 = 5802;
      key5= 5803;
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

/****** C01 Shared Memory *****/

 if ((shmid4 = shmget(key4, SHMSZ1,0777)) < 0) {
        perror("shmget");
        exit(1);
    }

  

    if ((a2 =(ANT_CMD*) shmat(shmid4,NULL, 0)) == (ANT_CMD *) -1) {
        printf("shmat");
        exit(1);
    }
    
   if( (shmid5 = shmget(key5,SHMSZ2,0777)) < 0 )
       {
         printf("shmget");
         exit(1);
       }

     if ( (r4 = (resp *)shmat(shmid5,NULL,0)) == (resp *) -1)
   
         {
           printf("shmat");
           exit(1);
         }

/********************** C01 Memory region ends Here ******/

     //printf("SHM\n");
 /*    if( (shmid3 = shmget(key3,sizeof(setdata),IPC_CREAT |0777)) < 0 )
       {
         printf("shmget");
        // exit(1);
       }
   
       if ( (s1= (setdata *)shmat(shmid3,NULL,0)) ==(setdata *)-1)
            {
               printf("shmat");
               //exit(1);
            } */
        // strcpy(c2->system_name,"RAJ SINGH");
        // fprintf(stderr," Read on the shared memory segment %s\n",c2->system_name);
        //  fprintf(stderr," Read on the shared memory segment %s\n",r2->system_name);
       /* c1= c2;
        r1=r2; */
       while(1)
       {
            printf("================================================================================\n");
            printf("\t\t\tUSER INOFRAMTION OF ONLINE PROGRAM\n");
    //  printf("=======================================================================\n");
     /*  for(i=0;i<MAX_LOOP;i++)
       {
           // printf("InISIED  FOR LOOP Shared memory attached\n"); 
         printf("=============================================================================\n");
       fprintf(stderr,"\tUSER NUMBER =>%d\t\t",s1->Tx[i].usernb);
       fprintf(stderr,"Timestamp=>%s\n",s1->Tx[i].timestamp);
       printf("=============================================================================\n");
     //   printf("Shared memory attached\n");
        for(k=0;k<MAX_LOOP;k++)
       {
          fprintf(stderr,"SUB ARRAY NUMBER=>%d\t\t",s1->Tx[i].s_a[k].sub_num);
             
           fprintf(stderr,"SELECTED ANTENNA=>");
           for(j=0;j<s1->Tx[i].s_a[k].num_in_sub;j++)
           {
             fprintf(stderr,"%s\t",s1->Tx[i].s_a[k].ant_name[j]);
           }
    printf("\n==============================================================================\n");          
         } 
     
   //  fprintf(stderr," Timestamp=> %s\n",c1->Tx[i].timestamp);
 
    }*/

         fprintf(stderr," ############ Command & Response for [[[[ %s ]]]]\n",a1->antenna_name);
          printresp(r2);
          sleep(1);
          c2 = &a1->CMD;
          memcpy(c2, &a1->CMD, sizeof(cmd));
          printcmd(c2);
          fprintf(stderr,"############ Command & Response for [[[[[ %s ]]]]\n",a2->antenna_name);
          printresp(r4);
          sleep(1);
          c3 = &a1->CMD;
          memcpy(c3, &a2->CMD, sizeof(cmd));
          printcmd(c3);
       }
        
       /*  while(1)
        {
          fprintf(stderr," Read on the shared memory segment %s\n",c2->system_name);
          fprintf(stderr," Read on the shared memory segment %s\n",r2->system_name);
        }*/ 

         
        
       
      return 0;
}
