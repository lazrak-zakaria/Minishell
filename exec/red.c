/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:45:51 by yel-mass          #+#    #+#             */
/*   Updated: 2023/02/22 12:43:42 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	red(t_list *cmd)
{
	int	i;
	int	j;
	int	fd_0;
	int	fd_1;
	int	pip[2];

	i = 0;
	j = 0;
	fd_0 = 0;
	fd_1 = 1;
	if (cmd->data->file  == NULL || cmd->data->file[0] == NULL)
		return -1;
	while(cmd->data->file[i])
	{
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
