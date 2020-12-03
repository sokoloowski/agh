#include <stdio.h>

int main(void)
{
    int *ws, tekst[12] = {7, 8, 9, 8, 5, 6, 76, 54, 55, 55};
    ws = &tekst[0];
    printf("%d %p\n", *ws, ws);
    ws++;
    printf("%d %p\n", *ws, ws);
    ws += 3;
    printf("%d %p\n", *ws, ws);
    printf("%d %p\n", *(ws + 4), ws + 4);
    return 0;
}