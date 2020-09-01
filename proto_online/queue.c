#include"queue.h"

void q_store(ANT_CMD element )
{
  if (Q.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(Q.store==Q.retrieve)
  {
    Q.store = 0; Q.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&Q.command[Q.store],MAXQUE);
    Q.command[Q.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",Q.command[Q.store].CMD.system_name);
    Q.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * q_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &Q.command[indx]); 
}

void q1_store(ANT_CMD element )
{
  if (Q1.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(Q1.store==Q1.retrieve)
  {
    Q1.store = 0; Q1.retrieve = 0;
  }
    fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&Q1.command[Q1.store],MAXQUE);
    Q1.command[Q1.store]=element; 
    fprintf(stderr," INSERTING in Command Queue %s\n",Q.command[Q.store].CMD.system_name);
    Q1.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * q1_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &Q1.command[indx]); 
}
