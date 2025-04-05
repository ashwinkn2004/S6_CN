#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

void main(){
	struct sockaddr_in serveraddr, clientaddr;
	int serversock, clientsock, clientsize, listener, binder;
	char server_message[2000], client_message[2000];
	
	memset(server_message, '\0', sizeof(server_message));
    	memset(client_message, '\0', sizeof(client_message));
	
	serversock = socket(AF_INET, SOCK_STREAM, 0);
	if(serversock < 0){
		printf("Error in creating Socket\n");
		return -1;
	}
	printf("Created socket\n");
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(2000);
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	binder = bind(serversock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
	if(binder < 0){
		printf("Error in binding\n");
		return -1;
	}
	printf("Binding done\n");
	
	listener = listen(serversock, 2);
	if(listener < 0){
		printf("Error in listening\n");
		return -1;
	}
	printf("Listening\n");
	
	clientsize = sizeof(clientaddr);
	clientsock = accept(serversock, (struct sockaddr *)&clientaddr, &clientsize);
	if(clientsock < 0){
		printf("Error in accept\n");
		return -1;
	}
	printf("Accept\n");
	
	int recvrr = recv(serversock, client_message, sizeof(client_message), 0);
	if(recvrr < 0){
		printf("Noting received\n");
		return -1;
	}
	printf("Message = %s",client_message);
	strcpy(server_message, "hii");
	
	send(clientsock, server_message, strlen(server_message), 0);
	
	close(serversock);
	close(clientsock);
}
