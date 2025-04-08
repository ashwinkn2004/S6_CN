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
	int total, frames, server_num, curr = 0, client_ack;
	
	serversock = socket(AF_INET, SOCK_STREAM, 0);
    	serveraddr.sin_family = AF_INET;
    	serveraddr.sin_port = htons(8888);  
    	serveraddr.sin_addr.s_addr = INADDR_ANY;
    	
    	connect(serversock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
	
	printf("Total : ");
	scanf("%d", &total);
	printf("Frame : ");
	scanf("%d", &frames);
	
	send(serversock, &total, sizeof(int), 0);
	send(serversock, &frames, sizeof(int), 0);
	
	int sender = frames;
	
	for(int i = 0; i < frames; i++){
		memset(&server_num, 0, sizeof(int));
		server_num = i;
		send(serversock, &server_num, sizeof(int), 0);
		printf("Frame %d sent\n", server_num);
	}
	
	while(curr < total - frames){
		memset(&server_num, 0, sizeof(int));
		memset(&client_ack, 0, sizeof(int));
		int ch = rand()%2;
		if(ch == 1){
			recv(serversock, &client_ack, sizeof(int), 0);
			printf("Ack %d received\n", client_ack);
			server_num = sender;
			send(serversock, &server_num, sizeof(int), 0);
			printf("Frame %d sent\n", server_num);
			curr++;
			sender++;
		}
		else{
			printf("Ack not recived.. RESENDING......%d\n", curr);
			server_num = curr;
			send(serversock, &server_num, sizeof(int), 0);
			printf("Frame %d sent\n", server_num);
		}
	}
	while(curr < total){
		memset(&client_ack, 0, sizeof(int));
		recv(serversock, &client_ack, sizeof(int), 0);
		printf("Ack %d received\n", client_ack);
		curr++;
	}
	close(serversock);
}
