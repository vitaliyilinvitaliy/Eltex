#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	pid_t parent = getpid();
	printf("Parent getpid() = %d\n",getpid());

	fork();
	fork();
	
	if(getppid() == parent){
		fork();
	}

	printf("Proc. getpid() = %d : getppid() = %d\n", getpid(), getppid());

	if(getpid() == parent){
		wait();
	}else{
		exit(0);
	}	
}