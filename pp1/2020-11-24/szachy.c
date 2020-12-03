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
#define BLANK 12

#define WIN 1000
#define LOSE -1000

int directions[] = {8, 8, 4, 4, 8, 3, 8, 8, 4, 4, 8, 3, 0};
int distances[] = {2, 8, 8, 8, 2, 2, 2, 8, 8, 8, 2, 2, 0};

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

int board[8][8] = {
    {WIEZA_K, SKOCZEK_K, GONIEC_K, HETMAN_K, KROL_K, GONIEC_K, SKOCZEK_K, WIEZA_K},
    {PIONEK_K, PIONEK_K, PIONEK_K, PIONEK_K, PIONEK_K, PIONEK_K, PIONEK_K, PIONEK_K},
    {BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK},
    {BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK},
    {BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK},
    {BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK},
    {PIONEK, PIONEK, PIONEK, PIONEK, PIONEK, PIONEK, PIONEK, PIONEK},
    {WIEZA, SKOCZEK, GONIEC, HETMAN, KROL, GONIEC, SKOCZEK, WIEZA}};

int heuristic[13][8][8] = {
    // ------------------------------ PLAYER ------------------------------ //
    // król
    {{LOSE, LOSE, LOSE, LOSE, LOSE, LOSE, LOSE, LOSE},
     {LOSE, LOSE, LOSE, LOSE, LOSE, LOSE, LOSE, LOSE},
     {LOSE, LOSE, LOSE, LOSE, LOSE, LOSE, LOSE, LOSE},
     {LOSE, LOSE, LOSE, LOSE, LOSE, LOSE, LOSE, LOSE},
     {LOSE, LOSE, LOSE, LOSE, LOSE, LOSE, LOSE, LOSE},
     {LOSE, LOSE, LOSE, LOSE, LOSE, LOSE, LOSE, LOSE},
     {LOSE, LOSE, LOSE, LOSE, LOSE, LOSE, LOSE, LOSE},
     {LOSE, LOSE, LOSE, LOSE, LOSE, LOSE, LOSE, LOSE}},
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
    {{WIN, WIN, WIN, WIN, WIN, WIN, WIN, WIN},
     {WIN, WIN, WIN, WIN, WIN, WIN, WIN, WIN},
     {WIN, WIN, WIN, WIN, WIN, WIN, WIN, WIN},
     {WIN, WIN, WIN, WIN, WIN, WIN, WIN, WIN},
     {WIN, WIN, WIN, WIN, WIN, WIN, WIN, WIN},
     {WIN, WIN, WIN, WIN, WIN, WIN, WIN, WIN},
     {WIN, WIN, WIN, WIN, WIN, WIN, WIN, WIN},
     {WIN, WIN, WIN, WIN, WIN, WIN, WIN, WIN}},
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
    // BLANK
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

    12 - field BLANK
*/

const char *chessman(int field)
{
    if (field == KROL)
        return "♛";
    if (field == HETMAN)
        return "♚";
    if (field == WIEZA)
        return "♜";
    if (field == GONIEC)
        return "♝";
    if (field == SKOCZEK)
        return "♞";
    if (field == PIONEK)
        return "♟";

    if (field == KROL_K)
        return "♕";
    if (field == HETMAN_K)
        return "♔";
    if (field == WIEZA_K)
        return "♖";
    if (field == GONIEC_K)
        return "♗";
    if (field == SKOCZEK_K)
        return "♘";
    if (field == PIONEK_K)
        return "♙";

    // default fallback
    return " ";
}

int estimateBoard(int board[8][8])
{
    int result = 0;
    for (int x = 0; x < 8; x++)
        for (int y = 0; y < 8; y++)
            result += heuristic[board[x][y]][x][y];
    return result;
}

int najlepszy(int board[8][8], int depth, int *x, int *y, int *dir, int *dist)
{
    int tmp_x,
        tmp_y,
        tmp_dir,
        tmp_dist,
        px,
        py,
        dx,
        dy,
        direction,
        distance,
        result = estimateBoard(board),
        wmax,
        wmin,
        ruch_fig,
        bita_fig;

    if (depth == 0 || 2 * result > WIN || 2 * result < LOSE)
        return result;

    if (depth % 2 == 0) // ruch komputera
    {
        for (px = 0, wmax = 100 * LOSE; px < 8; px++)
            for (py = 0; py < 8; py++)
                // na polu figura komputera
                if (board[px][py] >= KROL_K && board[px][py] <= PIONEK_K)
                    for (direction = 0; direction < directions[board[px][py]]; direction++)
                        for (distance = 1; distance < distances[board[px][py]]; distance++)
                        {
                            dx = (distance - 1) * WX[board[px][py]][direction];
                            dy = (distance - 1) * WY[board[px][py]][direction];
                            // jeśli po drodze nieBLANK
                            if (distance >= 2 && board[px + dx][py + dy] != BLANK)
                                break;
                            dx = distance * WX[board[px][py]][direction];
                            dy = distance * WY[board[px][py]][direction];
                            // ruch mieści się w szachownicy
                            if (px + dx >= 0 && px + dx < 8 && py + dy >= 0 && py + dy < 8)
                                // docelowe ple puste lub figura przeciwnika
                                if (board[px + dx][py + dy] == BLANK || board[px + dx][py + dy] <= PIONEK)
                                    // warunek dodatkowy dla piona (bicie w bok, ruch naprzód)
                                    if (board[px][py] != PIONEK_K || (board[px + dx][py + dy] == BLANK && dx == 0) || (board[px + dx][py + dy] != BLANK && dx != 0))
                                    {
                                        ruch_fig = board[px][py];
                                        bita_fig = board[px + dx][py + dy]; //ruch
                                        board[px + dx][py + dy] = board[px][py];
                                        board[px][py] = BLANK;
                                        if (board[px + dx][py + dy] == PIONEK_K && py + dy == 7) // pion doszedł do końca to
                                            board[px + dx][py + dy] = 7;                   // wymiana na hetmana
                                        result = najlepszy(board, depth - 1, &tmp_x, &tmp_y, &tmp_dir, &tmp_dist);
                                        // cofnięcie ruchu
                                        board[px][py] = ruch_fig;
                                        board[px + dx][py + dy] = bita_fig;
                                        if (result >= wmax)
                                        {
                                            wmax = result;
                                            *x = px;
                                            *y = py;
                                            *dir = direction;
                                            *dist = distance;
                                        }
                                    }
                        }
        return wmax; // należy również przewidzieć pat
    }
    else // ruch przeciwnika
    {
        for (px = 0, wmin = 100 * WIN; px < 8; px++)
            for (py = 0; py < 8; py++)
                // na polu figura przeciwnika
                if (board[px][py] <= PIONEK)
                    for (direction = 0; direction < directions[board[px][py]]; direction++)
                        for (distance = 1; distance < distances[board[px][py]]; distance++)
                        {
                            dx = (distance - 1) * WX[board[px][py]][direction];
                            dy = (distance - 1) * WY[board[px][py]][direction];
                            // jeśli po drodze nieBLANK
                            if (distance >= 2 && board[px + dx][py + dy] != BLANK)
                                break;
                            dx = distance * WX[board[px][py]][direction];
                            dy = distance * WY[board[px][py]][direction];
                            // ruch mieści się w szachownicy
                            if (px + dx >= 0 && px + dx < 8 && py + dy >= 0 && py + dy < 8)
                                // docelowe pole puste lub figura przeciwnika
                                if (board[px + dx][py + dy] >= KROL_K)
                                    // warunek dodatkowy dla piona (bicie w bok, ruch naprzód)
                                    if (board[px][py] != PIONEK || (board[px + dx][py + dy] == BLANK && dx == 0) || (board[px + dx][py + dy] != BLANK && dx != 0))
                                    {
                                        ruch_fig = board[px][py];
                                        bita_fig = board[px + dx][py + dy];
                                        board[px + dx][py + dy] = board[px][py];
                                        board[px][py] = BLANK;
                                        // jeśli pion doszedł do końca to wymiana na hetmana
                                        if (board[px + dx][py + dy] == PIONEK && py + dy == 0)
                                            board[px + dx][py + dy] = 1;
                                        result = najlepszy(board, depth - 1, &tmp_x, &tmp_y, &tmp_dir, &tmp_dist);
                                        // cofnięcie ruchu
                                        board[px][py] = ruch_fig;
                                        board[px + dx][py + dy] = bita_fig;
                                        if (result <= wmin)
                                        {
                                            wmin = result;
                                            *x = px;
                                            *y = py;
                                            *dir = direction;
                                            *dist = distance;
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

    printf("Move from (a1): ");
    scanf("%c%d%c", &tmpFrom, &rowFrom, &ch);
    rowFrom--;
    if (tmpFrom >= 'a' && tmpFrom <= 'h')
        colFrom = tmpFrom - 'a';
    else if (tmpFrom >= 'A' && tmpFrom <= 'H')
        colFrom = tmpFrom - 'A';

    if (rowFrom < 0 || rowFrom >= 8 || colFrom < 0 || colFrom >= 8 || board[rowFrom][colFrom] >= KROL_K)
    {
        printf("Invalid value! Try again!\n");
        getMove(board);
    }

    printf("Move to (a1): ");
    scanf("%c%d%c", &tmpTo, &rowTo, &ch);
    rowTo--;
    if (tmpTo >= 'a' && tmpTo <= 'h')
        colTo = tmpTo - 'a';
    else if (tmpTo >= 'A' && tmpTo <= 'H')
        colTo = tmpTo - 'A';

    if (rowTo < 0 || rowTo >= 8 || colTo < 0 || colTo >= 8)
    {
        printf("Invalid value! Try again!\n");
        getMove(board);
    }

    if (board[rowTo][colTo] <= PIONEK)
    {
        printf("This field is already taken! Try again!\n");
        getMove(board);
    }

    board[rowTo][colTo] = board[rowFrom][colFrom];
    board[rowFrom][colFrom] = BLANK;
}

void printBoard(int board[8][8])
{
    system("clear");
    printf("   | A | B | C | D | E | F | G | H |\n");
    printf("---+---+---+---+---+---+---+---+---+\n");
    for (int row = 0; row < 8; row++)
    {
        printf(" %d |", row + 1);
        for (int col = 0; col < 8; col++)
        {
            int field = board[row][col];
            printf(" %s |", chessman(field));
        }
        printf("\n---+---+---+---+---+---+---+---+---+\n");
        // printf("\n");
    }
}

int main(void)
{
    int koniec = 0,
        res = 0;
    printBoard(board);
    while (!koniec)
    {
        int x = 0, y = 0, dir = 0, dist = 0;
        getMove(board);
        printBoard(board);

        res = najlepszy(board, 6, &x, &y, &dir, &dist);

        if (abs(res) >= WIN)
            break;

        int px = WX[board[x][y]][dir] * dist;
        int py = WY[board[x][y]][dir] * dist;
        board[x + px][y + py] = board[x][y];
        board[x][y] = BLANK;
        printBoard(board);
    }
    if (res >= WIN)
        printf("You lost.\n");
    if (res <= LOSE)
        printf("You won!\n");
    return 0;
}