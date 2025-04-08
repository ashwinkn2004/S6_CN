#include<stdio.h>
#include<stdlib.h>

#define limit 10

int rndm(int a){
	int rn = (random()%10)%a;
	return rn == 0 ? 1 : rn;
}

void main(){
	int psize[limit], bsize, p_sz_rm = 0, clk, p_time, oprate, op = 0;
	
	for(int i = 0; i < limit; i++){
		psize[i] = rndm(6)*10;
		printf("Packet Size = %d\n", psize[i]);
	}
	
	printf("Enter the output rate : ");
	scanf("%d", &oprate);
	printf("Enter the bucket size : ");
	scanf("%d", &bsize);
	
	for(int i = 0; i < limit; i++){
		if(psize[i] + p_sz_rm > bsize){
			if(psize[i] > bsize){
				printf("Incoming packet is heavy\n");
			}
			else{
				printf("Bucket size exceeded.... packet %d discarded\n", psize[i]);
			}
		}
		else{
			p_sz_rm += psize[i];
			printf("Incoming packet %d \n", psize[i]);
			printf("Remaining to transmit %d\n", p_sz_rm);
			p_time = rndm(4)*10;
			for(clk = 10; clk <= p_time; clk += 10){
                sleep(1);
				if(p_sz_rm){
					if(p_sz_rm > oprate){
						op = oprate;
						p_sz_rm -= oprate;
					}
					else{
						op = p_sz_rm;
						p_sz_rm = 0;
					}
					printf("pakcet %d trnsmitted", op);
					printf("------Bytes remaining to transmit %d\n", p_sz_rm);
				}
				else{
					printf("No packet to transmit\n");
				}
			}
		}
	}
}
