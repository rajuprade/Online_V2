/*
 * shm-client - client program to demonstrate shared memory.
 */

#include"shm.h"
#include"user1.h"
#include <my_global.h>
#include <mysql.h>

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
 
         printf("RESPONSE TYPE => %d\tSEQUENCE=> %d\tTIMESTAMP=> %s\tSYSTEM NAME=> %s\n",r1->response_type,r1->seq,r1->timestamp,r1->system_name);
 
        printf("\n#######################   MONITORING RAW ###############################\n");
          for(i=0; i<64;i++)
          {
             printf("%s\t",r1->Mon_raw[i]);
          }
	printf("\n");
}

printr(resp *r2,ANT_CMD *a1)
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
    int shmid1,shmid2, shmid3,shmid4;
    key_t key1,key2,key3,key4;
	  int flag[30],sum;

  char query[1024];
  char queryn[1024];


     int i=0,j,k,m;
      cmd *c2,*c1;
      resp *r2,*r1;
	resp *r3;
       setdata *s1;
       ANT_CMD *a1;
       ANT_CMD *a2;
      c1 = (cmd *)malloc(sizeof(cmd));
      r1 = (resp *)malloc(sizeof(resp));

MYSQL *conn;



char *ant[30] = {"C03","C12","C04","C09","C02","C01","C00","W01","C11","C14","C13","C10","W02","W03","W04","W05","E02","E03","C05","C06","E04","E05","E06","C08","W06","S01","S02","S03","S04","S06"};

      
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


	
	// my sql call
	   conn = mysql_init(NULL);
           mysql_real_connect(conn, "incms", "cms", "cms123", "antdbm", 0, NULL, 0);
	


       while(1)
       {

	a2=a1;
        memcpy(a2, a1, sizeof(ANT_CMD*));
	r3=r2;
        memcpy(r3, r2, sizeof(resp*));


	// for all antenna

        sprintf(query,"VALUES(%s","NULL");
        sprintf(query,"%s,\"%s\",\"%s\"",query,a2->antenna_name,r3->system_name);
        for(j=0; j<64;j++){
        sprintf(query,"%s,%s",query,r3->Mon_raw[j]);
	}

        sprintf(query,"%s)",query);
        sprintf(queryn,"%s %s","INSERT INTO curdata",query);
       	mysql_query(conn,queryn);
	//mysql_query(conn,"DELETE FROM curdata WHERE `time` < NOW() - interval 5 hour");
	usleep(500000);
        }
        
        return 0;
}
