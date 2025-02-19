#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define TOTAL_PARKING_SPOTS 5
#define TOTAL_CARS 12

sem_t parking_spots;         // Semaphore for available parking spots
pthread_mutex_t parking_mutex; // Mutex to synchronize access to shared resources

void* entry_thread(void* arg) {
    int entry_id = *((int*)arg);
    free(arg);

    while (1) {
        int car_id = rand() % 100 + 1; // Random car ID
        printf("Car %d arriving at Entry %d.\n", car_id, entry_id);

        if (sem_trywait(&parking_spots) == 0) { // Try to park
            printf("Car %d has parked from Entry %d.\n", car_id, entry_id);
            sleep(rand() % 3 + 1); // Simulate parking time
        } else {
            printf("Car %d couldn't find a spot and is leaving from Entry %d.\n", car_id, entry_id);
        }

        sleep(rand() % 3 + 1); // Simulate delay between car arrivals
    }

    return NULL;
}

void* exit_thread(void* arg) {
    int exit_id = *((int*)arg);
    free(arg);

    while (1) {
        sleep(rand() % 5 + 1); // Simulate delay between car exits

        pthread_mutex_lock(&parking_mutex);
        int value;
        sem_getvalue(&parking_spots, &value);

        if (value < TOTAL_PARKING_SPOTS) { // Check if there are parked cars
            sem_post(&parking_spots); // Release a parking spot
            printf("A car is exiting through Exit %d. Spots available: %d\n", exit_id, value + 1);
        } else {
            printf("Exit %d: No cars are parked, waiting for cars to leave.\n", exit_id);
        }
        pthread_mutex_unlock(&parking_mutex);
    }

    return NULL;
}

int main() {
    pthread_t entry_threads[2];
    pthread_t exit_threads[2];

    // Initialize semaphore and mutex
    sem_init(&parking_spots, 0, TOTAL_PARKING_SPOTS);
    pthread_mutex_init(&parking_mutex, NULL);

    // Create entry threads
    for (int i = 0; i < 2; i++) {
        int* entry_id = malloc(sizeof(int));
        *entry_id = i + 1;
        if (pthread_create(&entry_threads[i], NULL, entry_thread, entry_id) != 0) {
            perror("Failed to create entry thread");
            return 1;
        }
    }

    // Create exit threads
    for (int i = 0; i < 2; i++) {
        int* exit_id = malloc(sizeof(int));
        *exit_id = i + 1;
        if (pthread_create(&exit_threads[i], NULL, exit_thread, exit_id) != 0) {
            perror("Failed to create exit thread");
            return 1;
        }
    }

    // Run simulation for a fixed time
    sleep(20);

    // Cancel threads after simulation
    for (int i = 0; i < 2; i++) {
        pthread_cancel(entry_threads[i]);
        pthread_cancel(exit_threads[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < 2; i++) {
        pthread_join(entry_threads[i], NULL);
        pthread_join(exit_threads[i], NULL);
    }

    // Destroy semaphore and mutex
    sem_destroy(&parking_spots);
    pthread_mutex_destroy(&parking_mutex);

    printf("Parking lot simulation completed.\n");
    return 0;
}
