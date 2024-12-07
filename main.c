/****************************************************************************************
Programming Assignment - 2 - CSC 456
Due: December 09, 2024

By Priyanshu Mittal
This is a main file for the program. 
It contains the main function where program ask user to input number of burgers he want.

*****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "producer.h"

//Main file
int main() {
    printf("How many burgers do you want? ");
    scanf("%d", &num_cheeseburgers);

    // Create Threads
    pthread_t milk_threads[3]; 
    pthread_t cheese_threads[2];
    pthread_t burger_thread;
    
    // Initialize semaphores and mutexes
    sem_init(&empty_milk, 0, MILK_BUFFER_SIZE);
    sem_init(&full_milk, 0, 0);
    sem_init(&empty_cheese, 0, CHEESE_BUFFER_SIZE);
    sem_init(&full_cheese, 0, 0);

    pthread_mutex_init(&milk_mutex, NULL);
    pthread_mutex_init(&cheese_mutex, NULL);

    // Create Producers IDs
    int milk_ids[3] = {1, 2, 3};
    int cheese_ids[2] = {4, 5};

    // Create threads
    for (int i = 0; i < 3; i++) {
        pthread_create(&milk_threads[i], NULL, milk_producer, &milk_ids[i]);
    }
    for (int i = 0; i < 2; i++) {
        pthread_create(&cheese_threads[i], NULL, cheese_producer, &cheese_ids[i]);
    }
    pthread_create(&burger_thread, NULL, cheeseburger_producer, NULL);

    // Join threads
    for (int i = 0; i < 3; i++) {
        pthread_join(milk_threads[i], NULL);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(cheese_threads[i], NULL);
    }
    pthread_join(burger_thread, NULL);

    // Destroy semaphores and mutexes
    sem_destroy(&empty_milk);
    sem_destroy(&full_milk);

    sem_destroy(&empty_cheese);
    sem_destroy(&full_cheese);

    pthread_mutex_destroy(&milk_mutex);
    pthread_mutex_destroy(&cheese_mutex);

    printf("All required number of cheeseburgers created.\n");
    return 0;
}
