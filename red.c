/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:45:51 by yel-mass          #+#    #+#             */
/*   Updated: 2023/03/03 10:46:05 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_write_pipe(char *s, int *j)
{
	int	pip[2];

	pipe(pip);
	write(pip[1], s, ft_strlen(s));
	close(pip[1]);
	*(j) += 1;
	return (pip[0]);
}

int	open_output_file(char *filename, char *relation)
{
	int	fd;

	if (relation[0] == 'T')
		fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else
		fd = open(filename, O_CREAT | O_APPEND | O_WRONLY, 0644);
	return (fd);
}

int	open_input_file(char *filename, char *relation, int *j, t_list *cmd)
{
	int	fd;

	if (relation[0] == 'I')
		fd = open(filename, O_RDONLY);
	else
		fd = ft_write_pipe(cmd->data->buffer[*j], j);
	return (fd);
}

int	handle_redirect(t_list *cmd, int *k, int *fd_0, int *fd_1)
{
	int	fd;

	if (cmd->data->rel[k[0]][0] == 'T' || cmd->data->rel[k[0]][0] == 'A')
	{
		if (*fd_1 != 1)
			close(*fd_1);
		fd = open_output_file(cmd->data->file[k[0]], cmd->data->rel[k[0]]);
		if (fd < 0)
			return (k[0]);
		*fd_1 = fd;
	}
	else if (cmd->data->rel[k[0]][0] == 'I' || cmd->data->rel[k[0]][0] == 'H')
	{
		if (*fd_0 != 0)
			close(*fd_0);
		fd = open_input_file(cmd->data->file[k[0]], \
									cmd->data->rel[k[0]], &k[1], cmd);
		if (fd < 0)
			return (k[0]);
		*fd_0 = fd;
	}
	else if (cmd->data->rel[k[0]][0] == 'B')
		return (-2);
	return (-1);
}

int	red(t_list *cmd)
{
	int	k[2];
	int	fd_0;
	int	fd_1;
	int	ret;

	k[0] = 0;
	k[1] = 0;
	fd_0 = 0;
	fd_1 = 1;
	while (cmd->data->file != NULL && cmd->data->file[k[0]] != NULL)
	{
		ret = handle_redirect(cmd, k, &fd_0, &fd_1);
		if (ret == -2)
			return (printf_error("bash: ", cmd->data->file[k[0]], \
									": ambiguous redirect\n"), -2);
		if (ret != -1)
			return (ret);
		k[0] += 1;
	}
	if (fd_0 != 0)
		cmd->data->fd_0 = fd_0;
	if (fd_1 != 1)
		cmd->data->fd_1 = fd_1;
	return (-1);
}
