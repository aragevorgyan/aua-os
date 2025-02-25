#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 1000000
#define STRIDE 128

int main() {
    char *data = (char *)malloc(ARRAY_SIZE * STRIDE); // Allocate a larger array for strided access
    if (!data) {
        perror("Memory allocation failed");
        return 1;
    }

    // Initialize data with some values
    for (size_t i = 0; i < ARRAY_SIZE * STRIDE; i++) {
        data[i] = (char)(i % 256);
    }

    unsigned int sum = 0;
    clock_t start, end;

    // Measure time for sequential access
    start = clock();
    for (size_t i = 0; i < ARRAY_SIZE; ++i) {
        sum += data[i];
    }
    end = clock();
    printf("Sequential access time: %.2f ms\n", (double)(end - start) / CLOCKS_PER_SEC * 1000);

    // Reset sum
    sum = 0;

    // Measure time for strided access
    start = clock();
    for (size_t i = 0; i < ARRAY_SIZE; ++i) {
        sum += data[i * STRIDE];
    }
    end = clock();
    printf("Strided access time: %.2f ms\n", (double)(end - start) / CLOCKS_PER_SEC * 1000);

    free(data);
    return 0;
}
