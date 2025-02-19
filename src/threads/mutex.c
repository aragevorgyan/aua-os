#include <pthread.h>
#include <stdio.h>

// Shared variable
int x = 5;

// Mutex for synchronization
pthread_mutex_t mutex;

// Thread function to increment x
void* increment(void* arg) {
    pthread_mutex_lock(&mutex);  // Acquire the mutex
    x++;
    pthread_mutex_unlock(&mutex);  // Release the mutex
    return NULL;
}

// Thread function to decrement x
void* decrement(void* arg) {
    pthread_mutex_lock(&mutex);  // Acquire the mutex
    x--;
    pthread_mutex_unlock(&mutex);  // Release the mutex
    return NULL;
}

int main() {
    pthread_t tid1, tid2;

    // Initialize the mutex
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < 10; i++) {
        // Create threads
        pthread_create(&tid1, NULL, increment, NULL);
        pthread_create(&tid2, NULL, decrement, NULL);

        // Wait for threads to complete
        pthread_join(tid1, NULL);
        pthread_join(tid2, NULL);

        // Print the final value of x
        printf("Final value of x: %d\n", x);
    }

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}
