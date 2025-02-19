#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define TOTAL_PARKING_SPOTS 3
#define TOTAL_CARS 10

sem_t parking_spots;

void* car(void* arg) {
    int car_id = *((int*)arg);

    printf("Car %d is looking for a parking spot...\n", car_id);

    // Try to acquire a parking spot
    if (sem_wait(&parking_spots) == 0) {
        printf("Car %d has parked.\n", car_id);

        // Simulate parking time
        sleep(rand() % 5 + 1);

        printf("Car %d is leaving the parking spot.\n", car_id);

        // Release the parking spot
        sem_post(&parking_spots);
    }
    free(arg);
    return NULL;
}

int main() {
    pthread_t car_threads[TOTAL_CARS];

    // Initialize semaphore with the total number of parking spots
    sem_init(&parking_spots, 0, TOTAL_PARKING_SPOTS);

    // Create threads for each car
    for (int i = 0; i < TOTAL_CARS; i++) {
        int* car_id = malloc(sizeof(int));
        *car_id = i + 1;

        if (pthread_create(&car_threads[i], NULL, car, car_id) != 0) {
            perror("Failed to create thread");
            return 1;
        }

        // Simulate cars arriving at different times
        sleep(rand() % 2);
    }

    // Wait for all car threads to finish
    for (int i = 0; i < TOTAL_CARS; i++) {
        pthread_join(car_threads[i], NULL);
    }

    // Destroy the semaphore
    sem_destroy(&parking_spots);

    printf("Parking lot simulation completed.\n");
    return 0;
}
