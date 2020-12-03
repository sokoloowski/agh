#include <stdio.h>
#include <limits.h>

int main(void)
{
    int a = INT_MAX;
    a++;    // robi INT_MIN
    printf("%d\n", a);
    return 0;
}