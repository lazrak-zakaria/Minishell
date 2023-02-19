#include "../minishell.h"

int	ft_exit(char **args, t_yassir *promet)
{
	printf("exit\n");
	if (args[1] == NULL)
		exit(promet->exit_status);
	if (args[2] == NULL)
	{
		if (ft_isdigit(args[1]) != 0)
		{
			printf("exit: %s: numeric argument required\n", args[1]);
			exit(255);
		}
		exit((unsigned char )ft_atoi(args[1]));
	}
	else
	{
		printf("exit: too many arguments\n");
		// exit(promet->exit_status);
		return (1);
	}
	return (0);
}