#include <stdio.h>
#include <stdbool.h>
#include <getopt.h>

#include "common.h"
#include "file.h"
#include "parse.h"

static void print_usage(char const *argv[]){
    printf("Usage: %s -n -f <database file>\n", argv[0]);
    printf("\t -n - create new database file\n");
    printf("\t -f - (required) path to database file\n");
}

int main(int argc, char *argv[])
{   
    int c;
    char *filepath = NULL;
    bool newfile = false;
    char *addstring = NULL;

    int dbfd = -1;
    struct dbheader_t *dbhdr = NULL;
    struct employee_t *employees = NULL;

    while ((c = getopt(argc, argv, "nf:a:")) != -1)
    {   
        switch(c){
            
            case 'n':
                newfile = true;
                break;
            case 'f':
                filepath = optarg;
                break; 
            case 'a':
                addstring = optarg;
                break;
            case '?':
                printf("Unknown option: -%c\n", c);
                break;
            default:
                return -1;
        }
    }

    if (filepath == NULL){
        printf("Filepath is a required argument\n");
        print_usage((char const **)argv);
        return 0;
    }

    if (newfile){
        dbfd = create_db_file(filepath);
        if (dbfd == STATUS_ERROR){
            printf("Failed to create new database file\n");
            return -1;
        } 

        if (create_db_header(dbfd, &dbhdr) == STATUS_ERROR){
            printf("Failed to create database header\n");
            return -1;
        }

    } else {
        dbfd = open_db_file(filepath);
        if (dbfd == STATUS_ERROR){
            printf("Failed to open new database file\n");
            return -1;
        }

        if (validate_db_header(dbfd, &dbhdr) == STATUS_ERROR){
            printf("Failed to validate database header\n");
            return -1;
        }
    }

    // printf("Newfile: %d\n", newfile);
    // printf("Filepath: %s\n", filepath);
    if (read_employees(dbfd, dbhdr, &employees) != STATUS_SUCCESS){
        printf("Failed to read employees\n");
        return -1;
    }

    if (addstring){
        
        dbhdr->count++;
        employees = realloc(employees, dbhdr->count * (sizeof(struct employee_t)));
        add_employee(dbhdr, employees, addstring);
    }

    output_file(dbfd, dbhdr, employees);
    
    return 0;
}
