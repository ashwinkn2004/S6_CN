#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<netdb.h>

void main(){
    int clientsock;
    struct sockaddr_in serveraddr, clientaddr;
    char filename[1000], filedata[1000];

    bzero((char *)&serveraddr, sizeof(serveraddr));

    clientsock = socket(AF_INET, SOCK_STREAM, 0);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(2000);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(clientsock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

    int n, length;
    printf("Enter the file name : ");
    scanf("%s", filename);
    length = strlen(filename);
    write(clientsock, filename, length);
    read(clientsock, filedata, 1000);
    printf("Contents : %s", filedata);

    close(clientsock);
}
