#include <stdio.h>

int main(void)
{
    char *ws, tekst[12] = "ala ma kota";
    ws = &tekst[0];
    printf("%c %p\n", *ws, ws);
    ws++;
    printf("%c %p\n", *ws, ws);
    ws += 3;
    printf("%c %p\n", *ws, ws);
    printf("%c %p\n", *(ws + 4), ws + 4);
    return 0;
}