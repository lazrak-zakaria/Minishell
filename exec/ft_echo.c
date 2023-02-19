
#include "../minishell.h"

int	ft_echo(char **args, int fd)
{
	int i;
	int j;
	int flag;
	
	flag = 0;
	i = 0;
	if (args[1] == NULL)
	{
		write(1, "\n", 1);
		return (0);
	}

	while(args[++i] != NULL && args[i][0] == '-')
	{
		int j = 0;
		while (args[i][++j])
		{
			if (args[i][j] != 'n')
				break;
		}
		if (args[i][j] != '\0')
			break;
	}
	if (i > 1)
		flag = 1;
	while (args[i])
	{
		j = 0;
		while(args[i][j]) 
			write(fd, &args[i][j++], 1);
		if (args[i + 1])
			write(fd, " ", 1);
		i++;
	}
	if (flag == 0)
		write(fd, "\n", 1);
	return (0);
}