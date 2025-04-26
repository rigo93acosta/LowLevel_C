#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_IDS 32

int main(int argc, char *argv[])
{
  //int ids[MAX_IDS];

  int ids[MAX_IDS] = {1,2,3,4,5};

  printf("%d\n", ids[0]);

  for (int i = 0; i < MAX_IDS; i++) {
    printf("ids[%d]: %d \n", i, ids[i]);
  }
  return 0;
}
