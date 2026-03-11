// compute_bound.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000000000

int main() {
    volatile double x = 1.0;
    for (long i = 0; i < N; i++) {
        x = x * 1.0000001 + 0.0000001;
    }
    printf("Result: %f\n", x);
    return 0;
}