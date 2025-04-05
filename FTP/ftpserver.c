#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<fcntl.h>

void main(){
	struct sockaddr_in serveraddr, clientaddr;
	int n, f, newserversock, serversock;
	char filename[300], filedata[1000];
	
	serversock = socket(AF_INET, SOCK_STREAM, 0);
	
	bzero((char *)&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(2000);
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	bind(serversock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
	listen(serversock, 2);
	
	while(1){
		int clientsize = sizeof(clientaddr);
		newserversock = accept(serversock, (struct sockaddr *)&clientaddr, &clientsize);
		
		n = read(newserversock, filename, 300);
		filename[n] = "\0";
		f = open(filename, O_RDWR);
		n = read(f, filedata, 1000);
		printf("Data = %s\n", filedata);
		write(newserversock, filedata, n);
	}
	close(serversock);
	close(newserversock);
}
