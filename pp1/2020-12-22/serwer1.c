#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>

int main(void)
{
    int status,
        gniazdo,
        dlugosc,
        nr = 0,
        end = 1,
        gniazdo2;
    struct sockaddr_in srv, cli;
    char buf[200];

    gniazdo = socket(AF_INET, SOCK_STREAM, 0);
    if (gniazdo == -1)
    {
        printf("Socket error!\n");
        return 0;
    }

    srv.sin_family = AF_INET;
    srv.sin_port = htons(9000);
    srv.sin_addr.s_addr = inet_addr("77.55.223.255");

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

    while (end)
    {
        dlugosc = sizeof cli;
        gniazdo2 = accept(gniazdo, (struct sockaddr *)&cli, (socklen_t *)&dlugosc);
        if (gniazdo2 == -1)
        {
            printf("Accept error!\n");
            return 0;
        }
        read(gniazdo2, buf, sizeof buf);
        if (buf[0] == 'Q')
        {
            sprintf(buf, "Terminating server...\n");
            end = 0;
        }
        else if (buf[0] == 'N')
        {
            sprintf(buf, "Jestes klientem nr %d\0", nr++);
        }
        else
        {
            sprintf(buf, "Nie rozumiem pytania\0");
        }
        write(gniazdo2, buf, strlen(buf));
        close(gniazdo2);
    }
    close(gniazdo);
}