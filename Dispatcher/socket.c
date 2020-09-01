#include"server.h"
extern socklen_t clilen;
extern struct sockaddr_in serv_addr, cli_addr;

int so_block(int sockfd,int flag)
{ int flg;
     flg = fcntl(sockfd, F_GETFL, &flg);
     if (flg < 0) return flg;
     if (flag){ flg |= O_NDELAY; }
     else { flg &= ~O_NDELAY; }
     return fcntl(sockfd, F_SETFL, flg);
}

int readable_timeo(int fd, int sec)
{
     fd_set rset;
     struct timeval tv;

      FD_ZERO(&rset);
      FD_SET(fd, &rset);

      tv.tv_sec = sec;
      tv.tv_usec = 0;

     return (select(fd + 1, &rset, NULL, NULL, &tv));
        /* > 0 if descriptor is readable */
}

void printresp(resp *r1)
{
   int i;
   printf(" Size of Response Struct is ######## %d\n",sizeof(resp));
         printf("$$$$$$$$$$$$$$$$$ got from Client\n");
         printf("##############Response Message from MCM setting##########\n %d\n %d\n %s\n %s\n ",r1->response_type,r1->seq,r1->timestamp,r1->system_name);
 
         for(i=0; i<32;i++)
          {
             printf("%s ",r1->Mon_sum[i]);
          }
 
        for(i=0; i<64;i++)
          {
             printf("%s ",r1->Mon_raw[i]);
          }
        
        for(i=0; i<r1->num_resp_msg;i++)
          {
            printf(" %s\n",r1->response_message[i]);
          }

}
void printcmd(cmd *c1)
{
   int i;
        printf("we wrote on the socket %d %s %s %s\n",c1->seq,c1->timestamp,c1->system_name,c1->op_name);
       
        for(i=0;i<c1->number_param;i++)
        {
          printf("%s %s %s\n",c1->parameter_name[i],c1->Argument_Ch1[i],c1->Argument_Ch2[i]);
        } 
        printf(" Size of Struct is ######## %d\n",sizeof(cmd));
     
}

int init_server(void)
{
      int reuse =1;
      struct linger wrplinger = { 0 , 0 };
      sockfd = socket(AF_INET, SOCK_STREAM, 0);
      if (sockfd < 0) 
      fprintf(stderr,"ERROR opening socket\n");

      if( setsockopt(sockfd, SOL_SOCKET, SO_LINGER, &wrplinger, sizeof(wrplinger)) == ERROR)
           {
              fprintf(stderr,"setsockopt-SO_LINGER"); 
              return ERROR; 
           } 

      if( setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == ERROR)
           { 
               fprintf(stderr,"setsockopt-SO_REUSEADDR");
               return ERROR; 
           }
     if( setsockopt(sockfd, SOL_SOCKET, SO_KEEPALIVE, &reuse, sizeof(reuse)) == ERROR)
             { 
               fprintf(stderr,"setsockopt-SO_KEEPALIVE");
               return ERROR; 
            }
  
     if(setsockopt(sockfd, IPPROTO_TCP,TCP_NODELAY, (char *)&reuse,sizeof(reuse)) == ERROR)
       { 
          fprintf(stderr,"setsockopt_TCP_NODELAY");
          return ERROR;
       }   

       bzero((char *) &serv_addr, sizeof(serv_addr));
  
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(SERVER_PORT);

     if (bind(sockfd, (struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
              { 
               fprintf(stderr,"ERROR binding socket\n");
              }

     listen(sockfd,5);
     return 0;
}

int connect_to_server(void)
{
     sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd < 0) 
        fprintf(stderr,"ERROR opening socket\n");
     server = gethostbyname(ADDRESS);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&servaddr.sin_addr.s_addr,
         server->h_length);
    servaddr.sin_port = htons(CL_PORT);
    if (connect(sfd,(struct sockaddr *) &servaddr,sizeof(servaddr)) < 0) 
          {
            fprintf(stderr,"ERROR connecting socket\n");
            return ERROR; 
          }
         
    return 0;
}

ssize_t writen(int fd, void *vptr, ssize_t nbytes)
{
  ssize_t l, nwritten, n = 0;
  extern unsigned char  *write_ptr ;


  write_ptr = ( unsigned char  *) vptr;
  while ( n < nbytes) {

     if (nbytes - n > MaxProtBuf) l = MaxProtBuf; else l = nbytes - n;

       so_block(fd,0); 
        nwritten = write(fd,write_ptr+n,l);
    // nwritten = send(fd,write_ptr+n,l, 0);
 //     ioctl (fd, I_FLUSH, FLUSHW); /* Flush the data to Socket */
       so_block(fd,1);

    if (nwritten <= 0) {
      if (errno == EINTR)
        nwritten = 0;
      else
        return -1;
    }
    n+=nwritten;
  }
  return (n);
}

ssize_t readn(int fd, void *vptr, ssize_t nbytes)
{
  ssize_t nread;
  ssize_t l, n = 0;
  extern unsigned char  *read_ptr ;

  read_ptr = ( unsigned char  *) vptr;
  while (n < nbytes) {
       if (nbytes - n > MaxProtBuf) l = MaxProtBuf; else l = nbytes - n;

   //    nread = read(fd,read_ptr+n,l);

 //       so_block(fd,0); 
        nread = recv(fd,read_ptr+n,l,MSG_DONTWAIT);
  //      so_block(fd,1); 
     
      // ssize_t n = recv(fd,read_ptr,nbytes,0); 
      //ioctl (fd, I_FLUSH, FLUSHR);  /*Flush the data from Socket  */

    if (nread < 0) {
      if (errno == EINTR || errno == EWOULDBLOCK) nread = 0;
        return -1;
    } else if (nread == 0) {
      break;
    }
     n+=nread;
  }
  return (n);
}

ssize_t read_from_online(int fd, void *vptr, ssize_t nbytes)
{
  ssize_t nread;
  ssize_t l, n = 0;
  extern unsigned char  *read_ptr ;

  read_ptr = ( unsigned char  *) vptr;
  while (n < nbytes) {
       if (nbytes - n > MaxProtBuf1) l = MaxProtBuf1; else l = nbytes - n;

   //    nread = read(fd,read_ptr+n,l);

 //       so_block(fd,0); 
        nread = recv(fd,read_ptr+n,l,MSG_DONTWAIT);
  //      so_block(fd,1); 
     
      // ssize_t n = recv(fd,read_ptr,nbytes,0); 
      //ioctl (fd, I_FLUSH, FLUSHR);  /*Flush the data from Socket  */

    if (nread < 0) {
      if (errno == EINTR || errno == EWOULDBLOCK) nread = 0;
        return -1;
    } else if (nread == 0) {
      break;
    }
     n+=nread;
  }
  return (n);
}

