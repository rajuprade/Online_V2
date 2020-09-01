#include"servo_queue.h"

// SENVO system queue 

void C00srv_store(SRVANT_CMD element)
{
   servocmd *c1;
   c1 = malloc(sizeof(servocmd));
  
  if (C00srvq.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(C00srvq.store==C00srvq.retrieve)
  {
    C00srvq.store = 0; C00srvq.retrieve = 0;
  }
    fprintf(stderr," ###### Element in Command Queue %s\n",element.SRVCMD.system_name);
    bzero(&C00srvq.srvcmd[C00srvq.store],MAXQUE);
    C00srvq.srvcmd[C00srvq.store]=element;
    c1 = &element.SRVCMD;
    printservocmd(c1); 
    fprintf(stderr," INSERTING in Command Queue %s\n",C00srvq.srvcmd[C00srvq.store].SRVCMD.system_name);
    C00srvq.store++;  // point to next available storage position in queue[]
 }

SRVANT_CMD * C00srv_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((SRVANT_CMD *) &C00srvq.srvcmd[indx]); 
}

// C01 Servo system Queue

void C01srv_store(SRVANT_CMD element)
{
   servocmd *c1;
   c1 = malloc(sizeof(servocmd));
  
  if (C01srvq.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(C01srvq.store==C01srvq.retrieve)
  {
    C01srvq.store = 0; C01srvq.retrieve = 0;
  }
    fprintf(stderr," ###### Element in Command Queue %s\n",element.SRVCMD.system_name);
    bzero(&C01srvq.srvcmd[C01srvq.store],MAXQUE);
    C01srvq.srvcmd[C01srvq.store]=element;
    c1 = &element.SRVCMD;
    printservocmd(c1); 
    fprintf(stderr," INSERTING in Command Queue %s\n",C01srvq.srvcmd[C00srvq.store].SRVCMD.system_name);
    C01srvq.store++;  // point to next available storage position in queue[]
 }

SRVANT_CMD * C01srv_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((SRVANT_CMD *) &C01srvq.srvcmd[indx]); 
}

// C02 Servo system Queue

void C02srv_store(SRVANT_CMD element)
{
   servocmd *c1;
   c1 = malloc(sizeof(servocmd));
  
  if (C02srvq.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(C02srvq.store==C02srvq.retrieve)
  {
    C02srvq.store = 0; C02srvq.retrieve = 0;
  }
    fprintf(stderr," ###### Element in Command Queue %s\n",element.SRVCMD.system_name);
    bzero(&C02srvq.srvcmd[C02srvq.store],MAXQUE);
    C02srvq.srvcmd[C02srvq.store]=element;
    c1 = &element.SRVCMD;
    printservocmd(c1); 
    fprintf(stderr," INSERTING in Command Queue %s\n",C02srvq.srvcmd[C00srvq.store].SRVCMD.system_name);
    C02srvq.store++;  // point to next available storage position in queue[]
 }

SRVANT_CMD * C02srv_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((SRVANT_CMD *) &C02srvq.srvcmd[indx]); 
}

// C03 Servo system Queue

void C03srv_store(SRVANT_CMD element)
{
   servocmd *c1;
   c1 = malloc(sizeof(servocmd));
  
  if (C03srvq.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(C03srvq.store==C03srvq.retrieve)
  {
    C03srvq.store = 0; C03srvq.retrieve = 0;
  }
    fprintf(stderr," ###### Element in Command Queue %s\n",element.SRVCMD.system_name);
    bzero(&C03srvq.srvcmd[C03srvq.store],MAXQUE);
    C03srvq.srvcmd[C03srvq.store]=element;
    c1 = &element.SRVCMD;
    printservocmd(c1); 
    fprintf(stderr," INSERTING in Command Queue %s\n",C03srvq.srvcmd[C00srvq.store].SRVCMD.system_name);
    C03srvq.store++;  // point to next available storage position in queue[]
 }

SRVANT_CMD * C03srv_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((SRVANT_CMD *) &C03srvq.srvcmd[indx]); 
}

// C04 Servo system Queue

