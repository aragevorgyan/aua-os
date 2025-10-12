#include <unistd.h>
#include <stdio.h>

int main()
{
    int ret;
    printf("Before exec\n");
    ret = execl("/usr/bin/ls", "ls", NULL);
    //fix the path for your user
    //ret = execl("/home/arag/workspace/aua-os/src/processes/hello", "hello", NULL);

    printf("After exec\n");
    return 0;
}
