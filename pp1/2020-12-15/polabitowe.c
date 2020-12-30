#include <stdio.h>

struct str1 {
    unsigned int pole1: 1;
    unsigned int byloPrzepelnienie: 1;
    unsigned int pole3: 1;
} flaga;

int main(void) {
    flaga.byloPrzepelnienie = 1;
    flaga.pole3 = 0;
    printf("%u %u\n", flaga.byloPrzepelnienie, flaga.pole3);
}