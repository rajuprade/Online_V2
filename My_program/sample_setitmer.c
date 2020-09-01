#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include<stdlib.h>
#include<unistd.h>
#define INTERVAL 10


/* struct itimerval {
             struct timeval it_interval; // next value 
             struct timeval it_value;    // current value 
};
struct timeval {
           long tv_sec;                // seconds 
           long tv_usec;               // microseconds 
}; */

void alarm_wakeup (int i)
{
   signal(SIGALRM,alarm_wakeup);
   printf("%d sec up partner, Wakeup!!!\n",INTERVAL);
   exit(0);
}

int main ()
{
  struct itimerval tout_val;
  
  tout_val.it_interval.tv_sec = 0;
  tout_val.it_interval.tv_usec = 0;
  tout_val.it_value.tv_sec = INTERVAL; /* set timer for "INTERVAL (10) seconds */
  tout_val.it_value.tv_usec = 0;
  setitimer(ITIMER_REAL, &tout_val,0);

  signal(SIGALRM,alarm_wakeup); /* set the Alarm signal capture */
  
  while (1)
  {
    ;
  }
  
  return 0;

}

