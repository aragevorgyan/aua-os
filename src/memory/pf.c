#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    size_t size = 1024UL * 1024UL * 1024UL; // 1 GB
    char *arr = malloc(size);

    for (size_t i = 0; i < size; i += 4096) { // touch each page
        arr[i] = 1; // triggers page fault for that page
    }

    pause(); // keep program alive
    return 0;
}