void C04srv_store(SRVANT_CMD element)
{
   servocmd *c1;
   c1 = malloc(sizeof(servocmd));
  
  if (C04srvq.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(C04srvq.store==C04srvq.retrieve)
  {
    C04srvq.store = 0; C04srvq.retrieve = 0;
  }
    fprintf(stderr," ###### Element in Command Queue %s\n",element.SRVCMD.system_name);
    bzero(&C04srvq.srvcmd[C04srvq.store],MAXQUE);
    C04srvq.srvcmd[C04srvq.store]=element;
    c1 = &element.SRVCMD;
    printservocmd(c1); 
    fprintf(stderr," INSERTING in Command Queue %s\n",C04srvq.srvcmd[C00srvq.store].SRVCMD.system_name);
    C04srvq.store++;  // point to next available storage position in queue[]
 }

SRVANT_CMD * C04srv_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((SRVANT_CMD *) &C04srvq.srvcmd[indx]); 
}

// C05 Servo system Queue

void C05srv_store(SRVANT_CMD element)
{
   servocmd *c1;
   c1 = malloc(sizeof(servocmd));
  
  if (C05srvq.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(C05srvq.store==C05srvq.retrieve)
  {
    C05srvq.store = 0; C05srvq.retrieve = 0;
  }
    fprintf(stderr," ###### Element in Command Queue %s\n",element.SRVCMD.system_name);
    bzero(&C05srvq.srvcmd[C05srvq.store],MAXQUE);
    C05srvq.srvcmd[C05srvq.store]=element;
    c1 = &element.SRVCMD;
    printservocmd(c1); 
    fprintf(stderr," INSERTING in Command Queue %s\n",C05srvq.srvcmd[C00srvq.store].SRVCMD.system_name);
    C05srvq.store++;  // point to next available storage position in queue[]
 }

SRVANT_CMD * C05srv_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((SRVANT_CMD *) &C05srvq.srvcmd[indx]); 
}

// C06 Servo system Queue

void C06srv_store(SRVANT_CMD element)
{
   servocmd *c1;
   c1 = malloc(sizeof(servocmd));
  
  if (C06srvq.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(C06srvq.store==C06srvq.retrieve)
  {
    C06srvq.store = 0; C06srvq.retrieve = 0;
  }
    fprintf(stderr," ###### Element in Command Queue %s\n",element.SRVCMD.system_name);
    bzero(&C06srvq.srvcmd[C06srvq.store],MAXQUE);
    C06srvq.srvcmd[C06srvq.store]=element;
    c1 = &element.SRVCMD;
    printservocmd(c1); 
    fprintf(stderr," INSERTING in Command Queue %s\n",C06srvq.srvcmd[C00srvq.store].SRVCMD.system_name);
    C06srvq.store++;  // point to next available storage position in queue[]
 }

SRVANT_CMD * C06srv_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((SRVANT_CMD *) &C06srvq.srvcmd[indx]); 
}

// C08 Servo system Queue

void C08srv_store(SRVANT_CMD element)
{
   servocmd *c1;
   c1 = malloc(sizeof(servocmd));
  
  if (C08srvq.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(C08srvq.store==C08srvq.retrieve)
  {
    C08srvq.store = 0; C08srvq.retrieve = 0;
  }
    fprintf(stderr," ###### Element in Command Queue %s\n",element.SRVCMD.system_name);
    bzero(&C08srvq.srvcmd[C08srvq.store],MAXQUE);
    C08srvq.srvcmd[C08srvq.store]=element;
    c1 = &element.SRVCMD;
    printservocmd(c1); 
    fprintf(stderr," INSERTING in Command Queue %s\n",C08srvq.srvcmd[C00srvq.store].SRVCMD.system_name);
    C08srvq.store++;  // point to next available storage position in queue[]
 }

SRVANT_CMD * C08srv_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((SRVANT_CMD *) &C08srvq.srvcmd[indx]); 
}

// C09 Servo system Queue

