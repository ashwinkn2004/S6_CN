#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <sys/time.h>

#define MAX 80

void sendData(int sersock, int frames, int window) {
    char buff[MAX];
    int ack, i = 0, n, k, w1 = 0, w2 = window - 1, j, flag = 0;
    struct timeval timeout;
    timeout.tv_sec = 3;
    timeout.tv_usec = 0;
    if (setsockopt(sersock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout)) < 0)
        perror("setsockopt(SO_RCVTIMEO) failed");
    while (1) {
        for (i = 0; i < frames && i <= w2; i++) {
            snprintf(buff, sizeof(buff), "%d", i);
            k = send(sersock, buff, sizeof(buff), 0);
            printf("Frame %d sent\n", i);
        }
        while (1) {
            if (w2 - w1 != window - 1 && flag == 0 && i != frames) {
                snprintf(buff, sizeof(buff), "%d", i);
                k = send(sersock, buff, sizeof(buff), 0);
                printf("Frame %d sent\n", i);
                w2++;
                i++;
            }
            flag = 0;
            n = recv(sersock, buff, MAX, 0);
            ack = atoi(buff);
            if (n > 0) {
                if (ack + 1 == frames) {
                    printf("Ack received %d\nEXIT\n", ack);
                    strcpy(buff, "EXIT");
                    k = send(sersock, buff, sizeof(buff), 0);
                    return;
                }
                if (ack == w1) {
                    w1++;
                    printf("Ack received %d\n", ack);
                }
            } else {
                printf("Ack not received for %d\nRESENDING ...\n", w1);
                for (j = w1; j < frames && j < w1 + window; j++) {
                    snprintf(buff, sizeof(buff), "%d", j);
                    k = send(sersock, buff, sizeof(buff), 0);
                    printf("Frame %d sent\n", j);
                }
                flag = 1;
            }
        }
    }
}

void main() {
    int sersock, frames, window;
    struct sockaddr_in serveraddr, clientaddr;
    sersock = socket(AF_INET, SOCK_STREAM, 0);
    if (sersock < 0) {
        printf("Socket creation failed\n");
        exit(0);
    }
    printf("Socket created\n");
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serveraddr.sin_port = htons(2000);
    if (connect(sersock, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) != 0) {
        printf("Connection failed\n");
        exit(0);
    }
    printf("Connected successfully\n");
    printf("Enter the number of frames: ");
    scanf("%d", &frames);
    printf("Enter the window size: ");
    scanf("%d", &window);
    sendData(sersock, frames, window);
    close(sersock);
}
