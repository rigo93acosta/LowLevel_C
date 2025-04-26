#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "file.h"

int open_db_file(char *filename)
{
    int fd = open(filename, O_RDWR);
    if (fd == -1) {
        perror("open");
        return -1;
    }

    return fd;
}