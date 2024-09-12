#include <stdio.h>
#include <unistd.h>

#include <stdio.h>
#include <unistd.h>

void do_some_work(int duration) {
    // Simulate a task by running a loop for 'duration' seconds
    for (int i = 0; i < duration * 100000000; i++) {
        // Dummy work
    }
}

int main() {
    printf("Process started. PID: %d\n", getpid());

    for (int i = 0; i < 5; i++) {
        printf("Iteration %d: Process is doing work (running).\n", i + 1);
        do_some_work(15); 

        printf("Iteration %d: Process is now sleeping.\n", i + 1);
        sleep(5);  // Process sleeps for 5 seconds
    }

    printf("Process completed.\n");
    return 0;
}