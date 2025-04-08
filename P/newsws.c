#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<netinet/in.h>

void main(){
	int serversock, clientsock;
	struct sockaddr_in serveraddr, clientaddr;
	char servermessage[1000], clientmessage[1000];
	
	serversock = socket(AF_INET, SOCK_STREAM, 0);
    	serveraddr.sin_family = AF_INET;
    	serveraddr.sin_port = htons(8888);  
    	serveraddr.sin_addr.s_addr = INADDR_ANY;
    	
    	bind(serversock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
	listen(serversock, 5);
	
	int clientsize = sizeof(clientaddr);
	clientsock = accept(serversock, (struct sockaddr *)&clientaddr, &clientsize);
	
	while(1){
		memset(clientmessage, '\0', sizeof(clientmessage));
		recv(clientsock, clientmessage, sizeof(clientmessage), 0);
		if(strcmp(clientmessage, "Exit") == 0)return;
		printf("Frame : %s \n", clientmessage);
		
		z:
		memset(servermessage, '\0', sizeof(servermessage));
		printf("Ack or not : ");
		scanf("%s", servermessage);
		send(clientsock, servermessage, strlen(servermessage), 0);
		
		if(strcmp(servermessage, "n") == 0){
			printf("Ack not received\n");
			goto z;
		}
	}
}
