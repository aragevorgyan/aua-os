#include <stdio.h>

// Basic pointer declaration and dereferencing
int main() {
    int num = 10;
    double d = 7.6;

    double* ptd = &d;
    int *ptr;      // Declaring a pointer to an integer

    ptr = &num;    // Assigning the address of num to ptr

    printf("Value of num: %d\n", num);            // Output the value of num
    printf("Address of num: %p\n", &num);         // Output the address of num
    printf("Value of ptr (address of num): %p\n", ptr);  // Output the address stored in ptr
    printf("Address of ptr (address of num): %p\n", &ptr);
    printf("Value pointed to by ptr: %d\n", *ptr);  // Dereferencing ptr to get the value of num

    return 0;
}