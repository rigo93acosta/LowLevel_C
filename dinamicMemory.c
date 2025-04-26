#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_EMPLOYEES 1000

struct employee_t {
  int id;
  int income;
  bool staff;
};

int initialize_employee(struct employee_t *e){
  static int numEmployees = 0;
  numEmployees++;

  e->id = numEmployees;
  e->income = 0;
  e->staff = false;

  return numEmployees;
}

int main()
{
  //struct employee_t employees[MAX_EMPLOYEES];
  //initialize_employee(&employees[0]);
  //printf("employees[0] = %d\n", employees[0].id);
  int n = 4;
  struct employee_t *employees = malloc(sizeof(struct employee_t)*n);


  if (employees == NULL){
    printf("The allacotar failed\n");
    return -1;
  }

  int num = initialize_employee(&employees[0]);
  printf("%d\n", num);
  int num_2 = initialize_employee(&employees[1]);
  printf("%d\n", num_2);
  printf("%d\n", employees[0].id);
  printf("%d\n", employees[1].id);
  free(employees);
  employees = NULL;
}
