#include <stdio.h>

// Pointer Arithmetic
int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    int *ptr = arr;  // Point to the first element of the array

    printf("Initial pointer value: %p\n", ptr);

    // Traverse the array using pointer arithmetic
    for (int i = 0; i < 5; i++) {
        printf("Value at ptr + %d: %d\n", i, *(ptr + i));
    }

    return 0;
}