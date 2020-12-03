#include <stdio.h>

int main(void)
{
    char x, y;
    int a;
    if (scanf("a=%c+%c", &x, &y) == 2)
    {
        a = (x - '0') + (y - '0');
        printf("Jest dobrze: %d\n", a);
    }
    return 0;
}