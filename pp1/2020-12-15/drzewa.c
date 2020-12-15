#include <stdio.h>
#include <stdlib.h>

struct el_drzewa
{
};

void wstaw(struct el_drzewa, **pocz, double war)
{
    struct el_drzewa *nowy, *ws = *pocz, *nastepny;
    ;
    nowy = malloc(sizeof(struct el_drzewa));
    nowy->w = war;
    nowy->lewy = nowy->prawy = 0;
    if (ws == 0)
        *pocz = nowy;
    else
    {
        while (1)
        {
            if (war < ws->w)
            {
                if (ws->lewy == 0)
                {
                    ws->lewy = nowy;
                    break;
                }
                else
                    ws = ws->lewy;
            }
            else
            {
                if (ws->prawy == 0)
                {
                    ws->prawy = nowy;
                    break;
                }
                else
                    ws = ws->prawy;
            }
        }
    }
}

void wypisz(struct el_drzewa *pocz)
{
    if (pocz == 0)
        return;
    wypisz(pocz->lewy);
    printf(" %lf ", pocz->w);
    wypisz(pocz->prawy);
}

int main(void)
{
    return 0;
}