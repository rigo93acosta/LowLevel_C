#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "file.h"
#include "common.h"

int open_db_file(char *filename)
{
    int fd = open(filename, O_RDWR, 0644);
    if (fd == -1) {
        perror("open");
        return STATUS_ERROR;
    }

    return fd;
}

int create_db_file(char *filename)
{   
    int fd = open(filename, O_RDWR);
    if (fd != -1) {
        close(fd);
        printf("File already exists: %s\n", filename);
        return STATUS_ERROR;
    }

    fd = open(filename, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("open");
        return STATUS_ERROR;
    }
    return fd;
}