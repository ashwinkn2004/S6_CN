#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<netdb.h>

void main(){
    int serversock, clientsock;
    struct sockaddr_in serveraddr, clientaddr;
    char servermessage[1000], clientmessage[1000];

    memset(servermessage, '\0', sizeof(servermessage));
    memset(clientmessage, '\0', sizeof(clientmessage));

    serversock = socket(AF_INET, SOCK_STREAM, 0);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(2000);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    bind(serversock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    listen(serversock, 5);
    
    int clientsize = sizeof(clientaddr);
    clientsock = accept(serversock, (struct sockaddr *)&clientaddr, &clientsize);
    //first number
    recv(clientsock, clientmessage, sizeof(clientmessage), 0);
    int a = atoi(clientmessage);
    printf("%d ",a);
    
    //operator
    memset(clientmessage, '\0', sizeof(clientmessage));
    recv(clientsock, clientmessage, sizeof(clientmessage), 0);
    char op = clientmessage[0];
    printf("%c ",op);
    
    //second number
    memset(clientmessage, '\0', sizeof(clientmessage));
    recv(clientsock, clientmessage, sizeof(clientmessage), 0);
    int b = atoi(clientmessage);
    printf("%d ",b);
    
    int res = 0;
    if(op == '+'){
    	res = a + b;
    }
    if(op == '-'){
    	res = a - b;
    }
    if(op == '*'){
    	res = a * b;
    }
    if(op == '/'){
    	res = a / b;
    }
    printf("= %d\n", res);
    sprintf(servermessage, "%d", res);
    send(clientsock, servermessage, strlen(servermessage), 0);
    close(serversock);
    close(clientsock);
}
