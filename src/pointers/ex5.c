#include <stdio.h>

// Pointer to a Function

// Function to be pointed to
void greet() {
    printf("Hello from a function!\n");
}

int main() {
    // Declare a pointer to a function that returns void and takes no parameters
    void (*funcPtr)();

    funcPtr = &greet;  // Assign the address of greet to the pointer

    // Call the function using the pointer
    (*funcPtr)();

    return 0;
}