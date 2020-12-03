#include <stdio.h>

// TODO: w ifie mieć możliwość wykonać dowolną operację (!)

int main(void)
{
    char z, x, y;
    int a, b, c;
    while (1)
    {
        if (scanf("%c=%c+%c", &z, &x, &y) == 3)
        {
            if (z == 'a')
                if (x - '0' > 9)
                {
                    if (x == 'a')
                        a = a + (y - '0');
                    if (x == 'b')
                        a = b + (y - '0');
                    if (x == 'c')
                        a = c + (y - '0');
                }
                else
                    a = (x - '0') + (y - '0');
            if (z == 'b')
                if (x - '0' > 9)
                {
                    if (x == 'a')
                        b = a + (y - '0');
                    if (x == 'b')
                        b = b + (y - '0');
                    if (x == 'c')
                        b = c + (y - '0');
                }
                else
                    b = (x - '0') + (y - '0');
            if (z == 'c')
                if (x - '0' > 9)
                {
                    if (x == 'a')
                        c = a + (y - '0');
                    if (x == 'b')
                        c = b + (y - '0');
                    if (x == 'c')
                        c = c + (y - '0');
                }
                else
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
        else if (scanf("%c++", &z) == 1)
        {
            if (z == 'a')
                a++;
            if (z == 'b')
                b++;
            if (z == 'c')
                c++;
        }
        else if (scanf("if(%c<%c)wypisz(%c)", &x, &y, &z))
        {
            if (x == 'a')
            {
                if (y == 'a')
                {
                    if (z == 'a')
                        if (a > a)
                            printf("%d\n", a);
                    if (z == 'b')
                        if (a > a)
                            printf("%d\n", b);
                    if (z == 'c')
                        if (a > a)
                            printf("%d\n", c);
                }
                else if (y == 'b')
                {
                    if (z == 'a')
                        if (a > b)
                            printf("%d\n", a);
                    if (z == 'b')
                        if (a > b)
                            printf("%d\n", b);
                    if (z == 'c')
                        if (a > b)
                            printf("%d\n", c);
                }
                else if (y == 'c')
                {
                    if (z == 'a')
                        if (a > c)
                            printf("%d\n", a);
                    if (z == 'b')
                        if (a > c)
                            printf("%d\n", b);
                    if (z == 'c')
                        if (a > c)
                            printf("%d\n", c);
                }
            }
            else if (x == 'b')
            {
                if (y == 'a')
                {
                    if (z == 'a')
                        if (b > a)
                            printf("%d\n", a);
                    if (z == 'b')
                        if (b > a)
                            printf("%d\n", b);
                    if (z == 'c')
                        if (b > a)
                            printf("%d\n", c);
                }
                else if (y == 'b')
                {
                    if (z == 'a')
                        if (b > b)
                            printf("%d\n", a);
                    if (z == 'b')
                        if (b > b)
                            printf("%d\n", b);
                    if (z == 'c')
                        if (b > b)
                            printf("%d\n", c);
                }
                else if (y == 'c')
                {
                    if (z == 'a')
                        if (b > c)
                            printf("%d\n", a);
                    if (z == 'b')
                        if (b > c)
                            printf("%d\n", b);
                    if (z == 'c')
                        if (b > c)
                            printf("%d\n", c);
                }
            }
            else if (x == 'c')
            {
                if (y == 'a')
                {
                    if (z == 'a')
                        if (c > a)
                            printf("%d\n", a);
                    if (z == 'b')
                        if (c > a)
                            printf("%d\n", b);
                    if (z == 'c')
                        if (c > a)
                            printf("%d\n", c);
                }
                else if (y == 'b')
                {
                    if (z == 'a')
                        if (c > b)
                            printf("%d\n", a);
                    if (z == 'b')
                        if (c > b)
                            printf("%d\n", b);
                    if (z == 'c')
                        if (c > b)
                            printf("%d\n", c);
                }
                else if (y == 'c')
                {
                    if (z == 'a')
                        if (c > c)
                            printf("%d\n", a);
                    if (z == 'b')
                        if (c > c)
                            printf("%d\n", b);
                    if (z == 'c')
                        if (c > c)
                            printf("%d\n", c);
                }
            }
        }
        else if (scanf("for(a=%c;a<%c;a+=%c)"))
        {
            // code...
        }
        else if (scanf("if(%c<%c)wypisz(%c)else_wypisz(%c)"))
        {
            // code...
        }
        else if ()
        {
            // code...
        }
    }
    return 0;
}
