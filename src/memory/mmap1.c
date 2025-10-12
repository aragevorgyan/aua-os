#include <stdlib.h>

int main() {
    void *p1 = malloc(1000);     // likely uses brk
    //void *p2 = malloc(2000000);  // likely uses mmap (anonymous mapping)
    (void)p1;
    //(void)p2;
    return 0;
}