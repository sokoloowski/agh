#include <stdio.h>

void strcpy(char *copy, char *original)
{
    while (*original)
        *copy++ = *original++;
}

void wypisz(char *t)
{
    printf("%s\n", t);
}

int main(void)
{
    char tekst[100] = "ala ma kota",
         kopia[100];

    strcpy(kopia, tekst);
    wypisz(kopia);

    return 0;
}