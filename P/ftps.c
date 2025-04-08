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

    bind(serversock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    listen(serversock, 5);

    while(1){
        int len = sizeof(clientaddr);
        clientsock = accept(serversock, (struct sockaddr *)&clientaddr, &len);
        n = read(clientsock, filename, sizeof(filename));
        filename[n] = '\0';
        f = open(filename, O_RDWR);
        n = read(f, filedata, sizeof(filedata));
        printf("filedata: %s\n", filedata);
        write(clientsock, filedata, n);
        close(clientsock);
    }
    close(serversock);
}