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
    int clientsock, frames, timer;
    struct sockaddr_in clientaddr;
    char servermessage[1000], clientmessage[1000];

    memset(clientmessage, '\0', sizeof(clientmessage));

    clientsock = socket(AF_INET, SOCK_STREAM, 0);
    clientaddr.sin_family = AF_INET;
    clientaddr.sin_port = htons(8080);
    clientaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(clientsock, (struct sockaddr *)&clientaddr, sizeof(clientaddr));

    printf("Enter the number of frames : ");
    scanf("%d", &frames);

    while(frames > 0){
        printf("Enter the mesage : ");
        scanf("%s", clientmessage);
        x:
        timer = 10;
        send(clientsock, clientmessage, strlen(clientmessage), 0);

        y:
        if(timer > 0){
            if(recv(clientsock, servermessage, sizeof(servermessage), 0) < 0){
                printf("Ack not received\n");
                timer--;
                goto y;
            }
            if(strcmp(servermessage, "Exit") == 0){
                break;
            }
            else if(strcmp(servermessage, "y") == 0){
                printf("Ack received\n");
                frames--;
                timer = 10;
            }
            else if(strcmp(servermessage, "n") == 0){
                printf("Ack not received\n");
                timer--;
                goto x;
            }
        }else{
            printf("Ack not received try again \n");
            goto x;
        }
    }
    close(clientsock);
}