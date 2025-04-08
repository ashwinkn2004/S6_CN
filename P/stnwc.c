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
    int serversock, clientsock, n, frame;
    struct sockaddr_in clientaddr, serveraddr; 
    char servermessage[1000], clientmessage[1000];

    serversock = socket(AF_INET, SOCK_STREAM, 0);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(2012);
    serveraddr.sin_addr.s_addr = INADDR_ANY;

    connect(serversock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

    printf("Enter the frame : ");
    scanf("%d", &frame);

    int timer, count;
    while(frame > 0){
        memset(clientmessage, '\0', sizeof(clientmessage));
        printf("Enter the frame message : ");
        scanf("%s", clientmessage);

        x:
        timer = 10;
        send(serversock, clientmessage, strlen(clientmessage), 0);

        y:
        if(timer > 0){
            if(recv(serversock, servermessage, sizeof(servermessage), 0) < 0){
                printf("Error in receiving data\n");
                timer--;
                goto y;
            }            
            if(strcmp(servermessage, "y") == 0){
                printf("Acknowledgement received\n");
                timer = 0;
                frame--;
                continue;
            }
            if(strcmp(servermessage, "n") == 0){
                printf("Acknowledgement not received\n");
                timer--;
                goto y;
            }
        }
    }
    strcpy(servermessage, "exit");
    send(serversock, servermessage, strlen(servermessage), 0);
    close(serversock);

}