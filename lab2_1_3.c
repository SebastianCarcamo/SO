#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>

int main(){
	int pipe1[2], pipe2[2];
	char a = 'a';
	struct timeval start;
	struct timeval finish;
	long suma = 0;
	long childT = 0;

	for(int i=0;i<20;i++){
		if(fork() ==0){
			gettimeofday(&start,0);
			write(pipe2[1],&a,1);
			read(pipe1[0],&a,1);
			gettimeofday(&finish,0);
			read(pipe1[0],&a,1);
			childT = (long)(finish.tv_usec-start.tv_usec);
			write(pipe2[1], &childT, 8);
			return 0;
		}else{
			write(pipe1[1],&a,1);
			gettimeofday(&start,0);
			read(pipe2[0],&a,1);
			gettimeofday(&finish,0);
			write(pipe1[1],&a,1);
			read(pipe2[0],&childT,8);
		}
		suma = suma + (long)(finish.tv_usec-start.tv_usec - childT);
	}
	printf("Tiempo de cambio de contexto: %.3Lg\n",(long double)(suma/40000000.0));
			return 0;
}
