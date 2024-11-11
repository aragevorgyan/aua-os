#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

extern int errno;

int main()
{
    const char *buf = "My ship is strong!!!";
    ssize_t nr = 0;
    int fd;
    int ret;
    errno = 0;
    fd = open("write_file.txt", O_RDONLY | O_WRONLY | O_APPEND); // | O_CREAT, S_IWUSR | S_IRUSR | S_IWGRP | S_IRGRP | S_IROTH);
    if (fd == -1)
    {
        perror("");
    }

    nr = write(fd, buf, strlen(buf));
    if (nr == -1)
    {
        perror("");
    }

    if (close (fd) == -1)
        perror ("");
    
    return 0;
}