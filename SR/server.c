#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <time.h>

void main() {
    int serversock, clientsock, len;
    struct sockaddr_in serveraddr, clientaddr;
    char buff[1000];
    int expected = 1, frame;
    int ws, n;

    serversock = socket(AF_INET, SOCK_STREAM, 0);

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(2000);

    bind(serversock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    listen(serversock, 5);

    len = sizeof(clientaddr);
    clientsock = accept(serversock, (struct sockaddr*)&clientaddr, &len);

    srand(time(0));

    printf("Enter the window size of the server: ");
    scanf("%d", &ws);

    while (1) {
        bzero(buff, sizeof(buff));
        n = recv(clientsock, buff, 2, 0);
        
        if (strcmp("EXIT", buff) == 0) {
            printf("Exit\n");
            break;
        }
        
        frame = atoi(buff);

        if (frame == expected) {
            printf("Frame %d received acknowledgement sent for %d\n", frame, frame);
            snprintf(buff, sizeof(buff), "%d", frame);
            send(clientsock, buff, strlen(buff), 0);
            expected++;
        } else if (frame > expected) {
            printf("Frame %d received instead of %d\n", frame, expected);
            snprintf(buff, sizeof(buff), "%d", -expected);
            printf("Sending NAK -%d\n", expected);
            send(clientsock, buff, strlen(buff), 0);
        }
    }

    close(clientsock);
    close(serversock);
}