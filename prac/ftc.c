#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<netinet/in.h>
#include<arpa/inet.h>

void main(){
    int clientsock, n, f, length;
    struct sockaddr_in serveraddr, clientaddr;
    char filename[1000], filedata[1000];

    bzero((char *)&serveraddr, sizeof(serveraddr));
    clientsock = socket(AF_INET, SOCK_STREAM, 0);
    clientaddr.sin_family = AF_INET;
    clientaddr.sin_port = htons(2000);
    clientaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(clientsock, (struct sockaddr *)&clientaddr, sizeof(clientaddr));
    
    printf("Enter the file name : ");
    scanf("%s", filename);
    length = strlen(filename);
    write(clientsock, filename, length);
    read(clientsock, filedata, 1000);
    printf("Contents : %s", filedata);
    close(clientsock);
}