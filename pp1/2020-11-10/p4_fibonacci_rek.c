#include <stdio.h>

int fibonacci(int n)
{
    int a = 0;
    int b = 1;
    if (n == 1)
        return a;
    if (n == 2)
        return b;
    return fibonacci(n-1) + fibonacci(n-2);
}

int main(void)
{
    printf("%d\n", fibonacci(6)); // 5
    return 0;
}