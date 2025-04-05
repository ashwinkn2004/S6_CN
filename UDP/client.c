#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

void main(){
	struct sockaddr_in serveraddr, clientaddr;
	int serversock, clientsize;
	char server_message[2000], client_message[2000];
	
	memset(server_message, '\0', sizeof(server_message));
    memset(client_message, '\0', sizeof(client_message));
	
	serversock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(2000);
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	printf("Enter the message : ");
	scanf("%s", client_message);
	
	clientsize = sizeof(serveraddr);
	
	sendto(serversock, client_message, strlen(client_message), 0, (struct sockaddr *)&serveraddr, clientsize);
	
	recvfrom(serversock, server_message, sizeof(server_message), 0, (struct sockaddr *)&serveraddr, &clientsize);
	printf("Message = %s",server_message);
	
	
	close(serversock);
}

