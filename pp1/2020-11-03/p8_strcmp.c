#include <stdio.h>

int strcmp(char *str1, char *str2)
{
    while (*str1 || *str2)
        if (*str1++ != *str2++)
            return 1;
    return 0;
}

void wypisz(char *t)
{
    printf("%s\n", t);
}

int main(void)
{
    char poczatek[100] = "mala ",
         tekst[100] = "ala ma kota",
         kopia[100] = "ala ma kota";

    printf("%d\n", strcmp(poczatek, tekst));
    printf("%d\n", strcmp(kopia, tekst));

    return 0;
}