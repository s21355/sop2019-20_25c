#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	pid_t rodzic = getpid();
	int procesy = 100;
	int i;
	for(i=0; i<procesy;++i)
	{
		if(fork()==0)
		{
			printf("%d. PID= %d, PPID= %d\n",i,getpid(),getppid());
			break;
		}
		if(rodzic==getpid())
		{
			int status= 0;
			waitpid(0,&status,0);
		}
	}
return 0;
}