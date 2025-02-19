#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h> // For sleep function

#define NUM_THREADS 2

// Shared variable
int x = 5;

// Bakery algorithm variables
volatile int choosing[NUM_THREADS];  // Flags for choosing tickets
volatile int tickets[NUM_THREADS];  // Array of tickets

// Helper function to find the maximum ticket value
int max_ticket() {
    int max = 0;
    for (int i = 0; i < NUM_THREADS; i++) {
        if (tickets[i] > max) {
            max = tickets[i];
        }
    }
    return max;
}

// Entry section for the Bakery algorithm
void lock(int thread_id) {
    choosing[thread_id] = 1;  // Indicate that the thread is choosing a ticket
    tickets[thread_id] = max_ticket() + 1;  // Assign the next ticket
    choosing[thread_id] = 0;  // Finished choosing

    // Wait until this thread's ticket is the smallest
    for (int i = 0; i < NUM_THREADS; i++) {
        if (i == thread_id) continue;  // Skip itself

        // Wait if the other thread is still choosing or has a smaller ticket
        while (choosing[i]) { /* Busy wait */ }
        while (tickets[i] != 0 &&
               (tickets[i] < tickets[thread_id] ||
                (tickets[i] == tickets[thread_id] && i < thread_id))) {
            /* Busy wait */
        }
    }
}

// Exit section for the Bakery algorithm
void unlock(int thread_id) {
    tickets[thread_id] = 0;  // Release the ticket
}

// Thread function to increment x
void* increment(void* arg) {
    int thread_id = *(int*)arg;

    lock(thread_id);
    x++;
    unlock(thread_id);

    return NULL;
}

// Thread function to decrement x
void* decrement(void* arg) {
    int thread_id = *(int*)arg;

    lock(thread_id);
    x--;
    unlock(thread_id);

    return NULL;
}

int main() {
    pthread_t tid1, tid2;
    int thread_ids[NUM_THREADS] = {0, 1};

    // Initialize Bakery algorithm variables
    for (int i = 0; i < NUM_THREADS; i++) {
        choosing[i] = 0;
        tickets[i] = 0;
    }

    for (int i = 0; i < 10; i++) {
        // Create threads
        pthread_create(&tid1, NULL, increment, &thread_ids[0]);
        pthread_create(&tid2, NULL, decrement, &thread_ids[1]);

        // Wait for threads to complete
        pthread_join(tid1, NULL);
        pthread_join(tid2, NULL);

        // Print the final value of x
        printf("Final value of x: %d\n", x);
    }

    return 0;
}
