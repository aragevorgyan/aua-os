#include <stdio.h>

// Pointer and Array relationship
int main() {
    int arr[3] = {10, 20, 30};
    int *ptr;

    ptr = &arr[0];  // Pointing to the first element of the array

    for (int i = 0; i < 3; i++) {
        printf("Value of arr[%d]: %d\n", i, *(ptr + i));  // Accessing array elements using pointer
    }

    return 0;
}