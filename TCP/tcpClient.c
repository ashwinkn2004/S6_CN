 #include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

void main(){
	struct sockaddr_in serveraddr, clientaddr;
	int serversock, clientsize, listener, connector;
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
	
	connector = connect(serversock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
	if(connector < 0){
		printf("Unable to connnect\n");
		return -1;
	}
	printf("Connecting done\n");
	
	printf("Enter the message : ");
	gets(client_message);
	
	send(serversock, client_message, strlen(client_message), 0);
	
	recv(serversock, server_message, sizeof(server_message), 0);
	printf("Server message : %s", server_message);
	
	close(serversock);
}
