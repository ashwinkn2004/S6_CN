#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<netinet/in.h>

void sendData(int serversock, int frames, int window){
	char clientmessage[1000];
	int flag = 0, ack, i, j, k, w1 = 0, w2 = window - 1;
	struct timeval timeout;
	timeout.tv_sec = 3;
	timeout.tv_usec = 0;
	setsockopt(serversock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
	
	while(1){
		for(i = 0; i < frames && i <= w2; i++){
			printf("Frame %d send\n", i);
			snprintf(clientmessage, sizeof(clientmessage), "%d", i);
			send(serversock, clientmessage, strlen(clientmessage), 0);
		}
		while(1){
			if(w2 - w1 != window - 1 && flag == 0 && i != frames){
				printf("Frame %d send\n", i);
				snprintf(clientmessage, sizeof(clientmessage), "%d", i);
				send(serversock, clientmessage, strlen(clientmessage), 0);
				w2++;
				i++;
			}
			flag = 0;
			k = recv(serversock, clientmessage, sizeof(clientmessage), 0);
			ack = atoi(clientmessage);
			if(k > 0){
				if(ack + 1 == frames){
					printf("Ack received %d\nEXIT\n", ack);
					strcpy(clientmessage, "EXIT");
					send(serversock, clientmessage, strlen(clientmessage), 0);
					return;
				}
				if(ack == w1){
					printf("Ack %d received\n", ack);
					w1++;
				}
			}
			else{
				printf("RESENDING...\n");
				for(j = w1; j < frames && j < w1+window; j++){
					printf("Frame %d send\n", i);
					snprintf(clientmessage, sizeof(clientmessage), "%d", j);
					send(serversock, clientmessage, strlen(clientmessage), 0);
				}
				flag = 1;
			}
		}
	}
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

	connect(serversock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
	
	int frames, window;
	
	printf("Enter the number of frames : ");
	scanf("%d", &frames);
	printf("Enter the window size : ");
	scanf("%d", &window);
	sendData(serversock, frames, window);
	close(serversock);
}
