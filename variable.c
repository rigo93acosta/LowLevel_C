#include <stdio.h>

#define MAX_PERSONS 1024

#define DEBUG 

// Global Scope
int g_NumPersons = 0;


int main()
{
  
  int personID = 0;
  int personID2 = personID + 1;

  #ifdef DEBUG
  printf("We are in debug mode: %s:%d\n", __FILE__, __LINE__);
  #endif /* ifdef DEBUG */
  
  
  return 0;
}
