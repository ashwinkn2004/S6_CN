#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<netdb.h>

void main(){
    int clientsock;
    struct sockaddr_in serveraddr;
    char servermessage[1000], clientmessage[1000];

    memset(servermessage, '\0', sizeof(servermessage));
    memset(clientmessage, '\0', sizeof(clientmessage));

    clientsock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(2000);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int clientsize = sizeof(serveraddr);

    strcpy( clientmessage, "Msg from client");
    sendto(clientsock, clientmessage, strlen(clientmessage), 0, (struct sockaddr *)&serveraddr, clientsize);
    recvfrom(clientsock, servermessage, sizeof(servermessage), 0, (struct sockaddr *)&serveraddr, &clientsize);
    printf("%s\n", servermessage);
    close(clientsock);
}
