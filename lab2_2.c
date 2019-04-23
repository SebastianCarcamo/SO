#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

#define rows1 1000
#define columns1 1000
#define rows2 1000
#define columns2 1000

#define MAX_T 1

struct data{
	int **mtx1;
	int **mtx2;
	int **mtx3;
	int start;
	int r1;
	int c1;
	int c2;
	int t;
};

void multiply(void* e){
struct data *pack = (struct data *) e;
int **mtx1 = pack->mtx1;
int **mtx2 = pack->mtx2;
int **mtx3 = pack->mtx3;
int start = pack->start;
int r1 = pack->r1;
int c1 = pack->c1;
int c2 = pack->c2;
int t = pack->t;

for(int i = start; i < r1*c2; i +=t){
	mtx3[i/c2][i%c2] = 0;
	for(int j = 0;j<c1; j++){
		mtx3[i/c2][i%c2] += mtx1[i/c2][j] * mtx2[j][i%c2];
	}
}

/*
for(int i=0;i<rows1;i++){
	for(int o=0;o<columns2;o++)
		matrx3[i][o]=0;
}
for(int i=0;i<rows1;i++){
	for(int o=0;o<columns2;o++){
		for(int p=0;p<columns1;p++){
			matrx3[i][o]+=matrx1[i][p]* matrx2[p][o];
			}
		}
}
*/
}

int main(){

struct timeval s;
struct timeval e;
int rc;

srand(time(NULL));


int *M1 = (int)malloc(rows1 * sizeof(int));
for(int i=0;i<rows1;i++){
	M1[i]=(int*)malloc(columns1 * sizeof(int));
}

int *M2 = (int)malloc(rows2 * sizeof(int));
for(int i=0;i<rows2;i++){
	M2[i]=(int*)malloc(columns2 * sizeof(int));
}

int *M3 = (int)malloc(rows1 * sizeof(int));
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

pthread_t threads[MAX_T];
struct data pack[MAX_T];


gettimeofday(&s,NULL);
for(int i =0;i<MAX_T;i++){
	pack[i].mtx1 = M1;
	pack[i].mtx2 = M2;
	pack[i].mtx3 = M3;
	pack[i].start = i;
	pack[i].r1 = rows1;
	pack[i].c1 = columns1;
	pack[i].c2 = columns2;
	pack[i].t = MAX_T;

    rc = pthread_create(threads + i, NULL, multiply,(void *)&pack[i]);

	if (rc){
		printf("ERROR, return code from pthread_create() is %d\n", rc);
		exit(-1);
	}
}

for(int i = 0; i< MAX_T;i++){
	rc = pthread_join(threads[i],NULL);
	if (rc){
		printf("ERROR, return code from pthread_create() is %d\n", rc);
		exit(-1);
	}	
}

gettimeofday(&e,NULL);

long long time = (long long)(e.tv_usec - s.tv_usec);
time += (long long)(e.tv_sec - s.tv_sec)*1000000;

printf("%lf\n",(double)time/1000000.0);

return 0;
