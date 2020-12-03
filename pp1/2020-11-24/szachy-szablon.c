#include <stdio.h>

#define KROL 0
#define HETMAN 1
#define WIEZA 2
#define GONIEC 3
#define SKOCZEK 4
#define PIONEK 5
#define KROL_K 6
#define HETMAN_K 7
#define WIEZA_K 8
#define GONIEC_K 9
#define SKOCZEK_K 10
#define PIONEK_K 11
#define PUSTE 12

#define WYGRANA 1000
#define PRZEGRANA -1000

int MAX_KIER[] = {8, 8, 4, 4, 8, 3, 8, 8, 4, 4, 8, 3, 0};
int MAX_ODL[] = {2, 8, 8, 8, 2, 2, 2, 8, 8, 8, 2, 2, 0};

int WX[12][8] = {
    {-1, -1, 0, 1, 1, 1, 0, -1},
    {-1, -1, 0, 1, 1, 1, 0, -1},
    {-1, 0, 1, 0},
    {-1, 1, 1, -1},
    {-2, -1, 1, 2, 2, 1, -1, -2},
    {-1, -1, -1},
    {-1, -1, 0, 1, 1, 1, 0, -1},
    {-1, -1, 0, 1, 1, 1, 0, -1},
    {-1, 0, 1, 0},
    {-1, 1, 1, -1},
    {-2, -1, 1, 2, 2, 1, -1, -2},
    {1, 1, 1}};

int WY[12][8] = {
    {0, 1, 1, 1, 0, -1, -1, -1},
    {0, 1, 1, 1, 0, -1, -1, -1},
    {0, 1, 0, -1},
    {1, 1, -1, -1},
    {1, 2, 2, 1, -1, -2, -2, -1},
    {-1, 0, 1},
    {0, 1, 1, 1, 0, -1, -1, -1},
    {0, 1, 1, 1, 0, -1, -1, -1},
    {0, 1, 0, -1},
    {1, 1, -1, -1},
    {1, 2, 2, 1, -1, -2, -2, -1},
    {-1, 0, 1}};

int plansza[8][8] = {
    {WIEZA_K, SKOCZEK_K, GONIEC_K, HETMAN_K, KROL_K, GONIEC_K, SKOCZEK_K, WIEZA_K},
    {PIONEK_K, PIONEK_K, PIONEK_K, PIONEK_K, PIONEK_K, PIONEK_K, PIONEK_K, PIONEK_K},
    {PUSTE, PUSTE, PUSTE, PUSTE, PUSTE, PUSTE, PUSTE, PUSTE},
    {PUSTE, PUSTE, PUSTE, PUSTE, PUSTE, PUSTE, PUSTE, PUSTE},
    {PUSTE, PUSTE, PUSTE, PUSTE, PUSTE, PUSTE, PUSTE, PUSTE},
    {PUSTE, PUSTE, PUSTE, PUSTE, PUSTE, PUSTE, PUSTE, PUSTE},
    {PIONEK, PIONEK, PIONEK, PIONEK, PIONEK, PIONEK, PIONEK, PIONEK},
    {WIEZA, SKOCZEK, GONIEC, HETMAN, KROL, GONIEC, SKOCZEK, WIEZA}};

