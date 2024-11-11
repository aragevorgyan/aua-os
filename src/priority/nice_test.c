#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>   // For getpriority, setpriority, PRIO_PROCESS
#include <errno.h>          // For errno

int main() {
    int nice_value;

    // Get the current nice value of the process
    nice_value = getpriority(PRIO_PROCESS, 0);
    if (nice_value == -1 && errno != 0) {
        perror("getpriority failed");
        return 1;
    }
    printf("Current nice value: %d\n", nice_value);

    // Set a new nice value
    printf("Setting nice value to 10...\n");
    if (nice(10) == -1) {
        perror("nice failed");
        return 1;
    }

    // Perform a CPU-intensive task to observe the impact of the nice value
    printf("Running a CPU-intensive task with nice value 10...\n");

    unsigned long long counter = 0;
    while (1) {
        counter++;
        if (counter % 1000000000 == 0) {
            printf("Counter: %llu\n", counter);
        }
    }

    return 0;
}
