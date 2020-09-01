#ifndef _QUEUE_H
#define _QUEUE_H

#include"server.h"
#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#define MAXQUE 256 

typedef struct
{
  int front, rear;
  int retrieve ;      
  int store ;         
  ANT_CMD command[MAXQUE]; // It indicates the Queue for Commands 
} Queue;


extern Queue Q,Q1; 
Queue Q,Q1;

extern void q_store(ANT_CMD );
extern ANT_CMD *q_retrieve(int );

extern void q1_store(ANT_CMD );
extern ANT_CMD *q1_retrieve(int );

typedef struct
{
  int f, r;
  int ret ;      
  int s;         
  resp Resp[MAXQUE]; // It indicates the Queue for Commands 
} RQueue;


extern RQueue RQ ; 
RQueue RQ;

extern void rq_store(ANT_CMD );
extern resp *rq_retrieve(int );

#endif
