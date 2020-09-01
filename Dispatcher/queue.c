#include"queue.h"

void q_store(cmd element )
{
  if (Q.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(Q.store==Q.retrieve)
  {
    Q.store = 0; Q.retrieve = 0;
  }
   //  fprintf(stderr," ###### Element in Command Queue %s\n",element.system_name);
    bzero(&Q.command[Q.store],MAXQUE);
    Q.command[Q.store]=element; 
 //   fprintf(stderr," INSERTING in Command Queue %s\n",Q.command[Q.store].system_name);
    Q.store++;  // point to next available storage position in queue[]
 }

cmd * q_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((cmd *) &Q.command[indx]); 
}

void rq_store(resp element )
{
  if (RQ.s == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }
  if(RQ.s==RQ.ret)
  {
    RQ.s = 0; RQ.ret= 0;
  }
  bzero(&RQ.Resp[RQ.s],MAXQUE);
 // fprintf(stderr," Element in Response Queue ######### %s\n",element.system_name);
  
    RQ.Resp[RQ.s]= element; 
   // memcpy(&RQ.Resp[RQ.s],&element,sizeof(resp));
   fprintf(stderr," >>>>>>>>>>>>> INSERTING in Response Queue ######### %s\n",RQ.Resp[Q.store].system_name);
    RQ.s++;  // point to next available storage position in queue[]
 }

resp * rq_retrieve(int indx)
{
 // fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((resp *) &RQ.Resp[indx]); 
}


/****** SENTINEL QUEUE ******/ 
void senq_store(cmd element )
{
  if (senQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(senQ.store==senQ.retrieve)
  {
    senQ.store = 0; senQ.retrieve = 0;
  }
   //  fprintf(stderr," ###### Element in Command Queue %s\n",element.system_name);
    bzero(&senQ.command[senQ.store],MAXQUE);
    senQ.command[senQ.store]=element; 
 //   fprintf(stderr," INSERTING in Command Queue %s\n",Q.command[Q.store].system_name);
    senQ.store++;  // point to next available storage position in queue[]
 }

cmd * senq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((cmd *) &senQ.command[indx]); 
}

/************* FIBER QUEUE ******/

void fiberq_store(cmd element )
{
  if (fiberQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(fiberQ.store==fiberQ.retrieve)
  {
    fiberQ.store = 0; fiberQ.retrieve = 0;
  }
   //  fprintf(stderr," ###### Element in Command Queue %s\n",element.system_name);
    bzero(&fiberQ.command[fiberQ.store],MAXQUE);
    fiberQ.command[fiberQ.store]=element; 
 //   fprintf(stderr," INSERTING in Command Queue %s\n",Q.command[Q.store].system_name);
    fiberQ.store++;  // point to next available storage position in queue[]
 }

cmd * fiberq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((cmd *) &fiberQ.command[indx]); 
}

/****** BACK END QUEUE *******/

void backq_store(cmd element )
{
  if (backQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(backQ.store==backQ.retrieve)
  {
    backQ.store = 0; backQ.retrieve = 0;
  }
   //  fprintf(stderr," ###### Element in Command Queue %s\n",element.system_name);
    bzero(&backQ.command[backQ.store],MAXQUE);
    backQ.command[backQ.store]=element; 
 //   fprintf(stderr," INSERTING in Command Queue %s\n",Q.command[Q.store].system_name);
    backQ.store++;  // point to next available storage position in queue[]
 }

cmd * backq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((cmd *) &backQ.command[indx]); 
}

