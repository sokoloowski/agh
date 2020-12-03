#include <stdio.h>

int main(void)
{
    int a,
        *w1,
        **w2,
        ***w3,
        ****w4,
        *****w5,
        ******w6,
        *******w7,
        ********w8,
        *********w9,
        **********w10,
        ***********wypierdalac;

    a = 7;
    w1 = &a;
    w2 = &w1;
    w3 = &w2;
    w4 = &w3;
    w5 = &w4;
    w6 = &w5;
    w7 = &w6;
    w8 = &w7;
    w9 = &w8;
    w10 = &w9;
    wypierdalac = &w10;

    ***********wypierdalac = 66;
    printf("%d\n", a);
}