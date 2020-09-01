/*
 * shm-client - client program to demonstrate shared memory.
 */

#include"server.h"


int main()
{
    int shmid1,shmid2;
    key_t key1,key2;
 
      cmd *c2;
      resp *r2;
      key1 = 5681;
      key2 = 5682; 
   
    if ((shmid1 = shmget(key1, SHMSZ, 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

   
    if ((c2 =(cmd *) shmat(shmid1, NULL, 0)) == (cmd *) -1) {
        perror("shmat");
        exit(1);
    }
    
      if( (shmid2 = shmget(key2,SHMSZ,IPC_CREAT | 0666)) < 0 )
       {
         printf("shmget");
         exit(1);
       }
    
       if ( (r2 = (resp *)shmat(shmid2,NULL,0)) == (resp *) -1)
   
         {
           printf("shmat");
           exit(1);
         }

          strcpy(r2->system_name,"RAJU UPRADE");          
          fprintf(stderr," Read on the shared memory segment %s\n",c2->system_name);
          fprintf(stderr," Read on the shared memory segment %s\n",r2->system_name);

         
        
       
      return 0;
}
