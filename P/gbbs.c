#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<netinet/in.h>

void sendMessage(int clientsock, int ack) {
    char servermessage[1000];
    sprintf(servermessage, "%d", ack);
    send(clientsock, servermessage, strlen(servermessage), 0);
}

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
	
	int frames, next = 0, ack;
	
	while(1){
		memset(clientmessage, '\0', sizeof(clientmessage));
		recv(clientsock, clientmessage, sizeof(clientmessage), 0);
		frames = atoi(clientmessage);
		if(frames != next){
			printf("Frame not received, Discarded\n");
			sendMessage(clientsock, ack);
			continue;
		}
		int ch = rand()%3;
		switch(ch){
			case 0:
				printf("Frame not received, Discarded\n");
				break;
			case 1:
				ack = frame;
				sleep(2);
				printf("Ack %d received\n", ack);
				sendMessage(clientsock, ack);
				next = ack + 1;
				break;
			case 2:
				ack = frame;
				printf("Ack %d received\n", ack);
				sendMessage(clientsock, ack);
				next = ack + 1;
				break;
		}
	}
	close(serversock);
	close(clientsock);
}
