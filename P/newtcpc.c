#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

void main(){
    int serversock;
    struct sockaddr_in serveraddr;
    char servermessage[1000], clientmessage[1000];

    memset(servermessage, '\0', sizeof(servermessage));
    memset(clientmessage, '\0', sizeof(clientmessage));

    serversock = socket(AF_INET, SOCK_STREAM, 0);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(2004);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(serversock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    
    int a , b, c;
    printf("Enter first number : ");
    scanf("%d", &a);
    printf("Enter second number : ");
    scanf("%d", &b);
    printf("Enter third number : ");
    scanf("%d", &c);
    
    send(serversock, &a, sizeof(int), 0);
    send(serversock, &b, sizeof(int), 0);
    send(serversock, &c, sizeof(int), 0);
    
    recv(serversock, servermessage, sizeof(servermessage), 0);
    printf("Result : %s\n", servermessage);
    
    close(serversock);
}
