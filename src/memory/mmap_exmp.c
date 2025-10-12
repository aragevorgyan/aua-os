#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>

int main() {
    size_t length = 4096; // one page
    printf("Allocating %zu bytes with mmap...\n", length);

    // Create anonymous mapping
    void *addr = mmap(NULL, length, PROT_READ | PROT_WRITE,
                      MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (addr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    printf("Anonymous mapping created at address: %p\n", addr);

    // Use the mapped memory
    strcpy((char *)addr, "Hello from anonymous mmap!");
    printf("Content in mapped memory: %s\n", (char *)addr);

    // Show the mapping in /proc/<pid>/maps
    printf("Check this region in /proc/%d/maps\n", getpid());
    getchar(); // Pause to allow inspection

    // Unmap the memory
    if (munmap(addr, length) == -1) {
        perror("munmap");
    } else {
        printf("Mapping successfully unmapped.\n");
    }

    return 0;
}
