#ifndef _QUEUE_H
#define _QUEUE_H

#include"server.h"
#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#define MAXQUE     10000

typedef struct
{
  int front, rear;
  int retrieve ;      
  int store ;         
  cmd command[MAXQUE]; // It indicates the Queue for Commands 
} Queue;


extern Queue senQ,Q,fiberQ,backQ ; 
Queue senQ,Q,fiberQ,backQ;

extern void q_store(cmd );
extern cmd *q_retrieve(int );
extern void senq_store(cmd );
extern cmd *senq_retrieve(int );
extern void fiberq_store(cmd );
extern cmd *fiberq_retrieve(int );
extern void frontq_store(cmd );
extern cmd *frontq_retrieve(int );
extern void backq_store(cmd );
extern cmd *backq_retrieve(int );


typedef struct
{
  int f, r;
  int ret ;      
  int s;         
  resp Resp[MAXQUE]; // It indicates the Queue for Commands 
} RQueue;


extern RQueue RQ ; 
RQueue RQ;

extern void rq_store(resp );
extern resp *rq_retrieve(int );

#endif
