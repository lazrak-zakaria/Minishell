#include "../minishell.h"


int	red(t_list	*cmd)
{
	int i = 0;
	int error = -1;
	int fd = 1;
	if (cmd->data->outfile == NULL)
		return (0);
	while(cmd->data->outfile[i] && cmd->data->rel_1[i])
	{
		if (cmd->data->rel_1[i][0] == 'T')
			fd = open(cmd->data->outfile[i], O_CREAT | O_TRUNC | O_WRONLY, 0644);
		else if (cmd->data->rel_1[i][0] == 'A')
			fd = open(cmd->data->outfile[i], O_CREAT | O_APPEND | O_WRONLY, 0644);
		i++;
	}
	if (fd > 1)
		cmd->data->fd_1 =  fd;
	return (1);
}

int	red_2(t_list	*cmd)
{
	int i = -1;
	int error = 0;
	int fd = 0;
	if (cmd->data->infile[0] == NULL)
		return (0);
	while(cmd->data->infile[++i] && cmd->data->rel_2[i][0])
	{
		printf("%s\n", cmd->data->rel_2[i]);
		if (cmd->data->rel_2[i][0] == 'I')
			fd = open(cmd->data->infile[i], O_RDONLY);
		else if (cmd->data->rel_2[i][0] == 'H')
		{
			int	pip[2];
			pipe(pip);
			fd = pip[0];
			while(1)
			{
				char *buffer = readline(">");
				if (my_strcmp(buffer, cmd->data->infile[i]))
				{
					free(buffer);
					close(pip[1]);
					break;
				}
				write(pip[1], buffer, ft_strlen(buffer));
				write(pip[1], "\n", 1);
				free(buffer);
			}
		}
	}
	if (fd > 1)
		cmd->data->fd_0 =  fd;
	return (1);
}