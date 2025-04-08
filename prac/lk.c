#include<stdio.h>

#define limit 10

int rndm(int a){
	int rn = (random()%10)%a;
	return rn == 0 ? 1 : rn;
}

void main(){
	int psize[limit], bsize, p_sz_rm = 0, clk, oprate, op;
	
	for(int i = 0; i < limit; i++){
		psize[i] = rndm(6)*10;
		printf("Packets : %d bytes\n", psize[i]);
	}
	printf("Enter the output rate : ");
	scanf("%d", &oprate);
	printf("Enter the bucket size : ");
	scanf("%d", &bsize);
	
	for(int i = 0; i < limit; i++){
		if(psize[i] + p_sz_rm > bsize){
			if(psize[i] > bsize) printf("Incoming packet size %d is heavy\n", psize[i]);
			else printf("Bucket size exceeded\n");
		}
		else{
			p_sz_rm += psize[i];
			printf("Incoming packet %d\n", psize[i]);
			printf("Remaining bsize = %d\n", bsize - p_sz_rm);
			int p_time = rndm(4)*10;
			for(int clk = 0; clk < p_time; clk += 10){
				if(p_sz_rm){
					if(p_sz_rm < oprate){
						op = p_sz_rm;
						p_sz_rm = 0;
					}
					else{
						op = oprate;
						p_sz_rm -= oprate;
					}
					printf("Packet %d received\n", psize[i]);
				}
				else{
					printf("No packet to send");
				}
			}
		}
	}
}
