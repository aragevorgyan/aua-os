#include <stdio.h>
#include <unistd.h>

int main() {
    void *initial_break_addr = sbrk(0);
    // Ask for 4 bytes
    void *p = sbrk(4);
    
    printf("Break after sbrk(+4): %p\n", sbrk(0));
    printf("initial_break_addr: %p\n", initial_break_addr);

    // Use the new memory
    int *num = (int *)p;    // point to the start of new area
    *num = 42;           // store a value
    printf("Stored value: %d at address %p\n", *num, (void*)num);

    return 0;
}