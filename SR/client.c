#include<netdb.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<time.h>
#include<sys/time.h>
#include <netinet/in.h>

struct timeval timeout;

void func(int serversock, int frames, int ws){
    char buff[1000];
    int ack, i = 0, n, w1 = 1, w2 = ws;

    setsockopt(serversock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));

    // Send initial window
    for (i = 1; i <= frames && i <= w2; i++) {
        bzero(buff, sizeof(buff));
        snprintf(buff, sizeof(buff), "%d", i);
        send(serversock, buff, strlen(buff), 0);
        printf("Frame %d sent\n", i);
    }

    while (1) {
        while (w2 - w1 != ws - 1 && w2 < frames) {
            w2++;
            bzero(buff, sizeof(buff));
            snprintf(buff, sizeof(buff), "%d", w2);
            send(serversock, buff, strlen(buff), 0);
            printf("Frame %d sent\n", w2);
        }

        n = recv(serversock, buff, sizeof(buff), 0);
        if (n < 0) {
            printf("Ack not received for %d\nRESENDING ...\n", w1);
            bzero(buff, sizeof(buff));
            snprintf(buff, sizeof(buff), "%d", w1);
            send(serversock, buff, strlen(buff), 0);
        } else {
            ack = atoi(buff);
            if (ack < 0) {
                printf("Ack not received for %d\nRESENDING ...\n", -ack);
                bzero(buff, sizeof(buff));
                snprintf(buff, sizeof(buff), "%d", -ack);
                send(serversock, buff, strlen(buff), 0);
            } else if (ack >= frames) {
                printf("Ack received %d\nEXIT\n", ack);
                bzero(buff, sizeof(buff));
                strcpy(buff, "EXIT");
                send(serversock, buff, strlen(buff), 0);
                break;
            } else if (ack >= w1 && ack <= w2) {
                w1 = ack + 1;
                printf("Ack received %d\n", ack);
            }
        }
    }
}

void main(){
    int serversock;
    struct sockaddr_in serveraddr;

    serversock = socket(AF_INET, SOCK_STREAM, 0);

    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    serveraddr.sin_port = htons(2000);

    timeout.tv_sec = 3;
    timeout.tv_usec = 0;

    connect(serversock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

    int frames, ws;
    printf("Enter the number of frames to be sent\n");
    scanf("%d", &frames);
    printf("Enter the window size\n");
    scanf("%d", &ws);

    func(serversock, frames, ws);
    close(serversock);
}
