#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <sys/time.h>

void sendData(int serversock, int frames, int window) {
    printf("Sending data...\n");
    char clientmessage[1000];
    int ack, i = 0, n, k, w1 = 0, w2 = window - 1, j, flag = 0;
    struct timeval timeout;

    timeout.tv_sec = 3;
    timeout.tv_usec = 0;
    setsockopt(serversock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));

    while (1) {
        for (i = 0; i < frames && i <= w2; i++) {
            snprintf(clientmessage, sizeof(clientmessage), "%d", i);
            k = send(serversock, clientmessage, sizeof(clientmessage), 0);
            printf("Frame %d sent\n", i);
        }
        while (1) {
            if (w2 - w1 != window - 1 && flag == 0 && i != frames) {
                snprintf(clientmessage, sizeof(clientmessage), "%d", i);
                k = send(serversock, clientmessage, sizeof(clientmessage), 0);
                printf("Frame %d sent\n", i);
                w2++;
                i++;
            }
            flag = 0;
            n = recv(serversock, clientmessage, sizeof(clientmessage), 0);
            ack = atoi(clientmessage);
            if (n > 0) {
                if (ack + 1 == frames) {
                    printf("Ack received %d\nEXIT\n", ack);
                    strcpy(clientmessage, "EXIT");
                    k = send(serversock, clientmessage, sizeof(clientmessage), 0);
                    return;
                }
                if (ack == w1) {
                    w1++;
                    printf("Ack received %d\n", ack);
                }
            } 
            else {
                printf("Ack not received for %d\nRESENDING ...\n", w1);
                for (j = w1; j < frames && j < w1 + window; j++) {
                    snprintf(clientmessage, sizeof(clientmessage), "%d", j);
                    k = send(serversock, clientmessage, sizeof(clientmessage), 0);
                    printf("Frame %d sent\n", j);
                }
                flag = 1;
            }
        }
    }
}

void main() {
    int serversock, frames, window;
    struct sockaddr_in serveraddr;

    serversock = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serveraddr.sin_port = htons(2000);

    connect(serversock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

    printf("Enter the number of frames: ");
    scanf("%d", &frames);
    printf("Enter the window size: ");
    scanf("%d", &window);

    sendData(serversock, frames, window);

    close(serversock);
}
