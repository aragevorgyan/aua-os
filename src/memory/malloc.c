#include <stdio.h>
#include <stdlib.h>  // For malloc() and free()

int main() {
    int *arr;
    int n;

    // Ask the user for the number of elements
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    // Allocate memory for 'n' integers using malloc
    arr = (int *)malloc(n * sizeof(int));

    // Check if memory allocation was successful
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Initialize and print the array
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;  // Assign values to the array
        printf("arr[%d] = %d\n", i, arr[i]);  // Print the values
    }

    // Free the allocated memory
    free(arr);

    return 0;
}
