#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>

int main (int argc, char** argv)
{
	int x;
	pid_t p;

	if(argc!=2)
	{
		return 1;
	}
	x=atoi(argv[1]);
	p= fork();
	if(p==0)
	{
		int z;
		printf("Dziecko: %d Rodzic: %d\n", getpid(), getppid());
		fflush(stdout);
		for(z=1; z<x; z=z+2){
			printf("z= %d\n", z);
		}
	}
	else
	{
		int suma=0;
		int y;
		printf("Rodzic: %d Rodzic: %d Dziecko: %d\n", getpid(), getppid(), p);
		fflush(stdout);
		for (y=0; y<x; y++)
		{
			suma = suma+y;
		}
		printf("suma: %d\n", suma);
		wait(NULL);
	}
	return 0;
}	