int HEUR[12][8][8] = {
    // ------------------------------ PLAYER ------------------------------ //
    // król
    {{PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA},
     {PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA},
     {PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA},
     {PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA},
     {PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA},
     {PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA},
     {PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA},
     {PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA, PRZEGRANA}},
    // hetman
    {{-176, -178, -178, -179, -179, -178, -178, -176},
     {-178, -180, -180, -180, -180, -180, -180, -178},
     {-178, -180, -181, -181, -181, -181, -180, -178},
     {-179, -180, -181, -181, -181, -181, -180, -179},
     {-180, -180, -181, -181, -181, -181, -180, -179},
     {-178, -181, -181, -181, -181, -181, -180, -178},
     {-178, -180, -181, -180, -180, -180, -180, -178},
     {-176, -178, -178, -179, -179, -178, -178, -176}},
    // wieża
    {{-100, -100, -100, -100, -100, -100, -100, -100},
     {-101, -102, -102, -102, -102, -102, -102, -101},
     {-99, -100, -100, -100, -100, -100, -100, -99},
     {-99, -100, -100, -100, -100, -100, -100, -99},
     {-99, -100, -100, -100, -100, -100, -100, -99},
     {-99, -100, -100, -100, -100, -100, -100, -99},
     {-99, -100, -100, -100, -100, -100, -100, -99},
     {-100, -100, 100, -101, -101, -100, -100, -100}},
    // goniec
    {{-56, -58, -58, -58, -58, -58, -58, -56},
     {-58, -60, -60, -60, -60, -60, -60, -58},
     {-58, -60, -61, -62, -62, -61, -60, -58},
     {-58, -61, -61, -62, -62, -61, -61, -58},
     {-58, -60, -62, -62, -62, -62, -60, -58},
     {-58, -62, -62, -62, -62, -62, -62, -58},
     {-58, -61, -60, -60, -60, -60, -61, -58},
     {-56, -58, -58, -58, -58, -58, -58, -56}},
    // skoczek
    {{-50, -52, -54, -54, -54, -54, -52, -50},
     {-52, -56, -60, -60, -60, -60, -56, -52},
     {-54, -60, -62, -63, -63, -62, -60, -54},
     {-54, -61, -63, -64, -64, -63, -61, -54},
     {-54, -60, -63, -64, -64, -63, -60, -54},
     {-54, -61, -62, -63, -63, -62, -61, -54},
     {-52, -56, -60, -61, -61, -60, -56, -52},
     {-50, -52, -54, -54, -54, -54, -52, -50}},
    // pionek
    {{-20, -20, -20, -20, -20, -20, -20, -20},
     {-30, -30, -30, -30, -30, -30, -30, -30},
     {-22, -22, -24, -26, -26, -24, -22, -22},
     {-21, -21, -22, -25, -25, -22, -21, -21},
     {-20, -20, -20, -24, -24, -20, -20, -20},
     {-21, -19, -18, -20, -20, -18, -19, -21},
     {-21, -22, -22, -16, -16, -22, -22, -21},
     {-20, -20, -20, -20, -20, -20, -20, -20}},

    // -------------------------------- AI -------------------------------- //
    // król komputera
    {{WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA},
     {WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA},
     {WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA},
     {WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA},
     {WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA},
     {WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA},
     {WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA},
     {WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA, WYGRANA}},
    // hetman komputera
    {{176, 178, 178, 179, 179, 178, 178, 176},
     {178, 180, 180, 180, 180, 180, 180, 178},
     {178, 180, 181, 181, 181, 181, 180, 178},
     {179, 180, 181, 181, 181, 181, 180, 179},
     {180, 180, 181, 181, 181, 181, 180, 179},
     {178, 181, 181, 181, 181, 181, 180, 178},
     {178, 180, 181, 180, 180, 180, 180, 178},
     {176, 178, 178, 179, 179, 178, 178, 176}},
    // wieża komputera
    {{100, 100, 100, 101, 101, 100, 100, 100},
     {99, 100, 100, 100, 100, 100, 100, 99},
     {99, 100, 100, 100, 100, 100, 100, 99},
     {99, 100, 100, 100, 100, 100, 100, 99},
     {99, 100, 100, 100, 100, 100, 100, 99},
     {99, 100, 100, 100, 100, 100, 100, 99},
     {101, 102, 102, 102, 102, 102, 102, 101},
     {100, 100, 100, 100, 100, 100, 100, 100}},
    // goniec komputera
    {{56, 58, 58, 58, 58, 58, 58, 56},
     {58, 61, 60, 60, 60, 60, 61, 58},
     {58, 62, 62, 62, 62, 62, 62, 58},
     {58, 60, 62, 62, 62, 62, 60, 58},
     {58, 61, 61, 62, 62, 61, 61, 58},
     {58, 60, 61, 62, 62, 61, 60, 58},
     {58, 60, 60, 60, 60, 60, 60, 58},
     {56, 58, 58, 58, 58, 58, 58, 56}},
    // skoczek komputera
    {{50, 52, 54, 54, 54, 54, 52, 50},
     {52, 56, 60, 60, 60, 60, 56, 52},
     {54, 60, 62, 63, 63, 62, 60, 54},
     {54, 61, 63, 64, 64, 63, 61, 54},
     {54, 60, 63, 64, 64, 63, 60, 54},
     {54, 61, 62, 63, 63, 62, 61, 54},
     {52, 56, 60, 61, 61, 60, 56, 52},
     {50, 52, 54, 54, 54, 54, 52, 50}},
    // pionek komputera
    {{20, 20, 20, 20, 20, 20, 20, 20},
     {21, 22, 22, 16, 16, 22, 22, 21},
     {21, 19, 18, 20, 20, 18, 19, 21},
     {20, 20, 20, 24, 24, 20, 20, 20},
     {21, 21, 22, 25, 25, 22, 21, 21},
     {22, 22, 24, 26, 26, 24, 22, 22},
     {30, 30, 30, 30, 30, 30, 30, 30},
     {20, 20, 20, 20, 20, 20, 20, 20}},
    // puste
    {{0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0},
     {0, 0, 0, 0, 0, 0, 0, 0}}};

/*
    0 - król
    1 - hetman
    2 - wieża
    3 - goniec
    4 - skoczek
    5 - pionek

    6 - król_k
    7 - hetman_k
    8 - wieża_k
    9 - goniec_k
    10 - skoczek_k
    11 - pionek_k

    12 - pole puste
*/

