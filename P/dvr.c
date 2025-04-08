#include<stdio.h>

struct node{
    unsigned dist[100];
    unsigned from[100];
}rt[100];

void main(){
    int costmatrix[100][100], count, limit;
    printf("Enter the number of nodes : ");
    scanf("%d", &limit);
    printf("Enter the Costmatrix : \n");
    for(int i = 0; i < limit; i++){
        for(int j = 0; j < limit; j++){
            scanf("%d", &costmatrix[i][j]);
            costmatrix[i][i] = 0;
            rt[i].dist[j] = costmatrix[i][j];
            rt[i].from[j] = j;
        }
    }
    do{
        count = 0;
        for(int i = 0; i < limit; i++){
            for(int j = 0; j < limit; j++){
                for(int k = 0; k < limit; k++){
                    if(rt[i].dist[j] > costmatrix[i][k] + rt[k].dist[j]){
                        rt[i].dist[j] = rt[i].dist[k] + rt[k].dist[j];
                        rt[i].from[j] = k;
                        count++;
                    }
                }
            }
        }
    }while(count != 0);

    printf("Final Routing Table : \n");
    for(int i = 0; i < limit; i++){
        printf("Router %d : ", i + 1);
        for(int j = 0; j < limit; j++){
            printf("Node %d via %d distance %d\n", j, rt[i].from[j]+1, rt[i].dist[j]);
        }
        printf("\n");
    }
}