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
    int input;
    printf("Process started. PID: %d\n", getpid());


    for (int i = 0; i < 5; i++) {
        printf("Iteration %d\n", i + 1);

        do_some_work(20);

        printf("Waiting for a character input...\n");

        scanf("%d", &input); // to read the input we can also use scanf

        printf("Iteration %d: Input received!\n", i + 1);
    }

    printf("Process completed.\n");
    return 0;
}