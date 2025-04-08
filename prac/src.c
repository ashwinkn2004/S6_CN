#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
//abbreviations to make code easily understandable
#define PORT 8080
#define SA struct sockaddr

int main(){
 
	int sock_desc,window,r=0,p=0,k,frame;
 	char queue[30][30],server_message[100],client_message[100],buffer[30][30];
 	struct sockaddr_in server_addr;
 
 	//create socket
 	sock_desc = socket(AF_INET,SOCK_STREAM,0);
 	if(sock_desc<0){
 		puts("Unable to create socket!");
 		exit(0);
 	}
 	puts("Socket created successfully");
 
 	//set port and ip
 	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
 	
 	// Send connection request to server
	if(connect(sock_desc, (SA*)&server_addr, sizeof(server_addr)) < 0){
		puts("Unable to connect");
		exit(0);
	}
	puts("Connected with server successfully\n");
	
	// Get input from the user:
	puts("enter window size:");
	scanf("%d",&window);
	printf("Enter the total number of frames:");
	scanf("%d",&frame);
	printf("Enter frames:");
	for(k=0;k<frame;k++){scanf("%s",buffer[k]);}
 	
 	for(k=0;k<window;k++){
 		strcpy(queue[r++],buffer[k]);
 	}
 	
 	while(frame>0){
 		memset(client_message,'\0',sizeof(client_message));
 		memset(server_message,'\0',sizeof(server_message));
		strcpy(client_message,queue[p]);
		printf("\nSending Message->%s...",queue[p]);
		if(send(sock_desc, client_message, strlen(client_message), 0) < 0){
			printf("Unable to send message\n");
			return -1;
		}
		if(recv(sock_desc, server_message, 1, 0) < 0){
				printf("Error while receiving server's msg\n");
		}
		else if(strcmp(server_message,"N")==0 || strcmp(server_message,"n")==0){
			printf("\nServer does not acknowledge->%s",buffer[p]);
			strcpy(queue[r++],queue[p]);
		}
		else if(strcmp(server_message,"Y")==0 || strcmp(server_message,"y")==0){
 			printf("\nServer Acknowledges->%s\n",queue[p]);
 			strcpy(queue[r++],buffer[k++]);
 			frame--;
 		}
 		p++;
 	}
 	send(sock_desc, "0",1, 0);
 	
 	close(sock_desc);
 	return -1;
 
}