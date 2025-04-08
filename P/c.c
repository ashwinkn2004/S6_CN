#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

void main(){
    int serversock, frames, total, client_Ack, server_num, curr = 0;
    struct sockaddr_in serveraddr;
    
    serversock = socket(AF_INET, SOCK_STREAM, 0);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(1211);
    serveraddr.sin_addr.s_addr = INADDR_ANY;

    connect(serversock, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

    printf("Enter the total number of elements: ");
    scanf("%d", &total);
    printf("Enter the frame size: ");
    scanf("%d", &frames);
    
    send(serversock, &total, sizeof(int), 0);
    send(serversock, &frames, sizeof(int), 0);

    int sender = frames;
    for(int i = 0; i < frames; i++){
        server_num = i;
        send(serversock, &server_num, sizeof(int), 0);
        printf("Frame %d sent\n", i);
    }

    while(curr < total - frames ){
        int choice = rand() % 2;
        if(choice == 1){
            memset(&client_Ack, 0, sizeof(int));
            recv(serversock, &client_Ack, sizeof(int), 0);
            printf("Received Ack for %d\n", client_Ack);
            server_num = sender;
            send(serversock, &server_num, sizeof(int), 0);
            printf("Frame %d sent\n", server_num);
            sender++;
            curr++;
        }
        else{
            printf("Acknowledgement lost, retransmitting %d\n", curr);
            server_num = curr;
            send(serversock, &server_num, sizeof(int), 0);
            printf("Frame %d sent\n", server_num);
        }
    }
    while(curr < total){
        memset(&client_Ack, 0, sizeof(int));
		recv(serversock, &client_Ack, sizeof(int), 0);
		printf("recieved ack for %d\n", client_Ack);
		curr++;
    }
    close(serversock);
}