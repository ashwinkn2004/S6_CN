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
	int total, frames;
	
	serversock = socket(AF_INET, SOCK_STREAM, 0);
    	serveraddr.sin_family = AF_INET;
    	serveraddr.sin_port = htons(8888);  
    	serveraddr.sin_addr.s_addr = INADDR_ANY;
    	
    	bind(serversock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
	listen(serversock, 5);
	
	int clientsize = sizeof(clientaddr);
	clientsock = accept(serversock, (struct sockaddr *)&clientaddr, &clientsize);
	
	recv(clientsock, &total, sizeof(int), 0);
	recv(clientsock, &frames, sizeof(int), 0);
	
	int selected[100], server_num, client_ack, curr = 0;
	
	for(int i = 0; i < 100; i++){
		selected[i] = 0;
	}
	
	for(int i = 0; i < frames; i++){
		memset(&server_num, 0, sizeof(int));
		memset(&client_ack, 0, sizeof(int));
		recv(clientsock, &server_num, sizeof(int), 0);
		selected[server_num] = 1;
		printf("Frame %d received\n", server_num);
		client_ack = i;
		send(clientsock, &client_ack, sizeof(int), 0);
		printf("Ack %d sent\n", client_ack);
		curr++;
	}
	while(curr < total){
		memset(&server_num, 0, sizeof(int));
		memset(&client_ack, 0, sizeof(int));
		
		recv(clientsock, &server_num, sizeof(int), 0);
		
		if(selected[server_num] == 0){
			selected[server_num] = 1;
			printf("Frame %d received\n", server_num);
			client_ack = server_num;
			send(clientsock, &client_ack, sizeof(int), 0);
			printf("Ack %d sent\n", client_ack);
			curr++;
		}
		else{
			printf("Alreadyt received... Ignoring.......\n");
		}
	}
	close(serversock);
	close(clientsock);
}
