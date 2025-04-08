//input if 1 then 0

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<netdb.h>
#include<fcntl.h>

void main(){
	int serversock;
    	struct sockaddr_in serveraddr;
    	char filename[1000], filedata[1000], answer[1000];
    	
    	serversock = socket(AF_INET, SOCK_STREAM, 0);
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(2000);
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	connect(serversock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    	listen(serversock, 5);
    	
    	int f, n;
    	
    	printf("Enter the filename : ");
    	scanf("%s", filename);
    	write(serversock, filename, 1000);
    	read(serversock, filedata, 1000);
    	
	printf("Contents : %s\n", filedata);
  
    	close(serversock);
}
