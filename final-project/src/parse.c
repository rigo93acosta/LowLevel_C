#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#include "parse.h"
#include "common.h"

int create_db_header(int fd, struct dbheader_t **headerOut)
{   
    struct dbheader_t *header = calloc(1, sizeof(struct dbheader_t));
    if (header == -1){
        printf("Failed to allocate memory for header\n");
        return STATUS_ERROR;
    }

    header->version = 0x1;
    header->count = 0;
    header->magic = HEADER_MAGIC;
    header->filesize = sizeof(struct dbheader_t);

    *headerOut = header;

    return STATUS_SUCCESS;
}

int validate_db_header(int fd, struct dbheader_t **headerOut)
{   
    if (fd < 0){
        printf("Invalid file descriptor\n");
        return STATUS_ERROR;
    }

    struct dbheader_t *header = calloc(1, sizeof(struct dbheader_t));
    if (header == -1){
        printf("Failed to allocate memory for header\n");
        return STATUS_ERROR;
    }

    if (read(fd, header, sizeof(struct dbheader_t)) != sizeof(struct dbheader_t)){
        perror("read");
        free(header);
        return STATUS_ERROR;
    }

    header->version = ntohs(header->version);
    header->count = ntohs(header->count);
    header->magic = ntohl(header->magic);
    header->filesize = ntohl(header->filesize);

    if (header->version != 0x1){
        printf("Invalid version: %u\n", header->version);
        free(header);
        return -1;
    }
    if (header->magic != HEADER_MAGIC){
        printf("Invalid magic number: %u\n", header->magic);
        free(header);
        return -1;
    }

    struct stat dbstat = {0};
    fstat(fd, &dbstat);
    if(header->filesize != dbstat.st_size){
        printf("Corrupted database\n");
        free(header);
        return -1;
    }

    *headerOut = header;
    return STATUS_SUCCESS;
}

void output_file(int fd, struct dbheader_t *dbhdr, struct employee_t *employees)
{   
    if (fd < 0){
        printf("Invalid file descriptor\n");
        return STATUS_ERROR;
    }
    int realcount = dbhdr->count;

    dbhdr->magic = htonl(dbhdr->magic);
    dbhdr->filesize = htonl(sizeof(struct dbheader_t) + (sizeof(struct employee_t) * realcount));
    dbhdr->count = htons(dbhdr->count);
    dbhdr->version = htons(dbhdr->version);

    lseek(fd, 0, SEEK_SET);
    write(fd, dbhdr, sizeof(struct dbheader_t));

    int i = 0;
    for(; i < realcount; i++){
        employees[i].hours = htonl(employees[i].hours);
        write(fd, &employees[i], sizeof(struct employee_t));
    }

    return;
}

int read_employees(int fd, struct dbheader_t *dbhdr, struct employee_t **employeesOut)
{
    if(fd < 0){
        printf("Invalid file descriptor\n");
        return STATUS_ERROR;
    }

    int count = dbhdr->count;

    struct employee_t *employees = calloc(count, sizeof(struct employee_t));
    if (employees == -1){
        printf("Failed to allocate memory for employees\n");
        return STATUS_ERROR;
    }

    read(fd, employees, count*sizeof(struct employee_t));

    int i = 0;
    for(; i < count; i++){
        employees[i].hours = ntohl(employees[i].hours);

    }

    *employeesOut = employees;
    return STATUS_SUCCESS;
}

int add_employee(struct dbheader_t *dbhdr, struct employee_t *employees, char *addstring)
{
    char *name = strtok(addstring, ",");
    char *address = strtok(NULL, ",");
    char *hours = strtok(NULL, ",");

    strncpy(employees[dbhdr->count-1].name, name, sizeof(employees[dbhdr->count-1].name));
    strncpy(employees[dbhdr->count-1].address, address, sizeof(employees[dbhdr->count-1].address));    
    employees[dbhdr->count-1].hours = atoi(hours);
   
    return STATUS_SUCCESS;
}