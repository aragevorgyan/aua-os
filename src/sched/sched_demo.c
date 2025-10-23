#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    struct sched_param param;
    param.sched_priority = 60;   // hardcoded priority

    // Choose ONE of these:
    //int policy = SCHED_OTHER;   // CFS
    //int policy = SCHED_RR;   // Round Robin (needs sudo)
    int policy = SCHED_FIFO; // FIFO (needs sudo)

    if (sched_setscheduler(0, policy, &param) == -1)
        perror("sched_setscheduler");

    printf("PID=%d running with ", getpid());
    if (policy == SCHED_OTHER) printf("SCHED_OTHER (normal)\n");
    else if (policy == SCHED_RR) printf("SCHED_RR (real-time round robin)\n");
    else if (policy == SCHED_FIFO) printf("SCHED_FIFO (real-time FIFO)\n");

    // Keep CPU busy
    for (;;) {
    }
}
