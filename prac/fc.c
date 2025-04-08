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
    struct sockaddr_in clientaddr;
    char servermessage[1000], clientmessage[1000];

    memset(servermessage, '\0', sizeof(servermessage));
    memset(clientmessage, '\0', sizeof(clientmessage));

    clientsock = socket(AF_INET, SOCK_STREAM, 0);
    clientaddr.sin_family = AF_INET;
    clientaddr.sin_port = htons(2000);
    clientaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
   
    connect(clientsock, (struct sockaddr *)&clientaddr, sizeof(clientaddr));
    
    //first number
    printf("Enter the First number : ");
    scanf("%s", clientmessage);
    send(clientsock, clientmessage, strlen(clientmessage), 0);
    
    //operator
    memset(clientmessage, '\0', sizeof(clientmessage));
    printf("Enter the operator : ");
    scanf("%s", clientmessage);
    send(clientsock, clientmessage, strlen(clientmessage), 0);
    
    //second number
    memset(clientmessage, '\0', sizeof(clientmessage));
    printf("Enter the Second number : ");
    scanf("%s", clientmessage);
    send(clientsock, clientmessage, strlen(clientmessage), 0);
    
    //result
    recv(clientsock, servermessage, sizeof(servermessage), 0);
    printf("Result = %s\n", servermessage);
    close(clientsock);
}
