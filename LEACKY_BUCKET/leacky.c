#include<stdio.h>
#include<string.h>
#include<unistd.h>

#define packets 10

int rndm(int a){
    int rn = (random()%10)%a;
    return rn == 0 ? 1 : rn;
}

void main(){
    int psize[packets], i, bsize, p_sz_rm = 0, oprate, op;
    for(i = 0; i < packets; i++){
        psize[i] = rndm(6)*10;
        printf("Packets = %d \n",psize[i]);
    }
    printf("Enter the output rate : ");
    scanf("%d",&oprate);
    printf("Enter the bucket size: ");
    scanf("%d",&bsize);
    
    for(i = 0; i < packets; i++){
        if(p_sz_rm+psize[i] > bsize){
            if(psize[i] > bsize){
                printf("Incoming packet size %d is greater than bucket size %d \n",psize[i],bsize);
            }
            else{
                printf("Bucket size exceeded \n");
            }
        }
        else{
            p_sz_rm += psize[i];
            printf("Incoming packet size %d bytes \n",psize[i]);
            printf("Bucket size remaining %d bytes \n",bsize-p_sz_rm);
            int p_time = rndm(4)*10, clk;
            for(clk = 10; clk < p_time; clk+=10){
                if(p_sz_rm){
                    if(p_sz_rm < oprate){
                        op = p_sz_rm;
                        p_sz_rm = 0;
                    }
                    else{
                        op = oprate;
                        p_sz_rm -= oprate;
                    }
                    printf("Received\n");
                }
                else{
                    printf("No packets to send \n");
                }
            }
        }
    }
} 