#include"server.h"
int main()
{
  
  int shmid1,shmid2;
  key_t key1,key2;
 
   cmd *c1,*c2;
   resp *r1;
   key1 = 5681;
   key2 = 5682;
   c2 = (cmd *)malloc(sizeof(cmd));
  if( (shmid1 = shmget(key1,SHMSZ,IPC_CREAT | 0666)) < 0 )
       {
         printf("shmget");
         exit(1);
       }
    
       if ( (c1 = (cmd *)shmat(shmid1,NULL,0)) == (cmd *) -1)
   
         {
           printf("shmat");
           exit(1);
         }
        
     if( (shmid2 = shmget(key2,SHMSZ,IPC_CREAT | 0666)) < 0 )
       {
         printf("shmget");
         exit(1);
       }
    
       if ( (r1 = (resp *)shmat(shmid2,NULL,0)) == (resp *) -1)
   
         {
           printf("shmat");
           exit(1);
         }
         
         // while(1)
          //{
            strcpy(c1->system_name,"Raj singh");
            sleep(10);
            c2=c1;
           fprintf(stderr," copied from c1 c2->system_name=> %s\n",c2->system_name);
            fprintf(stderr," Read on the shared memory segment %s\n",r1->system_name);
           //}
           
              return 0;
}   
       
   
