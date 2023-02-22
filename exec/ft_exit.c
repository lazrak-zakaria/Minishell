#include "../minishell.h"

int	ft_exit(char **args, t_prompt *prompt)
{
	if (args[1] == NULL)
		exit(prompt->exit_status);
	if (ft_isdigit(args[1]))
	{
		if (args[2] != NULL)
		{
			write(2, "exit: too many arguments\n", 26);
			return (1);
		}
		exit((unsigned char )ft_atoi(args[1]));
	}
	write(2, "exit: ", 7);
	write(2, args[1], ft_strlen(args[1]));
	write(2, ": numeric argument required\n", 29);
	exit(255);
	return (0);
}

/*
bash: exit: %s: numeric argument required && exit => 255 
*/
/*
bash: exit: too many arguments | $? => 1 if the first args numeric and there is more then one args
*/