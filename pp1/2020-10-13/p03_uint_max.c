#include <stdio.h>
#include <limits.h>

int main(void)
{
    int a = UINT_MAX;
    // a++;    // robi UINT_MIN
    printf("%u\n", a);
    return 0;
}