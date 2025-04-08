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
    	
    	int frames, window;
    	
    	printf("Enter the total frames : ");
    	scanf("%d", &frames);
    	
    	printf("Enter the window : ");
    	scanf("%d", &window);
    	sendData(clientsock, frames, window);
}
