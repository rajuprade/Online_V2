#include"queue.h"

// SENtinel system queue 

void senq_store(ANT_CMD element )
{
  if (senQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(senQ.store==senQ.retrieve)
  {
    senQ.store = 0; senQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&senQ.command[senQ.store],MAXQUE);
    senQ.command[senQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",senQ.command[senQ.store].CMD.system_name);
    senQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * senq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &senQ.command[indx]); 
}

// FPS system queue 

void fpsq_store(ANT_CMD element )
{
  if (fpsQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(fpsQ.store==fpsQ.retrieve)
  {
    fpsQ.store = 0; fpsQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&fpsQ.command[fpsQ.store],MAXQUE);
    fpsQ.command[fpsQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",fpsQ.command[fpsQ.store].CMD.system_name);
    fpsQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * fpsq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &fpsQ.command[indx]); 
}



// Front end system queue 

void frontq_store(ANT_CMD element )
{
  if (frontQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(frontQ.store==frontQ.retrieve)
  {
    frontQ.store = 0; frontQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&frontQ.command[frontQ.store],MAXQUE);
    frontQ.command[frontQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",frontQ.command[frontQ.store].CMD.system_name);
    frontQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * frontq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &frontQ.command[indx]); 
}


// fiber system queue 

void fiberq_store(ANT_CMD element )
{
  if (fiberQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(fiberQ.store==fiberQ.retrieve)
  {
    fiberQ.store = 0; fiberQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&fiberQ.command[fiberQ.store],MAXQUE);
    fiberQ.command[fiberQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",fiberQ.command[fiberQ.store].CMD.system_name);
    fiberQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * fiberq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &fiberQ.command[indx]); 
}

// Back end system queue 

void backq_store(ANT_CMD element )
{
  if (backQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(backQ.store==backQ.retrieve)
  {
    backQ.store = 0; backQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&backQ.command[backQ.store],MAXQUE);
    backQ.command[backQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",backQ.command[backQ.store].CMD.system_name);
    backQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * backq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &backQ.command[indx]); 
}


// Self test system queue 

void selfq_store(ANT_CMD element )
{
  if (selfQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(selfQ.store==selfQ.retrieve)
  {
    selfQ.store = 0; selfQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&selfQ.command[selfQ.store],MAXQUE);
    selfQ.command[selfQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",selfQ.command[selfQ.store].CMD.system_name);
    selfQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * selfq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &selfQ.command[indx]); 
}

/***************** C01 system Queue functions here ******************************/

void c1_senq_store(ANT_CMD element )
{
  if (c1senQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c1senQ.store==c1senQ.retrieve)
  {
    c1senQ.store = 0; c1senQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c1senQ.command[c1senQ.store],MAXQUE);
    c1senQ.command[c1senQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c1senQ.command[c1senQ.store].CMD.system_name);
    c1senQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c1_senq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c1senQ.command[indx]); 
}


// C1 FPS system queue 

void c1_fpsq_store(ANT_CMD element )
{
  if (c1fpsQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c1fpsQ.store==c1fpsQ.retrieve)
  {
    c1fpsQ.store = 0; c1fpsQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c1fpsQ.command[c1fpsQ.store],MAXQUE);
    c1fpsQ.command[c1fpsQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c1fpsQ.command[c1fpsQ.store].CMD.system_name);
    c1fpsQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c1_fpsq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c1fpsQ.command[indx]); 
}
// Front end system queue 

void c1_frontq_store(ANT_CMD element )
{
  if (c1frontQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c1frontQ.store==c1frontQ.retrieve)
  {
    c1frontQ.store = 0; c1frontQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c1frontQ.command[c1frontQ.store],MAXQUE);
    c1frontQ.command[c1frontQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c1frontQ.command[c1frontQ.store].CMD.system_name);
    c1frontQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c1_frontq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c1frontQ.command[indx]); 
}


// fiber system queue 

void c1_fiberq_store(ANT_CMD element )
{
  if (c1fiberQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c1fiberQ.store==c1fiberQ.retrieve)
  {
    c1fiberQ.store = 0; c1fiberQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c1fiberQ.command[c1fiberQ.store],MAXQUE);
    c1fiberQ.command[c1fiberQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c1fiberQ.command[c1fiberQ.store].CMD.system_name);
    c1fiberQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c1_fiberq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c1fiberQ.command[indx]); 
}

// Back end system queue 

void c1_backq_store(ANT_CMD element )
{
  if (c1backQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c1backQ.store==c1backQ.retrieve)
  {
    c1backQ.store = 0; c1backQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c1backQ.command[c1backQ.store],MAXQUE);
    c1backQ.command[c1backQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c1backQ.command[c1backQ.store].CMD.system_name);
    c1backQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c1_backq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c1backQ.command[indx]); 
}


// Self test system queue 

void c1_selfq_store(ANT_CMD element )
{
  if (c1selfQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c1selfQ.store==c1selfQ.retrieve)
  {
    c1selfQ.store = 0; c1selfQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c1selfQ.command[c1selfQ.store],MAXQUE);
    c1selfQ.command[c1selfQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c1selfQ.command[c1selfQ.store].CMD.system_name);
    c1selfQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c1_selfq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c1selfQ.command[indx]); 
}

/***************** C02 system Queue functions here ******************************/

void c2_senq_store(ANT_CMD element )
{
  if (c2senQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c2senQ.store==c2senQ.retrieve)
  {
    c2senQ.store = 0; c2senQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c2senQ.command[c2senQ.store],MAXQUE);
    c2senQ.command[c2senQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c2senQ.command[c2senQ.store].CMD.system_name);
    c2senQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c2_senq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c2senQ.command[indx]); 
}


// C2 FPS system queue 

void c2_fpsq_store(ANT_CMD element )
{
  if (c2fpsQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c2fpsQ.store==c2fpsQ.retrieve)
  {
    c2fpsQ.store = 0; c2fpsQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c2fpsQ.command[c2fpsQ.store],MAXQUE);
    c2fpsQ.command[c2fpsQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c2fpsQ.command[c2fpsQ.store].CMD.system_name);
    c2fpsQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c2_fpsq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c2fpsQ.command[indx]); 
}

// Front end system queue 

void c2_frontq_store(ANT_CMD element )
{
  if (c2frontQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c2frontQ.store==c2frontQ.retrieve)
  {
    c2frontQ.store = 0; c2frontQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c2frontQ.command[c2frontQ.store],MAXQUE);
    c2frontQ.command[c2frontQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c2frontQ.command[c2frontQ.store].CMD.system_name);
    c2frontQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c2_frontq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c2frontQ.command[indx]); 
}


// fiber system queue 

void c2_fiberq_store(ANT_CMD element )
{
  if (c2fiberQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c2fiberQ.store==c2fiberQ.retrieve)
  {
    c2fiberQ.store = 0; c2fiberQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c2fiberQ.command[c2fiberQ.store],MAXQUE);
    c2fiberQ.command[c2fiberQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c2fiberQ.command[c2fiberQ.store].CMD.system_name);
    c2fiberQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c2_fiberq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c2fiberQ.command[indx]); 
}

// Back end system queue 

void c2_backq_store(ANT_CMD element )
{
  if (c2backQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c2backQ.store==c2backQ.retrieve)
  {
    c2backQ.store = 0; c2backQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c2backQ.command[c2backQ.store],MAXQUE);
    c2backQ.command[c2backQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c2backQ.command[c2backQ.store].CMD.system_name);
    c2backQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c2_backq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c2backQ.command[indx]); 
}


// Self test system queue 

void c2_selfq_store(ANT_CMD element )
{
  if (c2selfQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c2selfQ.store==c2selfQ.retrieve)
  {
    c2selfQ.store = 0; c2selfQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c2selfQ.command[c2selfQ.store],MAXQUE);
    c2selfQ.command[c2selfQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c2selfQ.command[c2selfQ.store].CMD.system_name);
    c2selfQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c2_selfq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c2selfQ.command[indx]); 
}

/***************** C03 system Queue functions here ******************************/


// C3 FPS system queue 

void c3_fpsq_store(ANT_CMD element )
{
  if (c3fpsQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c3fpsQ.store==c3fpsQ.retrieve)
  {
    c3fpsQ.store = 0; c3fpsQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c3fpsQ.command[c3fpsQ.store],MAXQUE);
    c3fpsQ.command[c3fpsQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c3fpsQ.command[c3fpsQ.store].CMD.system_name);
    c3fpsQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c3_fpsq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c3fpsQ.command[indx]); 
}


void c3_senq_store(ANT_CMD element )
{
  if (c3senQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c3senQ.store==c3senQ.retrieve)
  {
    c3senQ.store = 0; c3senQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c3senQ.command[c3senQ.store],MAXQUE);
    c3senQ.command[c3senQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c3senQ.command[c3senQ.store].CMD.system_name);
    c3senQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c3_senq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c3senQ.command[indx]); 
}

// Front end system queue 

void c3_frontq_store(ANT_CMD element )
{
  if (c3frontQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c3frontQ.store==c3frontQ.retrieve)
  {
    c3frontQ.store = 0; c3frontQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c3frontQ.command[c3frontQ.store],MAXQUE);
    c3frontQ.command[c3frontQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c3frontQ.command[c3frontQ.store].CMD.system_name);
    c3frontQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c3_frontq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c3frontQ.command[indx]); 
}


// fiber system queue 

void c3_fiberq_store(ANT_CMD element )
{
  if (c3fiberQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c3fiberQ.store==c3fiberQ.retrieve)
  {
    c3fiberQ.store = 0; c3fiberQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c3fiberQ.command[c3fiberQ.store],MAXQUE);
    c3fiberQ.command[c3fiberQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c3fiberQ.command[c3fiberQ.store].CMD.system_name);
    c3fiberQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c3_fiberq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c3fiberQ.command[indx]); 
}

// Back end system queue 

void c3_backq_store(ANT_CMD element )
{
  if (c3backQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c3backQ.store==c3backQ.retrieve)
  {
    c3backQ.store = 0; c3backQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c3backQ.command[c3backQ.store],MAXQUE);
    c3backQ.command[c3backQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c3backQ.command[c3backQ.store].CMD.system_name);
    c3backQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c3_backq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c3backQ.command[indx]); 
}


// Self test system queue 

void c3_selfq_store(ANT_CMD element )
{
  if (c3selfQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c3selfQ.store==c3selfQ.retrieve)
  {
    c3selfQ.store = 0; c3selfQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c3selfQ.command[c3selfQ.store],MAXQUE);
    c3selfQ.command[c3selfQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c3selfQ.command[c3selfQ.store].CMD.system_name);
    c3selfQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c3_selfq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c3selfQ.command[indx]); 
}

