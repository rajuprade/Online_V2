/*
 * shmclient_readline.c - A shared memory client program to read command and response from Readline server program .
 */

#include"readline_server.h"
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

      c1 = (cmd *)malloc(sizeof(cmd));
      r1 = (resp *)malloc(sizeof(resp));
      key1 = 5800;
      key2 = 5801; 
   
   if ((shmid1 = shmget(key1, SHMSZ1,0777)) < 0) {
        perror("shmget");
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
  mysql_real_connect(conn, "incms", "cms", "cms123", "newant", 0, NULL, 0);

       
  mysql_query(conn,"DELETE FROM mcm0");
  mysql_query(conn,"DELETE FROM mcm1");
  mysql_query(conn,"DELETE FROM mcm2");
  mysql_query(conn,"DELETE FROM mcm3");
  mysql_query(conn,"DELETE FROM mcm4");
  mysql_query(conn,"DELETE FROM mcm5");

  while(1)
  {
  // for all antennas
  for(j=0;j<=31;j++) { 

  // copy time
  sprintf(query,"VALUES('%s'",r2->timestamp);
  sprintf(query,"%s,%d",query,j);

  // copy chan data
  for(i=0; i<64;i++){
  sprintf(query,"%s,%s",query,r2->Mon_raw[i]);
  }
  sprintf(query,"%s)",query);

  //mcm 0
  sprintf(queryn,"%s %s","INSERT INTO mcm0",query);
  mysql_query(conn,queryn);

  //mcm 1
  sprintf(queryn,"%s %s","INSERT INTO mcm1",query);
  mysql_query(conn,queryn);

  //mcm 2
  sprintf(queryn,"%s %s","INSERT INTO mcm2",query);
  mysql_query(conn,queryn);

  //mcm 3
  sprintf(queryn,"%s %s","INSERT INTO mcm3",query);
  mysql_query(conn,queryn);

  //mcm 4
  sprintf(queryn,"%s %s","INSERT INTO mcm4",query);
  mysql_query(conn,queryn);

  //mcm 5
  sprintf(queryn,"%s %s","INSERT INTO mcm5",query);
  mysql_query(conn,queryn);


  }
  //sleep(1);
mysql_close(conn);
exit(0);

  }
        
        return 0;
}