void C09srv_store(SRVANT_CMD element)
{
   servocmd *c1;
   c1 = malloc(sizeof(servocmd));
  
  if (C09srvq.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(C09srvq.store==C09srvq.retrieve)
  {
    C09srvq.store = 0; C09srvq.retrieve = 0;
  }
    fprintf(stderr," ###### Element in Command Queue %s\n",element.SRVCMD.system_name);
    bzero(&C09srvq.srvcmd[C09srvq.store],MAXQUE);
    C09srvq.srvcmd[C09srvq.store]=element;
    c1 = &element.SRVCMD;
    printservocmd(c1); 
    fprintf(stderr," INSERTING in Command Queue %s\n",C09srvq.srvcmd[C00srvq.store].SRVCMD.system_name);
    C09srvq.store++;  // point to next available storage position in queue[]
 }

SRVANT_CMD * C09srv_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((SRVANT_CMD *) &C09srvq.srvcmd[indx]); 
}

// C10 Servo system Queue

void C10srv_store(SRVANT_CMD element)
{
   servocmd *c1;
   c1 = malloc(sizeof(servocmd));
  
  if (C10srvq.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(C10srvq.store==C10srvq.retrieve)
  {
    C10srvq.store = 0; C10srvq.retrieve = 0;
  }
    fprintf(stderr," ###### Element in Command Queue %s\n",element.SRVCMD.system_name);
    bzero(&C10srvq.srvcmd[C10srvq.store],MAXQUE);
    C10srvq.srvcmd[C10srvq.store]=element;
    c1 = &element.SRVCMD;
    printservocmd(c1); 
    fprintf(stderr," INSERTING in Command Queue %s\n",C10srvq.srvcmd[C00srvq.store].SRVCMD.system_name);
    C10srvq.store++;  // point to next available storage position in queue[]
 }

SRVANT_CMD * C10srv_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((SRVANT_CMD *) &C10srvq.srvcmd[indx]); 
}

// C11 Servo system Queue

void C11srv_store(SRVANT_CMD element)
{
   servocmd *c1;
   c1 = malloc(sizeof(servocmd));
  
  if (C11srvq.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(C11srvq.store==C11srvq.retrieve)
  {
    C11srvq.store = 0; C11srvq.retrieve = 0;
  }
    fprintf(stderr," ###### Element in Command Queue %s\n",element.SRVCMD.system_name);
    bzero(&C11srvq.srvcmd[C11srvq.store],MAXQUE);
    C11srvq.srvcmd[C11srvq.store]=element;
    c1 = &element.SRVCMD;
    printservocmd(c1); 
    fprintf(stderr," INSERTING in Command Queue %s\n",C11srvq.srvcmd[C00srvq.store].SRVCMD.system_name);
    C11srvq.store++;  // point to next available storage position in queue[]
 }

SRVANT_CMD * C11srv_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((SRVANT_CMD *) &C11srvq.srvcmd[indx]); 
}
// C12 Servo system Queue

void C12srv_store(SRVANT_CMD element)
{
   servocmd *c1;
   c1 = malloc(sizeof(servocmd));
  
  if (C12srvq.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(C12srvq.store==C12srvq.retrieve)
  {
    C12srvq.store = 0; C12srvq.retrieve = 0;
  }
    fprintf(stderr," ###### Element in Command Queue %s\n",element.SRVCMD.system_name);
    bzero(&C12srvq.srvcmd[C12srvq.store],MAXQUE);
    C12srvq.srvcmd[C12srvq.store]=element;
    c1 = &element.SRVCMD;
    printservocmd(c1); 
    fprintf(stderr," INSERTING in Command Queue %s\n",C12srvq.srvcmd[C00srvq.store].SRVCMD.system_name);
    C12srvq.store++;  // point to next available storage position in queue[]
 }

SRVANT_CMD * C12srv_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((SRVANT_CMD *) &C12srvq.srvcmd[indx]); 
}
// C13 Servo system Queue

void C13srv_store(SRVANT_CMD element)
{
   servocmd *c1;
   c1 = malloc(sizeof(servocmd));
  
  if (C13srvq.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(C13srvq.store==C13srvq.retrieve)
  {
    C13srvq.store = 0; C13srvq.retrieve = 0;
  }
    fprintf(stderr," ###### Element in Command Queue %s\n",element.SRVCMD.system_name);
    bzero(&C13srvq.srvcmd[C13srvq.store],MAXQUE);
    C13srvq.srvcmd[C13srvq.store]=element;
    c1 = &element.SRVCMD;
    printservocmd(c1); 
    fprintf(stderr," INSERTING in Command Queue %s\n",C13srvq.srvcmd[C00srvq.store].SRVCMD.system_name);
    C13srvq.store++;  // point to next available storage position in queue[]
 }

SRVANT_CMD * C13srv_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((SRVANT_CMD *) &C13srvq.srvcmd[indx]); 
}
// C14 Servo system Queue

