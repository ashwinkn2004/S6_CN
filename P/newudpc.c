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
    
    int clientsize = sizeof(serveraddr);
    
    int limit;
    printf("Enter the limit : ");
    scanf("%d", &limit);
    
    sendto(serversock, &limit, sizeof(int), 0, (struct sockaddr *)&serveraddr, clientsize);
    for(int i = 0; i < limit; i++){
    	recvfrom(serversock, &clientmessage, sizeof(int), 0, (struct sockaddr *)&serveraddr, &clientsize);
    	printf("%d\t", clientmessage);
    }
    printf("\n");
    close(serversock);
}
