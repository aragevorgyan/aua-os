#include <stdio.h>

void test() {
    int a = 10;
    int b = 20;
    
    printf("Address of a: %p\n", (void*)&a);
    printf("Address of b: %p\n", (void*)&b);
}

int main() {
    test();
    return 0;
}