void C14srv_store(SRVANT_CMD element)
{
   servocmd *c1;
   c1 = malloc(sizeof(servocmd));
  
  if (C14srvq.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(C14srvq.store==C14srvq.retrieve)
  {
    C14srvq.store = 0; C14srvq.retrieve = 0;
  }
    fprintf(stderr," ###### Element in Command Queue %s\n",element.SRVCMD.system_name);
    bzero(&C14srvq.srvcmd[C14srvq.store],MAXQUE);
    C14srvq.srvcmd[C14srvq.store]=element;
    c1 = &element.SRVCMD;
    printservocmd(c1); 
    fprintf(stderr," INSERTING in Command Queue %s\n",C14srvq.srvcmd[C00srvq.store].SRVCMD.system_name);
    C14srvq.store++;  // point to next available storage position in queue[]
 }

SRVANT_CMD * C14srv_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((SRVANT_CMD *) &C14srvq.srvcmd[indx]); 
}

// E02 Servo system Queue

void E02srv_store(SRVANT_CMD element)
{
   servocmd *c1;
   c1 = malloc(sizeof(servocmd));
  
  if (E02srvq.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(E02srvq.store==E02srvq.retrieve)
  {
    E02srvq.store = 0; E02srvq.retrieve = 0;
  }
    fprintf(stderr," ###### Element in Command Queue %s\n",element.SRVCMD.system_name);
    bzero(&E02srvq.srvcmd[E02srvq.store],MAXQUE);
    E02srvq.srvcmd[E02srvq.store]=element;
    c1 = &element.SRVCMD;
    printservocmd(c1); 
    fprintf(stderr," INSERTING in Command Queue %s\n",E02srvq.srvcmd[C00srvq.store].SRVCMD.system_name);
    E02srvq.store++;  // point to next available storage position in queue[]
 }

SRVANT_CMD * E02srv_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((SRVANT_CMD *) &E02srvq.srvcmd[indx]); 
}
// E03 Servo system Queue

void E03srv_store(SRVANT_CMD element)
{
   servocmd *c1;
   c1 = malloc(sizeof(servocmd));
  
  if (E03srvq.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(E03srvq.store==E03srvq.retrieve)
  {
    E03srvq.store = 0; E03srvq.retrieve = 0;
  }
    fprintf(stderr," ###### Element in Command Queue %s\n",element.SRVCMD.system_name);
    bzero(&E03srvq.srvcmd[E03srvq.store],MAXQUE);
    E03srvq.srvcmd[E03srvq.store]=element;
    c1 = &element.SRVCMD;
    printservocmd(c1); 
    fprintf(stderr," INSERTING in Command Queue %s\n",E03srvq.srvcmd[C00srvq.store].SRVCMD.system_name);
    E03srvq.store++;  // point to next available storage position in queue[]
 }

SRVANT_CMD * E03srv_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((SRVANT_CMD *) &E03srvq.srvcmd[indx]); 
}

// E04 Servo system Queue

void E04srv_store(SRVANT_CMD element)
{
   servocmd *c1;
   c1 = malloc(sizeof(servocmd));
  
  if (E04srvq.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(E04srvq.store==E04srvq.retrieve)
  {
    E04srvq.store = 0; E04srvq.retrieve = 0;
  }
    fprintf(stderr," ###### Element in Command Queue %s\n",element.SRVCMD.system_name);
    bzero(&E04srvq.srvcmd[E04srvq.store],MAXQUE);
    E04srvq.srvcmd[E04srvq.store]=element;
    c1 = &element.SRVCMD;
    printservocmd(c1); 
    fprintf(stderr," INSERTING in Command Queue %s\n",E04srvq.srvcmd[C00srvq.store].SRVCMD.system_name);
    E04srvq.store++;  // point to next available storage position in queue[]
 }

SRVANT_CMD * E04srv_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((SRVANT_CMD *) &E04srvq.srvcmd[indx]); 
}

// E05 Servo system Queue

