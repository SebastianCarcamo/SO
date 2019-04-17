#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

void min(void){}

int main(){
	struct timeval start;
	struct timeval finish;

	long long sumA=0;
	for(int i=0;i<20;i++){
		gettimeofday(&start,0);
		min();
		gettimeofday(&finish,0);
		sumA = sumA + (finish.tv_usec-start.tv_usec);
	}
	printf("Tiempo funcion minima: %.3Lg \n",(long double)sumA/20000000);


	long long sumB=0;
	for(int i=0;i<20;i++){
		gettimeofday(&start,0);
		getpid();
		gettimeofday(&finish,0);
		sumB = sumB + (finish.tv_usec-start.tv_usec);
	}
	printf("TIempo de getpid(): %.3Lg \n",(long double)sumB/20000000);
}
