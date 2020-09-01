/*
 * shmclient_readline.c - A shared memory client program to read command and response from Readline server program .
 */

//#include"readline_server.h"
#include"shm.h"
//#include"user1.h"
#include <stdio.h>

printresp(resp *r2,ANT_CMD *a1)
{
int i;
	printf("%s",r2->timestamp);
	printf(" %s",a1->antenna_name);
	printf(" %s",r2->system_name);
	for(i=0;i<=63;i++) { 
	printf(" %s",r2->Mon_raw[i]);
	} 
	printf("\n");
}



int main()
{
  int shmid1,shmid2,i,j;
  int flag[30],sum;
  key_t key1,key2;
  char query[1024];
  char queryn[1024];

char *ant[30] = {"C03","C12","C04","C09","C02","C01","C00", "W01","C11","C14","C13","C10","W02","W03","W04", "W05","E02","E03","C05","C06","E04","E05","E06", "C9","W06","S01","S02","S03","S04","S06"};


 
      resp *r2;
      ANT_CMD *a1;


      key1 = 5800;
      key2 = 5801; 
   
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


	for(i=0;i<=29;i++) { flag[i]=0; } 
       
  while(1)
  {

	//if((!strcmp(a1->antenna_name,"C00")) && (!strcmp(r2->system_name,"back_end")))   { printresp(r2,a1);sleep(1);}
	if((!strcmp(a1->antenna_name,"W01")) && (!strcmp(r2->system_name,"back_end")))   { printresp(r2,a1);sleep(1);}


  } /* end while */
        
  return 0;
}
