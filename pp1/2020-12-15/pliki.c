#include <stdio.h>

int main(void)
{
    FILE *plik1, *plik2;
    int w;
    plik1 = fopen("plik1.txt", "w");
    if (plik1 == 0)
        printf("Błąd podczas otwierania pliku\n");
    for (int i = 0; i < 1000; i++)
    {
        w = fprintf(plik1, "%d ", i);
    }
    fclose(plik1);

    plik1 = fopen("plik1.txt", "r");
    plik2 = fopen("plik2.txt", "w");
}