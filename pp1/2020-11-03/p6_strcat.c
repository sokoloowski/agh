#include <stdio.h>

void strcat(char *begin, char *end)
{
    while (*begin)
        *begin++;
    while (*end)
        *begin++ = *end++;
}

void strcpy(char *copy, char *original)
{
    while (*original)
        *copy++ = *original++;
    *copy = *original;
}

void wypisz(char *t)
{
    printf("%s\n", t);
}

int main(void)
{
    char poczatek[100] = "mala ",
         tekst[100] = "ala ma kota",
         kopia[100];

    strcat(poczatek, tekst);
    wypisz(poczatek);

    strcpy(kopia, poczatek);
    wypisz(kopia);

    return 0;
}