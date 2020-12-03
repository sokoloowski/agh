#include <stdio.h>

int main(void)
{
    char tekst[16] = "ala ma kot kota";
    char a[4] = "kot";
    int i = 0;
    for (int _i = 0; _i < 15; _i++)
    {
        if (tekst[_i] == a[0])
        {
            for (int _j = 0; _j < 3; _j++)
            {
                if (tekst[_i + _j] != a[_j])
                {
                    break;
                }
                if (_j == 2)
                {
                    i++;
                }
            }
        }
    }
    printf("%d\n", i);
    return 0;
}