#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdint.h>

int main()
{
    printf("My id: %jd\n", (intmax_t)getpid());
    printf("Parent id: %jd\n", (intmax_t)getppid());
    //while(1);
    return 0;
}