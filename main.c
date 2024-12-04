/****************************************************************************************
Programming Assignment - 2 - CSC 456
Due: December 02, 2024

By Priyanshu Mittal

*****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "producer.h"


int main() {
    int num_burgers;

    //Ask user for number of burgers
    printf("How many burgers do you want? ");
    scanf("%d", &num_burgers);

    // Create threads
    pthread_t milk_producer_thread[3];
    pthread_t cheese_producer_thread[3];
    pthread_t cheeseburger_producer_thread;

    // Initialize semaphores and mutexes
    sem_init(&milk_sem, 0, MILK_BUFFER_SIZE);
    sem_init(&cheese_sem, 0, CHEESE_BUFFER_SIZE);

    pthread_mutex_init(&milk_mutex, NULL);
    pthread_mutex_init(&cheese_mutex, NULL);

    // Create producer IDs
    int milk_ids[3] = {1, 2, 3};
    int cheese_ids[2] = {4, 5};

    // Create threads
    for (int i = 0; i < 3; i++) {
        pthread_create(&milk_producer_thread[i], NULL, milk_producer, &milk_ids[i]);
    }
    for (int i = 0; i < 2; i++) {
        pthread_create(&cheese_producer_thread[i], NULL, cheese_producer, &cheese_ids[i]);
    }
    pthread_create(&cheeseburger_producer_thread, NULL, cheeseburger_producer, &num_burgers);

    // Join threads
    for (int i = 0; i < 3; i++) {
        pthread_join(milk_producer_thread[i], NULL);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(cheese_producer_thread[i], NULL);
    }
    pthread_join(cheeseburger_producer_thread, NULL);

    // Destroy semaphores and mutexes
    sem_destroy(&milk_sem);
    sem_destroy(&cheese_sem);

    pthread_mutex_destroy(&milk_mutex);
    pthread_mutex_destroy(&cheese_mutex);

    return 0;
}
