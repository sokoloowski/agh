#include <stdio.h>
#include <WinSock2.h>
#include <string.h>

#define PLAYER 'x'
#define AI 'o'
#define BLANK '_'

//Klient  Serwer
// 9001 <- 9001
// 9000 -> 9000

int optimalMove;

int estimateBoard(char board[9])
{
    if (
            (board[0] == PLAYER && board[1] == PLAYER && board[2] == PLAYER) ||
            (board[3] == PLAYER && board[4] == PLAYER && board[5] == PLAYER) ||
            (board[6] == PLAYER && board[7] == PLAYER && board[8] == PLAYER) ||
            (board[0] == PLAYER && board[3] == PLAYER && board[6] == PLAYER) ||
            (board[1] == PLAYER && board[4] == PLAYER && board[7] == PLAYER) ||
            (board[2] == PLAYER && board[5] == PLAYER && board[8] == PLAYER) ||
            (board[0] == PLAYER && board[4] == PLAYER && board[8] == PLAYER) ||
            (board[2] == PLAYER && board[4] == PLAYER && board[6] == PLAYER))
        return -1;
    else if (
            (board[0] == AI && board[1] == AI && board[2] == AI) ||
            (board[3] == AI && board[4] == AI && board[5] == AI) ||
            (board[6] == AI && board[7] == AI && board[8] == AI) ||
            (board[0] == AI && board[3] == AI && board[6] == AI) ||
            (board[1] == AI && board[4] == AI && board[7] == AI) ||
            (board[2] == AI && board[5] == AI && board[8] == AI) ||
            (board[0] == AI && board[4] == AI && board[8] == AI) ||
            (board[2] == AI && board[4] == AI && board[6] == AI))
        return 1;
    else
        return 0;
}

int minimax(char board[9], int player)
{
    if (estimateBoard(board) != 0)
    {
        return estimateBoard(board) * player; // -1 * -1 || 1 * 1
    }

    int localMove = -1;
    int score = -2;

    for (int i = 0; i < 9; i++) {
        int tmp = board[i];
        if (board[i] == BLANK) {
            if (player == 1) {
                board[i] = AI;
            } else {
                board[i] = PLAYER;
            }
            int scoreForTheMove = -minimax(board, -player);
            if (scoreForTheMove > score)
            {
                score = scoreForTheMove;
                localMove = i;
            }
            board[i] = BLANK;
        }
    }
    optimalMove = localMove;
    if (optimalMove == -1)
    {
        return 0; // No move - it's a draw
    }
    return score;
}


int main(void)
{
    int status, dlugosc, end = 0;
    SOCKET gniazdo, gniazdo2;
    struct sockaddr_in srv, cli;
    char buf[9];
    char board[9] = {
            BLANK, BLANK, BLANK,
            BLANK, BLANK, BLANK,
            BLANK, BLANK, BLANK};
    WSADATA wsadata;

    if (WSAStartup(MAKEWORD(2, 0), &wsadata)) {
        return 0;
    }

    while (!end) {
//        Reciever part
        gniazdo = socket(AF_INET, SOCK_STREAM, 0);
        if (gniazdo == -1)
        {
            printf("Socket error!\n");
            return 0;
        }

        srv.sin_family = AF_INET;
        srv.sin_port = htons(9000);
        srv.sin_addr.s_addr = inet_addr("127.0.0.1");

        status = bind(gniazdo, (struct sockaddr *)&srv, sizeof srv);
        if (status == -1)
        {
            printf("Bind error!\n");
            return 0;
        }

        status = listen(gniazdo, 10);
        if (status == -1)
        {
            printf("Listen error\n");
            return 0;
        }

        while (1) {
            dlugosc = sizeof cli;
            gniazdo2 = accept(gniazdo, (struct sockaddr *)&cli, (int *)&dlugosc);
            if (gniazdo2 == -1)
            {
                printf("Accept error!\n");
                return 0;
            }
            status = recv(gniazdo2, buf, sizeof buf, 0);
            buf[status] = '\0';
            if (buf[0] != 'b') {
                int userMove = (buf[0] - '0') - 1;
                if (userMove >= 0 && userMove <= 8) {
                    board[userMove] = PLAYER;
                    if (estimateBoard(board) == -1)
                    {
                        end = 1;
                        sprintf(buf, "You won!");
                        send(gniazdo2, buf, strlen(buf), 0);
                        closesocket(gniazdo2);
                        break;
                    }

                    printf("Processing...\n");
                    minimax(board, 1);
                    board[optimalMove] = AI;

                    if (estimateBoard(board) == 1)
                    {
                        end = 1;
                        sprintf(buf, "You lost.");
                        send(gniazdo2, buf, strlen(buf), 0);
                        closesocket(gniazdo2);
                        break;
                    }
                    printf("----------------\n\n");

                    end = 1;
                    for (int i = 0; i < 9; i++)
                        if (board[i] == BLANK)
                            end = 0;
                    if (end == 1) {
                        sprintf(buf, "Draw.");
                        send(gniazdo2, buf, strlen(buf), 0);
                        closesocket(gniazdo2);
                        break;
                    }
                }
            }
            sprintf(buf, "%s", board);
            send(gniazdo2, buf, strlen(buf), 0);
            closesocket(gniazdo2);
            break;
        }
        closesocket(gniazdo);
    }
    return 0;
}