/***************** C04 system Queue functions here ******************************/

// C4 FPS system queue 

void c4_fpsq_store(ANT_CMD element )
{
  if (c4fpsQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c4fpsQ.store==c4fpsQ.retrieve)
  {
    c4fpsQ.store = 0; c4fpsQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c4fpsQ.command[c4fpsQ.store],MAXQUE);
    c4fpsQ.command[c4fpsQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c4fpsQ.command[c4fpsQ.store].CMD.system_name);
    c4fpsQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c4_fpsq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c4fpsQ.command[indx]); 
}


void c4_senq_store(ANT_CMD element )
{
  if (c4senQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c4senQ.store==c4senQ.retrieve)
  {
    c4senQ.store = 0; c4senQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c4senQ.command[c4senQ.store],MAXQUE);
    c4senQ.command[c4senQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c4senQ.command[c4senQ.store].CMD.system_name);
    c4senQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c4_senq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c4senQ.command[indx]); 
}

// Front end system queue 

void c4_frontq_store(ANT_CMD element )
{
  if (c4frontQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c4frontQ.store==c4frontQ.retrieve)
  {
    c4frontQ.store = 0; c4frontQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c4frontQ.command[c4frontQ.store],MAXQUE);
    c4frontQ.command[c4frontQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c4frontQ.command[c4frontQ.store].CMD.system_name);
    c4frontQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c4_frontq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c4frontQ.command[indx]); 
}


// fiber system queue 

void c4_fiberq_store(ANT_CMD element )
{
  if (c4fiberQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c4fiberQ.store==c4fiberQ.retrieve)
  {
    c4fiberQ.store = 0; c4fiberQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c4fiberQ.command[c4fiberQ.store],MAXQUE);
    c4fiberQ.command[c4fiberQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c4fiberQ.command[c4fiberQ.store].CMD.system_name);
    c4fiberQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c4_fiberq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c4fiberQ.command[indx]); 
}

// Back end system queue 

void c4_backq_store(ANT_CMD element )
{
  if (c4backQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c4backQ.store==c4backQ.retrieve)
  {
    c4backQ.store = 0; c4backQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c4backQ.command[c4backQ.store],MAXQUE);
    c4backQ.command[c4backQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c4backQ.command[c4backQ.store].CMD.system_name);
    c4backQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c4_backq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c4backQ.command[indx]); 
}


// Self test system queue 

void c4_selfq_store(ANT_CMD element )
{
  if (c4selfQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c4selfQ.store==c4selfQ.retrieve)
  {
    c4selfQ.store = 0; c4selfQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c4selfQ.command[c4selfQ.store],MAXQUE);
    c4selfQ.command[c4selfQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c4selfQ.command[c4selfQ.store].CMD.system_name);
    c4selfQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c4_selfq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c4selfQ.command[indx]); 
}

/***************** C05 system Queue functions here ******************************/


// C5 FPS system queue 

void c5_fpsq_store(ANT_CMD element )
{
  if (c5fpsQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c5fpsQ.store==c5fpsQ.retrieve)
  {
    c5fpsQ.store = 0; c5fpsQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c5fpsQ.command[c5fpsQ.store],MAXQUE);
    c5fpsQ.command[c5fpsQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c5fpsQ.command[c5fpsQ.store].CMD.system_name);
    c5fpsQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c5_fpsq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c5fpsQ.command[indx]); 
}

void c5_senq_store(ANT_CMD element )
{
  if (c5senQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c5senQ.store==c5senQ.retrieve)
  {
    c5senQ.store = 0; c5senQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c5senQ.command[c5senQ.store],MAXQUE);
    c5senQ.command[c5senQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c5senQ.command[c5senQ.store].CMD.system_name);
    c5senQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c5_senq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c5senQ.command[indx]); 
}

// Front end system queue 

void c5_frontq_store(ANT_CMD element )
{
  if (c5frontQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c5frontQ.store==c5frontQ.retrieve)
  {
    c5frontQ.store = 0; c5frontQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c5frontQ.command[c5frontQ.store],MAXQUE);
    c5frontQ.command[c5frontQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c5frontQ.command[c5frontQ.store].CMD.system_name);
    c5frontQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c5_frontq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c5frontQ.command[indx]); 
}


// fiber system queue 

void c5_fiberq_store(ANT_CMD element )
{
  if (c5fiberQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c5fiberQ.store==c5fiberQ.retrieve)
  {
    c5fiberQ.store = 0; c5fiberQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c5fiberQ.command[c5fiberQ.store],MAXQUE);
    c5fiberQ.command[c5fiberQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c5fiberQ.command[c5fiberQ.store].CMD.system_name);
    c5fiberQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c5_fiberq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c5fiberQ.command[indx]); 
}

// Back end system queue 

void c5_backq_store(ANT_CMD element )
{
  if (c5backQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c5backQ.store==c5backQ.retrieve)
  {
    c5backQ.store = 0; c5backQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c5backQ.command[c5backQ.store],MAXQUE);
    c5backQ.command[c5backQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c5backQ.command[c5backQ.store].CMD.system_name);
    c5backQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c5_backq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c5backQ.command[indx]); 
}


// Self test system queue 

void c5_selfq_store(ANT_CMD element )
{
  if (c5selfQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c5selfQ.store==c5selfQ.retrieve)
  {
    c5selfQ.store = 0; c5selfQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c5selfQ.command[c5selfQ.store],MAXQUE);
    c5selfQ.command[c5selfQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c5selfQ.command[c5selfQ.store].CMD.system_name);
    c5selfQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c5_selfq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c5selfQ.command[indx]); 
}

/***************** C06 system Queue functions here ******************************/

// C06 FPS system queue 

void c6_fpsq_store(ANT_CMD element )
{
  if (c6fpsQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c6fpsQ.store==c6fpsQ.retrieve)
  {
    c6fpsQ.store = 0; c6fpsQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c6fpsQ.command[c6fpsQ.store],MAXQUE);
    c6fpsQ.command[c6fpsQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c6fpsQ.command[c6fpsQ.store].CMD.system_name);
    c6fpsQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c6_fpsq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c6fpsQ.command[indx]); 
}


void c6_senq_store(ANT_CMD element )
{
  if (c6senQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c6senQ.store==c6senQ.retrieve)
  {
    c6senQ.store = 0; c6senQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c6senQ.command[c6senQ.store],MAXQUE);
    c6senQ.command[c6senQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c6senQ.command[c6senQ.store].CMD.system_name);
    c6senQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c6_senq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c6senQ.command[indx]); 
}

// Front end system queue 

void c6_frontq_store(ANT_CMD element )
{
  if (c6frontQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c6frontQ.store==c6frontQ.retrieve)
  {
    c6frontQ.store = 0; c6frontQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c6frontQ.command[c6frontQ.store],MAXQUE);
    c6frontQ.command[c6frontQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c6frontQ.command[c6frontQ.store].CMD.system_name);
    c6frontQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c6_frontq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c6frontQ.command[indx]); 
}


// fiber system queue 

void c6_fiberq_store(ANT_CMD element )
{
  if (c6fiberQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c6fiberQ.store==c6fiberQ.retrieve)
  {
    c6fiberQ.store = 0; c6fiberQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c6fiberQ.command[c6fiberQ.store],MAXQUE);
    c6fiberQ.command[c6fiberQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c6fiberQ.command[c6fiberQ.store].CMD.system_name);
    c6fiberQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c6_fiberq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c6fiberQ.command[indx]); 
}

// Back end system queue 

void c6_backq_store(ANT_CMD element )
{
  if (c6backQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c6backQ.store==c6backQ.retrieve)
  {
    c6backQ.store = 0; c6backQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c6backQ.command[c6backQ.store],MAXQUE);
    c6backQ.command[c6backQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c6backQ.command[c6backQ.store].CMD.system_name);
    c6backQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c6_backq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c6backQ.command[indx]); 
}

// Self test system queue 

void c6_selfq_store(ANT_CMD element )
{
  if (c6selfQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c6selfQ.store==c6selfQ.retrieve)
  {
    c6selfQ.store = 0; c6selfQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c6selfQ.command[c6selfQ.store],MAXQUE);
    c6selfQ.command[c6selfQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c6selfQ.command[c6selfQ.store].CMD.system_name);
    c6selfQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c6_selfq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c6selfQ.command[indx]); 
}

/***************** C08 system Queue functions here ******************************/
// C8 FPS system queue 

void c8_fpsq_store(ANT_CMD element )
{
  if (c8fpsQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c8fpsQ.store==c8fpsQ.retrieve)
  {
    c8fpsQ.store = 0; c8fpsQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c8fpsQ.command[c8fpsQ.store],MAXQUE);
    c8fpsQ.command[c8fpsQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c8fpsQ.command[c8fpsQ.store].CMD.system_name);
    c8fpsQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c8_fpsq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c8fpsQ.command[indx]); 
}


void c8_senq_store(ANT_CMD element )
{
  if (c8senQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c8senQ.store==c8senQ.retrieve)
  {
    c8senQ.store = 0; c8senQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c8senQ.command[c8senQ.store],MAXQUE);
    c8senQ.command[c8senQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c8senQ.command[c8senQ.store].CMD.system_name);
    c8senQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c8_senq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c8senQ.command[indx]); 
}

// Front end system queue 

void c8_frontq_store(ANT_CMD element )
{
  if (c8frontQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c8frontQ.store==c8frontQ.retrieve)
  {
    c8frontQ.store = 0; c8frontQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c8frontQ.command[c8frontQ.store],MAXQUE);
    c8frontQ.command[c8frontQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c8frontQ.command[c8frontQ.store].CMD.system_name);
    c8frontQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c8_frontq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c8frontQ.command[indx]); 
}


// fiber system queue 

void c8_fiberq_store(ANT_CMD element )
{
  if (c8fiberQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c8fiberQ.store==c8fiberQ.retrieve)
  {
    c8fiberQ.store = 0; c8fiberQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c8fiberQ.command[c8fiberQ.store],MAXQUE);
    c8fiberQ.command[c8fiberQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c8fiberQ.command[c8fiberQ.store].CMD.system_name);
    c8fiberQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c8_fiberq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c8fiberQ.command[indx]); 
}

// Back end system queue 

