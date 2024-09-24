#include <stdio.h>

// Global initialized variable (data section)
int global_var = 42;

// Global uninitialized variable (bss section)
int uninitialized_var;

// Static variable (data section)
static int static_var = 10;

// Function (text section)
void demo_function() {
    int x = 7;
    printf("Inside demo_function x = %d\n", x);
}

int main() {
    // Local variable (stack section)
    int local_var = 5;

    printf("Inside main function\n");
    demo_function();

    return 0;
}
