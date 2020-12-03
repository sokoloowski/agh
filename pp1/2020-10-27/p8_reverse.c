#include <stdio.h>

int main(void)
{
    char *ws, *ws2, tekst[100] = "ala ma kota", tekst2[100];
    ws = tekst;
    ws2 = tekst2;
    while (*++ws);
    ws--;
    while (ws >= tekst)
    {
        *ws2++ = *ws--;
        printf("%c\n", *(ws2 - 1));
        // printf("%c\n", *ws);
    }
    *ws2 = 0;
    printf("%s\n", tekst2);
    return 0;
}