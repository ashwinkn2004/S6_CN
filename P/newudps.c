#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<netdb.h>

void main(){
    int serversock;
    struct sockaddr_in serveraddr, clientaddr;
    int servermessage, clientmessage;
    
    serversock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(2000);
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    
    bind(serversock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    
    int clientsize = sizeof(clientaddr);
    
    recvfrom(serversock, &clientmessage, sizeof(int), 0, (struct sockaddr *)&clientaddr, &clientsize);
    int a = 0, b = 1, c = 0;
    sendto(serversock, &a, sizeof(int), 0, (struct sockaddr *)&clientaddr, clientsize);
    printf("%d\t", a);
    sendto(serversock, &b, sizeof(int), 0, (struct sockaddr *)&clientaddr, clientsize);
    printf("%d\t", b);
    for(int i = 0; i < clientmessage - 2; i++){
    	c = a + b;
    	sendto(serversock, &c, sizeof(int), 0, (struct sockaddr *)&clientaddr, clientsize);
    	printf("%d\t", c);
    	a = b;
    	b = c;
    }
    printf("\n");
    close(serversock);
}
