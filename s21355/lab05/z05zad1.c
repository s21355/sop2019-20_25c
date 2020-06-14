#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>

int main (int argc, char** argv)
{
	
	printf("Moj pid:%d,Pid rodzica:%d\n",getpid(),getppid());
	
	return 0;
}	