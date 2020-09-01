#ifndef _MCM_THREAD_H
#define _MCM_THREAD_H

#include"server.h"
#include"queue.h"


#define SENTINEL_IP "192.168.33.2"
#define FIBER_IP "192.168.31.2"
#define FRONT_IP "192.168.31.3"
#define BACKEND_IP "192.168.31.4"
#define SELF_IP "192.168.4.124"
void *sentinel_thread(void *);
void *fiber_thread(void *);
void *front_thread(void *);
void *backend_thread(void *);
void *self_thread(void *);
#endif
