#include <stdio.h>
#include <unistd.h>

// Sending SIGSTOP
// kill -STOP <PID>

// Sending SIGCONT
// kill -CONT <PID>
int main() {
    printf("Running process PID: %d\n", getpid());
    while(1) {
        // Infinite loop to keep the process running
    }
    return 0;
}