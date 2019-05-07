#include <stdio.h>
#include "atomic_ops.h"
#include "hrtimer_x86.c"
#include <pthread.h>

#define THREADS_NUM 8


int vGlobal =0;
ticket_lock_t serve;


void* sumar(void*){	

	for(int i=0;i<50000;i++){
		ticket_acquire(&serve);
		vGlobal++;
		ticket_release(&serve);
		
	}
}

int main(){
	pthread_t threads[THREADS_NUM];
	double start;
	double end;

	start = gethrtime_x86();
	for(int i=0;i<THREADS_NUM;i++){
		pthread_create(&threads[i],NULL,sumar,NULL);
	}

	for(int i=0;i<THREADS_NUM;i++){
		pthread_join(threads[i],NULL);
	}
	end = gethrtime_x86();
	printf("%f\n",end - start);
}
