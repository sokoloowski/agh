#include <stdio.h>

#if defined __linux__
#define IS_LINUX 1
#elif defined _WIN32
#define IS_LINUX 0
#endif

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define DEFAULT "\033[0m"

#define PLAYER -1
#define AI 1
#define INF 1000000
#define TO_WIN 5
#define SIZE 10

int scaleFactor[5] = {1, 5, 20, 50, 1000};
int optimalX,
    optimalY;

int arr[SIZE][SIZE] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

char symbol(int player)
{
    return player == PLAYER ? 'o' : (player == AI ? 'x' : ' ');
}

int min(int a, int b)
{
    if (a < b)
        return a;
    else
        return b;
}

int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

void printBoard(int board[SIZE][SIZE])
{
    if (IS_LINUX)
        system("clear"); // for Unix
    else
        system("cls"); // for Windows
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            printf(" ");
            if (board[i][j] == AI && IS_LINUX)
            {
                printf(RED);
            }
            else if (board[i][j] == PLAYER && IS_LINUX)
            {
                printf(GREEN);
            }
            printf("%c ", !board[i][j] ? ' ' : symbol(board[i][j]));
            if (IS_LINUX)
                printf(DEFAULT);
            if (j != SIZE - 1)
                printf("|");
        }
        if (i != SIZE - 1)
        {
            printf("\n---");
            for (int j = 0; j < SIZE - 1; j++)
                printf("+---");
            printf("\n");
        }
    }
    printf("\n");
}

int estimateBoard(int board[SIZE][SIZE], int player)
{
    int result = 0;
    for (int x = 0; x < SIZE; x++)
        for (int y = 0; y < SIZE; y++)
            if (board[x][y] == player)
            {
                // check horizontal
                for (int p = 0; p < TO_WIN && y + p < SIZE; p++)
                {
                    int current = board[x][y + p];

                    // if current and original are the same
                    if (current == board[x][y])
                    {
                        if (abs(result) < scaleFactor[p])
                            result = scaleFactor[p] * board[x][y];
                    }
                    // if current and original are opposite
                    else if (abs(current) == abs(board[x][y]))
                    {
                        if (abs(result) == scaleFactor[p] && p != TO_WIN - 1)
                        {
                            if (y - 1 >= 0 && board[x][y - 1] == current)
                                result > 0 ? result-- : result++;
                            result > 0 ? result-- : result++;
                        }
                        break;
                    }
                    else if (!current)
                    {
                        break;
                    }
                }

                // check vertical
                for (int p = 0; p < TO_WIN && x + p < SIZE; p++)
                {
                    int current = board[x + p][y];

                    // if current and original are the same
                    if (current == board[x][y])
                    {
                        if (abs(result) < scaleFactor[p])
                            result = scaleFactor[p] * board[x][y];
                    }
                    // if current and original are opposite
                    else if (abs(current) == abs(board[x][y]))
                    {
                        if (abs(result) == scaleFactor[p] && p != TO_WIN - 1)
                        {
                            if (x - 1 >= 0 && board[x - 1][y] == current)
                                result > 0 ? result-- : result++;
                            result > 0 ? result-- : result++;
                        }
                        break;
                    }
                    else if (!current)
                    {
                        p = TO_WIN;
                        break;
                    }
                }

                // check diagonal top left to bottom right
                for (int p = 0; p < TO_WIN && x + p < SIZE && y + p < SIZE; p++)
                {
                    int current = board[x + p][y + p];

                    // if current and original are the same
                    if (current == board[x][y])
                    {
                        if (abs(result) < scaleFactor[p])
                            result = scaleFactor[p] * board[x][y];
                    }
                    // if current and original are opposite
                    else if (abs(current) == abs(board[x][y]))
                    {
                        if (abs(result) == scaleFactor[p] && p != TO_WIN - 1)
                        {
                            if (x - 1 >= 0 && y - 1 >= 0 && board[x - 1][y - 1] == current)
                                result > 0 ? result-- : result++;
                            result > 0 ? result-- : result++;
                        }
                        break;
                    }
                    else if (!current)
                    {
                        p = TO_WIN;
                        break;
                    }
                }

                // check diagonal bottom left to top right
                for (int p = 0; p < TO_WIN && x >= TO_WIN - 1 && y + p < SIZE; p++)
                {
                    int current = board[x - p][y + p];

                    // if current and original are the same
                    if (current == board[x][y])
                    {
                        if (abs(result) < scaleFactor[p])
                            result = scaleFactor[p] * board[x][y];
                    }
                    // if current and original are opposite
                    else if (abs(current) == abs(board[x][y]))
                    {
                        if (abs(result) == scaleFactor[p] && p != TO_WIN - 1)
                        {
                            if (x + 1 < SIZE && y - 1 >= 0 && board[x + 1][y - 1] == current)
                                result > 0 ? result-- : result++;
                            result > 0 ? result-- : result++;
                        }
                        break;
                    }
                    else if (!current)
                    {
                        p = TO_WIN;
                        break;
                    }
                }
            }

    // printf("estimateBoard: %d\n", result);
    return result;
}

