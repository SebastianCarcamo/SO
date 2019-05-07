#include <stdio.h>
#include <pthread.h>
#include "hrtimer_x86.c"

#define THREAD_NUM 8
#define TIMES 10000

struct bar_type{
	int counter = 0;
	pthread_mutex_t lock;
	int flag = 0;
	};

struct bar_type rsb;

int sense = 0;

void BARRIER (bar_type* rsb,int p){

	int local_sense = 1 - sense;
	pthread_mutex_lock(&(rsb->lock));
	rsb->counter++;
	int arrived = rsb->counter;
	if(arrived == p){
		pthread_mutex_unlock(&(rsb->lock));
		rsb->counter = 0;
		rsb->flag = local_sense;
	}
	else{
		pthread_mutex_unlock(&(rsb->lock));
		while(rsb->flag != local_sense){}
	}
}

void* algo(void*){

	for(int i = 0;i< TIMES ;i++){
		//algo antes de llegar a la barrera
		BARRIER(&rsb,THREAD_NUM);
	}

}

int main(){

	pthread_t threads[THREAD_NUM];
	double start;
	double end;
	

	start = gethrtime_x86();
	for(int i=0;i<THREAD_NUM;i++){
		pthread_create(&threads[i],NULL,algo,NULL);
	}

	BARRIER(&rsb,THREAD_NUM);

	for(int i=0;i<THREAD_NUM;i++){
		pthread_join(threads[i],NULL);
	}
	end = gethrtime_x86();
	printf("%f\n",end-start);

	return 0;
}
