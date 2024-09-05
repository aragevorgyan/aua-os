#include <unistd.h>
#include <stdio.h>

int main()
{
    int ret;
    printf("Before exec\n");
    ret = execl("/usr/bin/vim", "vim", NULL);
    //fix the path for your user
    //ret = execl("/home/ara/workspace/sysprog/aua/out/hello", "hello", NULL);
    {
        perror("execl");
    }
    printf("After exec\n");
    return 0;
}
