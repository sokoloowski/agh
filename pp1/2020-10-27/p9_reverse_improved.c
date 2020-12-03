#include <stdio.h>

int main(void)
{
    char *ws, *ws2, tekst[100] = "ala ma kota", tmp;
    ws = ws2 = tekst;
    while (*++ws2);
    ws2--;
    while (ws2 > ws)
    {
        tmp = *ws;
        *ws++ = *ws2;
        *ws2-- = tmp;
    }
    printf("%s\n", tekst);
    return 0;
}