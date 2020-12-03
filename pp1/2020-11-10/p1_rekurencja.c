#include <stdio.h>

int silnia(int n)
{
    if (n == 0)
    {
        return 1;
    }
    else
    {
        return n * silnia(n - 1);
    }
}

int main(void)
{
    printf("%d\n", silnia(5));
    return 0;
}