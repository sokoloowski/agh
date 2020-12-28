#include <stdio.h>
#include <WinSock2.h>
#include <string.h>

int main(void)
{
    int status;
    SOCKET gniazdo;
    struct sockaddr_in srv;
    char buf[1025];
    WSADATA wsadata;

    if (WSAStartup(MAKEWORD(2, 0), &wsadata)) {
        return 0;
    }

    while (1)
    {
        gniazdo = socket(AF_INET, SOCK_STREAM, 0);
        if (gniazdo == -1)
        {
            printf("Socket error!\n");
            return 0;
        }

        srv.sin_family = AF_INET;
        srv.sin_port = htons(9000);
        srv.sin_addr.s_addr = inet_addr("127.0.0.1");

        printf("podaj: ");
        fgets(buf, sizeof buf, stdin);

        status = connect(gniazdo, (struct sockaddr *)&srv, sizeof srv);
        if (status < 0)
        {
            printf("Connect error!\n");
            return 0;
        }

        send(gniazdo, buf, strlen(buf), 0);
        status = recv(gniazdo, buf, sizeof buf, 0);
        if (status <= 1024) {
            buf[status] = '\0';
            printf("%s\n", buf);
        } else {
            printf("Podany plik jest za duży!\n");
        }
        closesocket(gniazdo);
    }
    return 0;
}