#include <stdio.h>
#include <WinSock2.h>
#include <string.h>

//Klient  Serwer
// 9001 <- 9001
// 9000 -> 9000

void printBoard(char board[9]) {
    printf("--------------------\n\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", board[(3 * i) + j]);
            if (j != 2) {
                printf("|");
            } else {
                printf("\n");
            }
        }
        if (i != 2) {
            printf("---+---+---\n");
        }
    }
}

int main(void)
{
    int status, end = 0;
    SOCKET gniazdo;
    struct sockaddr_in srv;
    char buf[9];
    WSADATA wsadata;

    if (WSAStartup(MAKEWORD(2, 0), &wsadata)) {
        return 0;
    }

//    Ask for board
    gniazdo = socket(AF_INET, SOCK_STREAM, 0);
    if (gniazdo == -1)
    {
        printf("Socket error!\n");
        return 0;
    }

    srv.sin_family = AF_INET;
    srv.sin_port = htons(9000);
    srv.sin_addr.s_addr = inet_addr("127.0.0.1");

    sprintf(buf, "b");

    status = connect(gniazdo, (struct sockaddr *)&srv, sizeof srv);
    if (status < 0)
    {
        printf("Connect error!\n");
        return 0;
    }

    send(gniazdo, buf, strlen(buf), 0);
    recv(gniazdo, buf, sizeof buf, 0);
    printBoard(buf);
    closesocket(gniazdo);

    while (!end)
    {
//        Sender part
        gniazdo = socket(AF_INET, SOCK_STREAM, 0);
        if (gniazdo == -1)
        {
            printf("Socket error!\n");
            return 0;
        }

        srv.sin_family = AF_INET;
        srv.sin_port = htons(9000);
        srv.sin_addr.s_addr = inet_addr("127.0.0.1");

        printf("Wybierz pole: ");
        fgets(buf, sizeof buf, stdin);

        status = connect(gniazdo, (struct sockaddr *)&srv, sizeof srv);
        if (status < 0)
        {
            printf("Connect error!\n");
            return 0;
        }

        send(gniazdo, buf, strlen(buf), 0);
        status = recv(gniazdo, buf, sizeof buf, 0);
        if (buf[0] == 'Y' || buf[0] == 'D') {
            buf[status] = '\0';
            printf("%s", buf);
            end = 1;
        } else {
            printBoard(buf);
        }
        closesocket(gniazdo);
    }
    return 0;
}