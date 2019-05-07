#include <stdio.h>
#include <pthread.h>
#include "hrtimer_x86.c"

#define THREAD_NUM 2
#define TIMES 10

pthread_barrier_t barrier;

void* algo(void*){

	for(int i = 0;i< TIMES ;i++){
		//algo antes de llegar a la barrera
		pthread_barrier_wait(&barrier);
	}

}

int main(){
	pthread_t threads[THREAD_NUM];
	pthread_barrier_init(&barrier,NULL,THREAD_NUM);
	double start;
	double end;

	start = gethrtime_x86();
	for(int i=0;i<THREAD_NUM;i++){
		pthread_create(&threads[i],NULL,algo,NULL);
	}

	pthread_barrier_wait(&barrier);

	for(int i=0;i<THREAD_NUM;i++){
		pthread_join(threads[i],NULL);
	}
	pthread_barrier_destroy(&barrier);
	end = gethrtime_x86();
	printf("%f\n",end-start);

	return 0;
}
