#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

void main(){
    struct sockaddr_in serveraddr, clientaddr;
    int serversock, clientsock;
    char servermessage[1000], clientmessage[1000];
    socklen_t clientsize; 
    
    memset(servermessage, '\0', sizeof(servermessage));
    memset(clientmessage, '\0', sizeof(clientmessage));
    
    serversock = socket(AF_INET, SOCK_STREAM, 0);
    
    serveraddr.amily = AF_INET;
    serveraddr.sin_port = htons(8080);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    bind(serversock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    listen(serversock, 1); 
    
    clientsize = sizeof(clientaddr);
    clientsock = accept(serversock, (struct sockaddr *)&clientaddr, &clientsize);
    
    while(1){
        recv(clientsock, clientmessage, sizeof(clientmessage), 0);
        printf("Message from client = %s", clientmessage);

        memset(clientmessage, '\0', sizeof(clientmessage));
        
        printf("\nAck y or n : ");
        
        z:
        
        memset(servermessage, '\0', sizeof(servermessage));
        scanf("%s", servermessage);
        
        send(clientsock, servermessage, strlen(servermessage), 0);
        
        if(strcmp(servermessage, "n") == 0){
            printf("ack not received\n"); 
            goto z;
        }
    }
    close(serversock);
    close(clientsock);
}
