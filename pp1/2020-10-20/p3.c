#include <stdio.h>

int main(void)
{
    char tekst[12] = "ala ma kota"; // 12 wywołuje błędy:
    // *** stack smashing detected ***: terminated
    // [1]    10866 abort (core dumped)  ./p3
    int w;

    w = 0;
    printf("%d\n", w);

    for (int i = 12; i < 100; i++)
        tekst[i] = 1; // 12 wywołuje błędy:
    printf("%d\n", w);

    return 0;
}