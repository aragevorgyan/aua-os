#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* compute_square(void* arg) {
    int* num = (int*)arg;
    int* result = malloc(sizeof(int)); // Allocate memory for the result
    if (result == NULL) {
        perror("Failed to allocate memory");
        pthread_exit(NULL); // Exit if memory allocation fails
    }
    *result = (*num) * (*num); // Compute the square

    return (void*)result; // Return the result as void*
}

int main() {
    pthread_t thread;
    int number = 5;
    int* result;

    // Create the thread, passing a pointer to number as the argument
    if (pthread_create(&thread, NULL, compute_square, (void*)&number) != 0) {
        perror("Failed to create thread");
        return 1;
    }

    // Wait for the thread to finish and retrieve the result
    if (pthread_join(thread, (void**)&result) != 0) {
        perror("Failed to join thread");
        return 1;
    }

    // Print the result
    printf("Square of %d is %d\n", number, *result);

    free(result); // Free the allocated memory
    return 0;
}
