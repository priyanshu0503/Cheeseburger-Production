#ifndef PRODUCER_H
#define PRODUCER_H

#include <pthread.h>
#include <semaphore.h>

// Buffer Sizes
#define MILK_BUFFER_SIZE 9
#define CHEESE_BUFFER_SIZE 4

// Shared Buffers
extern int milk_buffer[MILK_BUFFER_SIZE];
extern int cheese_buffer[CHEESE_BUFFER_SIZE];
extern int milk_count, cheese_count;
extern int num_cheeseburgers;

// Semaphores and Mutexes
extern sem_t empty_milk, full_milk;
extern sem_t empty_cheese, full_cheese;
extern pthread_mutex_t milk_mutex, cheese_mutex;

// Function Prototypes
void* milk_producer(void* arg);
void* cheese_producer(void* arg);
void* cheeseburger_producer(void* arg);

#endif
