#include <stdio.h>

int main(void)
{
    char z, x, y;
    int a, b, c;
    while (1)
    {
        if (scanf("%c=%c+%c", &z, &x, &y) == 3)
        {
            if (z == 'a')
                a = (x - '0') + (y - '0');
            if (z == 'b')
                b = (x - '0') + (y - '0');
            if (z == 'c')
                c = (x - '0') + (y - '0');
        }
        else if (scanf("wypisz(%c)", &z) == 1)
        {
            if (z == 'a')
                printf("%d\n", a);
            if (z == 'b')
                printf("%d\n", b);
            if (z == 'c')
                printf("%d\n", c);
        }
    }
    return 0;
}