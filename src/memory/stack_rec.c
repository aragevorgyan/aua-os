#include <stdio.h>

void f(int d) {
    volatile int local = d;           // volatile: keep it on the stack
    printf("depth=%d  &local=%p\n", d, (void*)&local);
    if (d < 6) f(d+1);
}

int main(void) { 
    f(1); 
}
