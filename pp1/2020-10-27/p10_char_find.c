#include <stdio.h>

int main(void)
{
    char *ws, tekst[100] = "ala ma kota", search = 'a';
    int i = 0;
    ws = tekst;
    while (*ws) {
        if (*ws == search) i++;
        *ws++;
    };
    printf("%d\n", i);
    return 0;
}