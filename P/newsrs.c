#include<stdio.h>
#include<arpa/inet.h>
#include<string.h>
#include<sys/socket.h>

void main(){
	int serversock, clientsock;
	struct sockaddr_in serveraddr, clientaddr;
	
	serversock = socket(AF_INET, SOCK_STREAM, 0);
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(8888);
	serveraddr.sin_addr.s_addr = INADDR_ANY;
	
	bind(serversock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
	listen(serversock, 5);
	
	int len = sizeof(clientaddr);
	clientsock = accept(serversock, (struct sockaddr *)&clientaddr, &len);
	
	int total, frames, selected[1000], client_ack, server_num, curr = 0;
	
	recv(clientsock, &total, sizeof(int), 0);
	recv(clientsock, &frames, sizeof(int), 0);
	
	for(int i = 0; i < 1000; i++){
		selected[i] = 0;
	}
	
	for(int i = 0; i < frames; i++){
		memset(&server_num, 0, sizeof(int));
		memset(&client_ack, 0, sizeof(int));
		recv(clientsock, &server_num, sizeof(int), 0);
		selected[server_num] = 1;
		printf("Frame %d received\n", server_num);
		client_ack = server_num;
		send(clientsock, &client_ack, sizeof(int), 0);
		printf("Ack received for %d\n", client_ack);
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
			printf("Ack received for %d\n", client_ack);
			send(clientsock, &client_ack, sizeof(int), 0);
			curr++;
		}
		else{
			printf("Frame already received ignoring.......\n");
		}
	}
	close(clientsock);
	close(serversock);
}
