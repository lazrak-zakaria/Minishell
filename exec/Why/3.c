#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>

int main(int ac, char **av, char **env)
{

	if (fork() == 0)
		exit(5);
	int ex;
	wait(&ex);
	printf("exit status = %d\n", ex);
	return (0);
}