#include <pthread.h>
#include <stdio.h>

// Shared variable
int x = 5;

// Spinlock for synchronization
pthread_spinlock_t spinlock;

// Thread function to increment x
void* increment(void* arg) {
    pthread_spin_lock(&spinlock);  // Acquire the lock
    x++;
    pthread_spin_unlock(&spinlock);  // Release the lock
    return NULL;
}

// Thread function to decrement x
void* decrement(void* arg) {
    pthread_spin_lock(&spinlock);  // Acquire the lock
    x--;
    pthread_spin_unlock(&spinlock);  // Release the lock
    return NULL;
}

int main() {
    pthread_t tid1, tid2;

    // Initialize the spinlock
    pthread_spin_init(&spinlock, PTHREAD_PROCESS_PRIVATE);

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

    // Destroy the spinlock
    pthread_spin_destroy(&spinlock);

    return 0;
}
