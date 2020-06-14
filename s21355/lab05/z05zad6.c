#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	int procesy = 100;
	int i;
	for( i=0; i<procesy;++i)
	{
		if(fork()==0)
		{
			printf("%d. PID= %d, PPID= %d\n",i,getpid(),getppid());
		}
		else
		{
			wait(NULL);
			break;
		}
	}
	return 0;
}