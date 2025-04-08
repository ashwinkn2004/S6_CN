#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<netinet/in.h>

void sendMessage(int clientsock, int ack){
	char servermessage[1000];
	//memset(servermessage, '\0', sizeof(servermessage));
	sprintf(servermessage, "%d", ack);
	send(clientsock, servermessage, strlen(servermessage), 0);
}

void main(){
	int serversock, clientsock;
	struct sockaddr_in serveraddr, clientaddr;
	char clientmessage[1000];

	serversock = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(2000);
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	bind(serversock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
	listen(serversock, 5);

	int clientsize = sizeof(clientaddr);
	clientsock = accept(serversock, (struct sockaddr *)&clientaddr, &clientsize);
	
	int frame, next = 0, ack = 0, ch;
	
	while(1){
		memset(clientmessage, '\0', sizeof(clientmessage));
		recv(clientsock, clientmessage, sizeof(clientmessage), 0);
		frame = atoi(clientmessage);
		
		/*if(strcmp(clientmessage, "EXIT") == 0){
			break;
		}*/
		
		if(frame != next){
			printf("Frame %d discarded", frame);
			sendMessage(clientmessage, ack);
			continue;
		}
		
		ch = rand()%3;
		
		switch(ch){
			case 0:
				printf("Frame %d not received\n", frame);
				break;
			case 1:
				printf("Frame %d received\nAck %d printed\n", frame, ack);
				ack = frame;
				sleep(2);
				next = ack + 1;
				sendMessage(clientsock, ack);
				break;
			case 2:
				printf("Frame %d received\nAck %d printed\n", frame, ack);
				ack = frame;
				next = ack + 1;
				sendMessage(clientsock, ack);
				break;
		}
	}
	close(serversock);
}












