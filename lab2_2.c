#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define rows1 4
#define columns1 5
#define rows2 5
#define columns2 4

#define MAX_T 2



void multiply(int **matrx1, int **matrx2,int **matrx3,int z,int x, int v){


for(int i=0;i<z;i++){
	for(int o=0;o<v;o++)
		matrx3[i][o]=0;
}
for(int i=0;i<z;i++){
	for(int o=0;o<v;o++){
		for(int p=0;p<x;p++){
			matrx3[i][o]+=matrx1[i][p]* matrx2[p][o];
			}
		}
}
}


int main(){

srand(time(NULL));


int **M1 = (int**)malloc(rows1 * sizeof(int*));
for(int i=0;i<rows1;i++){
	M1[i]=(int*)malloc(columns1 * sizeof(int));
}

int **M2 = (int**)malloc(rows2 * sizeof(int*));
for(int i=0;i<rows2;i++){
	M2[i]=(int*)malloc(columns2 * sizeof(int));
}

int **M3 = (int**)malloc(rows1 * sizeof(int*));
for(int i=0;i<rows1;i++){
	M3[i]=(int*)malloc(columns2 * sizeof(int));
}


for(int i=0;i<rows1;i++){
	for(int o=0;o<columns1;o++)
		M1[i][o]= rand() %6;
}


for(int i=0;i<rows2;i++){
	for(int o=0;o<columns2;o++)
		M2[i][o]= rand() %6;
}

//impresion de matrices 1 y 2
for(int i=0;i<rows1;i++){
	printf("\n");
	for(int o=0;o<columns2;o++)
		printf("%d\t",M1[i][o]);
}
printf("\n\n");

for(int i=0;i<rows2;i++){
	printf("\n");
	for(int o=0;o<columns2;o++)
		printf("%d\t",M2[i][o]);
}
printf("\n");
//termina impresion de matrices

multiply(M1,M2,M3,rows1,columns1,columns2);

//impresion matriz resultante

for(int i=0;i<rows1;i++){
	printf("\n");
	for(int o=0;o<columns2;o++)
		printf("%d\t",M3[i][o]);
}
printf("\n");
//impresion matriz resultante

return 0;
}
