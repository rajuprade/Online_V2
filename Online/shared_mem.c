/********* Shared memory *****/
#include"server.h"
void write_us_shm(setdata *set)
{
  int shmid3;
  //int i=0,j,k,m,flag=0;
  key_t key3;
   setdata *s1;
  // printf("I am in shm\n");
   key3 = 9100;
     if( (shmid3 = shmget(key3,sizeof(setdata),IPC_CREAT | 0777)) < 0 )
       {
         printf("shmget");
        // exit(1);
       }
    
       if ( (s1 = (setdata *)shmat(shmid3,NULL,0)) ==(setdata *)-1)
            {
           printf("shmat");
           //exit(1);
         }
      memcpy(s1,set,sizeof(setdata));
       // s1= set;
     // sleep(30);
      fprintf(stderr,"successfully copied in SHM\n");
  
     /* for(i=0;i<MAX_LOOP;i++)
     {
       fprintf(stderr,"usernb is %d\n",c1->Tx[i].usernb);
        for(k=0;k<MAX_LOOP;k++)
       {
          fprintf(stderr,"Sub ARRAy Number %d\n",c1->Tx[i].s_a[k].sub_num);
           
           fprintf(stderr,"The Antenna names in your sub Array\n");
           for(j=0;j<c1->Tx[i].s_a[k].num_in_sub;j++)
           {
             fprintf(stderr,"%s\n",c1->Tx[i].s_a[k].ant_name[j]);
           }
             
         } 
       
     fprintf(stderr," Timestamp=> %s\n",c1->Tx[i].timestamp);
 
     } */
    shmdt(s1);      
}

void write_shm(ANT_CMD *a1, resp *r1)
{
 int shmid1,shmid2;
  key_t key1,key2;
 
   ANT_CMD *a2;
   //cmd  *c2;
   resp *r2;
   key1 = 5800;
   key2 = 5801;

 
  if( (shmid1 = shmget(key1,SHMSZ1,IPC_CREAT | 0777)) < 0 )
       {
         printf("shmget");
         exit(1);
       }
    
       if ( (a2 = (ANT_CMD *)shmat(shmid1,NULL,0)) == (ANT_CMD *) -1)
   
         {
           printf("shmat");
           exit(1);
         }
        
     if( (shmid2 = shmget(key2,SHMSZ2,IPC_CREAT | 0777)) < 0 )
       {
         printf("shmget");
         exit(1);
       }
    
       if ( (r2 = (resp *)shmat(shmid2,NULL,0)) == (resp *) -1)
   
         {
           printf("shmat");
           exit(1);
         }
 
    /*   c2= c1;
         r2= r1; */

    memcpy(a2, a1, sizeof(ANT_CMD));
    memcpy(r2, r1, sizeof(resp)); 
   // fprintf(stderr," ************************Writing on shared Memory***********\n");         
  /*  printcmd(c2);
    printresp(r2);
    write_command_xml(c2);
    write_response_xml(r2);*/
    shmdt(a2);
    shmdt(r2);
   /* bzero(c1,sizeof(cmd));
    bzero(c2,sizeof(cmd));
    bzero(r1,sizeof(resp));
    bzero(r2,sizeof(resp)); */
         
}

/***** C01 Shared Memory ***/

void write_shm_C01(ANT_CMD *a1, resp *r1)
{
 int shmid1,shmid2;
  key_t key1,key2;
 
   ANT_CMD *a2;
   //cmd  *c2;
   resp *r2;
   key1 = 5802;
   key2 = 5803;

 
  if( (shmid1 = shmget(key1,SHMSZ1,IPC_CREAT | 0777)) < 0 )
       {
         printf("shmget");
         exit(1);
       }
    
       if ( (a2 = (ANT_CMD *)shmat(shmid1,NULL,0)) == (ANT_CMD *) -1)
   
         {
           printf("shmat");
           exit(1);
         }
        
     if( (shmid2 = shmget(key2,SHMSZ2,IPC_CREAT | 0777)) < 0 )
       {
         printf("shmget");
         exit(1);
       }
    
       if ( (r2 = (resp *)shmat(shmid2,NULL,0)) == (resp *) -1)
   
         {
           printf("shmat");
           exit(1);
         }
 
    /*   c2= c1;
         r2= r1; */

    memcpy(a2, a1, sizeof(ANT_CMD));
    memcpy(r2, r1, sizeof(resp)); 
   // fprintf(stderr," ************************Writing on shared Memory***********\n");         
  /*  printcmd(c2);
    printresp(r2);
    write_command_xml(c2);
    write_response_xml(r2);*/
    shmdt(a2);
    shmdt(r2);
   /* bzero(c1,sizeof(cmd));
    bzero(c2,sizeof(cmd));
    bzero(r1,sizeof(resp));
    bzero(r2,sizeof(resp)); */
         
}

void write_shm_das(char *msg)
{
  int shmid1;
  key_t key1;
  char *das;
  das = (char *)malloc(sizeof(20));
   key1 = 4999;
   

 
  if( (shmid1 = shmget(key1,20,IPC_CREAT | 0777)) < 0 )
       {
         printf("shmget");
         exit(1);
       }
    
       if ( (das = (char *)shmat(shmid1,NULL,0)) == sizeof(das) -1)
   
         {
           printf("shmat");
           exit(1);
         }
    
    memcpy(das,msg, 20);
    fprintf(stderr,"####### Cpoied in Shared Memory %s ==== %s\n",das,msg);
    shmdt(das);
  
}


