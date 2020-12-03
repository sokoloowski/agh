#include <stdio.h>

int fibonacci(int n)
{
    int a = 0;
    int b = 1;
    int res;
    if (n == 1)
        return a;
    if (n == 2)
        return b;
    while (n > 2)
    {
        res = a + b;
        a = b;
        b = res;
        n--;
    }
    return res;
}

int main(void)
{
    printf("%d\n", fibonacci(6));
    return 0;
}