#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>

int main() {
    int nice_value = nice(0);
    printf("Current nice value: %d\n", nice_value);
    printf("PID: %d\n", (int)getpid());
    nice(-20); // increase niceness
    printf("After changing, new nice value: %d\n", nice(0));

    while(1) {
        printf("Running process with nice value...\n");
        sleep(3);
    }
}