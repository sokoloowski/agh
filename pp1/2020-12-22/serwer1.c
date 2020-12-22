#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>

int main(void)
{
    int status, gniazdo;
    struct sockaddr_in srv;
    char buf[200];

    gniazdo = socket(AF_INET, SOCK_STREAM, 0);
    if (gniazdo == -1)
    {
        printf("Socket error!\n");
        return 0;
    }

    srv.sin_family = AF_INET;
    srv.sin_port = htons(9000);
    srv.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Podaj tekst: ");
    fgets(buf, sizeof buf, stdin);

    status = connect(gniazdo, (struct sockaddr *)&srv, sizeof srv);
    if (status < 0)
    {
        printf("Connect error!\n");
        return 0;
    }

    status = write(gniazdo, buf, strlen(buf));
    status = read(gniazdo, buf, sizeof buf);
    buf[status] = '\0';
    printf("Otrzymalem: %s\n", buf);

    close(gniazdo);
}