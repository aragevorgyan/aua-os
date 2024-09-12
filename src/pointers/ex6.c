#include <stdio.h>

// Function pointer to sum function

// Function to calculate sum of two integers
int sum(int a, int b) {
    return a + b;
}

int main() {
    // Declare a pointer to a function that returns an int and takes two int arguments
    int (*funcPtr)(int, int);

    // Assign the address of the sum function to the function pointer
    funcPtr = &sum;

    // Call the function using the function pointer
    int result = funcPtr(5, 10);

    // Output the result
    printf("The sum of 5 and 10 is: %d\n", result);

    return 0;
}