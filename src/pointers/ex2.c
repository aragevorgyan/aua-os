#include <stdio.h>

// Pointer to Pointer
int main() {
    int num = 20;
    int *ptr1;      // Pointer to an integer
    int **ptr2;     // Pointer to a pointer to an integer

    ptr1 = &num;    // ptr1 points to num
    ptr2 = &ptr1;   // ptr2 points to ptr1

    printf("Value of num: %d\n", num);               // Output num
    printf("Value pointed to by ptr1: %d\n", *ptr1);  // Dereference ptr1 to get num
    printf("Value pointed to by ptr2: %d\n", **ptr2); // Dereference ptr2 twice to get num

    return 0;
}