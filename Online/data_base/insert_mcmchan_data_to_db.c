/*
 * shmclient_readline.c - A shared memory client program to read command and response from Readline server program .
 */

//#include"readline_server.h"
#include"shm.h"
#include <my_global.h>
#include <mysql.h>
#include <stdio.h>


int main()
{
    int shmid1,shmid2,i,j;
    key_t key1,key2;
  char query[1024];
  char queryn[1024];

MYSQL *conn;


 
      cmd *c2,*c1;
      resp *r2,*r1;
      ANT_CMD *a1;


     // c1 = (cmd *)malloc(sizeof(cmd));
     // r1 = (resp *)malloc(sizeof(resp));
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
    if ((c2 =(cmd *) shmat(shmid1,NULL, 0)) == (cmd *) -1) {
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


	// my sql call
  conn = mysql_init(NULL);
  mysql_real_connect(conn, "incms", "cms", "cms123", "antdbm", 0, NULL, 0);

       
  while(1)
  {

	if(!strcmp(a1->antenna_name,"C00") && !strcmp(r2->system_name,"sentinel") ){ 
	
	printf("a: %s\n",a1->antenna_name);
	printf("s: %s\n",r2->system_name);
	printf("c: %s\n",c2->timestamp);
	printf("r: %s\n",r2->timestamp);
	printf("d:");
	for(i=0;i<=63;i++) { 
	printf(" %s",r2->Mon_raw[i]);
	} 
	printf("\n");
	sleep(1);

  

  // start query for antenna j=0;
  j=0;
  sprintf(query,"VALUES(%s","NULL");
  sprintf(query,"%s,%d",query,j);

  // copy chan data to query
  for(i=0; i<64;i++){
  sprintf(query,"%s,%s",query,r2->Mon_raw[i]);
  }
  // close data 
  sprintf(query,"%s)",query);

  // close query  for  mcm0
  sprintf(queryn,"%s %s","INSERT INTO mcm0",query);

  // execute query
  mysql_query(conn,queryn);
  mysql_query(conn,"DELETE FROM curdata WHERE `time` < NOW() - interval 10 second");

  //mcm 1
  //sprintf(queryn,"%s %s","INSERT INTO mcm1",query);
  //mysql_query(conn,queryn);
  } 
  usleep(100);
  } /* end while */
        
  return 0;
}
