#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define ONE_SECOND 1000000
#define RANGE 10
#define PERIOD 2
#define NUM_THREADS 4 

typedef struct {
  int *carpark;
  int capacity;
  int occupied;
  int nextin;
  int nextout;
  pthread_mutex_t lock;
  pthread_cond_t space;
  pthread_cond_t car;
  pthread_barrier_t bar;
} cp_t;

static void initialise(cp_t *cp, int size) { 

    cp->capacity = size;
    cp->occupied = cp-> nextin = cp->nextout = 0;
    /*Tried calloc here but it didn't init the struct members properly */
    cp->carpark = malloc(cp->capacity * sizeof(*cp->carpark));

    if(cp->carpark == NULL) {
        perror("malloc()");
        exit(EXIT_FAILURE);
    }
    /*Moved to here so we have done the null check BEFORE using the barrier */
    pthread_barrier_init(&cp->bar, NULL, NUM_THREADS);
    srand((unsigned int)getpid());
    pthread_mutex_init(&cp->lock, NULL);
    pthread_cond_init(&cp->space, NULL);
    pthread_cond_init(&cp->car, NULL);
} 

static void* car_in_handler(void *carpark_in) {

    unsigned int seed;
    cp_t *cp = carpark_in;
    pthread_barrier_wait(&cp->bar);

    for(; ;) { 
        usleep(rand_r(&seed) % ONE_SECOND);
        pthread_mutex_lock(&cp->lock);

        while (cp->occupied == cp->capacity)
            pthread_cond_wait(&cp->space, &cp->lock);

        /*insert an arbitrary item to represent a car for simplicity*/ 
        cp->carpark[cp->nextin] = rand_r(&seed) % RANGE;
        cp->occupied++;
        cp->nextin++;
        cp->nextin %= cp->capacity;

        pthread_cond_signal(&cp->car);
        pthread_mutex_unlock(&cp->lock);
    }
    return (NULL);
}

static void* car_out_handler(void *carpark_out) {

    unsigned int seed;
    cp_t *cp = carpark_out;
    pthread_barrier_wait(&cp->bar);
    for(; ;) { 

    usleep(rand_r(&seed) % ONE_SECOND);
    pthread_mutex_lock(&cp->lock);

    while(cp->occupied == 0) 
            pthread_cond_wait(&cp->car, &cp->lock);

    cp->occupied--;
    cp->nextout++;
    cp->nextout %= cp->capacity;

    pthread_cond_signal(&cp->space);
    pthread_mutex_unlock(&cp->lock);
    }
    return (NULL);
}

static void *monitor(void *carpark_in) {

    cp_t *cp = carpark_in;
    for(; ;) { 
        sleep(PERIOD);
        pthread_mutex_lock(&cp->lock);
        printf("Number of cars in carpark: %d\n", cp->occupied);
        pthread_mutex_unlock(&cp->lock);
    }
    return (NULL);
}
int main(int argc, char *argv[]) {

    cp_t ourpark;
    pthread_t car_in, car_out, m;
    pthread_t car_in2, car_out2;

    if (argc != 2) { 
        printf("Usage: %s carparksize\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    initialise(&ourpark, atoi(argv[1]));

    pthread_create(&car_in, NULL, car_in_handler, (void *) &ourpark);
    pthread_create(&car_out, NULL, car_out_handler, (void *) &ourpark);
    pthread_create(&car_in2, NULL, car_in_handler, (void *) &ourpark);
    pthread_create(&car_out2, NULL, car_out_handler, (void *) &ourpark);
    pthread_create(&m, NULL, monitor, (void *) &ourpark);

    pthread_join(car_in, NULL);
    pthread_join(car_out, NULL);
    pthread_join(car_in2, NULL);
    pthread_join(car_out2, NULL);
    pthread_join(m, NULL);

    /*Changed from resturn(0) */
    return(EXIT_SUCCESS);
} 

