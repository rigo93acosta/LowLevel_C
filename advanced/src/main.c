#include <stdio.h>

#include "file.h"
#include "parse.h"

int main(int argc, char const *argv[])
{
    int fd, numEmployees = 0;

    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return -1;
    }

    fd = open_db_file(argv[1]);
    if (fd == -1) {
        perror("open");
        return -1;
    }
    if (parse_file_header(fd, &numEmployees))
        return -1;
        
    printf("Number of employees stored: %d\n", numEmployees);

    return 0;
}