void E05srv_store(SRVANT_CMD element)
{
   servocmd *c1;
   c1 = malloc(sizeof(servocmd));
  
  if (E05srvq.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(E05srvq.store==E05srvq.retrieve)
  {
    E05srvq.store = 0; E05srvq.retrieve = 0;
  }
    fprintf(stderr," ###### Element in Command Queue %s\n",element.SRVCMD.system_name);
    bzero(&E05srvq.srvcmd[E05srvq.store],MAXQUE);
    E05srvq.srvcmd[E05srvq.store]=element;
    c1 = &element.SRVCMD;
    printservocmd(c1); 
    fprintf(stderr," INSERTING in Command Queue %s\n",E05srvq.srvcmd[C00srvq.store].SRVCMD.system_name);
    E05srvq.store++;  // point to next available storage position in queue[]
 }

SRVANT_CMD * E05srv_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((SRVANT_CMD *) &E05srvq.srvcmd[indx]); 
}


// E06 Servo system Queue

void E06srv_store(SRVANT_CMD element)
{
   servocmd *c1;
   c1 = malloc(sizeof(servocmd));
  
  if (E06srvq.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(E06srvq.store==E06srvq.retrieve)
  {
    E06srvq.store = 0; E06srvq.retrieve = 0;
  }
    fprintf(stderr," ###### Element in Command Queue %s\n",element.SRVCMD.system_name);
    bzero(&E06srvq.srvcmd[E06srvq.store],MAXQUE);
    E06srvq.srvcmd[E06srvq.store]=element;
    c1 = &element.SRVCMD;
    printservocmd(c1); 
    fprintf(stderr," INSERTING in Command Queue %s\n",E06srvq.srvcmd[C00srvq.store].SRVCMD.system_name);
    E06srvq.store++;  // point to next available storage position in queue[]
 }

SRVANT_CMD * E06srv_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((SRVANT_CMD *) &E06srvq.srvcmd[indx]); 
}
// S01 Servo system Queue

void S01srv_store(SRVANT_CMD element)
{
   servocmd *c1;
   c1 = malloc(sizeof(servocmd));
  
  if (S01srvq.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(S01srvq.store==S01srvq.retrieve)
  {
    S01srvq.store = 0; S01srvq.retrieve = 0;
  }
    fprintf(stderr," ###### Element in Command Queue %s\n",element.SRVCMD.system_name);
    bzero(&S01srvq.srvcmd[S01srvq.store],MAXQUE);
    S01srvq.srvcmd[S01srvq.store]=element;
    c1 = &element.SRVCMD;
    printservocmd(c1); 
    fprintf(stderr," INSERTING in Command Queue %s\n",S01srvq.srvcmd[C00srvq.store].SRVCMD.system_name);
    S01srvq.store++;  // point to next available storage position in queue[]
 }

SRVANT_CMD * S01srv_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((SRVANT_CMD *) &S01srvq.srvcmd[indx]); 
}

// S02 Servo system Queue

void S02srv_store(SRVANT_CMD element)
{
   servocmd *c1;
   c1 = malloc(sizeof(servocmd));
  
  if (S02srvq.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(S02srvq.store==S02srvq.retrieve)
  {
    S02srvq.store = 0; S02srvq.retrieve = 0;
  }
    fprintf(stderr," ###### Element in Command Queue %s\n",element.SRVCMD.system_name);
    bzero(&S02srvq.srvcmd[S02srvq.store],MAXQUE);
    S02srvq.srvcmd[S02srvq.store]=element;
    c1 = &element.SRVCMD;
    printservocmd(c1); 
    fprintf(stderr," INSERTING in Command Queue %s\n",S02srvq.srvcmd[C00srvq.store].SRVCMD.system_name);
    S02srvq.store++;  // point to next available storage position in queue[]
 }

SRVANT_CMD * S02srv_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((SRVANT_CMD *) &S02srvq.srvcmd[indx]); 
}

// S03 Servo system Queue