const char *figura(int pole)
{
    if (pole == KROL)
        return "♛";
    if (pole == HETMAN)
        return "♚";
    if (pole == WIEZA)
        return "♜";
    if (pole == GONIEC)
        return "♝";
    if (pole == SKOCZEK)
        return "♞";
    if (pole == PIONEK)
        return "♟";

    if (pole == KROL_K)
        return "♕";
    if (pole == HETMAN_K)
        return "♔";
    if (pole == WIEZA_K)
        return "♖";
    if (pole == GONIEC_K)
        return "♗";
    if (pole == SKOCZEK_K)
        return "♘";
    if (pole == PIONEK_K)
        return "♙";

    // default fallback
    return " ";
}

int ocena(int plansza[8][8])
{
    int i,
        j,
        w = 0;
    for (i = 0; i < 8; i++)
        for (j = 0; j < 8; j++)
            w += HEUR[plansza[i][j]][i][j];
    return w;
}

int najlepszy(int plansza[8][8], int tryb, int *x, int *y, int *k, int *o)
{
    int px_pom,
        py_pom,
        k_pom,
        o_pom,
        px,
        py,
        dx,
        dy,
        kierunek,
        odleglosc,
        wynik = ocena(plansza),
        wmax,
        wmin,
        ruch_fig,
        bita_fig;

    if (tryb == 0 || wynik > WYGRANA || wynik < PRZEGRANA)
        return wynik;

    if (tryb % 2 == 0) // ruch komputera
    {
        for (px = 0, wmax = 100 * PRZEGRANA; px < 8; px++)
            for (py = 0; py < 8; py++)
                // na polu figura komputera
                if (plansza[px][py] >= 6 && plansza[px][py] <= 12)
                    for (kierunek = 0; kierunek < MAX_KIER[plansza[px][py]]; kierunek++)
                        for (odleglosc = 1; kierunek < MAX_ODL[plansza[px][py]]; odleglosc++)
                        {
                            dx = (odleglosc - 1) * WX[plansza[px][py]][kierunek];
                            dy = (odleglosc - 1) * WY[plansza[px][py]][kierunek];
                            // jeśli po drodze niepuste
                            if (odleglosc >= 2 && plansza[px + dx][py + dy] != PUSTE)
                                break;
                            dx = odleglosc * WX[plansza[px][py]][kierunek];
                            dy = odleglosc * WY[plansza[px][py]][kierunek];
                            // ruch mieści się w szachownicy
                            if (px + dx >= 0 && px + dx < 8 && py + dy >= 0 && py + dy < 8)
                                // docelowe pole puste lub figura przeciwnika
                                if (plansza[px + dx][py + dy] == PUSTE || plansza[px + dx][py + dy] <= 5)
                                    // warunek dodatkowy dla piona (bicie w bok, ruch naprzód)
                                    if (plansza[px][py] != 11 || (plansza[px + dx][py + dy] == PUSTE && dx == 0) || (plansza[px + dx][py + dy] != PUSTE && dx != 0))
                                    {
                                        ruch_fig = plansza[px][py];
                                        bita_fig = plansza[px + dx][py + dy]; //ruch
                                        plansza[px + dx][py + dy] = plansza[px][py];
                                        plansza[px][py] = PUSTE;
                                        if (plansza[px + dx][py + dy] == 11 && py + dy == 7) // pion doszedł do końca to
                                            plansza[px + dx][py + dy] = 7;                   // wymiana na hetmana
                                        wynik = najlepszy(plansza, tryb - 1, &px_pom, &py_pom, &k_pom, &o_pom);
                                        // cofnięcie ruchu
                                        plansza[px][py] = ruch_fig;
                                        plansza[px + dx][py + dy] = bita_fig;
                                        if (wynik >= wmax)
                                        {
                                            wmax = wynik;
                                            *x = px;
                                            *y = py;
                                            *k = kierunek;
                                            *o = odleglosc;
                                        }
                                    }
                        }
        return wmax; // należy również przewidzieć pat
    }
    else // ruch przeciwnika
    {
        for (px = 0, wmin = 100 * WYGRANA; px < 8; px++)
            for (py = 0; py < 8; py++)
                // na polu figura przeciwnika
                if (plansza[px][py] <= 5)
                    for (kierunek = 0; kierunek < MAX_KIER[plansza[px][py]]; kierunek++)
                        for (odleglosc = 1; odleglosc < MAX_ODL[plansza[px][py]]; odleglosc++)
                        {
                            dx = (odleglosc - 1) * WX[plansza[px][py]][kierunek];
                            dy = (odleglosc - 1) * WY[plansza[px][py]][kierunek];
                            // jeśli po drodze niepuste
                            if (odleglosc >= 2 && plansza[px + dx][py + dy] != PUSTE)
                                break;
                            dx = odleglosc * WX[plansza[px][py]][kierunek];
                            dy = odleglosc * WY[plansza[px][py]][kierunek];
                            // ruch mieści się w szachownicy
                            if (px + dx >= 0 && px + dx < 8 && py + dy >= 0 && py + dy < 8)
                                // docelowe pole puste lub fig przeciwnika
                                if (plansza[px + dx][py + dy] >= 6)
                                    // warunek dodatkowy dla piona (picie w bok, ruch naprzód)
                                    if (plansza[px][py] != 5 || (plansza[px + dx][py + dy] == PUSTE && dx == 0) || (plansza[px + dx][py + dy] != PUSTE && dx != 0))
                                    {
                                        ruch_fig = plansza[px][py];
                                        bita_fig = plansza[px + dx][py + dy];
                                        plansza[px + dx][py + dy] = plansza[px][py];
                                        plansza[px][py] = PUSTE;
                                        // jeśli pion doszedł do końca to wymiana na hetmana
                                        if (plansza[px + dx][py + dy] == 5 && py + dy == 0)
                                            plansza[px + dx][py + dy] = 1;
                                        wynik = najlepszy(plansza, tryb - 1, &px_pom, &py_pom, &k_pom, &o_pom);
                                        // cofnięcie ruchu
                                        plansza[px][py] = ruch_fig;
                                        plansza[px + dx][py + dy] = bita_fig;
                                        if (wynik <= wmin)
                                        {
                                            wmin = wynik;
                                            *x = px;
                                            *y = py;
                                            *k = kierunek;
                                            *o = odleglosc;
                                        }
                                    }
                        }
        return wmin; // należy również przewidzieć pat
    }
}

