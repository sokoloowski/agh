#include <stdio.h>

int strlen(char *tekst)
{
    int i = 0;
    while (*tekst++)
        i++;
    return i;
}

int main(void)
{
    char poczatek[100] = "mala ",
         tekst[100] = "ala ma kota",
         kopia[100];

    printf("%d\n", strlen(tekst));

    return 0;
}