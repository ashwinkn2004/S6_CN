#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<netinet/in.h>

void sendData(int serversock, int frames, int window) {
    char clientmessage[1000];
    int i, j, k, n, w1 = 0, w2 = window - 1, ack, flag = 0;
    struct timeval timeout;

    timeout.tv_sec = 3;
    timeout.tv_usec = 0;

    setsockopt(serversock, SOL_SOCKET, SO_RCVTIMEO , (const char*)&timeout, sizeof(timeout));

    while(1){
        for(i = 0; i < frames && i <= w2; i++){
            sprintf(clientmessage, "%d", i);
            k = send(serversock, clientmessage, strlen(clientmessage), 0);
            printf("Frame %d received\n", i);
        }
        while(1){
            if(w2 - w1 != window - 1 && flag == 0 && i != frames){
                sprintf(clientmessage, "%d", i);
                k = send(serversock, clientmessage, strlen(clientmessage), 0);
                printf("Frame %d received\n", i);
                w2++;
                i++;
            }
            flag = 0;
            n = recv(serversock, clientmessage, sizeof(clientmessage), 0);
            ack = atoi(clientmessage);
            if(n > 0){
                if(ack + 1 == frames){
                    printf("Exit\n");
                    strcpy(clientmessage, "EXIT");
                    k = send(serversock, clientmessage, strlen(clientmessage), 0);
                    return;
                }
                if(ack == w1){
                    w1++;
                    printf("Ack %d received\n", ack);
                }
            }else{
                printf("Ack not received for %d\nRESENDING ...\n", w1);
                for(j = w1; j < frames && j < w1 + window; j++){
                    sprintf(clientmessage, "%d", j);
                    k = send(serversock, clientmessage, strlen(clientmessage), 0);
                    printf("Frame %d received\n", j);
                }
                flag = 1;
            }
        }
    }
}

void main(){
    int serversock, clientsock;
    struct sockaddr_in serveraddr, clientaddr;
    char clientmessage[1000];

    serversock = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(2000);
    serveraddr.sin_addr.s_addr = INADDR_ANY;

    connect(serversock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

    int frames, window, next, ack = 0;

    printf("Enter the number of frames: ");
    scanf("%d", &frames);

    printf("Enter the window size: ");
    scanf("%d", &window);

    sendData(serversock, frames, window);    
    close(serversock);
}