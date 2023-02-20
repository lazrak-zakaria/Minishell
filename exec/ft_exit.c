#include "../minishell.h"

int	ft_exit(char **args, t_yassir *promet)
{
	if (args[1] == NULL)
		exit(promet->exit_status);
	// if (args[2] == NULL)
	// {
	if (ft_isdigit(args[1]))
	{
		if (args[2] != NULL)
		{
			printf("exit: too many arguments\n");
			return (1);
		}
		exit((unsigned char )ft_atoi(args[1]));
	}
	printf("exit: %s: numeric argument required\n", args[1]);
	exit(255);
	// }
	// else
	// {
		
		// exit(promet->exit_status);
	// }
	return (0);
}

/*
bash: exit: %s: numeric argument required && exit => 255 
*/
/*
bash: exit: too many arguments | $? => 1 if the first args numeric and there is more then one args
*/