#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>

int main ()
{
	pid_t pe= fork();
	if(pe==0)
	{
		printf("Dziecko o PID: %d rodzic o PID: %d\n", getpid(), getppid());
		fflush(stdout);
		sleep(3);
	}
	else
	{
		printf("Ja proces o PID: %d PID rodzica: %d PID dziecka: %d\n", getpid(), getppid(), pe);
		fflush(stdout);
		wait(NULL);
		printf("Koniec rodzica \n");
		fflush(stdout);
	}
	return 0;
}	