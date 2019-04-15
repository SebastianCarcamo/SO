#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/wait.h>


char *limpiar = "\033[H\033[J";
#define MAX 1024
char prompt[] = "SebastianOS> ";


void ls(char* array[]){
DIR *mydir;
char ptr[MAX];
struct dirent *dptr;
getcwd(ptr,sizeof(ptr));

mydir = opendir((const char*)ptr);
while((dptr=readdir(mydir))!=NULL){
	if(dptr->d_name[0] == '.')continue;
	printf("%s\t", dptr->d_name);
}
printf("\n");
closedir(mydir);
} 

void pwd(char* array[]){
char cwd[MAX];
getcwd(cwd,sizeof(cwd));
printf("%s\n",cwd);
}

void cd(char* array[]){
chdir(array[1]);
}

void dir(char* array[]){
mkdir(array[1],S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}

void rm(char* array[]){
remove(array[1]);
}

void nano(char* array[]){
execvp("nano",array);
}

void cat(char* array[]){
	execvp("cat",array);
}

void readstr (char* str,char* array[]){
	char *pch = strtok (str," ");
	int i = 0;

	while (pch != NULL){
		array[i++] = pch;
		pch = strtok (NULL," ");
	}

}

int main(){
	char cmdline[MAX];
	while(1){
		printf("%s", prompt);
		char *array[MAX];
		
		if((fgets(cmdline, MAX, stdin) == NULL) && ferror(stdin))
			break;

		if(feof(stdin)){
			printf("\n");
			exit(0);
		}

		cmdline[strlen(cmdline)-1] = '\0';
		readstr(cmdline,array);

		if (strcmp(array[0],"cd")==0){
		cd(array);
		}
		else{
			if(fork() ==0){

		if (strcmp(array[0],"clear")==0){
		printf("%s",limpiar);
		}
		if (strcmp(array[0],"pwd")==0){
		pwd(array);
		}
		if (strcmp(array[0],"mkdir")==0){
		dir(array);	
		}
		if (strcmp(array[0],"rm")==0){
		rm(array);
		}
		if (strcmp(array[0],"ls")==0){
		ls(array);
		}
		if (strcmp(array[0],"nano")==0){
		nano(array);
		}
		if (strcmp(array[0],"cat")==0){
		cat(array);
		}

			}
			else wait(NULL);
	}
	}
}