void c8_backq_store(ANT_CMD element )
{
  if (c8backQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c8backQ.store==c8backQ.retrieve)
  {
    c8backQ.store = 0; c8backQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c8backQ.command[c8backQ.store],MAXQUE);
    c8backQ.command[c8backQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c8backQ.command[c8backQ.store].CMD.system_name);
    c8backQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c8_backq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c8backQ.command[indx]); 
}


// Self test system queue 

void c8_selfq_store(ANT_CMD element )
{
  if (c8selfQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c8selfQ.store==c8selfQ.retrieve)
  {
    c8selfQ.store = 0; c8selfQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c8selfQ.command[c8selfQ.store],MAXQUE);
    c8selfQ.command[c8selfQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c8selfQ.command[c8selfQ.store].CMD.system_name);
    c8selfQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c8_selfq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c8selfQ.command[indx]); 
}

/***************** C09 system Queue functions here ******************************/

// C9 FPS system queue 

void c9_fpsq_store(ANT_CMD element )
{
  if (c9fpsQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c9fpsQ.store==c9fpsQ.retrieve)
  {
    c9fpsQ.store = 0; c9fpsQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c9fpsQ.command[c9fpsQ.store],MAXQUE);
    c9fpsQ.command[c9fpsQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c9fpsQ.command[c9fpsQ.store].CMD.system_name);
    c9fpsQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c9_fpsq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c9fpsQ.command[indx]); 
}


void c9_senq_store(ANT_CMD element )
{
  if (c9senQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c9senQ.store==c9senQ.retrieve)
  {
    c9senQ.store = 0; c9senQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c9senQ.command[c9senQ.store],MAXQUE);
    c9senQ.command[c9senQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c9senQ.command[c9senQ.store].CMD.system_name);
    c9senQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c9_senq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c9senQ.command[indx]); 
}

// Front end system queue 

void c9_frontq_store(ANT_CMD element )
{
  if (c9frontQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c9frontQ.store==c9frontQ.retrieve)
  {
    c9frontQ.store = 0; c9frontQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c9frontQ.command[c9frontQ.store],MAXQUE);
    c9frontQ.command[c9frontQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c9frontQ.command[c9frontQ.store].CMD.system_name);
    c9frontQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c9_frontq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c9frontQ.command[indx]); 
}


// fiber system queue 

void c9_fiberq_store(ANT_CMD element )
{
  if (c9fiberQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c9fiberQ.store==c9fiberQ.retrieve)
  {
    c9fiberQ.store = 0; c9fiberQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c9fiberQ.command[c9fiberQ.store],MAXQUE);
    c9fiberQ.command[c9fiberQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c9fiberQ.command[c9fiberQ.store].CMD.system_name);
    c9fiberQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c9_fiberq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c9fiberQ.command[indx]); 
}

// Back end system queue 

void c9_backq_store(ANT_CMD element )
{
  if (c9backQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c9backQ.store==c9backQ.retrieve)
  {
    c9backQ.store = 0; c9backQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c9backQ.command[c9backQ.store],MAXQUE);
    c9backQ.command[c9backQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c9backQ.command[c9backQ.store].CMD.system_name);
    c9backQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c9_backq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c9backQ.command[indx]); 
}


// Self test system queue 

void c9_selfq_store(ANT_CMD element )
{
  if (c9selfQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c9selfQ.store==c9selfQ.retrieve)
  {
    c9selfQ.store = 0; c9selfQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c9selfQ.command[c9selfQ.store],MAXQUE);
    c9selfQ.command[c9selfQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c9selfQ.command[c9selfQ.store].CMD.system_name);
    c9selfQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c9_selfq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c9selfQ.command[indx]); 
}

/***************** C10 system Queue functions here ******************************/

// C10 FPS system queue 

void c10_fpsq_store(ANT_CMD element )
{
  if (c10fpsQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c10fpsQ.store==c10fpsQ.retrieve)
  {
    c10fpsQ.store = 0; c10fpsQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c10fpsQ.command[c10fpsQ.store],MAXQUE);
    c10fpsQ.command[c10fpsQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c10fpsQ.command[c10fpsQ.store].CMD.system_name);
    c10fpsQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c10_fpsq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c10fpsQ.command[indx]); 
}

void c10_senq_store(ANT_CMD element )
{
  if (c10senQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c10senQ.store==c10senQ.retrieve)
  {
    c10senQ.store = 0; c10senQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c10senQ.command[c10senQ.store],MAXQUE);
    c10senQ.command[c10senQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c10senQ.command[c10senQ.store].CMD.system_name);
    c10senQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c10_senq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c10senQ.command[indx]); 
}

// Front end system queue 

void c10_frontq_store(ANT_CMD element )
{
  if (c10frontQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c10frontQ.store==c10frontQ.retrieve)
  {
    c10frontQ.store = 0; c10frontQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c10frontQ.command[c10frontQ.store],MAXQUE);
    c10frontQ.command[c10frontQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c10frontQ.command[c10frontQ.store].CMD.system_name);
    c10frontQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c10_frontq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c10frontQ.command[indx]); 
}


// fiber system queue 

void c10_fiberq_store(ANT_CMD element )
{
  if (c10fiberQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c10fiberQ.store==c10fiberQ.retrieve)
  {
    c10fiberQ.store = 0; c10fiberQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c10fiberQ.command[c10fiberQ.store],MAXQUE);
    c10fiberQ.command[c10fiberQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c10fiberQ.command[c10fiberQ.store].CMD.system_name);
    c10fiberQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c10_fiberq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c10fiberQ.command[indx]); 
}

// Back end system queue 

void c10_backq_store(ANT_CMD element )
{
  if (c10backQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c10backQ.store==c10backQ.retrieve)
  {
    c10backQ.store = 0; c10backQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c10backQ.command[c10backQ.store],MAXQUE);
    c10backQ.command[c10backQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c10backQ.command[c10backQ.store].CMD.system_name);
    c10backQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c10_backq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c10backQ.command[indx]); 
}


// Self test system queue 

void c10_selfq_store(ANT_CMD element )
{
  if (c10selfQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c10selfQ.store==c10selfQ.retrieve)
  {
    c10selfQ.store = 0; c10selfQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c10selfQ.command[c10selfQ.store],MAXQUE);
    c10selfQ.command[c10selfQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c10selfQ.command[c10selfQ.store].CMD.system_name);
    c10selfQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c10_selfq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c10selfQ.command[indx]); 
}


/***************** C11 system Queue functions here ******************************/

// C11 FPS system queue 

void c11_fpsq_store(ANT_CMD element )
{
  if (c11fpsQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c11fpsQ.store==c11fpsQ.retrieve)
  {
    c11fpsQ.store = 0; c11fpsQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c11fpsQ.command[c11fpsQ.store],MAXQUE);
    c11fpsQ.command[c11fpsQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c11fpsQ.command[c11fpsQ.store].CMD.system_name);
    c11fpsQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c11_fpsq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c11fpsQ.command[indx]); 
}

void c11_senq_store(ANT_CMD element )
{
  if (c11senQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c11senQ.store==c11senQ.retrieve)
  {
    c11senQ.store = 0; c11senQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c11senQ.command[c11senQ.store],MAXQUE);
    c11senQ.command[c11senQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c11senQ.command[c11senQ.store].CMD.system_name);
    c11senQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c11_senq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c11senQ.command[indx]); 
}

// Front end system queue 

void c11_frontq_store(ANT_CMD element )
{
  if (c11frontQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c11frontQ.store==c11frontQ.retrieve)
  {
    c11frontQ.store = 0; c11frontQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c11frontQ.command[c11frontQ.store],MAXQUE);
    c11frontQ.command[c11frontQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c11frontQ.command[c11frontQ.store].CMD.system_name);
    c11frontQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c11_frontq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c11frontQ.command[indx]); 
}


// fiber system queue 

void c11_fiberq_store(ANT_CMD element )
{
  if (c11fiberQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c11fiberQ.store==c11fiberQ.retrieve)
  {
    c11fiberQ.store = 0; c11fiberQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c11fiberQ.command[c11fiberQ.store],MAXQUE);
    c11fiberQ.command[c11fiberQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c11fiberQ.command[c11fiberQ.store].CMD.system_name);
    c11fiberQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c11_fiberq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c11fiberQ.command[indx]); 
}

// Back end system queue 

void c11_backq_store(ANT_CMD element )
{
  if (c11backQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c11backQ.store==c11backQ.retrieve)
  {
    c11backQ.store = 0; c11backQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c11backQ.command[c11backQ.store],MAXQUE);
    c11backQ.command[c11backQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c11backQ.command[c11backQ.store].CMD.system_name);
    c11backQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c11_backq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c11backQ.command[indx]); 
}


// Self test system queue 

void c11_selfq_store(ANT_CMD element )
{
  if (c11selfQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c11selfQ.store==c11selfQ.retrieve)
  {
    c11selfQ.store = 0; c11selfQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c11selfQ.command[c11selfQ.store],MAXQUE);
    c11selfQ.command[c11selfQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c11selfQ.command[c11selfQ.store].CMD.system_name);
    c11selfQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c11_selfq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c11selfQ.command[indx]); 
}

/***************** C12 system Queue functions here ******************************/

// C12 FPS system queue 

void c12_fpsq_store(ANT_CMD element )
{
  if (c12fpsQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c12fpsQ.store==c12fpsQ.retrieve)
  {
    c12fpsQ.store = 0; c12fpsQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c12fpsQ.command[c12fpsQ.store],MAXQUE);
    c12fpsQ.command[c12fpsQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c12fpsQ.command[c12fpsQ.store].CMD.system_name);
    c12fpsQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c12_fpsq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c12fpsQ.command[indx]); 
}

void c12_senq_store(ANT_CMD element )
{
  if (c12senQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c12senQ.store==c12senQ.retrieve)
  {
    c12senQ.store = 0; c12senQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c12senQ.command[c12senQ.store],MAXQUE);
    c12senQ.command[c12senQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c12senQ.command[c12senQ.store].CMD.system_name);
    c12senQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c12_senq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c12senQ.command[indx]); 
}

// Front end system queue 

void c12_frontq_store(ANT_CMD element )
{
  if (c12frontQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c12frontQ.store==c12frontQ.retrieve)
  {
    c12frontQ.store = 0; c12frontQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c12frontQ.command[c12frontQ.store],MAXQUE);
    c12frontQ.command[c12frontQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c12frontQ.command[c12frontQ.store].CMD.system_name);
    c12frontQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c12_frontq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c12frontQ.command[indx]); 
}


// fiber system queue 

