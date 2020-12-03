#include <stdio.h>

void wypisz(char *t)
{
    printf("%s\n", t);
}

int main(void)
{
    char tekst[12] = "ala ma kota",
         *ws;

    wypisz(tekst);
    ws = tekst + 2;
    wypisz(ws);
   
    return 0;
}