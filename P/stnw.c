#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<netdb.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>

void main(){
    int serversock, clientsock, n, f;
    struct sockaddr_in clientaddr, serveraddr; 
    char servermessage[1000], clientmessage[1000];

    serversock = socket(AF_INET, SOCK_STREAM, 0);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(2012);
    serveraddr.sin_addr.s_addr = INADDR_ANY;

    bind(serversock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    listen(serversock, 5);

    int len = sizeof(clientaddr), frame;
    clientsock = accept(serversock, (struct sockaddr *)&clientaddr, &len);
    while(1){
        memset(clientmessage, '\0', sizeof(clientmessage));
        recv(clientsock, clientmessage, sizeof(clientmessage), 0);
        if(strcmp(clientmessage, "exit") == 0){
            break;
        }
        printf("Frames: %s\n", clientmessage);

        frame = atoi(clientmessage);

        z:
        printf("Ack y or n : ");
        memset(servermessage, '\0', sizeof(servermessage));
        scanf("%s", servermessage);
        send(clientsock, servermessage, strlen(servermessage), 0);

        if(strcmp(servermessage, "n") == 0){
            printf("Acknowledgement not received\n");
            goto z;
        }
    }
    close(clientsock);
    close(serversock);
}