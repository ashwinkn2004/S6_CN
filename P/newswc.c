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
	int serversock;
	struct sockaddr_in serveraddr;
	char servermessage[1000], clientmessage[1000];
	
	serversock = socket(AF_INET, SOCK_STREAM, 0);
    	serveraddr.sin_family = AF_INET;
    	serveraddr.sin_port = htons(8888);  
    	serveraddr.sin_addr.s_addr = INADDR_ANY;
    	
    	connect(serversock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    	
    	int frames, timer;
    	printf("Enter the total frames : ");
    	scanf("%d", &frames);
	
	while(frames > 0){
		memset(clientmessage, '\0', sizeof(clientmessage));
		memset(servermessage, '\0', sizeof(servermessage));
		printf("Frame :  \n");
		scanf("%s", clientmessage);
		
		x:
		timer = 10;
		send(serversock, clientmessage, strlen(clientmessage), 0);
		
		y:
		if(timer > 0){
			if(recv(serversock, servermessage, sizeof(servermessage), 0) < 0){
				printf("Ack not received\n");
				timer--;
				goto y;
			}
			if(strcmp(servermessage, "n") == 0){
				printf("Ack not received\n");
				timer--;
				goto y;
			}
			if(strcmp(servermessage, "y") == 0){
				printf("Ack received\n");
				timer = 0;
				frames--;
				continue;
			}
		}	
	}
	strcpy(clientmessage, "Exit");
	send(serversock, clientmessage, strlen(clientmessage), 0);
	close(serversock);
}