void getMove(int board[8][8])
{
    int colFrom, rowFrom,
        colTo, rowTo, toMove;
    char tmpFrom, tmpTo, ch;

    printf("Ruch z (a1): ");
    scanf("%c%d%c", &tmpFrom, &rowFrom, &ch);
    rowFrom--;
    if (tmpFrom >= 'a' && tmpFrom <= 'h')
        colFrom = tmpFrom - 'a';
    else if (tmpFrom >= 'A' && tmpFrom <= 'H')
        colFrom = tmpFrom - 'A';

    if (rowFrom < 0 || rowFrom >= 8 || colFrom < 0 || colFrom >= 8 || board[rowFrom][colFrom] >= KROL_K)
    {
        printf("Nieprawidłowa wartość! Spróbuj ponownie!\n");
        getMove(board);
    }

    printf("Ruch do (a1): ");
    scanf("%c%d%c", &tmpTo, &rowTo, &ch);
    rowTo--;
    if (tmpTo >= 'a' && tmpTo <= 'h')
        colTo = tmpTo - 'a';
    else if (tmpTo >= 'A' && tmpTo <= 'H')
        colTo = tmpTo - 'A';

    if (rowTo < 0 || rowTo >= 8 || colTo < 0 || colTo >= 8)
    {
        printf("Nieprawidłowa wartość! Spróbuj ponownie!\n");
        getMove(board);
    }

    if (board[rowTo][colTo] <= PIONEK)
    {
        printf("To pole jest już zajęte! Spróbuj ponownie!\n");
        getMove(board);
    }

    board[rowTo][colTo] = board[rowFrom][colFrom];
    board[rowFrom][colFrom] = PUSTE;
}

void wypisz(int plansza[8][8])
{
    system("clear");
    printf("   | A | B | C | D | E | F | G | H |\n");
    printf("---+---+---+---+---+---+---+---+---+\n");
    for (int row = 0; row < 8; row++)
    {
        printf(" %d |", row + 1);
        for (int col = 0; col < 8; col++)
        {
            int field = plansza[row][col];
            printf(" %s |", figura(field));
        }
        printf("\n---+---+---+---+---+---+---+---+---+\n");
        // printf("\n");
    }
}

int main(void)
{
    int koniec = 0,
        res = 0;
    wypisz(plansza);
    printf("Białe zaczynają...\n\n");
    while (!koniec)
    {
        int x = 0, y = 0, k = 0, o = 0;
        getMove(plansza);
        wypisz(plansza);

        res = najlepszy(plansza, 6, &x, &y, &k, &o);

        // if (abs(res) >= WYGRANA)
        //     break;

        plansza[x + WX[plansza[x][y]][k]][y + WY[plansza[x][y]][k]] = plansza[x][y];
        plansza[x][y] = PUSTE;
        wypisz(plansza);
    }
    if (res >= WYGRANA)
        printf("AI wygrywa\n");
    if (res <= PRZEGRANA)
        printf("Brawo, wygrałeś!");
    return 0;
}