int minimax(int board[SIZE][SIZE], int player, int depth, int alpha, int beta)
{
    if (estimateBoard(board, player) == scaleFactor[TO_WIN - 1] * player || depth == 0)
    {
        // printf("estimateBoard: %d, Głębokość: %d\n", estimateBoard(board), depth);
        return estimateBoard(board, -player) * player;
    }

    int localX = -1,
        localY = -1,
        minEval = INF,
        maxEval = -INF;

    if (player == AI)
    {
        for (int x = 0; x < SIZE; x++)
            for (int y = 0; y < SIZE; y++)
                if (!board[x][y])
                {
                    board[x][y] = player;
                    int eval = minimax(board, player == PLAYER ? AI : PLAYER, depth - 1, alpha, beta);
                    maxEval = max(maxEval, eval);
                    // if (maxEval <= eval)
                    //     maxEval = eval, localX = x, localY = y;
                    // alpha = max(alpha, eval);
                    if (alpha <= eval)
                        alpha = eval, localX = x, localY = y;
                    board[x][y] = 0;
                    if (alpha >= beta)
                        break;
                }
        optimalX = localX;
        optimalY = localY;
        return maxEval;
    }
    else if (player == PLAYER)
    {
        for (int x = 0; x < SIZE; x++)
            for (int y = 0; y < SIZE; y++)
                if (!board[x][y])
                {
                    board[x][y] = player;
                    int eval = minimax(board, player == PLAYER ? AI : PLAYER, depth - 1, alpha, beta);
                    minEval = min(minEval, eval);
                    // if (minEval >= eval)
                    //     minEval = eval, localX = x, localY = y;
                    // beta = min(beta, eval);
                    if (beta >= eval)
                        beta = eval, localX = x, localY = y;
                    board[x][y] = 0;
                    if (alpha >= beta)
                        break;
                }
        optimalX = localX;
        optimalY = localY;
        return minEval;
    }
}

void getMove(int board[SIZE][SIZE])
{
    int poz = 0;
    printf("Enter the number of the field on the board: ");
    scanf("%d", &poz);
    if (poz >= 1 && poz <= 100)
    {
        int x = (poz - 1) / SIZE;
        int y = (poz - 1) % SIZE;
        if (!board[x][y])
        {
            board[x][y] = PLAYER;
        }
        else
        {
            printBoard(board);
            if (IS_LINUX)
                printf(RED);
            printf("This field is already taken!");
            if (IS_LINUX)
                printf(DEFAULT);
            printf("\n");
            getMove(board);
        }
    }
    else
    {
        printBoard(board);
        if (IS_LINUX)
            printf(RED);
        printf("Invalid value!");
        if (IS_LINUX)
            printf(DEFAULT);
        printf("\n");
        getMove(board);
    }
}

int main(void)
{
    printBoard(arr);

    int end = 0;
    while (!end)
    {
        // Debug
        // printf("estimateBoard gracza:\t%d\n", -estimateBoard(arr, PLAYER));
        // printf("estimateBoard AI:\t%d\n", estimateBoard(arr, AI));

        getMove(arr);

        printBoard(arr);

        if (estimateBoard(arr, PLAYER) == PLAYER * scaleFactor[TO_WIN - 1])
        {
            printf("You won!\n");
            return 0;
        }

        // Debug
        // printf("estimateBoard gracza:\t%d\n", -estimateBoard(arr, PLAYER));
        // printf("estimateBoard AI:\t%d\n", estimateBoard(arr, AI));

        minimax(arr, AI, 4, -INF, INF);
        arr[optimalX][optimalY] = AI;
        printBoard(arr);

        if (estimateBoard(arr, AI) == AI * scaleFactor[TO_WIN - 1])
        {
            printf("You lost...\n");
            return 0;
        }

        end = 1;
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                if (!arr[i][j])
                    end = 0;
    }
    printf("Draw.\n");
    return 0;
}