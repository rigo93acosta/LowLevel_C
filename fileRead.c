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
    struct stat dbStat = {0};

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

    /*
    Read metadata from the file
    */
    if (fstat(fd, &dbStat) < 0) {
        perror("stat");
        close(fd);
        return -1;
    }

    // Read file 
    if (read(fd, &head, sizeof(head)) != sizeof(head)) {
        perror("read");
        close(fd);
        return -1;
    }
    printf("Version: %u\n", head.version);
    printf("Employees: %u\n", head.employees);
    printf("Filesize: %u\n", head.filesize);
    printf("DB Length, employee stat: %lu\n", dbStat.st_size);

    if (dbStat.st_size != head.filesize){
        printf("GET OUTTA HERE HACKER!\n");
        close(fd);
        return -2;
    }
    close(fd);
    return 0;
}