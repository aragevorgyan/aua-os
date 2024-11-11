#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Thread function to print a message
void* print_message(void* arg) {
    char* message = (char*)arg;
    printf("%s\n", message);
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    char* message1 = "Hello from Thread 1";
    char* message2 = "Hello from Thread 2";

    // Create two threads
    if (pthread_create(&thread1, NULL, print_message, (void*)message1) != 0) {
        perror("Failed to create thread 1");
        return 1;
    }

    if (pthread_create(&thread2, NULL, print_message, (void*)message2) != 0) {
        perror("Failed to create thread 2");
        return 1;
    }

    // Wait for both threads to finish
    if (pthread_join(thread1, NULL) != 0) {
        perror("Failed to join thread 1");
        return 1;
    }

    if (pthread_join(thread2, NULL) != 0) {
        perror("Failed to join thread 2");
        return 1;
    }

    printf("Both threads have finished execution\n");

    return 0;
}