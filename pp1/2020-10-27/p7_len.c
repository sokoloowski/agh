#include <stdio.h>

int main(void)
{
    char *ws, tekst[100] = "ala ma kota";
    ws = tekst;
    while (*ws++ != 0)
    {
        // do nothing
    };
    printf("%d\n", ws - tekst - 1);
    return 0;
}