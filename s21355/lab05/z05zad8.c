#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	pid_t rodzic = getpid();
	int procesy = 6;
	int i;
	for( i=0;i<procesy;++i )
	{
		if(fork()==0)
		{
			printf("%d. PID= %d, PPID= %d\n",i,getpid(),getppid());
			if(i%2==0)
			{
				rodzic=getpid();
				break;
			}
		}
		else
		{
			wait(NULL);
		}			
	}	
	return 0;
}
