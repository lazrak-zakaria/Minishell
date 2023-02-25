/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_one_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:03:24 by yel-mass          #+#    #+#             */
/*   Updated: 2023/02/25 17:03:25 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	ft_builting_2(t_prompt *prompt)
{
	char	**cmd;

	cmd = prompt->list_cmd->data->cmd;
	if (my_strcmp(cmd[0], "exit"))
	{
		write(2, "exit\n", 5);
		prompt->exit_status = ft_exit(cmd, prompt);
	}
	else if (my_strcmp(cmd[0], "echo"))
		prompt->exit_status = ft_echo(cmd, \
						prompt->list_cmd->data->fd_1);
	else if (my_strcmp(cmd[0], "cd"))
		prompt->exit_status = ft_cd(cmd, prompt, 1, \
							prompt->list_cmd->data->fd_1);
	else if (my_strcmp(cmd[0], "pwd"))
		prompt->exit_status = ft_cd(cmd, prompt, 2, \
							prompt->list_cmd->data->fd_1);
	else if (my_strcmp(cmd[0], "unset"))
		prompt->exit_status = ft_unset(prompt, cmd);
	else if (my_strcmp(cmd[0], "env"))
		prompt->exit_status = ft_env(prompt);
	else if (my_strcmp(cmd[0], "export"))
		prompt->exit_status = ft_export(prompt);
}

int	ft_red_nor(t_prompt *prompt, t_pipex *pipex)
{
	int	ret;

	ret = red(prompt->list_cmd);
	if (ret == -2 || ret != -1)
	{
		prompt->exit_status = 1;
		if (ret == -2)
			return (-1);
		write(2, "bash: ", 7);
		perror(prompt->list_cmd->data->file[ret]);
		return (-1);
	}
	if (prompt->list_cmd->data->cmd[0] == NULL)
		return (-1);
	return (0);
}

void	one_cmd(t_prompt *prompt, t_pipex *pipex)
{
	if (ft_red_nor(prompt, pipex) == -1)
		return ;
	if (is_builting(prompt->list_cmd->data->cmd[0]) == 1)
		ft_builting_2(prompt);
	else
	{
		prompt->flag = 1;
		if (fork() == 0)
			get_cmd_child(pipex, prompt);
		else
		{
			wait(&prompt->exit_status);
			if (prompt->exit_status == 2)
				prompt->exit_status = 130;
			else
				prompt->exit_status = prompt->exit_status / 256;
		}
		prompt->flag = 0;

	}
}
