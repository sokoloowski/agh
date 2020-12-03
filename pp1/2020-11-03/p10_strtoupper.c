#include <stdio.h>

void strtoupper(char *tekst)
{
    while (*tekst)
    {
        if (*tekst >= 'a' && *tekst <= 'z')
        {
            *tekst -= 32;
        }
        tekst++;
    }
}

int main(void)
{
    char tekst[100] = "ala ma kota";
    printf("%s\n", tekst);
    strtoupper(tekst);
    printf("%s\n", tekst);
    return 0;
}