#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

union IpAddress {
    uint32_t address;           // La dirección IP como un entero de 32 bits
    uint8_t bytes[4];           // La dirección IP como 4 bytes individuales
};

int main(int argc, char *argv[])
{
  union IpAddress my_ip;
  my_ip.address = 0xC0A80102;
  for (int i = 0; i < 4; i++) {
    printf("ip[%d] = %d\n", i, my_ip.bytes[i]);
  }
  
  return 0;
}
