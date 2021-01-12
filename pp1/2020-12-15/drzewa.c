#include <stdio.h>
#include <stdlib.h>

struct el_drzewa {
    double w;
    struct el_drzewa *lewy, *prawy;
};

void wstaw(struct el_drzewa **pocz, double war) {
    struct el_drzewa *nowy, *ws = *pocz, *nastepny;
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

void wypisz(struct el_drzewa *pocz) {
    if (pocz == 0)
        return;
    wypisz(pocz->lewy);
    printf(" %lf ", pocz->w);
    wypisz(pocz->prawy);
}

struct el_drzewa *znajdz(struct el_drzewa *pocz, double war) {
    if (pocz == 0)
        return 0;
    if (pocz->w == war)
        return pocz;
    else if (pocz->w > war)
        znajdz(pocz->lewy, war);
    else
        znajdz(pocz->prawy, war);
}

int main(void) {
    struct el_drzewa *drzewo = 0;
    wstaw(&drzewo, 5);
    wstaw(&drzewo, 8);
    wstaw(&drzewo, 2);
    wstaw(&drzewo, 10);
    wstaw(&drzewo, 22);
//    wypisz(znajdz(drzewo, 2));
//    wypisz(znajdz(drzewo, 3));
    wypisz(drzewo);
    return 0;
}