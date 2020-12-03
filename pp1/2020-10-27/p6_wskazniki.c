#include <stdio.h>

int main(void)
{
    char tekst[12] = "ala ma kota";
    int war;
    printf("%p %p\n", tekst, &war);
    war = 0;
    printf("%d\n", war);
    tekst[-4] = 2;
    printf("%d\n", war);
    return 0;
}