#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<netdb.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>

#define limit 10

int rndm(int a){
    int rn = (random()%10)%a;
    return rn == 0 ? 1 : rn;
}

void main(){
    int psize[limit], bsize, p_sz_rm = 0, op_rate, op = 0;
    for(int i = 0; i < limit; i++){
        psize[i] = rndm(6)*10;
        printf("Packet : %d\n", psize[i]);
    }
    printf("Enter the bsize :");
    scanf("%d", &bsize);
    printf("Enter the op_rate :");
    scanf("%d", &op_rate);

    for(int i = 0; i < limit; i++){
        if(psize[i] + p_sz_rm > bsize){
            if(psize[i] > bsize) printf("Incoming packet is heavy\n");
            else printf("packet %d rejected\n", psize[i]);
        }
        else{
            p_sz_rm += psize[i];
            printf("Packet %d is accepted\n", psize[i]);
            printf("Packet size remaining : %d\n", p_sz_rm);
            int p_time = rndm(4)*10;
            for(int clk = 10; clk < p_time; clk += 10){
                sleep(2);
                if(p_sz_rm){
                    if(p_sz_rm < op_rate){
                        op = p_sz_rm;
                        p_sz_rm = 0;
                    }
                    else{
                        op = op_rate;
                        p_sz_rm -= op_rate;
                    }
                    printf("Packet %d received\n", op);
                }
                else{
                    printf("No packets to receive\n");
                }
            }
        }
    }
}