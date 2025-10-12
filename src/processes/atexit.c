#include <stdio.h>
#include <stdlib.h>

void out(void)
{
    printf("atexit() succeeded!\n");
}

int main()
{
    atexit(out);







    printf("Hello!\n");



    

    return 0;   
}