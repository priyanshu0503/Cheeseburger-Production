
*****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Buffer sizes
#define MILK_BUFFER_SIZE 9
#define CHEESE_BUFFER_SIZE 4

// Shared buffers
int milk_buffer[MILK_BUFFER_SIZE] = {0};
int cheese_buffer[CHEESE_BUFFER_SIZE] = {0};

// Semaphores and mutexes
sem_t milk_sem;
sem_t cheese_sem;
pthread_mutex_t milk_mutex;
pthread_mutex_t cheese_mutex;

// Milk producer function
void* milk_producer(void* arg) {
    int id = *(int*)arg;
    int produced = 0;

    while (produced < MILK_BUFFER_SIZE / 3) {
        sem_wait(&milk_sem); // Wait for space in the milk buffer
        pthread_mutex_lock(&milk_mutex); // Lock the milk buffer


        // Produce milk
        for (int i = 0; i < MILK_BUFFER_SIZE; i++) {
            if (milk_buffer[i] == 0) {
                milk_buffer[i] = id;
                //For testing purposes, I tried to print the milk producer ID and the time at which milk was produced
                printf("Milk producer %d produced milk at %d\n", id, i);
                produced++;
                break;
            }
        }

        pthread_mutex_unlock(&milk_mutex); // Unlock the milk buffer
        sem_post(&milk_sem); // Signal that milk has been produced
    }
    return NULL;
}

// Cheese producer function
void* cheese_producer(void* arg) {
    int id = *(int*)arg;
    int produced = 0;
    static int cheese_id_counter = 2314;

    while (1) {
        pthread_mutex_lock(&milk_mutex); // Lock the milk buffer

        // Count available milk bottles
        int milk_count = 0;
        for (int i = 0; i < MILK_BUFFER_SIZE; i++) {
            if (milk_buffer[i] != 0) milk_count++;
        }

        if (milk_count >= 3) {
            pthread_mutex_lock(&cheese_mutex);

            // Consume 3 milk bottles
            //int used_milk[3], idx = 0;
            for (int i = 0, used = 0; i < MILK_BUFFER_SIZE && used < 3; i++) {
                if (milk_buffer[i] != 0) {
                    milk_buffer[i] = 0;
                    used++;
                }
            }

            //Assign a valid cheese slice ID to the buffer
            for (int i = 0; i < CHEESE_BUFFER_SIZE; i++) {
                if (cheese_buffer[i] == 0) {
                    cheese_buffer[i] = cheese_id_counter;
                    //For testing purposes, I tried to print the cheese slice ID 
                    printf("Cheese producer %d produced cheese slice %d at %d\n", id, cheese_id_counter, i);
                    cheese_id_counter += 1111;  // Increase for the next slice
                    pthread_mutex_unlock(&cheese_mutex);
                    break;
                }
            }

        }
        
        pthread_mutex_unlock(&milk_mutex);// Unlock the cheese buffer
        sleep(1);
    }

    return NULL;
}

void* cheeseburger_producer(void* arg) {
    int num_burgers = *(int*)arg;

    for (int i = 0; i < num_burgers; i++) {
        int cheese_ids[2];
        int idx = 0;

        // Wait until 2 valid cheese slices are available
        while (1) {
            pthread_mutex_lock(&cheese_mutex);

            // Count the number of valid cheese slices
            int cheese_count = 0;
            for (int j = 0; j < CHEESE_BUFFER_SIZE; j++) {
                if (cheese_buffer[j] != 0) cheese_count++;
            }

            // If enough cheese slices are available, consume them
            if (cheese_count >= 2) {
                // Collect two cheese slices
                for (int j = 0; j < CHEESE_BUFFER_SIZE && idx < 2; j++) {
                    if (cheese_buffer[j] != 0) {
                        cheese_ids[idx++] = cheese_buffer[j];
                        cheese_buffer[j] = 0;  // Consume the cheese slice
                    }
                }
                pthread_mutex_unlock(&cheese_mutex);
                break;
            }

            pthread_mutex_unlock(&cheese_mutex);
            
        }
        // Check if the cheese slices are valid before making a cheeseburger
        // Earlier I was printing directly and sometimes it was printing 0 and 1
        // So I added a check to see if the cheese slices are valid
        if (cheese_ids[0] != 0 && cheese_ids[1] != 0) {
            printf("Printed Cheeseburger IDs, e.g., %d%d (made with two cheese slices %d and %d)\n",
                   cheese_ids[0], cheese_ids[1], cheese_ids[0], cheese_ids[1]);
        } else {
            printf("Error: Invalid cheese slices detected during cheeseburger production\n");
        }

        sleep(1); 
    }

    return NULL;
}
