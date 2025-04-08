#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void main(){
    int serversock, frames, total, clientsock, server_num, client_ack, curr = 0;
    struct sockaddr_in serveraddr, clientaddr;

    serversock = socket(AF_INET, SOCK_STREAM, 0);
    
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(1211);
    serveraddr.sin_addr.s_addr = INADDR_ANY;

    bind(serversock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    listen(serversock, 1);

    int clientsize = sizeof(clientaddr);
    clientsock = accept(serversock, (struct sockaddr *)&clientaddr, &clientsize);

    recv(clientsock, &total, sizeof(int), 0);
    recv(clientsock, &frames, sizeof(int), 0);

    int checker_array[100];
    for(int i = 0; i < 100; i++){
        checker_array[i] = 0;
    }

    for(int i = 0; i < frames; i++){
        memset(&client_ack, 0, sizeof(int));
        recv(clientsock, &server_num, sizeof(int), 0);
        checker_array[server_num] = 1;
        printf("Frame %d received\n", server_num);
        client_ack = i;
        send(clientsock, &client_ack, sizeof(int), 0);
        printf("ACK %d sent\n", client_ack);
        curr++;
    }
    while(curr < total){
        memset(&server_num, 0, sizeof(int));
        recv(clientsock, &server_num, sizeof(int), 0);

        if(checker_array[server_num] == 0){
            printf("Frame %d received\n", server_num);
            checker_array[server_num] = 1;
            client_ack = server_num;
            send(clientsock, &client_ack, sizeof(int), 0);
            printf("ACK %d sent\n", client_ack);
            curr++;
        }
        else{
            printf("Frame received already, Ignoring\n");
        }
    }
    close(clientsock);
    close(serversock);
}