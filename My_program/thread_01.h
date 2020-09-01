typedef struct
{
   pthread_t thread_tid; /* thread id */
   long thread_count;    /* connections handled */
} Thread;

Thread *tptr;

int listenfd ,nthreads = 0;
socklen_t addrlen;
pthread_mutex_t mlock;

#define MAXNCLI 32
 int     clifd[MAXNCLI], iget, iput;
 pthread_mutex_t clifd_mutex;
 pthread_cond_t clifd_cond; 
