#include <stdlib.h>
#include <pthread.h>
#include "hrtimer_x86.c"
#define THREAD_NUM 8

int vGlobal = 0;
pthread_mutex_t lock;


void *sumar(void*){
	for(int i=0; i<50000;i++){
		pthread_mutex_lock(&lock);
		vGlobal++;
		pthread_mutex_unlock(&lock);
	}
}

int main(){
	pthread_t threads[THREAD_NUM];
	double start;
	double end;

	start = gethrtime_x86();
	for(int i=0;i<THREAD_NUM;i++){
		pthread_create(&threads[i],NULL,sumar,NULL);
	}
	for(int i=0;i<THREAD_NUM;i++){
		pthread_join(threads[i],NULL);
	}
	end = gethrtime_x86();
	printf("%f\n",end - start);
	return 0;
}
