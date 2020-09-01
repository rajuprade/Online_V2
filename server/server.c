/* A simple server in the internet domain using TCP
   demonstrating how to send structure over sockets ******/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#define PORT 6000

void signal_handler(sig)
int sig;
{
	switch(sig) {
	case SIGHUP:
		//log_message(LOG_FILE,"hangup signal catched");
                 fprintf(stderr,"hangup signal catched\n");
		break;
	case SIGTERM:
		//log_message(LOG_FILE,"terminate signal catched");
		//exit(0);
                fprintf(stderr," TERMINATE signal catched\n");
		break;
	}
}

typedef struct 
{
  char Ant_name[10];
  char system[20];
} ant;

typedef struct
{
  char Ant_name[10];
  char Resp_msg[100];
}ACK;
  

int main(int argc, char *argv[])
{
     int sockfd, newsockfd,n,yes=1;
     socklen_t clilen;
     struct sockaddr_in serv_addr, cli_addr;
     int i;
     ant *e1;
     e1 = malloc(sizeof(ant));
     ACK *a1;
    a1 = malloc(sizeof(ACK));
    fprintf(stderr," Enter the Antenna Names which You want to communicate\n");
   
      scanf("%s",e1->Ant_name);
   
    // strcpy(e1->Ant_name,"C12");
     strcpy(e1->system,"SENTINEL");
     //e1->emp_code= 1;
       // printf("%s %d\n",e1->name,e1->emp_code);
   /*  if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     } */
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
       fprintf(stderr,"ERROR opening socket\n");
    if(setsockopt(sockfd, SOL_SOCKET , SO_REUSEADDR, &yes, sizeof(int)) == -1)
    {
          error(" Error\n");
    } 
     bzero((char *) &serv_addr, sizeof(serv_addr));
    // portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(PORT);

     if (bind(sockfd, (struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
              { 
               fprintf(stderr,"ERROR binding socket\n");
              }

     listen(sockfd,5);
       signal(SIGHUP,signal_handler); /* catch hangup signal */
       signal(SIGTERM,signal_handler); /* catch kill signal */
     clilen = sizeof(cli_addr);
     
         fprintf(stderr,"############# SERVER WANTING FOR CLIENT CONNECTION #####\n");
     while(1)
     {
       newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr,&clilen);
       fprintf(stderr,"Received connection from Client $$$$$$$$$ ===> %s on Port %d ####\n",inet_ntoa(cli_addr.sin_addr),ntohs(cli_addr.sin_port));

     if (newsockfd < 0) 
          fprintf(stderr,"ERROR Accept socket\n");
         n = write(newsockfd,e1,sizeof(ant));

       if (n < 0)
                fprintf(stderr,"ERROR writing socket\n");
       else
       printf("we wrote on the socket %s %s \n",e1->Ant_name,e1->system);
        printf(" Size of Struct is ######## %d\n",sizeof(ant));
        
         n=read(newsockfd,a1,sizeof(ACK));
          if (n < 0)
                fprintf(stderr,"ERROR READING socket\n");
       else
        printf("we read on the socket %s %s \n",a1->Ant_name,a1->Resp_msg);
      
        close(newsockfd);
      }
        close(sockfd);
     return 0; 
}
