/*
 * setitimer.c - simple use of the interval timer
 */

#include <sys/time.h>		/* for setitimer */
#include <unistd.h>		/* for pause */
#include <signal.h>		/* for signal */
#include<stdio.h>
#include<stdlib.h>
//#define INTERVAL 500		/* number of milliseconds to go off */
#define INTERVAL 1
/* function prototype */
void DoStuff(void);

int main(int argc, char *argv[]) {

  struct itimerval it_val;	/* for setting itimer */

  /* Upon SIGALRM, call DoStuff().
   * Set interval timer.  We want frequency in ms, 
   * but the setitimer call needs seconds and useconds. */
  if (signal(SIGALRM, (void (*)(int)) DoStuff) == SIG_ERR) {
    perror("Unable to catch SIGALRM");
    exit(1);
  }
 /* it_val.it_value.tv_sec =     INTERVAL/1000;
  it_val.it_value.tv_usec =    (INTERVAL*1000) % 1000000;	
  it_val.it_interval = it_val.it_value; */
  it_val.it_value.tv_sec =     INTERVAL;
  it_val.it_value.tv_usec =    0;	
  it_val.it_interval = it_val.it_value;
  if (setitimer(ITIMER_REAL, &it_val, NULL) == -1) {
    perror("error calling setitimer()");
    exit(1);
  }

  while (1) 
    pause();

}

/*
 * DoStuff
 */
void DoStuff(void) {

  printf("Command sent to MCM for Monitoring\n");

}
