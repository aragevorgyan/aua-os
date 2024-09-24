#include <stdio.h>
#include <stdlib.h>

int main() {
    int *arr;
    int initial_size = 3;
    int new_size = 5;

    // Allocate memory for 'initial_size' integers
    arr = (int *)malloc(initial_size * sizeof(int));

    // Check if memory allocation was successful
    if (arr == NULL) {
        printf("Initial memory allocation failed!\n");
        return 1;
    }

    // Initialize the array
    for (int i = 0; i < initial_size; i++) {
        arr[i] = i + 1;  // Assign values to the array
        printf("arr[%d] = %d\n", i, arr[i]);  // Print the values
    }

    // Reallocate memory to expand the array to 'new_size' elements
    int *new_arr = (int *)realloc(arr, new_size * sizeof(int));

    // Check if realloc was successful
    if (new_arr == NULL) {
        printf("Memory reallocation failed!\n");
        free(arr);  // Free the original memory if realloc fails
        return 1;
    }

    // Initialize the new elements in the array
    for (int i = initial_size; i < new_size; i++) {
        new_arr[i] = i + 1;
    }

    // Print the entire resized array
    printf("\nAfter realloc:\n");
    for (int i = 0; i < new_size; i++) {
        printf("new_arr[%d] = %d\n", i, new_arr[i]);
    }

    // Free the memory
    free(new_arr);

    return 0;
}
