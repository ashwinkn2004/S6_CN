#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<netinet/in.h>

void sendMessage(int clientsock, int ack) {
    char servermessage[1000];
    sprintf(servermessage, "%d", ack);
    send(clientsock, servermessage, strlen(servermessage), 0);
}

void main() {
    int serversock, clientsock;
    struct sockaddr_in serveraddr, clientaddr;
    char clientmessage[1000];

    serversock = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(2000);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(serversock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    listen(serversock, 5);

    int clientsize = sizeof(clientaddr);
    clientsock = accept(serversock, (struct sockaddr *)&clientaddr, &clientsize);

    int frame, ch, next = 0, ack = 0;
    while(1) {
        memset(clientmessage, '\0', sizeof(clientmessage));
        recv(clientsock, clientmessage, sizeof(clientmessage), 0);
        frame = atoi(clientmessage);

        if (frame != next) {
            printf("Frame %d discarded\nAcknowledgment: %d\n", frame, ack);
            sendMessage(clientsock, ack);
            continue;
        }

        ch = rand() % 3;
        switch(ch) {
            case 0:
                printf("Frame %d not received\n", frame); 
                break;
            case 1:
                ack = frame;
                sleep(2);
                printf("Frame %d received\nAcknowledgment %d printed\n", frame, ack);
                sendMessage(clientsock, ack);
                next = ack + 1;
                break;
            case 2:
                ack = frame;
                printf("Frame %d received\nAcknowledgment %d printed\n", frame, ack);
                sendMessage(clientsock, ack);
                next = ack + 1;
                break;
        }
    }
    close(clientsock);
    close(serversock);
}
