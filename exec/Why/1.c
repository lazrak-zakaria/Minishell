#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int ac, char **av, char **env)
{
	if (fork() == 0)
	{
		char *args[] = {"ls", "no", NULL};
		execve("/bin/ls", args, env);
	}
	int ex;
	wait(&ex);
	printf("%d\n", ex);
	return (0);
}