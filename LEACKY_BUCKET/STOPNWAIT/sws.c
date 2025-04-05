#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<netinet/in.h>

void main(){
    int serversock, clientsock;
    struct sockaddr_in serveraddr, clientaddr;
    char servermessage[1000], clientmessage[1000];

    memset(clientmessage, '\0', sizeof(clientmessage));

    serversock = socket(AF_INET, SOCK_STREAM, 0);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8080);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(serversock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    listen(serversock, 5);

    int clientsize = sizeof(clientaddr);
    clientsock = accept(serversock, (struct sockaddr *)&clientaddr, &clientsize);
    while(1){
        recv(clientsock, clientmessage, sizeof(clientmessage), 0);
        printf("Client msg : %s", clientmessage);

        memset(clientmessage, '\0', sizeof(clientmessage));
        z:
        printf("\nAck y or n : ");
        memset(servermessage, '\0', sizeof(servermessage));
        scanf("%s", servermessage);
        send(clientsock, servermessage, strlen(servermessage), 0);
        if(strcmp(servermessage, "n") == 0){
            printf("Ack not received\n");
            goto z;
        }
    }
    strcpy(servermessage, "Exit");
    send(serversock, servermessage, strlen(servermessage), 0);
    close(serversock);
    close(clientsock);
}