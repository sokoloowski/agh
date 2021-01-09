#include <stdio.h>
#include <WinSock2.h>
#include <string.h>

int main(void)
{
    int status, dlugosc;
    SOCKET gniazdo, gniazdo2;
    struct sockaddr_in srv, cli;
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

        while (1)
        {
            dlugosc = sizeof cli;
            gniazdo2 = accept(gniazdo, (struct sockaddr *)&cli, (int *)&dlugosc);
            if (gniazdo2 == -1)
            {
                printf("Accept error!\n");
                return 0;
            }
            status = recv(gniazdo2, buf, sizeof buf, 0);
            buf[status] = '\0';
            printf("%s", buf);

            FILE *plik;
            plik = fopen(strtok(buf, "\n"), "r");
            if (plik == 0) {
                sprintf(buf, "Wystapil blad podczas otwierania pliku\n");
                send(gniazdo2, buf, strlen(buf), 0);
                closesocket(gniazdo2);
                continue;
            }
            char tmp[1024] = "";
            int c = fgetc((FILE*)plik),
                k = 0;
            while (c != EOF) {
                tmp[k] = c;
                c = fgetc((FILE*)plik);
                k++;
            }
            fclose(plik);

            fflush(stdin);
            sprintf(buf, "%s", tmp);
            send(gniazdo2, buf, strlen(buf), 0);
            closesocket(gniazdo2);
            break;
        }
        closesocket(gniazdo);
    }
    return 0;
}