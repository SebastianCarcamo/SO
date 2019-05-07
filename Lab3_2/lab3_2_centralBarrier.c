#include <stdio.h>
#include <pthread.h>
#include "hrtimer_x86.c"

#define THREAD_NUM 1
#define TIMES 10

struct bar_type{
	int counter_in;
	int counter_out;
	pthread_mutex_t lock;
	int flag = 0;
	};

struct bar_type cb;

void BARRIER (bar_type* cb,int p){
	pthread_mutex_lock(&(cb->lock));
	if(cb->counter_in == p){
		if(cb->counter_out==0){
			cb->flag =0;
		}
		else{
			pthread_mutex_unlock(&(cb->lock));
			while(cb->counter_out != p);
			pthread_mutex_lock(&(cb->lock));
			cb->flag = 0;
		}
	}
	cb->counter_in++;
	int arrived = cb->counter_in;
	pthread_mutex_unlock(&(cb->lock));
	if(arrived ==p){
		cb->counter_in = 0;
		cb->counter_out =1;
		cb->flag =1 ;
	}
	else{
		while(cb->flag ==0);
		pthread_mutex_lock(&(cb->lock));
		cb->counter_out++;
		pthread_mutex_unlock(&(cb->lock));
	}
}

void* algo(void*){

	for(int i = 0;i< TIMES ;i++){
		//algo antes de llegar a la barrera
		BARRIER(&cb,THREAD_NUM);
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

	BARRIER(&cb,THREAD_NUM);

	for(int i=0;i<THREAD_NUM;i++){
		pthread_join(threads[i],NULL);
	}
	end = gethrtime_x86();
	printf("%f\n",end-start);

	return 0;
}
