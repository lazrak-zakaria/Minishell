#include "../minishell.h"


int	red(t_list	*cmd)
{
	int	i = 0;
	int	j = 0;
	int	fd_0 = 0;
	int	fd_1 = 1;
	int pip[2];

	if (cmd->data->file  == NULL)
		return -1;
	if (cmd->data->file[0] == NULL)
		return -1;
	while(cmd->data->file[i])
	{
		// if (fd_0 != 0)
		// 	close(fd_0);
		// if (fd_1 != 1)
		// 	close(fd_1);
		if (cmd->data->rel[i][0] == 'T')
			fd_1 = open(cmd->data->file[i], O_CREAT | O_TRUNC | O_WRONLY, 0644);
		else if (cmd->data->rel[i][0] == 'A')
			fd_1 = open(cmd->data->file[i], O_CREAT | O_APPEND | O_WRONLY, 0644);
		else if (cmd->data->rel[i][0] == 'I')
			fd_0 = open(cmd->data->file[i], O_RDONLY);
		else if (cmd->data->rel[i][0] == 'H')
		{
			pipe(pip);
			write(pip[1], cmd->data->buffer[j], ft_strlen(cmd->data->buffer[j]));
			close(pip[1]);
			fd_0 = pip[0];
			j++;
		}
		else if (cmd->data->rel[i][0] == 'B')
		{
			printf("%s\n", "ambiguous redirect"); // ambiguous redirect
			return i;
		}
		if (fd_1 < 0 || fd_0 < 0)
			return i;
		i++;
	}
	if (fd_0 != 0)
		cmd->data->fd_0 = fd_0;
	if (fd_1 != 1)
		cmd->data->fd_1 = fd_1;
	return (-1);
}

// int	red1(t_list	*cmd)
// {
// 	int i = 0;
// 	int error = -1;
// 	int fd = 1;
// 	if (cmd->data->outfile == NULL)
// 		return (-1);
// 	while(cmd->data->outfile[i] && cmd->data->rel_1[i])
// 	{
// 		if (cmd->data->rel_1[i][0] == 'T')
// 			fd = open(cmd->data->outfile[i], O_CREAT | O_TRUNC | O_WRONLY, 0644);
// 		else if (cmd->data->rel_1[i][0] == 'A')
// 			fd = open(cmd->data->outfile[i], O_CREAT | O_APPEND | O_WRONLY, 0644);
// 		if (error == -1 && fd < 0)
// 			error = i;
// 		i++;
// 	}
// 	if (fd > 1)
// 		cmd->data->fd_1 =  fd;
// 	return (error);
// }

// int	red_2(t_list	*cmd)
// {
// 	int i = -1;
// 	int error = -1;
// 	int fd = 0;
// 	if (cmd->data->infile[0] == NULL)
// 		return (-1);
// 	while(cmd->data->infile[++i] && cmd->data->rel_2[i][0])
// 	{
// 		if (cmd->data->rel_2[i][0] == 'I')
// 			fd = open(cmd->data->infile[i], O_RDONLY);
// 		else if (cmd->data->rel_2[i][0] == 'H')
// 		{
// 			int	pip[2];
// 			pipe(pip);
// 			fd = pip[0];
// 			while(1)
// 			{
// 				char *buffer = readline(">");
// 				if (buffer == NULL)
// 				{
// 					fd = -1;	// Error
// 					break; // Show New prompt 
// 				}
// 				if (my_strcmp(buffer, cmd->data->infile[i]))
// 				{
// 					free(buffer);
// 					close(pip[1]);
// 					break;
// 				}
// 				write(pip[1], buffer, ft_strlen(buffer));
// 				write(pip[1], "\n", 1);
// 				free(buffer);
// 			}
// 		}
// 		if (error == -1 && fd < 0)
// 			error = i;
// 	}
// 	if (fd > 1)
// 		cmd->data->fd_0 =  fd;
// 	return (error);
// }