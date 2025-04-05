#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

void main(){
    struct sockaddr_in serveraddr, clientaddr;
    int serversock, clientsock, binder, listener;
    char clinet_message[2000], server_message[2000];

    memset(server_message, "\0", sizeof(server_message));
    memset(clinet_message, "\0", sizeof(clinet_message));

    serversock = socket(AF_INET, SOCK_STREAM, 0);
    if(serversock < 0){
        printf("Socket Failed \n");
        return -1;
    }
    printf("Socket done\n");

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(2000);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    binder = bind(serversock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    if(binder < 0){
        printf("Binding failed\n");
        return -1;
    }
    printf("Binding done\n");

    listener = listen(serversock, 5);
    if(listener < 0){
        printf("Listening failed\n");
        return -1;
    }
    printf("Listening done\n");

    int clientsize = sizeof(clientaddr);
    clinetsock = accept(serversock, (struct sockaddr *)&clientaddr, &clientsize);
    if(clinetsock < 0){
        printf("Accept failed\n");
        return -1;
    }
    printf("Accept done\n");

    int revrr = recv(slientsock, client_message, sizeof(client_message), 0);
    if(revrr < 0){
        printf("Receiving failed\n");
        return -1;
    }
    printf("Received message: %s\n", client_message);

    strcpy(server_message, "Hii");
    sndr = send(clientsock, server_message, sizeof(server_message), 0);
    if(sndr < 0){
        printf("Sending failed\n");
        return -1;
    }
    printf("Message sent\n");
    
    close(serversock);
    close(clientsock);
}