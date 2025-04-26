#include <stdio.h>
#include <stdbool.h>

#define MAX_IDS 32
#define MAX_EMPLOYEES 1000

struct employee_t {
  int id;
  char firstname[64];
  char lastname[64];
  float income;
  bool ismanager;
};

union myunion_u {
  int x;
  char c;
};

int main(void)
{
  struct employee_t Fred;
  Fred.income = 100.00;
  Fred.ismanager = true;
  printf("%f\n", Fred.income);

  struct employee_t employees[MAX_EMPLOYEES];

  int i = 0;
  for (i=0;i < MAX_EMPLOYEES; i++) {
    employees[i].income = 0;
    employees[i].ismanager = false;
  }

  return 0;
}
