#ifndef PRODUCERS_H
#define PRODUCERS_H

#include <pthread.h>
#include <semaphore.h>

// Buffer sizes
#define MILK_BUFFER_SIZE 10
#define CHEESE_BUFFER_SIZE 4

// Shared buffers
extern int milk_buffer[MILK_BUFFER_SIZE];
extern int cheese_buffer[CHEESE_BUFFER_SIZE];

// Semaphores and mutexes
extern sem_t milk_sem;
extern sem_t cheese_sem;
extern pthread_mutex_t milk_mutex;
extern pthread_mutex_t cheese_mutex;

// Function prototypes
void* milk_producer(void* arg);
void* cheese_producer(void* arg);
void* cheeseburger_producer(void* arg);

#endif
