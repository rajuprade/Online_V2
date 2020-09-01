#ifndef H_MCM_H
#define H_MCM_H
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<time.h>
#include <math.h>
#include <unistd.h>

#ifndef THREAD_STACK_SZ 
#define THREAD_STACK_SZ 65536
#endif
void* mcmsystem( void* parameters);

#endif //H_MCM_H
