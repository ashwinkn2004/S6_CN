#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

void main(){
    int serversock, clientsock;
    struct sockaddr_in serveraddr, clientaddr;
    char servermessage[1000], clientmessage[1000];

    memset(servermessage, '\0', sizeof(servermessage));
    memset(clientmessage, '\0', sizeof(clientmessage));

    serversock = socket(AF_INET, SOCK_STREAM, 0);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(2000);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(serversock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    listen(serversock, 1);
    int clinetsize = sizeof(clientaddr);
    clientsock = accept(serversock, (struct sockaddr *)&clientaddr, &clinetsize);
    recv(clientsock, clientmessage, sizeof(clientmessage), 0);
    printf("%s", clientmessage);
    int num = atoi(clientmessage);
    
    strcpy(servermessage, clientmessage);
    recv(clientsock, servermessage, strlen(servermessage), 0);
    close(serversock);
    close(clientsock);
}