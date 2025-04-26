#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

struct database_header_t
{
    unsigned short version;
    unsigned short employees;
    unsigned int filesize;
};

int main(int argc, char *argv[]) {

    struct database_header_t head = {0};

    /* 0 = stdin
    * 1 = stdout
    * 2 = stderr */
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return -1;
    }

    int fd = open(argv[1], O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("open");
        return -1;
    }

    char *mydata = "Hello, World!\n";
    ssize_t bytes_written = write(fd, mydata, strlen(mydata));
    printf("Wrote %zd bytes to %s\n", bytes_written, argv[1]);
    close(fd);
    return 0;
}