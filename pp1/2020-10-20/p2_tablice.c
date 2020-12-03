#include <stdio.h>

int main(void)
{
    char tekst[12] = "ala ma kota";
    char a;
    int i = 0,
        size = sizeof(tekst) / sizeof(tekst[0]);
    scanf("%c", &a);
    for (int _i = 0; _i < size; _i++)
    {
        if (tekst[_i] == a)
            i++;
    }
    printf("%d\n", i);
    return 0;
}