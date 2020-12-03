#include <stdio.h>

#define WIN 10
#define LOSE 20

int currentX,
    currentY,
    optimalX,
    optimalY,
    optimalDepth = 999;

char tab[3][3] = {"   ", "   ", "   "};

void wypisz(char tablica[3][3])
{
    system("clear"); // for Unix
    // system("cls");   // for Windows
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf(" ");
            if (tablica[i][j] == 'o')
            {
                printf("\033[0;31m");
            }
            else if (tablica[i][j] == 'x')
            {
                printf("\033[0;32m");
            }
            printf("%c\033[0m ", tablica[i][j] == ' ' ? (3 * i) + j + 1 + '0' : tablica[i][j]);
            if (j != 2)
                printf("|");
        }
        if (i != 2)
            printf("\n---+---+---\n");
    }
    printf("\n");
}

int ocena(char tablica[3][3])
{
    if (
        (tablica[0][0] == 'x' && tablica[0][1] == 'x' && tablica[0][2] == 'x') ||
        (tablica[1][0] == 'x' && tablica[1][1] == 'x' && tablica[1][2] == 'x') ||
        (tablica[2][0] == 'x' && tablica[2][1] == 'x' && tablica[2][2] == 'x') ||
        (tablica[0][0] == 'x' && tablica[1][0] == 'x' && tablica[2][0] == 'x') ||
        (tablica[0][1] == 'x' && tablica[1][1] == 'x' && tablica[2][1] == 'x') ||
        (tablica[0][2] == 'x' && tablica[1][2] == 'x' && tablica[2][2] == 'x') ||
        (tablica[0][0] == 'x' && tablica[1][1] == 'x' && tablica[2][2] == 'x') ||
        (tablica[0][2] == 'x' && tablica[1][1] == 'x' && tablica[2][0] == 'x'))
        return WIN;
    else if (
        (tablica[0][0] == 'o' && tablica[0][1] == 'o' && tablica[0][2] == 'o') ||
        (tablica[1][0] == 'o' && tablica[1][1] == 'o' && tablica[1][2] == 'o') ||
        (tablica[2][0] == 'o' && tablica[2][1] == 'o' && tablica[2][2] == 'o') ||
        (tablica[0][0] == 'o' && tablica[1][0] == 'o' && tablica[2][0] == 'o') ||
        (tablica[0][1] == 'o' && tablica[1][1] == 'o' && tablica[2][1] == 'o') ||
        (tablica[0][2] == 'o' && tablica[1][2] == 'o' && tablica[2][2] == 'o') ||
        (tablica[0][0] == 'o' && tablica[1][1] == 'o' && tablica[2][2] == 'o') ||
        (tablica[0][2] == 'o' && tablica[1][1] == 'o' && tablica[2][0] == 'o'))
        return LOSE;
    else
        return 0;
}

void analizuj(char tablica[3][3], char znak, int poziom)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (tablica[i][j] == ' ')
            {
                tablica[i][j] = znak;
                if (poziom == 1)
                {
                    // Zapamiętaj pole wyjściowe
                    currentX = i;
                    currentY = j;
                }

                if (ocena(tablica) == LOSE)
                {
                    // Jeśli komputer może wygrać
                    if (optimalDepth >= poziom)
                    {
                        optimalDepth = poziom;
                        optimalX = currentX;
                        optimalY = currentY;
                    }
                    if (poziom == 1)
                    {
                        optimalDepth = 0;
                        optimalX = i;
                        optimalY = j;
                    }
                }
                else if (ocena(tablica) == WIN && poziom == 0 && znak == 'x')
                {
                    // Jeśli gracz może wygrać
                    optimalDepth = 0;
                    optimalX = i;
                    optimalY = j;
                }
                else
                {
                    // printf("%d: %c - %d,%d\n", poziom, znak, i + 1, j + 1);
                    analizuj(tablica, znak == 'x' ? 'o' : 'x', poziom + 1);
                }
                tablica[i][j] = ' ';
            }
        }
    }
    if (optimalDepth >= 3)
    {
        // Preferuj środek i rogi
        if (tablica[1][1] == ' ')
            optimalX = optimalY = 1;
        else
            for (int i = 0; i < 3; i += 2)
                for (int j = 0; j < 3; j += 2)
                    if (tablica[i][j] == ' ')
                    {
                        optimalX = i;
                        optimalY = j;
                    }
    }
}

void czytaj(char tablica[3][3])
{
    int poz = 0;
    printf("Podaj numer pola na planszy: ");
    scanf("%d", &poz);
    int x = (poz - 1) / 3;
    int y = (poz - 1) % 3;
    if (tablica[x][y] == ' ')
    {
        tablica[x][y] = 'x';
    }
    else
    {
        wypisz(tab);
        printf("\033[0;31mTo pole jest już zajęte!\033[0m\n");
        czytaj(tablica);
    }
}

int main(void)
{
    int koniec = 0;
    while (!koniec)
    {
        wypisz(tab);
        czytaj(tab);

        if (ocena(tab) == WIN)
        {
            wypisz(tab);
            printf("Wygrałeś!\n");
            break;
        }

        analizuj(tab, 'x', 0);
        analizuj(tab, 'o', 1);
        tab[optimalX][optimalY] = 'o';
        optimalDepth = 999;

        if (ocena(tab) == LOSE)
        {
            wypisz(tab);
            printf("Przegrałeś...\n");
            break;
        }

        koniec = 1;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (tab[i][j] == ' ')
                    koniec = 0;
        if (koniec)
        {
            wypisz(tab);
            printf("Remis.\n");
        }
    }
    return 0;
}