void S03srv_store(SRVANT_CMD element)
{
   servocmd *c1;
   c1 = malloc(sizeof(servocmd));
  
  if (S03srvq.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(S03srvq.store==S03srvq.retrieve)
  {
    S03srvq.store = 0; S03srvq.retrieve = 0;
  }
    fprintf(stderr," ###### Element in Command Queue %s\n",element.SRVCMD.system_name);
    bzero(&S03srvq.srvcmd[S03srvq.store],MAXQUE);
    S03srvq.srvcmd[S03srvq.store]=element;
    c1 = &element.SRVCMD;
    printservocmd(c1); 
    fprintf(stderr," INSERTING in Command Queue %s\n",S03srvq.srvcmd[C00srvq.store].SRVCMD.system_name);
    S03srvq.store++;  // point to next available storage position in queue[]
 }

SRVANT_CMD * S03srv_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((SRVANT_CMD *) &S03srvq.srvcmd[indx]); 
}

// S04 Servo system Queue

void S04srv_store(SRVANT_CMD element)
{
   servocmd *c1;
   c1 = malloc(sizeof(servocmd));
  
  if (S04srvq.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(S04srvq.store==S04srvq.retrieve)
  {
    S04srvq.store = 0; S04srvq.retrieve = 0;
  }
    fprintf(stderr," ###### Element in Command Queue %s\n",element.SRVCMD.system_name);
    bzero(&S04srvq.srvcmd[S04srvq.store],MAXQUE);
    S04srvq.srvcmd[S04srvq.store]=element;
    c1 = &element.SRVCMD;
    printservocmd(c1); 
    fprintf(stderr," INSERTING in Command Queue %s\n",S04srvq.srvcmd[C00srvq.store].SRVCMD.system_name);
    S04srvq.store++;  // point to next available storage position in queue[]
 }

SRVANT_CMD * S04srv_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((SRVANT_CMD *) &S04srvq.srvcmd[indx]); 
}


// S06 Servo system Queue

void S06srv_store(SRVANT_CMD element)
{
   servocmd *c1;
   c1 = malloc(sizeof(servocmd));
  
  if (S06srvq.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(S06srvq.store==S06srvq.retrieve)
  {
    S06srvq.store = 0; S06srvq.retrieve = 0;
  }
    fprintf(stderr," ###### Element in Command Queue %s\n",element.SRVCMD.system_name);
    bzero(&S06srvq.srvcmd[S06srvq.store],MAXQUE);
    S06srvq.srvcmd[S06srvq.store]=element;
    c1 = &element.SRVCMD;
    printservocmd(c1); 
    fprintf(stderr," INSERTING in Command Queue %s\n",S06srvq.srvcmd[C00srvq.store].SRVCMD.system_name);
    S06srvq.store++;  // point to next available storage position in queue[]
 }

SRVANT_CMD * S06srv_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((SRVANT_CMD *) &S06srvq.srvcmd[indx]); 
}

// W01 Servo system Queue

void W01srv_store(SRVANT_CMD element)
{
   servocmd *c1;
   c1 = malloc(sizeof(servocmd));
  
  if (W01srvq.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(W01srvq.store==W01srvq.retrieve)
  {
    W01srvq.store = 0; W01srvq.retrieve = 0;
  }
    fprintf(stderr," ###### Element in Command Queue %s\n",element.SRVCMD.system_name);
    bzero(&W01srvq.srvcmd[W01srvq.store],MAXQUE);
    W01srvq.srvcmd[W01srvq.store]=element;
    c1 = &element.SRVCMD;
    printservocmd(c1); 
    fprintf(stderr," INSERTING in Command Queue %s\n",W01srvq.srvcmd[C00srvq.store].SRVCMD.system_name);
    W01srvq.store++;  // point to next available storage position in queue[]
 }

SRVANT_CMD * W01srv_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((SRVANT_CMD *) &W01srvq.srvcmd[indx]); 
}

// W02 Servo system Queue

void W02srv_store(SRVANT_CMD element)
{
   servocmd *c1;
   c1 = malloc(sizeof(servocmd));
  
  if (W02srvq.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(W02srvq.store==W02srvq.retrieve)
  {
    W02srvq.store = 0; W02srvq.retrieve = 0;
  }
    fprintf(stderr," ###### Element in Command Queue %s\n",element.SRVCMD.system_name);
    bzero(&W02srvq.srvcmd[W02srvq.store],MAXQUE);
    W02srvq.srvcmd[W02srvq.store]=element;
    c1 = &element.SRVCMD;
    printservocmd(c1); 
    fprintf(stderr," INSERTING in Command Queue %s\n",W02srvq.srvcmd[C00srvq.store].SRVCMD.system_name);
    W02srvq.store++;  // point to next available storage position in queue[]
 }

SRVANT_CMD * W02srv_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((SRVANT_CMD *) &W02srvq.srvcmd[indx]); 
}

