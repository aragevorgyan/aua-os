#include <stdio.h>
#include <stdlib.h>

void out(void)
{
    printf("atexit() succeeded!\n");
}

int main()
{

    int x;
    float f;

    f = (float)x;
    
    if (atexit(out))
    {
        fprintf(stderr, "atexit() failed!\n");
    }

    printf("Hello!\n");

    return 0;   
}