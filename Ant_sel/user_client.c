/*
 * shm-client - client program to demonstrate shared memory.
 */

#include"user.h"


int main()
{
    int shmid1;
    int i=0,j,k,m,flag=0;
    key_t key1;
    setdata *c1;//,*c2;
    key1 = 9001;
    printf("SHM\n");
     if( (shmid1 = shmget(key1,sizeof(setdata),0777)) < 0 )
       {
         printf("shmget");
        // exit(1);
       }
   
       if ( (c1= (setdata *)shmat(shmid1,NULL,0)) ==(setdata *)-1)
            {
               printf("shmat");
               //exit(1);
            }
       printf("Shared memory attached\n");

    /* c2 = (setdata *)malloc(sizeof(setdata));
       for(i=0;i<MAX_LOOP;i++)
        {
         c2->Tx[i] = (user *)malloc(sizeof(user));
        } 
     
       memcpy(c2,c1,sizeof(setdata));*/
      
   

//while(1)
 // {
   
   // fprintf(stderr,"usernb is %d\n",c1->Tx[0]->usernb);
     for(i=0;i<MAX_LOOP;i++)
     {
        printf("InISIED  FOR LOOP Shared memory attached\n"); 
       fprintf(stderr,"usernb is %d\n",c1->Tx[i]->usernb);
        printf("Shared memory attached\n");
        for(k=0;k<MAX_LOOP;k++)
       {
          fprintf(stderr,"Sub ARRAy Number %d\n",c1->Tx[i]->s_a[k].sub_num);
           
           fprintf(stderr,"The Antenna names in your sub Array\n");
           for(j=0;j<c1->Tx[i]->s_a[k].num_in_sub;j++)
           {
             fprintf(stderr,"%s\n",c1->Tx[i]->s_a[k].ant_name[j]);
           }
             
         } 
       
     fprintf(stderr," Timestamp=> %s\n",c1->Tx[i]->timestamp);
 
    }
 //} 
       
      return 0;
}
