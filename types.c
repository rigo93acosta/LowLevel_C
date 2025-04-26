#include <stdio.h>

int main(int argc, char const *argv[])
{
    unsigned int x = 4;

    int sx = (int)(x);

    printf("x = %u\n", x);
    printf("sx = %d\n", sx);

    unsigned int bigx  = 0xFFFFFEFE;
    short kindabigx = (short)(bigx);

    printf("bigx = %u\n", bigx);
    printf("kindabigx = %d\n", kindabigx);
    printf("kindabigx = %u\n", kindabigx);
    
    return 0;
}
