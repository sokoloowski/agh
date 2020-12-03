#include <stdio.h>

#define ROZMIAR 3

void mnoz(double m1[ROZMIAR][ROZMIAR], double m2[ROZMIAR][ROZMIAR], double m3[ROZMIAR][ROZMIAR])
{
    for (int w = 0; w < ROZMIAR; w++)
    {
        for (int k = 0; k < ROZMIAR; k++)
        {
            for (int i = 0; i < ROZMIAR; i++)
            {
                m3[w][k] += m1[w][i] * m2[i][k];
            }
        }
    }
}

void wypisz(double m1[ROZMIAR][ROZMIAR])
{
    for (int w = 0; w < ROZMIAR; w++)
    {
        for (int k = 0; k < ROZMIAR; k++)
        {
            printf("%d\t", m1[w][k]);
        }
        printf("\n");
    }
}

int main(void)
{
    double mac1[ROZMIAR][ROZMIAR] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    double mac2[ROZMIAR][ROZMIAR] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    double mac3[ROZMIAR][ROZMIAR];

    mnoz(mac1, mac2, mac3);
    wypisz(mac3);

    return 0;
}