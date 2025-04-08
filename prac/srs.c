#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
//abbreviations to make code easily understandable
#define PORT 8080
#define SA struct sockaddr

int main(){
	
	//initialize all the thingys
	int sock_desc, client_sock,client_size, frame, window;
	char client_message[100],server_message[100],queue[30][30];
	struct sockaddr_in server_addr, client_addr;
	
	//create a socket 
	sock_desc = socket(AF_INET,SOCK_STREAM,0);
	if(sock_desc < 0){
		puts("ERROR CREATING SOCKET!!");
		exit(0);
	}
	puts("SOCKET CREATED SUCCESSFULLY");
	
	//set the port and the ip
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(PORT);
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	
	//bind it
	if(bind(sock_desc, (SA*)&server_addr,sizeof(server_addr))<0){
		puts("COULDN'T BIND!!");
		exit(0);
	}	
	puts("BINDING SUCCESSFULL");
	
	//listen for clients
	listen(sock_desc,1);
	
	//accept connection
	client_size = sizeof(client_addr);
	client_sock = accept(sock_desc, (SA*)&client_addr,&client_size);
	
	printf(
		"\nClient connected at ip: %s and port: %i\n"
		,inet_ntoa(client_addr.sin_addr)
		,ntohs(client_addr.sin_port)
		);
		
	//the actual running part
	while(1)
	{
		memset(client_message, '\0', sizeof(client_message));
		memset(server_message, '\0', sizeof(server_message));
		recv(client_sock,client_message,1,0);
		if(atoi(client_message)==0){break;}
		printf("Frame recieved: %s\n", client_message);
		printf("\nFrame [%s] Acknowledgement:? Ack-Y or y, NACK- N or n: ",client_message);
		scanf("%s",server_message);
		if (send(client_sock, server_message, strlen(server_message), 0) < 0){
			printf("Can't send\n");
			exit(0);
		}
	}
	close(sock_desc);
	close(client_sock);	
	return 0;
}