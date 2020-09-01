#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct{
int x,y,z;
}data;

volatile data buffer[20];
volatile int count;
pthread_mutex_t m;
pthread_cond_t qu_empty_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t qu_full_cond = PTHREAD_COND_INITIALIZER;



void produce();
void consume();
void createData(data*);
void writeBuffer(data);
void readBuffer(data*);
void waitRandom();
void shiftBuffer();


int main (){
pthread_t p, c;
count = 0;

if(pthread_mutex_init(&m, NULL)){
        printf("mutex creation failed\n");
        return 1;
}
else printf("mutex creation sucess\n");

if(pthread_create (&p,NULL,(void *) &produce,NULL)){
        printf("producer creation failed\n");
        return 1;
}

if (pthread_create (&c,NULL,(void *) &consume,NULL)){
        printf("consumer creation failed\n");
        return 1;
}

return 0;
}

void produce(void){
printf("producer creation success count\n");
while(1){
        data a;
        createData(&a);
        printf("PRODUCE: checking for mutual exclusion\n");
        if(pthread_mutex_lock(&m))
                printf("MUTEX lock in PRODUCER failed, blocking until MUTEX is available \n");
        else
        printf("have mutual exclusion to produce\n");
        //if 20 block
        /*while(count>=20){
                printf("stuck \n");
                pthread_cond_wait(&qu_full_cond, &m);
                }*/
        writeBuffer(a);
        //increment
        count++;
        if(count==1)
                pthread_cond_signal(&qu_empty_cond);
        pthread_mutex_unlock(&m);
        printf("lost mutual exclusion to produce\n");
        waitRandom();
        }
}

void consume(void){
printf("consumer creation success \n");
while(1){
        data a;
        printf("CONSUME: checking for mutual exclusion\n");
        if(pthread_mutex_lock(&m))
                printf("MUTEX lock in CONSUMER failed, blocking until MUTEX is available \n");
        else
                printf("have mutual exclusion to consume\n");
        //if 0 block
        while(count<=0){
                printf("stuck\n");
                waitRandom();
                pthread_cond_wait(&qu_empty_cond, &m);
                }
        readBuffer(&a);
        shiftBuffer();
        count--;
        //if 19 release
        if(count==19)
                pthread_cond_signal(&qu_full_cond);
        pthread_mutex_unlock(&m);
        printf("lost mutual exclusion to consume\n");
        waitRandom();
        }
}



void createData(data* a){
        printf("creating data\n");
        a->x=1;
        a->y=2;
        a->z=3;
}

void writeBuffer(data a){
        printf("inthefunction1111\n");
        printf("writing to buffer slot %d, new size of buffer is %d\n", count, count+1);
        buffer[count] = a;
        printf("%d      %d      %d",buffer[count].x,buffer[count].y,buffer[count].z);
}

void readBuffer(data* a){
        printf("reading buffer slot 0 \n");
        a->x = buffer[0].x;
        a->y = buffer[0].y;
        a->z = buffer[0].z;
}

void shiftBuffer(void){
        int i;
        printf("deleting buffer slot 0 \n");
        for(i=0;i<count;i++)
                buffer[i]=buffer[i+1];
}

void waitRandom(void){
        srand ( time(NULL) );
        sleep(rand()%2000 + 1000 );
}
