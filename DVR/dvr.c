#include<stdio.h>

#define max 20

struct node{
	unsigned dist[max];
	unsigned from[max];
}rt[max];

void main(){
	int costmatrix[max][max], count, nodes;
	
	printf("Enter the number of nodes : ");
	scanf("%d",&nodes);
	
	printf("Enter the costmatrix : \n");
	for(int i = 0; i < nodes; i++){
		for(int j = 0; j < nodes; j++){
			scanf("%d",&costmatrix[i][j]);
			costmatrix[i][i] = 0;
			rt[i].dist[j] = costmatrix[i][j];
			rt[i].from[j] = j;
		}
	}
	do{
		count = 0;
		for(int i = 0; i < nodes; i++){
			for(int j = 0; j < nodes; j++){
				for(int k = 0; k < nodes; k++){
					if(rt[i].dist[j] > costmatrix[i][k] + rt[k].dist[j]){
						rt[i].dist[j] = rt[i].dist[k] + rt[k].dist[j];
						rt[i].from[j] = k;
						count++;
					}
				}
			}
		}
	}while(count != 0);
	
	for(int i = 0; i < nodes; i++){
		printf("Router : %d\n", i+1);
		for(int j = 0; j < nodes; j++){
			printf("Nodes %d via %d distance %d\n", j+1, rt[i].from[j]+1, rt[i].dist[j]);
		}
	}
}
