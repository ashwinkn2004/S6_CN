#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<netdb.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>

void main(){
    int serversock, clientsock, n, f;
    struct sockaddr_in clientaddr, serveraddr; 
    char filename[1000], filedata[1000];

    serversock = socket(AF_INET, SOCK_STREAM, 0);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8080);
    serveraddr.sin_addr.s_addr = INADDR_ANY;

    connect(serversock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

    printf("Enter the filename : ");
    scanf("%s", filename);

    int len = strlen(filename);

    write(serversock, filename, len);
    read(serversock, filedata, sizeof(filedata));
    printf("filedata: %s\n", filedata);
    close(serversock);
}