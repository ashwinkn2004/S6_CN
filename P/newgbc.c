#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<netinet/in.h>
#include<unistd.h>

void sendData(int serversock, int frames, int window){
	int i, j, k, n, w1 = 0, w2 = window - 1, flag = 0, ack;
	char clientmessage[1000];
	
	struct timeval timeout;
	
	timeout.tv_sec = 3;
	timeout.tv_usec = 0;
	setsockopt(serversock, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof(timeout));
	
	while(1){
		for(i = 0; i < frames && i <= w2; i++){
			memset(clientmessage, '\0', sizeof(clientmessage));
			sprintf(clientmessage, "%d", i);
			send(serversock, clientmessage, strlen(clientmessage), 0);
			printf("Frame %d sent\n", i);
		}
		while(1){
			if(w2 - w1 != window - 1 && flag == 0 && i != frames){
				memset(clientmessage, '\0', sizeof(clientmessage));
				sprintf(clientmessage, "%d", i);
				send(serversock, clientmessage, strlen(clientmessage), 0);
				printf("Frame %d sent\n", i);
				w2++;
				i++;
			}
			flag = 0;
			n = recv(serversock, clientmessage, sizeof(clientmessage), 0);
			ack = atoi(clientmessage);
			if(n > 0){
				if(ack + 1 == frames){
					strcpy(clientmessage, "EXIT");
                    			k = send(serversock, clientmessage, strlen(clientmessage), 0);
                    			return;
				}
				if(ack == w1){
					w1++;
					printf("Ack %d received\n", ack);
				}
			}
			else{
				printf("RESENDING.....................\n");
				for(j = w1; j < frames && j < w1 + window; j++){
					memset(clientmessage, '\0', sizeof(clientmessage));
					sprintf(clientmessage, "%d", j);
					k = send(serversock, clientmessage, strlen(clientmessage), 0);
					printf("Frame %d sent\n", j);
				}
				flag = 1;
			}
		}
	}
}

void main(){
	int serversock;
	struct sockaddr_in serveraddr;
	
	bzero(&serveraddr, sizeof(serveraddr));
	serversock = socket(AF_INET, SOCK_STREAM, 0);
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(6644);
	serveraddr.sin_addr.s_addr = INADDR_ANY;
	
	connect(serversock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
	
	int frames, window;
	
	printf("Enter the total frames : ");
	scanf("%d", &frames);
	printf("Enter the window size : ");
	scanf("%d", &window);
	
	sendData(serversock, frames, window);
}
