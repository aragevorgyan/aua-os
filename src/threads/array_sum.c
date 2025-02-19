#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100000000
#define NUM_THREADS 4

// Global array to sum
int array[ARRAY_SIZE];
long partial_sums[NUM_THREADS]; // Array to store partial sums

// Function to sum part of the array (false sharing)
void* sum_array(void* arg) {
    int thread_id = *((int*)arg);

    // Each thread sums its portion of the array
    long sum = 0;
    for (int i = thread_id * (ARRAY_SIZE / NUM_THREADS); i < (thread_id + 1) * (ARRAY_SIZE / NUM_THREADS); i++) {
        sum += array[i];
    }

    // Store the partial sum in the global array (may cause false sharing)
    partial_sums[thread_id] = sum;
    return NULL;
}

int main() {
    // Initialize the array with values
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = 1;
    }

    // Variable to store thread results
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    clock_t start, end;

    for (int num_threads = 1; num_threads <= NUM_THREADS; num_threads++) {
        printf("Running with %d threads...\n", num_threads);
        start = clock();

        // Create threads
        for (int i = 0; i < num_threads; i++) {
            thread_ids[i] = i;
            pthread_create(&threads[i], NULL, sum_array, (void*)&thread_ids[i]);
        }

        long total_sum = 0;
        for (int i = 0; i < num_threads; i++) {
            pthread_join(threads[i], NULL);
            total_sum += partial_sums[i];
        }

        end = clock();
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Total sum: %ld, Time taken: %f seconds\n", total_sum, time_taken);
    }

    return 0;
}