// W03 Servo system Queue

void W03srv_store(SRVANT_CMD element)
{
   servocmd *c1;
   c1 = malloc(sizeof(servocmd));
  
  if (W03srvq.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(W03srvq.store==W03srvq.retrieve)
  {
    W03srvq.store = 0; W03srvq.retrieve = 0;
  }
    fprintf(stderr," ###### Element in Command Queue %s\n",element.SRVCMD.system_name);
    bzero(&W03srvq.srvcmd[W03srvq.store],MAXQUE);
    W03srvq.srvcmd[W03srvq.store]=element;
    c1 = &element.SRVCMD;
    printservocmd(c1); 
    fprintf(stderr," INSERTING in Command Queue %s\n",W03srvq.srvcmd[C00srvq.store].SRVCMD.system_name);
    W03srvq.store++;  // point to next available storage position in queue[]
 }

SRVANT_CMD * W03srv_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((SRVANT_CMD *) &W03srvq.srvcmd[indx]); 
}

// W04 Servo system Queue

void W04srv_store(SRVANT_CMD element)
{
   servocmd *c1;
   c1 = malloc(sizeof(servocmd));
  
  if (W04srvq.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(W04srvq.store==W04srvq.retrieve)
  {
    W04srvq.store = 0; W04srvq.retrieve = 0;
  }
    fprintf(stderr," ###### Element in Command Queue %s\n",element.SRVCMD.system_name);
    bzero(&W04srvq.srvcmd[W04srvq.store],MAXQUE);
    W04srvq.srvcmd[W04srvq.store]=element;
    c1 = &element.SRVCMD;
    printservocmd(c1); 
    fprintf(stderr," INSERTING in Command Queue %s\n",W04srvq.srvcmd[C00srvq.store].SRVCMD.system_name);
    W04srvq.store++;  // point to next available storage position in queue[]
 }

SRVANT_CMD * W04srv_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((SRVANT_CMD *) &W04srvq.srvcmd[indx]); 
}

// W05 Servo system Queue

void W05srv_store(SRVANT_CMD element)
{
   servocmd *c1;
   c1 = malloc(sizeof(servocmd));
  
  if (W05srvq.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(W05srvq.store==W05srvq.retrieve)
  {
    W05srvq.store = 0; W05srvq.retrieve = 0;
  }
    fprintf(stderr," ###### Element in Command Queue %s\n",element.SRVCMD.system_name);
    bzero(&W05srvq.srvcmd[W05srvq.store],MAXQUE);
    W05srvq.srvcmd[W05srvq.store]=element;
    c1 = &element.SRVCMD;
    printservocmd(c1); 
    fprintf(stderr," INSERTING in Command Queue %s\n",W05srvq.srvcmd[C00srvq.store].SRVCMD.system_name);
    W05srvq.store++;  // point to next available storage position in queue[]
 }

SRVANT_CMD * W05srv_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((SRVANT_CMD *) &W05srvq.srvcmd[indx]); 
}

// W06 Servo system Queue

void W06srv_store(SRVANT_CMD element)
{
   servocmd *c1;
   c1 = malloc(sizeof(servocmd));
  
  if (W06srvq.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(W06srvq.store==W06srvq.retrieve)
  {
    W06srvq.store = 0; W06srvq.retrieve = 0;
  }
    fprintf(stderr," ###### Element in Command Queue %s\n",element.SRVCMD.system_name);
    bzero(&W06srvq.srvcmd[W06srvq.store],MAXQUE);
    W06srvq.srvcmd[W06srvq.store]=element;
    c1 = &element.SRVCMD;
    printservocmd(c1); 
    fprintf(stderr," INSERTING in Command Queue %s\n",W06srvq.srvcmd[C00srvq.store].SRVCMD.system_name);
    W06srvq.store++;  // point to next available storage position in queue[]
 }

SRVANT_CMD * W06srv_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((SRVANT_CMD *) &W06srvq.srvcmd[indx]); 
}





