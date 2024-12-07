/****************************************************************************************
Programming Assignment - 2 - CSC 456
Due: December 09, 2024

By Priyanshu Mittal
This is a producer file for the program. 
It contains all required producers function.

*****************************************************************************************/



#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include "producer.h"

// Buffer sizes
#define MILK_BUFFER_SIZE 9
#define CHEESE_BUFFER_SIZE 4

volatile int done =0; // Flag to indicate if all threads have finished

// Shared Buffers
int milk_buffer[MILK_BUFFER_SIZE];
int cheese_buffer[CHEESE_BUFFER_SIZE];

// Count for milk bottles and cheese slices
int milk_count = 0, cheese_count = 0;

// Number of Cheeseburger produced
int num_cheeseburgers;

// Semaphores and Mutexes
sem_t empty_milk, full_milk;
sem_t empty_cheese, full_cheese;

pthread_mutex_t milk_mutex;
pthread_mutex_t cheese_mutex;


// Milk Producer Function
void* milk_producer(void* arg) {
    int id = *(int*)arg;
    while (!done) {
        sem_wait(&empty_milk); // Wait for empty space in milk buffer
        pthread_mutex_lock(&milk_mutex); // Lock milk buffer
        
        // Produce Milk
        if (!done) {
            milk_buffer[milk_count++] = id;
            //For Debugging Purposes, I tried to milk producer ID
            //printf("Milk Producer %d: Produced milk. Milk count = %d\n", id, milk_count);
        }

        pthread_mutex_unlock(&milk_mutex); // Unlock milk buffer
        sem_post(&full_milk); // Signal that milk buffer is full
    }
    return NULL;
}

// Cheese Producer Function
void* cheese_producer(void* arg) {
    int id = *(int*)arg;
    static int global_cheese_id = 1234; // Initialize with a value
    while (!done) {
        // Consume 3 bottles of milk
        sem_wait(&full_milk);
        sem_wait(&full_milk);
        sem_wait(&full_milk);

        pthread_mutex_lock(&milk_mutex); // Lock milk buffer
        if(!done) {
        int milk1 = milk_buffer[--milk_count]; // Consume 1 bottle of milk
        int milk2 = milk_buffer[--milk_count]; // Consume 2 bottles of milk
        int milk3 = milk_buffer[--milk_count]; // Consume 3 bottles of milk
        
        pthread_mutex_unlock(&milk_mutex); // Unlock milk buffer
        
        sem_post(&empty_milk); // Signal that milk buffer is empty
        sem_post(&empty_milk);
        sem_post(&empty_milk);


        sem_wait(&empty_cheese); // Wait for empty space in cheese buffer
        pthread_mutex_lock(&cheese_mutex);
        int cheese = global_cheese_id ++;

        // Add the cheese to the buffer
        cheese_buffer[cheese_count++] = cheese;
        //For Debugging Purposes, I tried to cheese producer ID
        //printf("Cheese Producer %d: Produced cheese %d. Cheese count = %d\n", id, cheese, cheese_count);

        pthread_mutex_unlock(&cheese_mutex); // Unlock cheese buffer
        sem_post(&full_cheese); // Signal that cheese buffer is full
        }
        else{
            pthread_mutex_unlock(&milk_mutex); // Unlock milk buffer
            sem_post(&empty_milk); // Signal that milk buffer is empty
            sem_post(&empty_milk);
            sem_post(&empty_milk);
        }
    }
    return NULL;
}

//  Cheeseburger Producer Function
void* cheeseburger_producer(void* arg) {
    int cheeseburger_count = 0;  // Count of cheeseburgers produced
    
    while (num_cheeseburgers > 0) {
        sem_wait(&full_cheese); // Wait for cheese buffer to be full
        sem_wait(&full_cheese);

        pthread_mutex_lock(&cheese_mutex); // Lock cheese buffer

        int cheese1 = cheese_buffer[--cheese_count]; // Consume 1 cheese from the buffer
        int cheese2 = cheese_buffer[--cheese_count]; // Consume 2 cheese from the buffer

        pthread_mutex_unlock(&cheese_mutex); // Unlock cheese buffer
        
        sem_post(&empty_cheese); // Signal that cheese buffer is empty
        sem_post(&empty_cheese);

        // Create the cheeseburger ID by concatenating the two cheese slice IDs
        long long cheeseburger_id = (long long)cheese1 * 10000 + cheese2;

        // Increment the local cheeseburger count
        cheeseburger_count++;

        // Print the cheeseburger ID and details along with count
        printf("Cheeseburger Producer %d: Produced cheeseburger %lld (made with two cheese slices %d and %d).\n", 
               cheeseburger_count, cheeseburger_id, cheese1, cheese2);
        
        num_cheeseburgers--;
    }
    done = 1; // Set done flag to 1
    return NULL;
}


