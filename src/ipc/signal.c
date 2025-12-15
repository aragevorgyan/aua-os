#include <signal.h>
#include <stdio.h>

void handler(int sig) {
    printf("Caught signal %d!\n", sig);
}

int main() {
    signal(SIGINT, handler);
    while (1) {}
}
