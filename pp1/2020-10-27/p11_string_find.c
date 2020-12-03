#include <stdio.h>

int main(void)
{
    char *ws, *ws2, tekst[] = "ala ma kot kota", search[] = "kot";
    int i = 0;
    ws = tekst;
    while (*ws)
    {
        ws2 = search;
        if (*ws == *ws2)
        {
            while (*ws2)
            {
                if (*ws++ != *ws2++)
                    break;
            }
            if (!*ws2)
                i++;
        }
        else
        {
            *ws++;
        }
    };
    printf("%d\n", i);
    return 0;
}