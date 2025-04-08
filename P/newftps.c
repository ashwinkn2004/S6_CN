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
	int serversock, clientsock;
    	struct sockaddr_in serveraddr, clientaddr;
    	char filename[1000], filedata[1000], answer[1000];
    	
    	serversock = socket(AF_INET, SOCK_STREAM, 0);
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(2000);
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	bind(serversock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    	listen(serversock, 5);
    	
    	int f, n;
    	
    	while(1){
    		int clientsize = sizeof(clientaddr);
    		clientsock = accept(serversock, (struct sockaddr *)&clientaddr, &clientsize);
    		
    		n = read(clientsock, filename, 1000);
    		filename[n] = '\0';
    		f = open(filename, O_RDWR);
    		n = read(f, filedata, 1000);
    		filedata[n] = '\0';
    		printf("Contents : %s\n", filedata);
  
    		for(int i = 0; i < strlen(filedata); i++){
    			if(filedata[i] == '0'){
    				filedata[i] = '1';
    			}
    			else filedata[i] = '0';
    		}
    		printf("After conversion : %s\n", filedata);
    		write(clientsock, filedata, n);
    		close(clientsock);
    	}
    	close(serversock);
}
