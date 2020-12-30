#include <stdio.h>

int main(void)
{
    FILE *plik1, *plik2;
    int w, val;
    plik1 = fopen("plik1.txt", "w");
    if (plik1 == 0)
    {
        printf("Błąd podczas otwierania pliku\n");
        return 0;
    }
    for (int i = 0; i < 1000; i++)
    {
        w = fprintf(plik1, "%d ", i);
    }
    fclose(plik1);

    // ------------ Przepisywanie ------------

    plik1 = fopen("plik1.txt", "r");
    plik2 = fopen("plik2.txt", "w");

    if (plik1 == 0)
    {
        printf("Błąd podczas otwierania pliku plik1.txt\n");
        return 0;
    }
    if (plik2 == 0)
    {
        printf("Błąd podczas otwierania pliku plik2.txt\n");
        return 0;
    }

    for (int i = 0; i < 1000; i++)
    {
        fscanf(plik1, "%d", &val);
        if (i % 2)
        {
            fprintf(plik2, "%d ", val);
        }
    }
}