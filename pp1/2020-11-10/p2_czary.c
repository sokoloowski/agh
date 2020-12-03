#include <stdio.h>

long f2(long n);
long f1(long n)
{
    if (n > 0)
        return n + f2(n - 1);
    else
        return n;
}

long f2(long n)
{
    if (n > 0)
        return 2 * n + f1(n - 1);
    else
        return n;
}

int main(void)
{
    printf("%d\n", f1(5));
    return 0;
}