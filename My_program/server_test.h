#include<sys/types.h>
#include<sys/socket.h>
#include<sys/time.h>
#include<time.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
#include<fcntl.h>
#include<netdb.h>
#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/uio.h>
#include<unistd.h>
#include<sys/wait.h>

#ifdef HAVE_SYS_SYSCTL_H
#include<sys/sysctl.h>
#endif

#ifdef HAVE_SYS_EVENT_H
#include<sys/event.h>
#endif

#ifdef HAVE_SYS_SELECT_H
#include<sys/select.h>
#endif

#ifdef HAVE_POLL_H
#include<poll.h>
#endif

#ifdef HAVE_STRINGS_H
#include<strings.h>
#endif

#ifdef HAVE_PTHREAD_H
#include<pthread.h>
#endif

#ifdef HAVE_SYS_IOCTL_H
#include<sys/ioctl.h>
#endif


#define recv(a,b,c,d) recvfrom(a,b,c,d,0,0)
#define send(a,b,cd)  sendto(a,b,c,d,0,0)

typedef void sigfunc(int);

#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))

/* #ifndef HAVE_TIMESPEC_STRUCT
   struct timespec
          {
             time_t tv_sec;
             long tv_nsec;
          };
#endif */

#define LISTENQ 1024
#define MAXLINE 4096  /* max text line length */
#define BUFFSIZE 8192 /* buffer size for reads n writes */

#define MAXN 16384 /* max # bytes client can request */

typedef struct _msg
{
  int length;
  unsigned char Msg[2000];
}MSG;

