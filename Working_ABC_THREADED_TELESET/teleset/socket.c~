#include"server.h"
extern socklen_t clilen;
extern struct sockaddr_in serv_addr, cli_addr;
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
     serv_addr.sin_port = htons(PORT);

     if (bind(sockfd, (struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
              { 
               fprintf(stderr,"ERROR binding socket\n");
              }

     listen(sockfd,5);
     return 0;
}
ssize_t  writen(int fd, void *vptr, size_t n)
  {
      size_t nleft;
      ssize_t nwritten;
      unsigned char *ptr;

      ptr = (unsigned char *)vptr;
      nleft = n;
     while (nleft > 0) {
         if ( (nwritten = write(fd, ptr, nleft)) <= 0) {
             if (nwritten < 0 && errno == EINTR)
                 nwritten = 0;   /* and call write() again */
             else
                 return (-1);    /* error */
          }

          nleft -= nwritten;
          ptr += nwritten;
     }
     return (n);
 }


ssize_t  readline(int fd, void *vptr, size_t maxlen)
  {
      ssize_t n, rc;
      unsigned char c, *ptr;

      ptr = (unsigned char *)vptr;
      for (n = 1; n < maxlen; n++) {
       again:
         if ( (rc = read(fd, &c, 1)) == 1) {
             *ptr++ = c;
             if (c == '\n')
                 break;          /* newline is stored, like fgets() */
         } else if (rc == 0) {
             *ptr = 0;
             return (n - 1);     /* EOF, n - 1 bytes were read */
         } else {
             if (errno == EINTR)
                 goto again;
             return (-1);        /* error, errno set by read() */
         }
     }

     *ptr = 0;                   /* null terminate like fgets() */
     return (n);
}


