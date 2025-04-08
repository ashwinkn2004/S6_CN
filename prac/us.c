#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<netdb.h>

void main(){
    int serversock;
    struct sockaddr_in serveraddr, clientaddr;
    char servermessage[1000], clientmessage[1000];

    memset(servermessage, '\0', sizeof(servermessage));
    memset(clientmessage, '\0', sizeof(clientmessage));

    serversock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(2000);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    bind(serversock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    int clientsize = sizeof(clientaddr);
    
    recvfrom(serversock, clientmessage, sizeof(clientmessage), 0, (struct sockaddr *)&clientaddr, &clientsize);
    printf("%s\n", clientmessage);
    strcpy(servermessage, "Message from server");
    sendto(serversock, servermessage, strlen(servermessage), 0, (struct sockaddr *)&clientaddr, clientsize);
    close(serversock);
}
