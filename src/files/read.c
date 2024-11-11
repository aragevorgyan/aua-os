#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

extern int errno;

int main()
{
    int fd;
    errno = 0;
    unsigned long word;
    ssize_t nr;
    unsigned char c[10];

    fd = open("read_file.txt", O_RDONLY); // | O_CREAT, S_IWUSR | S_IRUSR | S_IWGRP | S_IRGRP | S_IROTH);
    if (fd == -1)
    {
        perror("");
    }

    //nr = read(fd, c, 8);
    ssize_t ret;
    int len = 8;
    char *buf;
    buf = c;
    while (len != 0 && (ret = read(fd, buf, len)) != 0)
    {
        if (ret == -1)
        {
            if (errno == EINTR)
                continue;
            perror("read");
            break;
        }
        len -= ret;
        buf += ret;
    }
    perror("read");
    printf("word = %s\n", c);
    printf("End of reading, nr = %ld\n", nr);
    return 0;
}