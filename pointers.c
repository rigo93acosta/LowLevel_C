#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_EMPLOYEES 1000

struct employee_t {
  int id;
  int income;
  bool staff;
};

void initialize_employee(struct employee_t *e){
  e->id = 0;
  e->income =0;
  e->staff = false;

  return;
}

int main()
{
  struct employee_t Ralph;

  initialize_employee(&Ralph);
  // setting the default value for Ralph
  
  printf("Ralph.income = %d\n", Ralph.income);
  Ralph.id = 1;
  Ralph.income = 10;
  printf("Ralph.income = %d\n", Ralph.income);
}
