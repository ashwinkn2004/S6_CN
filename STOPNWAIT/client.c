#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

void main(){
    struct sockaddr_in serveraddr;
    int clientsock, timer, frames;
    char servermessage[1000], clientmessage[1000];
    socklen_t clientsize; 
    
    memset(servermessage, '\0', sizeof(servermessage));
    memset(clientmessage, '\0', sizeof(clientmessage));
    
    clientsock = socket(AF_INET, SOCK_STREAM, 0);
    
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8080);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    connect(clientsock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    printf("Enter the total frames : ");
    scanf("%d", &frames); 
    
    while(frames > 1){
        memset(clientmessage, '\0', sizeof(clientmessage));
        
        printf("Enter the frame message : ");
        scanf("%s", clientmessage);
        
        x:
        
        timer = 10;
        send(clientsock, clientmessage, strlen(clientmessage), 0);
        
        y:
        
        if(timer > 0){
            if(recv(clientsock, servermessage, sizeof(servermessage), 0) < 0){
                printf("Not received\n");
                timer--;
                goto y;
            }
            if(strcmp(servermessage, "n") == 0){
                printf("waiting..\n");
                timer--;
                goto y;
            }
            if(strcmp(servermessage, "y") == 0){
                printf("Ack received\n");
                timer = 0;
                frames--;
            }
        }
        else{
            printf("ack not received\n"); 
            goto x;
        }
    }
    close(clientsock);
}
