#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t num_elements = 5; // Number of elements in the array
    int *arr;

    // Use calloc to allocate memory for an array of integers
    arr = (int *)calloc(num_elements, sizeof(int));

    // Check if the memory allocation was successful
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1; // Exit with error
    }

    // Display the initialized values (should be zero)
    printf("Array values after calloc:\n");
    for (int i = 0; i < num_elements; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    // Free the allocated memory
    free(arr);
    
    return 0; // Exit successfully
}
