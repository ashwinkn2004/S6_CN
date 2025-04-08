#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<netdb.h>

void main(){
    int serversock, clientsock;
    struct sockaddr_in serveraddr, clientaddr;
    char servermessage[1000], clientmessage[1000];

    memset(servermessage, '\0', sizeof(servermessage));
    memset(clientmessage, '\0', sizeof(clientmessage));

    serversock = socket(AF_INET, SOCK_STREAM, 0);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(2004);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(serversock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    listen(serversock, 1);
    int clientsize = sizeof(clientaddr);
    clientsock = accept(serversock, (struct sockaddr *)&clientaddr, &clientsize);
    
    int a, b, c;
    recv(clientsock, &a, sizeof(int), 0);
    recv(clientsock, &b, sizeof(int), 0);
    recv(clientsock, &c, sizeof(int), 0);
    
    if(a > b  && a > c){
    	memset(servermessage, '\0', sizeof(servermessage));
    	strcpy(servermessage, "First is greater");
    	send(clientsock, servermessage, strlen(servermessage), 0);
    	return;
    }
    if(b > a && b > c ){
    	memset(servermessage, '\0', sizeof(servermessage));
    	strcpy(servermessage, "Second is greater");
    	send(clientsock, servermessage, strlen(servermessage), 0);
    	return;
    }
    else{
    	memset(servermessage, '\0', sizeof(servermessage));
    	strcpy(servermessage, "Third is greater");
    	send(clientsock, servermessage, strlen(servermessage), 0);
    	return;
    }
    
    close(clientsock);
    close(serversock);
}
