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
    int serversock, newserversock, n, f;
    struct sockaddr_in serveraddr, clientaddr;
    char filename[1000], filedata[1000];

    bzero((char *)&serveraddr, sizeof(serveraddr));
    serversock = socket(AF_INET, SOCK_STREAM, 0);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(2000);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(serversock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    listen(serversock, 5);
    while(1){
        int clientsize = sizeof(clientaddr);
        newserversock = accept(serversock, (struct sockaddr *)&clientaddr, &clientsize);

        n = read(newserversock, filename, 1000);
        filename[n] = '\0';

        f = open(filename, O_RDWR);
        n = read(f, filedata, 1000);
        printf("Contents : %s", filedata);
        write(newserversock, filedata, n);
        close(newserversock);
    }
    close(serversock);
}