void c12_fiberq_store(ANT_CMD element )
{
  if (c12fiberQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c12fiberQ.store==c12fiberQ.retrieve)
  {
    c12fiberQ.store = 0; c12fiberQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c12fiberQ.command[c12fiberQ.store],MAXQUE);
    c12fiberQ.command[c12fiberQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c12fiberQ.command[c12fiberQ.store].CMD.system_name);
    c12fiberQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c12_fiberq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c12fiberQ.command[indx]); 
}

// Back end system queue 

void c12_backq_store(ANT_CMD element )
{
  if (c12backQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c12backQ.store==c12backQ.retrieve)
  {
    c12backQ.store = 0; c12backQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c12backQ.command[c12backQ.store],MAXQUE);
    c12backQ.command[c12backQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c12backQ.command[c12backQ.store].CMD.system_name);
    c12backQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c12_backq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c12backQ.command[indx]); 
}


// Self test system queue 

void c12_selfq_store(ANT_CMD element )
{
  if (c12selfQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c12selfQ.store==c12selfQ.retrieve)
  {
    c12selfQ.store = 0; c12selfQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c12selfQ.command[c12selfQ.store],MAXQUE);
    c12selfQ.command[c12selfQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c12selfQ.command[c12selfQ.store].CMD.system_name);
    c12selfQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c12_selfq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c12selfQ.command[indx]); 
}


/***************** C13 system Queue functions here ******************************/

// C13 FPS system queue 

void c13_fpsq_store(ANT_CMD element )
{
  if (c13fpsQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c13fpsQ.store==c13fpsQ.retrieve)
  {
    c13fpsQ.store = 0; c13fpsQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c13fpsQ.command[c13fpsQ.store],MAXQUE);
    c13fpsQ.command[c13fpsQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c13fpsQ.command[c13fpsQ.store].CMD.system_name);
    c13fpsQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c13_fpsq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c13fpsQ.command[indx]); 
}

void c13_senq_store(ANT_CMD element )
{
  if (c13senQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c13senQ.store==c13senQ.retrieve)
  {
    c13senQ.store = 0; c13senQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c13senQ.command[c13senQ.store],MAXQUE);
    c13senQ.command[c13senQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c13senQ.command[c13senQ.store].CMD.system_name);
    c13senQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c13_senq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c13senQ.command[indx]); 
}

// Front end system queue 

void c13_frontq_store(ANT_CMD element )
{
  if (c13frontQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c13frontQ.store==c13frontQ.retrieve)
  {
    c13frontQ.store = 0; c13frontQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c13frontQ.command[c13frontQ.store],MAXQUE);
    c13frontQ.command[c13frontQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c13frontQ.command[c13frontQ.store].CMD.system_name);
    c13frontQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c13_frontq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c13frontQ.command[indx]); 
}


// fiber system queue 

void c13_fiberq_store(ANT_CMD element )
{
  if (c13fiberQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c13fiberQ.store==c13fiberQ.retrieve)
  {
    c13fiberQ.store = 0; c13fiberQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c13fiberQ.command[c13fiberQ.store],MAXQUE);
    c13fiberQ.command[c13fiberQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c13fiberQ.command[c13fiberQ.store].CMD.system_name);
    c13fiberQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c13_fiberq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c13fiberQ.command[indx]); 
}

// Back end system queue 

void c13_backq_store(ANT_CMD element )
{
  if (c13backQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c13backQ.store==c13backQ.retrieve)
  {
    c13backQ.store = 0; c13backQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c13backQ.command[c13backQ.store],MAXQUE);
    c13backQ.command[c13backQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c13backQ.command[c13backQ.store].CMD.system_name);
    c13backQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c13_backq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c13backQ.command[indx]); 
}


// Self test system queue 

void c13_selfq_store(ANT_CMD element )
{
  if (c13selfQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c13selfQ.store==c13selfQ.retrieve)
  {
    c13selfQ.store = 0; c13selfQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c13selfQ.command[c13selfQ.store],MAXQUE);
    c13selfQ.command[c13selfQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c13selfQ.command[c13selfQ.store].CMD.system_name);
    c13selfQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c13_selfq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c13selfQ.command[indx]); 
}

/***************** C14 system Queue functions here ******************************/

// C14 FPS system queue 

void c14_fpsq_store(ANT_CMD element )
{
  if (c14fpsQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c14fpsQ.store==c14fpsQ.retrieve)
  {
    c14fpsQ.store = 0; c14fpsQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c14fpsQ.command[c14fpsQ.store],MAXQUE);
    c14fpsQ.command[c14fpsQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c14fpsQ.command[c14fpsQ.store].CMD.system_name);
    c14fpsQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c14_fpsq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c14fpsQ.command[indx]); 
}

void c14_senq_store(ANT_CMD element )
{
  if (c14senQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c14senQ.store==c14senQ.retrieve)
  {
    c14senQ.store = 0; c14senQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c14senQ.command[c14senQ.store],MAXQUE);
    c14senQ.command[c14senQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c14senQ.command[c14senQ.store].CMD.system_name);
    c14senQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c14_senq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c14senQ.command[indx]); 
}

// Front end system queue 

void c14_frontq_store(ANT_CMD element )
{
  if (c14frontQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c14frontQ.store==c14frontQ.retrieve)
  {
    c14frontQ.store = 0; c14frontQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c14frontQ.command[c14frontQ.store],MAXQUE);
    c14frontQ.command[c14frontQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c14frontQ.command[c14frontQ.store].CMD.system_name);
    c14frontQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c14_frontq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c14frontQ.command[indx]); 
}


// fiber system queue 

void c14_fiberq_store(ANT_CMD element )
{
  if (c14fiberQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c14fiberQ.store==c14fiberQ.retrieve)
  {
    c14fiberQ.store = 0; c14fiberQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c14fiberQ.command[c14fiberQ.store],MAXQUE);
    c14fiberQ.command[c14fiberQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c14fiberQ.command[c14fiberQ.store].CMD.system_name);
    c14fiberQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c14_fiberq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c14fiberQ.command[indx]); 
}

// Back end system queue 

void c14_backq_store(ANT_CMD element )
{
  if (c14backQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c14backQ.store==c14backQ.retrieve)
  {
    c14backQ.store = 0; c14backQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c14backQ.command[c14backQ.store],MAXQUE);
    c14backQ.command[c14backQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c14backQ.command[c14backQ.store].CMD.system_name);
    c14backQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c14_backq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c14backQ.command[indx]); 
}


// Self test system queue 

