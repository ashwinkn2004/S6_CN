#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<netinet/in.h>
#include<unistd.h>

void sendMessage(int clientsock, int ack){
	char servermessage[1000];
	memset(servermessage, '\0', sizeof(servermessage));
	sprintf(servermessage, "%d", ack);
	send(clientsock, servermessage, strlen(servermessage), 0);
}

void main(){
	int serversock, clientsock;
	struct sockaddr_in serveraddr, clientaddr;
	char clientmessage[1000];
	
	bzero(&serveraddr, sizeof(serveraddr));
	serversock = socket(AF_INET, SOCK_STREAM, 0);
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(6644);
	serveraddr.sin_addr.s_addr = INADDR_ANY;
    
	bind(serversock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
	listen(serversock, 5);
	
	int clientsize = sizeof(clientaddr);
	clientsock = accept(serversock, (struct sockaddr *)&clientaddr, &clientsize);
	
	int frames, next = 0, ack = 0;
	
	while(1){
		memset(clientmessage, '\0', sizeof(clientmessage));
		recv(clientsock, clientmessage, sizeof(clientmessage), 0);
		frames = atoi(clientmessage);
		
		if(frames != next){
			printf("Frame %d not received\n", frames);
			sendMessage(clientsock, ack);
			continue;
		}
		
		int ch = rand()%3;
		switch(ch){
			case 0:
				printf("Frame %d not received\n", frames);
				break;
			case 1:
				ack = frames;
				sleep(2);
				printf("Frame &+%d received Ack %d printed.....\n", frames, ack);
				sendMessage(clientsock, ack);
				next = ack + 1;
				break;
			case 2:
				ack = frames;
				printf("Frame &+%d received Ack %d printed.....\n", frames, ack);
				sendMessage(clientsock, ack);
				next = ack + 1;
				break;
		}
		
	}
	close(serversock);
	close(clientsock);
}
