#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<netdb.h>
#include<fcntl.h>

void main(){
    int serversock, newserversock;
    struct sockaddr_in serveraddr, clientaddr;
    char filename[1000], filedata[1000];

    bzero((char *)&serveraddr, sizeof(serveraddr));

    serversock = socket(AF_INET, SOCK_STREAM, 0);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(2000);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    bind(serversock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    listen(serversock, 5);

    int n, f;

    while(1){
        int clientsize = sizeof(clientaddr);
        newserversock = accpet(serversock, (struct sockaddr *)&clientaddr, &clientsize);
        n = read(newserversock, filename, 1000);
        filename[n] = "\0";
        f = read(newserversock, filedata, O_RDWR);
        printf("Contents : %s", filedata);
        write(newserversock, filenada, n);
    }
    
    close(serversock);
    close(newserversock);
}