void c14_selfq_store(ANT_CMD element )
{
  if (c14selfQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(c14selfQ.store==c14selfQ.retrieve)
  {
    c14selfQ.store = 0; c14selfQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&c14selfQ.command[c14selfQ.store],MAXQUE);
    c14selfQ.command[c14selfQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",c14selfQ.command[c14selfQ.store].CMD.system_name);
    c14selfQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * c14_selfq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &c14selfQ.command[indx]); 
}





/***************** E02 system Queue functions here ******************************/

void e2_senq_store(ANT_CMD element )
{
  if (e2senQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(e2senQ.store==e2senQ.retrieve)
  {
    e2senQ.store = 0; e2senQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&e2senQ.command[e2senQ.store],MAXQUE);
    e2senQ.command[e2senQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",e2senQ.command[e2senQ.store].CMD.system_name);
    e2senQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * e2_senq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &e2senQ.command[indx]); 
}


// e2 FPS system queue 

void e2_fpsq_store(ANT_CMD element )
{
  if (e2fpsQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(e2fpsQ.store==e2fpsQ.retrieve)
  {
    e2fpsQ.store = 0; e2fpsQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&e2fpsQ.command[e2fpsQ.store],MAXQUE);
    e2fpsQ.command[e2fpsQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",e2fpsQ.command[e2fpsQ.store].CMD.system_name);
    e2fpsQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * e2_fpsq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &e2fpsQ.command[indx]); 
}
// Front end system queue 

void e2_frontq_store(ANT_CMD element )
{
  if (e2frontQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(e2frontQ.store==e2frontQ.retrieve)
  {
    e2frontQ.store = 0; e2frontQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&e2frontQ.command[e2frontQ.store],MAXQUE);
    e2frontQ.command[e2frontQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",e2frontQ.command[e2frontQ.store].CMD.system_name);
    e2frontQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * e2_frontq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &e2frontQ.command[indx]); 
}


// fiber system queue 

void e2_fiberq_store(ANT_CMD element )
{
  if (e2fiberQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(e2fiberQ.store==e2fiberQ.retrieve)
  {
    e2fiberQ.store = 0; e2fiberQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&e2fiberQ.command[e2fiberQ.store],MAXQUE);
    e2fiberQ.command[e2fiberQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",e2fiberQ.command[e2fiberQ.store].CMD.system_name);
    e2fiberQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * e2_fiberq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &e2fiberQ.command[indx]); 
}

// Back end system queue 

void e2_backq_store(ANT_CMD element )
{
  if (e2backQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(e2backQ.store==e2backQ.retrieve)
  {
    e2backQ.store = 0; e2backQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&e2backQ.command[e2backQ.store],MAXQUE);
    e2backQ.command[e2backQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",e2backQ.command[e2backQ.store].CMD.system_name);
    e2backQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * e2_backq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &e2backQ.command[indx]); 
}


// Self test system queue 

void e2_selfq_store(ANT_CMD element )
{
  if (e2selfQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(e2selfQ.store==e2selfQ.retrieve)
  {
    e2selfQ.store = 0; e2selfQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&e2selfQ.command[e2selfQ.store],MAXQUE);
    e2selfQ.command[e2selfQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",e2selfQ.command[e2selfQ.store].CMD.system_name);
    e2selfQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * e2_selfq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &e2selfQ.command[indx]); 
}


/***************** E03 system Queue functions here ******************************/

void e3_senq_store(ANT_CMD element )
{
  if (e3senQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(e3senQ.store==e3senQ.retrieve)
  {
    e3senQ.store = 0; e3senQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&e3senQ.command[e3senQ.store],MAXQUE);
    e3senQ.command[e3senQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",e3senQ.command[e3senQ.store].CMD.system_name);
    e3senQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * e3_senq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &e3senQ.command[indx]); 
}


// e3 FPS system queue 

void e3_fpsq_store(ANT_CMD element )
{
  if (e3fpsQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(e3fpsQ.store==e3fpsQ.retrieve)
  {
    e3fpsQ.store = 0; e3fpsQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&e3fpsQ.command[e3fpsQ.store],MAXQUE);
    e3fpsQ.command[e3fpsQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",e3fpsQ.command[e3fpsQ.store].CMD.system_name);
    e3fpsQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * e3_fpsq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &e3fpsQ.command[indx]); 
}
// Front end system queue 

void e3_frontq_store(ANT_CMD element )
{
  if (e3frontQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(e3frontQ.store==e3frontQ.retrieve)
  {
    e3frontQ.store = 0; e3frontQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&e3frontQ.command[e3frontQ.store],MAXQUE);
    e3frontQ.command[e3frontQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",e3frontQ.command[e3frontQ.store].CMD.system_name);
    e3frontQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * e3_frontq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &e3frontQ.command[indx]); 
}


// fiber system queue 

void e3_fiberq_store(ANT_CMD element )
{
  if (e3fiberQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(e3fiberQ.store==e3fiberQ.retrieve)
  {
    e3fiberQ.store = 0; e3fiberQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&e3fiberQ.command[e3fiberQ.store],MAXQUE);
    e3fiberQ.command[e3fiberQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",e3fiberQ.command[e3fiberQ.store].CMD.system_name);
    e3fiberQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * e3_fiberq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &e3fiberQ.command[indx]); 
}

// Back end system queue 

void e3_backq_store(ANT_CMD element )
{
  if (e3backQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(e3backQ.store==e3backQ.retrieve)
  {
    e3backQ.store = 0; e3backQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&e3backQ.command[e3backQ.store],MAXQUE);
    e3backQ.command[e3backQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",e3backQ.command[e3backQ.store].CMD.system_name);
    e3backQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * e3_backq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &e3backQ.command[indx]); 
}


// Self test system queue 

void e3_selfq_store(ANT_CMD element )
{
  if (e3selfQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(e3selfQ.store==e3selfQ.retrieve)
  {
    e3selfQ.store = 0; e3selfQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&e3selfQ.command[e3selfQ.store],MAXQUE);
    e3selfQ.command[e3selfQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",e3selfQ.command[e3selfQ.store].CMD.system_name);
    e3selfQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * e3_selfq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &e3selfQ.command[indx]); 
}


/***************** E04 system Queue functions here ******************************/

void e4_senq_store(ANT_CMD element )
{
  if (e4senQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(e4senQ.store==e4senQ.retrieve)
  {
    e4senQ.store = 0; e4senQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&e4senQ.command[e4senQ.store],MAXQUE);
    e4senQ.command[e4senQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",e4senQ.command[e4senQ.store].CMD.system_name);
    e4senQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * e4_senq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &e4senQ.command[indx]); 
}


// e4 FPS system queue 

void e4_fpsq_store(ANT_CMD element )
{
  if (e4fpsQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(e4fpsQ.store==e4fpsQ.retrieve)
  {
    e4fpsQ.store = 0; e4fpsQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&e4fpsQ.command[e4fpsQ.store],MAXQUE);
    e4fpsQ.command[e4fpsQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",e4fpsQ.command[e4fpsQ.store].CMD.system_name);
    e4fpsQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * e4_fpsq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &e4fpsQ.command[indx]); 
}
// Front end system queue 

void e4_frontq_store(ANT_CMD element )
{
  if (e4frontQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(e4frontQ.store==e4frontQ.retrieve)
  {
    e4frontQ.store = 0; e4frontQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&e4frontQ.command[e4frontQ.store],MAXQUE);
    e4frontQ.command[e4frontQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",e4frontQ.command[e4frontQ.store].CMD.system_name);
    e4frontQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * e4_frontq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &e4frontQ.command[indx]); 
}


// fiber system queue 

void e4_fiberq_store(ANT_CMD element )
{
  if (e4fiberQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(e4fiberQ.store==e4fiberQ.retrieve)
  {
    e4fiberQ.store = 0; e4fiberQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&e4fiberQ.command[e4fiberQ.store],MAXQUE);
    e4fiberQ.command[e4fiberQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",e4fiberQ.command[e4fiberQ.store].CMD.system_name);
    e4fiberQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * e4_fiberq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &e4fiberQ.command[indx]); 
}

// Back end system queue 

void e4_backq_store(ANT_CMD element )
{
  if (e4backQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(e4backQ.store==e4backQ.retrieve)
  {
    e4backQ.store = 0; e4backQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&e4backQ.command[e4backQ.store],MAXQUE);
    e4backQ.command[e4backQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",e4backQ.command[e4backQ.store].CMD.system_name);
    e4backQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * e4_backq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &e4backQ.command[indx]); 
}


// Self test system queue 

void e4_selfq_store(ANT_CMD element )
{
  if (e4selfQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(e4selfQ.store==e4selfQ.retrieve)
  {
    e4selfQ.store = 0; e4selfQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&e4selfQ.command[e4selfQ.store],MAXQUE);
    e4selfQ.command[e4selfQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",e4selfQ.command[e4selfQ.store].CMD.system_name);
    e4selfQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * e4_selfq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &e4selfQ.command[indx]); 
}


/***************** E05 system Queue functions here ******************************/

void e5_senq_store(ANT_CMD element )
{
  if (e5senQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(e5senQ.store==e5senQ.retrieve)
  {
    e5senQ.store = 0; e5senQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&e5senQ.command[e5senQ.store],MAXQUE);
    e5senQ.command[e5senQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",e5senQ.command[e5senQ.store].CMD.system_name);
    e5senQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * e5_senq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &e5senQ.command[indx]); 
}


// e5 FPS system queue 

void e5_fpsq_store(ANT_CMD element )
{
  if (e5fpsQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(e5fpsQ.store==e5fpsQ.retrieve)
  {
    e5fpsQ.store = 0; e5fpsQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&e5fpsQ.command[e5fpsQ.store],MAXQUE);
    e5fpsQ.command[e5fpsQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",e5fpsQ.command[e5fpsQ.store].CMD.system_name);
    e5fpsQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * e5_fpsq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &e5fpsQ.command[indx]); 
}
// Front end system queue 

void e5_frontq_store(ANT_CMD element )
{
  if (e5frontQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(e5frontQ.store==e5frontQ.retrieve)
  {
    e5frontQ.store = 0; e5frontQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&e5frontQ.command[e5frontQ.store],MAXQUE);
    e5frontQ.command[e5frontQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",e5frontQ.command[e5frontQ.store].CMD.system_name);
    e5frontQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * e5_frontq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &e5frontQ.command[indx]); 
}


// fiber system queue 

void e5_fiberq_store(ANT_CMD element )
{
  if (e5fiberQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(e5fiberQ.store==e5fiberQ.retrieve)
  {
    e5fiberQ.store = 0; e5fiberQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&e5fiberQ.command[e5fiberQ.store],MAXQUE);
    e5fiberQ.command[e5fiberQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",e5fiberQ.command[e5fiberQ.store].CMD.system_name);
    e5fiberQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * e5_fiberq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &e5fiberQ.command[indx]); 
}

// Back end system queue 

void e5_backq_store(ANT_CMD element )
{
  if (e5backQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(e5backQ.store==e5backQ.retrieve)
  {
    e5backQ.store = 0; e5backQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&e5backQ.command[e5backQ.store],MAXQUE);
    e5backQ.command[e5backQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",e5backQ.command[e5backQ.store].CMD.system_name);
    e5backQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * e5_backq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &e5backQ.command[indx]); 
}


// Self test system queue 

void e5_selfq_store(ANT_CMD element )
{
  if (e5selfQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(e5selfQ.store==e5selfQ.retrieve)
  {
    e5selfQ.store = 0; e5selfQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&e5selfQ.command[e5selfQ.store],MAXQUE);
    e5selfQ.command[e5selfQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",e5selfQ.command[e5selfQ.store].CMD.system_name);
    e5selfQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * e5_selfq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &e5selfQ.command[indx]); 
}


/***************** E06 system Queue functions here ******************************/

void e6_senq_store(ANT_CMD element )
{
  if (e6senQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(e6senQ.store==e6senQ.retrieve)
  {
    e6senQ.store = 0; e6senQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&e6senQ.command[e6senQ.store],MAXQUE);
    e6senQ.command[e6senQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",e6senQ.command[e6senQ.store].CMD.system_name);
    e6senQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * e6_senq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &e6senQ.command[indx]); 
}


// e6 FPS system queue 

void e6_fpsq_store(ANT_CMD element )
{
  if (e6fpsQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(e6fpsQ.store==e6fpsQ.retrieve)
  {
    e6fpsQ.store = 0; e6fpsQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&e6fpsQ.command[e6fpsQ.store],MAXQUE);
    e6fpsQ.command[e6fpsQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",e6fpsQ.command[e6fpsQ.store].CMD.system_name);
    e6fpsQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * e6_fpsq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &e6fpsQ.command[indx]); 
}
// Front end system queue 

void e6_frontq_store(ANT_CMD element )
{
  if (e6frontQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(e6frontQ.store==e6frontQ.retrieve)
  {
    e6frontQ.store = 0; e6frontQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&e6frontQ.command[e6frontQ.store],MAXQUE);
    e6frontQ.command[e6frontQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",e6frontQ.command[e6frontQ.store].CMD.system_name);
    e6frontQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * e6_frontq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &e6frontQ.command[indx]); 
}


// fiber system queue 

void e6_fiberq_store(ANT_CMD element )
{
  if (e6fiberQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(e6fiberQ.store==e6fiberQ.retrieve)
  {
    e6fiberQ.store = 0; e6fiberQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&e6fiberQ.command[e6fiberQ.store],MAXQUE);
    e6fiberQ.command[e6fiberQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",e6fiberQ.command[e6fiberQ.store].CMD.system_name);
    e6fiberQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * e6_fiberq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &e6fiberQ.command[indx]); 
}

// Back end system queue 

void e6_backq_store(ANT_CMD element )
{
  if (e6backQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(e6backQ.store==e6backQ.retrieve)
  {
    e6backQ.store = 0; e6backQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&e6backQ.command[e6backQ.store],MAXQUE);
    e6backQ.command[e6backQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",e6backQ.command[e6backQ.store].CMD.system_name);
    e6backQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * e6_backq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &e6backQ.command[indx]); 
}


// Self test system queue 

void e6_selfq_store(ANT_CMD element )
{
  if (e6selfQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(e6selfQ.store==e6selfQ.retrieve)
  {
    e6selfQ.store = 0; e6selfQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&e6selfQ.command[e6selfQ.store],MAXQUE);
    e6selfQ.command[e6selfQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",e6selfQ.command[e6selfQ.store].CMD.system_name);
    e6selfQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * e6_selfq_retrieve(int indx)
{
   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &e6selfQ.command[indx]); 
}

/***************** S01 system Queue functions here ******************************/

void s1_senq_store(ANT_CMD element )
{
  if (s1senQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(s1senQ.store==s1senQ.retrieve)
  {
    s1senQ.store = 0; s1senQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&s1senQ.command[s1senQ.store],MAXQUE);
    s1senQ.command[s1senQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",s1senQ.command[s1senQ.store].CMD.system_name);
    s1senQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * s1_senq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &s1senQ.command[indx]); 
}


// s1 FPS system queue 

void s1_fpsq_store(ANT_CMD element )
{
  if (s1fpsQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(s1fpsQ.store==s1fpsQ.retrieve)
  {
    s1fpsQ.store = 0; s1fpsQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&s1fpsQ.command[s1fpsQ.store],MAXQUE);
    s1fpsQ.command[s1fpsQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",s1fpsQ.command[s1fpsQ.store].CMD.system_name);
    s1fpsQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * s1_fpsq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &s1fpsQ.command[indx]); 
}
// Front end system queue 

void s1_frontq_store(ANT_CMD element )
{
  if (s1frontQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(s1frontQ.store==s1frontQ.retrieve)
  {
    s1frontQ.store = 0; s1frontQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&s1frontQ.command[s1frontQ.store],MAXQUE);
    s1frontQ.command[s1frontQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",s1frontQ.command[s1frontQ.store].CMD.system_name);
    s1frontQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * s1_frontq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &s1frontQ.command[indx]); 
}


// fiber system queue 

void s1_fiberq_store(ANT_CMD element )
{
  if (s1fiberQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(s1fiberQ.store==s1fiberQ.retrieve)
  {
    s1fiberQ.store = 0; s1fiberQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&s1fiberQ.command[s1fiberQ.store],MAXQUE);
    s1fiberQ.command[s1fiberQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",s1fiberQ.command[s1fiberQ.store].CMD.system_name);
    s1fiberQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * s1_fiberq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &s1fiberQ.command[indx]); 
}

// Back end system queue 

void s1_backq_store(ANT_CMD element )
{
  if (s1backQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(s1backQ.store==s1backQ.retrieve)
  {
    s1backQ.store = 0; s1backQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&s1backQ.command[s1backQ.store],MAXQUE);
    s1backQ.command[s1backQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",s1backQ.command[s1backQ.store].CMD.system_name);
    s1backQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * s1_backq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &s1backQ.command[indx]); 
}


// Self test system queue 

void s1_selfq_store(ANT_CMD element )
{
  if (s1selfQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(s1selfQ.store==s1selfQ.retrieve)
  {
    s1selfQ.store = 0; s1selfQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&s1selfQ.command[s1selfQ.store],MAXQUE);
    s1selfQ.command[s1selfQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",s1selfQ.command[s1selfQ.store].CMD.system_name);
    s1selfQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * s1_selfq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &s1selfQ.command[indx]); 
}


/***************** S02 system Queue functions here ******************************/

void s2_senq_store(ANT_CMD element )
{
  if (s2senQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(s2senQ.store==s2senQ.retrieve)
  {
    s2senQ.store = 0; s2senQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&s2senQ.command[s2senQ.store],MAXQUE);
    s2senQ.command[s2senQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",s2senQ.command[s2senQ.store].CMD.system_name);
    s2senQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * s2_senq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &s2senQ.command[indx]); 
}


// s2 FPS system queue 

void s2_fpsq_store(ANT_CMD element )
{
  if (s2fpsQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(s2fpsQ.store==s2fpsQ.retrieve)
  {
    s2fpsQ.store = 0; s2fpsQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&s2fpsQ.command[s2fpsQ.store],MAXQUE);
    s2fpsQ.command[s2fpsQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",s2fpsQ.command[s2fpsQ.store].CMD.system_name);
    s2fpsQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * s2_fpsq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &s2fpsQ.command[indx]); 
}
// Front end system queue 

void s2_frontq_store(ANT_CMD element )
{
  if (s2frontQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(s2frontQ.store==s2frontQ.retrieve)
  {
    s2frontQ.store = 0; s2frontQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&s2frontQ.command[s2frontQ.store],MAXQUE);
    s2frontQ.command[s2frontQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",s2frontQ.command[s2frontQ.store].CMD.system_name);
    s2frontQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * s2_frontq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &s2frontQ.command[indx]); 
}


// fiber system queue 

void s2_fiberq_store(ANT_CMD element )
{
  if (s2fiberQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(s2fiberQ.store==s2fiberQ.retrieve)
  {
    s2fiberQ.store = 0; s2fiberQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&s2fiberQ.command[s2fiberQ.store],MAXQUE);
    s2fiberQ.command[s2fiberQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",s2fiberQ.command[s2fiberQ.store].CMD.system_name);
    s2fiberQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * s2_fiberq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &s2fiberQ.command[indx]); 
}

// Back end system queue 

void s2_backq_store(ANT_CMD element )
{
  if (s2backQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(s2backQ.store==s2backQ.retrieve)
  {
    s2backQ.store = 0; s2backQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&s2backQ.command[s2backQ.store],MAXQUE);
    s2backQ.command[s2backQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",s2backQ.command[s2backQ.store].CMD.system_name);
    s2backQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * s2_backq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &s2backQ.command[indx]); 
}


// Self test system queue 

void s2_selfq_store(ANT_CMD element )
{
  if (s2selfQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(s2selfQ.store==s2selfQ.retrieve)
  {
    s2selfQ.store = 0; s2selfQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&s2selfQ.command[s2selfQ.store],MAXQUE);
    s2selfQ.command[s2selfQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",s2selfQ.command[s2selfQ.store].CMD.system_name);
    s2selfQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * s2_selfq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &s2selfQ.command[indx]); 
}

/***************** S03 system Queue functions here ******************************/

void s3_senq_store(ANT_CMD element )
{
  if (s3senQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(s3senQ.store==s3senQ.retrieve)
  {
    s3senQ.store = 0; s3senQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&s3senQ.command[s3senQ.store],MAXQUE);
    s3senQ.command[s3senQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",s3senQ.command[s3senQ.store].CMD.system_name);
    s3senQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * s3_senq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &s3senQ.command[indx]); 
}


// s3 FPS system queue 

void s3_fpsq_store(ANT_CMD element )
{
  if (s3fpsQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(s3fpsQ.store==s3fpsQ.retrieve)
  {
    s3fpsQ.store = 0; s3fpsQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&s3fpsQ.command[s3fpsQ.store],MAXQUE);
    s3fpsQ.command[s3fpsQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",s3fpsQ.command[s3fpsQ.store].CMD.system_name);
    s3fpsQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * s3_fpsq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &s3fpsQ.command[indx]); 
}
// Front end system queue 

void s3_frontq_store(ANT_CMD element )
{
  if (s3frontQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(s3frontQ.store==s3frontQ.retrieve)
  {
    s3frontQ.store = 0; s3frontQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&s3frontQ.command[s3frontQ.store],MAXQUE);
    s3frontQ.command[s3frontQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",s3frontQ.command[s3frontQ.store].CMD.system_name);
    s3frontQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * s3_frontq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &s3frontQ.command[indx]); 
}


// fiber system queue 

void s3_fiberq_store(ANT_CMD element )
{
  if (s3fiberQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(s3fiberQ.store==s3fiberQ.retrieve)
  {
    s3fiberQ.store = 0; s3fiberQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&s3fiberQ.command[s3fiberQ.store],MAXQUE);
    s3fiberQ.command[s3fiberQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",s3fiberQ.command[s3fiberQ.store].CMD.system_name);
    s3fiberQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * s3_fiberq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &s3fiberQ.command[indx]); 
}

// Back end system queue 

void s3_backq_store(ANT_CMD element )
{
  if (s3backQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(s3backQ.store==s3backQ.retrieve)
  {
    s3backQ.store = 0; s3backQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&s3backQ.command[s3backQ.store],MAXQUE);
    s3backQ.command[s3backQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",s3backQ.command[s3backQ.store].CMD.system_name);
    s3backQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * s3_backq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &s3backQ.command[indx]); 
}


// Self test system queue 

void s3_selfq_store(ANT_CMD element )
{
  if (s3selfQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(s3selfQ.store==s3selfQ.retrieve)
  {
    s3selfQ.store = 0; s3selfQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&s3selfQ.command[s3selfQ.store],MAXQUE);
    s3selfQ.command[s3selfQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",s3selfQ.command[s3selfQ.store].CMD.system_name);
    s3selfQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * s3_selfq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &s3selfQ.command[indx]); 
}

/***************** S04 system Queue functions here ******************************/

void s4_senq_store(ANT_CMD element )
{
  if (s4senQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(s4senQ.store==s4senQ.retrieve)
  {
    s4senQ.store = 0; s4senQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&s4senQ.command[s4senQ.store],MAXQUE);
    s4senQ.command[s4senQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",s4senQ.command[s4senQ.store].CMD.system_name);
    s4senQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * s4_senq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &s4senQ.command[indx]); 
}


// s4 FPS system queue 

void s4_fpsq_store(ANT_CMD element )
{
  if (s4fpsQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(s4fpsQ.store==s4fpsQ.retrieve)
  {
    s4fpsQ.store = 0; s4fpsQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&s4fpsQ.command[s4fpsQ.store],MAXQUE);
    s4fpsQ.command[s4fpsQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",s4fpsQ.command[s4fpsQ.store].CMD.system_name);
    s4fpsQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * s4_fpsq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &s4fpsQ.command[indx]); 
}
// Front end system queue 

void s4_frontq_store(ANT_CMD element )
{
  if (s4frontQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(s4frontQ.store==s4frontQ.retrieve)
  {
    s4frontQ.store = 0; s4frontQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&s4frontQ.command[s4frontQ.store],MAXQUE);
    s4frontQ.command[s4frontQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",s4frontQ.command[s4frontQ.store].CMD.system_name);
    s4frontQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * s4_frontq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &s4frontQ.command[indx]); 
}


// fiber system queue 

void s4_fiberq_store(ANT_CMD element )
{
  if (s4fiberQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(s4fiberQ.store==s4fiberQ.retrieve)
  {
    s4fiberQ.store = 0; s4fiberQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&s4fiberQ.command[s4fiberQ.store],MAXQUE);
    s4fiberQ.command[s4fiberQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",s4fiberQ.command[s4fiberQ.store].CMD.system_name);
    s4fiberQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * s4_fiberq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &s4fiberQ.command[indx]); 
}

// Back end system queue 

void s4_backq_store(ANT_CMD element )
{
  if (s4backQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(s4backQ.store==s4backQ.retrieve)
  {
    s4backQ.store = 0; s4backQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&s4backQ.command[s4backQ.store],MAXQUE);
    s4backQ.command[s4backQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",s4backQ.command[s4backQ.store].CMD.system_name);
    s4backQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * s4_backq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &s4backQ.command[indx]); 
}


// Self test system queue 

void s4_selfq_store(ANT_CMD element )
{
  if (s4selfQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(s4selfQ.store==s4selfQ.retrieve)
  {
    s4selfQ.store = 0; s4selfQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&s4selfQ.command[s4selfQ.store],MAXQUE);
    s4selfQ.command[s4selfQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",s4selfQ.command[s4selfQ.store].CMD.system_name);
    s4selfQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * s4_selfq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &s4selfQ.command[indx]); 
}

/***************** S06 system Queue functions here ******************************/

void s6_senq_store(ANT_CMD element )
{
  if (s6senQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(s6senQ.store==s6senQ.retrieve)
  {
    s6senQ.store = 0; s6senQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&s6senQ.command[s6senQ.store],MAXQUE);
    s6senQ.command[s6senQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",s6senQ.command[s6senQ.store].CMD.system_name);
    s6senQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * s6_senq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &s6senQ.command[indx]); 
}


// s6 FPS system queue 

void s6_fpsq_store(ANT_CMD element )
{
  if (s6fpsQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(s6fpsQ.store==s6fpsQ.retrieve)
  {
    s6fpsQ.store = 0; s6fpsQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&s6fpsQ.command[s6fpsQ.store],MAXQUE);
    s6fpsQ.command[s6fpsQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",s6fpsQ.command[s6fpsQ.store].CMD.system_name);
    s6fpsQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * s6_fpsq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &s6fpsQ.command[indx]); 
}
// Front end system queue 

void s6_frontq_store(ANT_CMD element )
{
  if (s6frontQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(s6frontQ.store==s6frontQ.retrieve)
  {
    s6frontQ.store = 0; s6frontQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&s6frontQ.command[s6frontQ.store],MAXQUE);
    s6frontQ.command[s6frontQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",s6frontQ.command[s6frontQ.store].CMD.system_name);
    s6frontQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * s6_frontq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &s6frontQ.command[indx]); 
}


// fiber system queue 

void s6_fiberq_store(ANT_CMD element )
{
  if (s6fiberQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(s6fiberQ.store==s6fiberQ.retrieve)
  {
    s6fiberQ.store = 0; s6fiberQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&s6fiberQ.command[s6fiberQ.store],MAXQUE);
    s6fiberQ.command[s6fiberQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",s6fiberQ.command[s6fiberQ.store].CMD.system_name);
    s6fiberQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * s6_fiberq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &s6fiberQ.command[indx]); 
}

// Back end system queue 

void s6_backq_store(ANT_CMD element )
{
  if (s6backQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(s6backQ.store==s6backQ.retrieve)
  {
    s6backQ.store = 0; s6backQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&s6backQ.command[s6backQ.store],MAXQUE);
    s6backQ.command[s6backQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",s6backQ.command[s6backQ.store].CMD.system_name);
    s6backQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * s6_backq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &s6backQ.command[indx]); 
}


// Self test system queue 

void s6_selfq_store(ANT_CMD element )
{
  if (s6selfQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(s6selfQ.store==s6selfQ.retrieve)
  {
    s6selfQ.store = 0; s6selfQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&s6selfQ.command[s6selfQ.store],MAXQUE);
    s6selfQ.command[s6selfQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",s6selfQ.command[s6selfQ.store].CMD.system_name);
    s6selfQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * s6_selfq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &s6selfQ.command[indx]); 
}

/***************** W01 system Queue functions here ******************************/

void w1_senq_store(ANT_CMD element )
{
  if (w1senQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(w1senQ.store==w1senQ.retrieve)
  {
    w1senQ.store = 0; w1senQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&w1senQ.command[w1senQ.store],MAXQUE);
    w1senQ.command[w1senQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",w1senQ.command[w1senQ.store].CMD.system_name);
    w1senQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * w1_senq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &w1senQ.command[indx]); 
}


// w1 FPS system queue 

void w1_fpsq_store(ANT_CMD element )
{
  if (w1fpsQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(w1fpsQ.store==w1fpsQ.retrieve)
  {
    w1fpsQ.store = 0; w1fpsQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&w1fpsQ.command[w1fpsQ.store],MAXQUE);
    w1fpsQ.command[w1fpsQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",w1fpsQ.command[w1fpsQ.store].CMD.system_name);
    w1fpsQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * w1_fpsq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &w1fpsQ.command[indx]); 
}
// Front end system queue 

void w1_frontq_store(ANT_CMD element )
{
  if (w1frontQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(w1frontQ.store==w1frontQ.retrieve)
  {
    w1frontQ.store = 0; w1frontQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&w1frontQ.command[w1frontQ.store],MAXQUE);
    w1frontQ.command[w1frontQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",w1frontQ.command[w1frontQ.store].CMD.system_name);
    w1frontQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * w1_frontq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &w1frontQ.command[indx]); 
}


// fiber system queue 

void w1_fiberq_store(ANT_CMD element )
{
  if (w1fiberQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(w1fiberQ.store==w1fiberQ.retrieve)
  {
    w1fiberQ.store = 0; w1fiberQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&w1fiberQ.command[w1fiberQ.store],MAXQUE);
    w1fiberQ.command[w1fiberQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",w1fiberQ.command[w1fiberQ.store].CMD.system_name);
    w1fiberQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * w1_fiberq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &w1fiberQ.command[indx]); 
}

// Back end system queue 

void w1_backq_store(ANT_CMD element )
{
  if (w1backQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(w1backQ.store==w1backQ.retrieve)
  {
    w1backQ.store = 0; w1backQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&w1backQ.command[w1backQ.store],MAXQUE);
    w1backQ.command[w1backQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",w1backQ.command[w1backQ.store].CMD.system_name);
    w1backQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * w1_backq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &w1backQ.command[indx]); 
}


// Self test system queue 

void w1_selfq_store(ANT_CMD element )
{
  if (w1selfQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(w1selfQ.store==w1selfQ.retrieve)
  {
    w1selfQ.store = 0; w1selfQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&w1selfQ.command[w1selfQ.store],MAXQUE);
    w1selfQ.command[w1selfQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",w1selfQ.command[w1selfQ.store].CMD.system_name);
    w1selfQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * w1_selfq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &w1selfQ.command[indx]); 
}

/***************** W02 system Queue functions here ******************************/

void w2_senq_store(ANT_CMD element )
{
  if (w2senQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(w2senQ.store==w2senQ.retrieve)
  {
    w2senQ.store = 0; w2senQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&w2senQ.command[w2senQ.store],MAXQUE);
    w2senQ.command[w2senQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",w2senQ.command[w2senQ.store].CMD.system_name);
    w2senQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * w2_senq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &w2senQ.command[indx]); 
}


// w2 FPS system queue 

void w2_fpsq_store(ANT_CMD element )
{
  if (w2fpsQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(w2fpsQ.store==w2fpsQ.retrieve)
  {
    w2fpsQ.store = 0; w2fpsQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&w2fpsQ.command[w2fpsQ.store],MAXQUE);
    w2fpsQ.command[w2fpsQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",w2fpsQ.command[w2fpsQ.store].CMD.system_name);
    w2fpsQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * w2_fpsq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &w2fpsQ.command[indx]); 
}
// Front end system queue 

void w2_frontq_store(ANT_CMD element )
{
  if (w2frontQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(w2frontQ.store==w2frontQ.retrieve)
  {
    w2frontQ.store = 0; w2frontQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&w2frontQ.command[w2frontQ.store],MAXQUE);
    w2frontQ.command[w2frontQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",w2frontQ.command[w2frontQ.store].CMD.system_name);
    w2frontQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * w2_frontq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &w2frontQ.command[indx]); 
}


// fiber system queue 

void w2_fiberq_store(ANT_CMD element )
{
  if (w2fiberQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(w2fiberQ.store==w2fiberQ.retrieve)
  {
    w2fiberQ.store = 0; w2fiberQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&w2fiberQ.command[w2fiberQ.store],MAXQUE);
    w2fiberQ.command[w2fiberQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",w2fiberQ.command[w2fiberQ.store].CMD.system_name);
    w2fiberQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * w2_fiberq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &w2fiberQ.command[indx]); 
}

// Back end system queue 

void w2_backq_store(ANT_CMD element )
{
  if (w2backQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(w2backQ.store==w2backQ.retrieve)
  {
    w2backQ.store = 0; w2backQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&w2backQ.command[w2backQ.store],MAXQUE);
    w2backQ.command[w2backQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",w2backQ.command[w2backQ.store].CMD.system_name);
    w2backQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * w2_backq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &w2backQ.command[indx]); 
}


// Self test system queue 

void w2_selfq_store(ANT_CMD element )
{
  if (w2selfQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(w2selfQ.store==w2selfQ.retrieve)
  {
    w2selfQ.store = 0; w2selfQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&w2selfQ.command[w2selfQ.store],MAXQUE);
    w2selfQ.command[w2selfQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",w2selfQ.command[w2selfQ.store].CMD.system_name);
    w2selfQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * w2_selfq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &w2selfQ.command[indx]); 
}

/***************** W03 system Queue functions here ******************************/

void w3_senq_store(ANT_CMD element )
{
  if (w3senQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(w3senQ.store==w3senQ.retrieve)
  {
    w3senQ.store = 0; w3senQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&w3senQ.command[w3senQ.store],MAXQUE);
    w3senQ.command[w3senQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",w3senQ.command[w3senQ.store].CMD.system_name);
    w3senQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * w3_senq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &w3senQ.command[indx]); 
}


// w3 FPS system queue 

void w3_fpsq_store(ANT_CMD element )
{
  if (w3fpsQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(w3fpsQ.store==w3fpsQ.retrieve)
  {
    w3fpsQ.store = 0; w3fpsQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&w3fpsQ.command[w3fpsQ.store],MAXQUE);
    w3fpsQ.command[w3fpsQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",w3fpsQ.command[w3fpsQ.store].CMD.system_name);
    w3fpsQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * w3_fpsq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &w3fpsQ.command[indx]); 
}
// Front end system queue 

void w3_frontq_store(ANT_CMD element )
{
  if (w3frontQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(w3frontQ.store==w3frontQ.retrieve)
  {
    w3frontQ.store = 0; w3frontQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&w3frontQ.command[w3frontQ.store],MAXQUE);
    w3frontQ.command[w3frontQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",w3frontQ.command[w3frontQ.store].CMD.system_name);
    w3frontQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * w3_frontq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &w3frontQ.command[indx]); 
}


// fiber system queue 

void w3_fiberq_store(ANT_CMD element )
{
  if (w3fiberQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(w3fiberQ.store==w3fiberQ.retrieve)
  {
    w3fiberQ.store = 0; w3fiberQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&w3fiberQ.command[w3fiberQ.store],MAXQUE);
    w3fiberQ.command[w3fiberQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",w3fiberQ.command[w3fiberQ.store].CMD.system_name);
    w3fiberQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * w3_fiberq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &w3fiberQ.command[indx]); 
}

// Back end system queue 

void w3_backq_store(ANT_CMD element )
{
  if (w3backQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(w3backQ.store==w3backQ.retrieve)
  {
    w3backQ.store = 0; w3backQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&w3backQ.command[w3backQ.store],MAXQUE);
    w3backQ.command[w3backQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",w3backQ.command[w3backQ.store].CMD.system_name);
    w3backQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * w3_backq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &w3backQ.command[indx]); 
}


// Self test system queue 

void w3_selfq_store(ANT_CMD element )
{
  if (w3selfQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(w3selfQ.store==w3selfQ.retrieve)
  {
    w3selfQ.store = 0; w3selfQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&w3selfQ.command[w3selfQ.store],MAXQUE);
    w3selfQ.command[w3selfQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",w3selfQ.command[w3selfQ.store].CMD.system_name);
    w3selfQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * w3_selfq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &w3selfQ.command[indx]); 
}

/***************** W04 system Queue functions here ******************************/

void w4_senq_store(ANT_CMD element )
{
  if (w4senQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(w4senQ.store==w4senQ.retrieve)
  {
    w4senQ.store = 0; w4senQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&w4senQ.command[w4senQ.store],MAXQUE);
    w4senQ.command[w4senQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",w4senQ.command[w4senQ.store].CMD.system_name);
    w4senQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * w4_senq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &w4senQ.command[indx]); 
}


// w4 FPS system queue 

void w4_fpsq_store(ANT_CMD element )
{
  if (w4fpsQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(w4fpsQ.store==w4fpsQ.retrieve)
  {
    w4fpsQ.store = 0; w4fpsQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&w4fpsQ.command[w4fpsQ.store],MAXQUE);
    w4fpsQ.command[w4fpsQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",w4fpsQ.command[w4fpsQ.store].CMD.system_name);
    w4fpsQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * w4_fpsq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &w4fpsQ.command[indx]); 
}
// Front end system queue 

void w4_frontq_store(ANT_CMD element )
{
  if (w4frontQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(w4frontQ.store==w4frontQ.retrieve)
  {
    w4frontQ.store = 0; w4frontQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&w4frontQ.command[w4frontQ.store],MAXQUE);
    w4frontQ.command[w4frontQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",w4frontQ.command[w4frontQ.store].CMD.system_name);
    w4frontQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * w4_frontq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &w4frontQ.command[indx]); 
}


// fiber system queue 

void w4_fiberq_store(ANT_CMD element )
{
  if (w4fiberQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(w4fiberQ.store==w4fiberQ.retrieve)
  {
    w4fiberQ.store = 0; w4fiberQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&w4fiberQ.command[w4fiberQ.store],MAXQUE);
    w4fiberQ.command[w4fiberQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",w4fiberQ.command[w4fiberQ.store].CMD.system_name);
    w4fiberQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * w4_fiberq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &w4fiberQ.command[indx]); 
}

// Back end system queue 

void w4_backq_store(ANT_CMD element )
{
  if (w4backQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(w4backQ.store==w4backQ.retrieve)
  {
    w4backQ.store = 0; w4backQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&w4backQ.command[w4backQ.store],MAXQUE);
    w4backQ.command[w4backQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",w4backQ.command[w4backQ.store].CMD.system_name);
    w4backQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * w4_backq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &w4backQ.command[indx]); 
}


// Self test system queue 

void w4_selfq_store(ANT_CMD element )
{
  if (w4selfQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(w4selfQ.store==w4selfQ.retrieve)
  {
    w4selfQ.store = 0; w4selfQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&w4selfQ.command[w4selfQ.store],MAXQUE);
    w4selfQ.command[w4selfQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",w4selfQ.command[w4selfQ.store].CMD.system_name);
    w4selfQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * w4_selfq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &w4selfQ.command[indx]); 
}

/***************** W05 system Queue functions here ******************************/

void w5_senq_store(ANT_CMD element )
{
  if (w5senQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(w5senQ.store==w5senQ.retrieve)
  {
    w5senQ.store = 0; w5senQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&w5senQ.command[w5senQ.store],MAXQUE);
    w5senQ.command[w5senQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",w5senQ.command[w5senQ.store].CMD.system_name);
    w5senQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * w5_senq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &w5senQ.command[indx]); 
}


// w5 FPS system queue 

void w5_fpsq_store(ANT_CMD element )
{
  if (w5fpsQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(w5fpsQ.store==w5fpsQ.retrieve)
  {
    w5fpsQ.store = 0; w5fpsQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&w5fpsQ.command[w5fpsQ.store],MAXQUE);
    w5fpsQ.command[w5fpsQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",w5fpsQ.command[w5fpsQ.store].CMD.system_name);
    w5fpsQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * w5_fpsq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &w5fpsQ.command[indx]); 
}
// Front end system queue 

void w5_frontq_store(ANT_CMD element )
{
  if (w5frontQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(w5frontQ.store==w5frontQ.retrieve)
  {
    w5frontQ.store = 0; w5frontQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&w5frontQ.command[w5frontQ.store],MAXQUE);
    w5frontQ.command[w5frontQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",w5frontQ.command[w5frontQ.store].CMD.system_name);
    w5frontQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * w5_frontq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &w5frontQ.command[indx]); 
}


// fiber system queue 

void w5_fiberq_store(ANT_CMD element )
{
  if (w5fiberQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(w5fiberQ.store==w5fiberQ.retrieve)
  {
    w5fiberQ.store = 0; w5fiberQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&w5fiberQ.command[w5fiberQ.store],MAXQUE);
    w5fiberQ.command[w5fiberQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",w5fiberQ.command[w5fiberQ.store].CMD.system_name);
    w5fiberQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * w5_fiberq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &w5fiberQ.command[indx]); 
}

// Back end system queue 

void w5_backq_store(ANT_CMD element )
{
  if (w5backQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(w5backQ.store==w5backQ.retrieve)
  {
    w5backQ.store = 0; w5backQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&w5backQ.command[w5backQ.store],MAXQUE);
    w5backQ.command[w5backQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",w5backQ.command[w5backQ.store].CMD.system_name);
    w5backQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * w5_backq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &w5backQ.command[indx]); 
}


// Self test system queue 

void w5_selfq_store(ANT_CMD element )
{
  if (w5selfQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(w5selfQ.store==w5selfQ.retrieve)
  {
    w5selfQ.store = 0; w5selfQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&w5selfQ.command[w5selfQ.store],MAXQUE);
    w5selfQ.command[w5selfQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",w5selfQ.command[w5selfQ.store].CMD.system_name);
    w5selfQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * w5_selfq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &w5selfQ.command[indx]); 
}

/***************** W06 system Queue functions here ******************************/

void w6_senq_store(ANT_CMD element )
{
  if (w6senQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(w6senQ.store==w6senQ.retrieve)
  {
    w6senQ.store = 0; w6senQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&w6senQ.command[w6senQ.store],MAXQUE);
    w6senQ.command[w6senQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",w6senQ.command[w6senQ.store].CMD.system_name);
    w6senQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * w6_senq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &w6senQ.command[indx]); 
}


// w6 FPS system queue 

void w6_fpsq_store(ANT_CMD element )
{
  if (w6fpsQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(w6fpsQ.store==w6fpsQ.retrieve)
  {
    w6fpsQ.store = 0; w6fpsQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&w6fpsQ.command[w6fpsQ.store],MAXQUE);
    w6fpsQ.command[w6fpsQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",w6fpsQ.command[w6fpsQ.store].CMD.system_name);
    w6fpsQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * w6_fpsq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &w6fpsQ.command[indx]); 
}
// Front end system queue 

void w6_frontq_store(ANT_CMD element )
{
  if (w6frontQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(w6frontQ.store==w6frontQ.retrieve)
  {
    w6frontQ.store = 0; w6frontQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&w6frontQ.command[w6frontQ.store],MAXQUE);
    w6frontQ.command[w6frontQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",w6frontQ.command[w6frontQ.store].CMD.system_name);
    w6frontQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * w6_frontq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &w6frontQ.command[indx]); 
}


// fiber system queue 

void w6_fiberq_store(ANT_CMD element )
{
  if (w6fiberQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(w6fiberQ.store==w6fiberQ.retrieve)
  {
    w6fiberQ.store = 0; w6fiberQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&w6fiberQ.command[w6fiberQ.store],MAXQUE);
    w6fiberQ.command[w6fiberQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",w6fiberQ.command[w6fiberQ.store].CMD.system_name);
    w6fiberQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * w6_fiberq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &w6fiberQ.command[indx]); 
}

// Back end system queue 

void w6_backq_store(ANT_CMD element )
{
  if (w6backQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(w6backQ.store==w6backQ.retrieve)
  {
    w6backQ.store = 0; w6backQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&w6backQ.command[w6backQ.store],MAXQUE);
    w6backQ.command[w6backQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",w6backQ.command[w6backQ.store].CMD.system_name);
    w6backQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * w6_backq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &w6backQ.command[indx]); 
}


// Self test system queue 

void w6_selfq_store(ANT_CMD element )
{
  if (w6selfQ.store == MAXQUE ) {
    fprintf(stderr, "\nQueue is full!");
    return;
  }

  if(w6selfQ.store==w6selfQ.retrieve)
  {
    w6selfQ.store = 0; w6selfQ.retrieve = 0;
  }
     fprintf(stderr," ###### Element in Command Queue %s\n",element.CMD.system_name);
    bzero(&w6selfQ.command[w6selfQ.store],MAXQUE);
    w6selfQ.command[w6selfQ.store]=element; 
   fprintf(stderr," INSERTING in Command Queue %s\n",w6selfQ.command[w6selfQ.store].CMD.system_name);
    w6selfQ.store++;  // point to next available storage position in queue[]
 }

ANT_CMD * w6_selfq_retrieve(int indx)
{

   //fprintf(stderr, "\nq_retrieve() %d\n",indx);
  return((ANT_CMD *) &w6selfQ.command[indx]); 
}




















