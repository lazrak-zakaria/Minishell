/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:47:55 by yel-mass          #+#    #+#             */
/*   Updated: 2023/02/22 17:09:15 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_child_child(t_pipex *pipex, t_prompt *prompt)
{
	int	ret;

	while (prompt->list_cmd->next != NULL)
	{
		pipe(pipex->pipe2);
		if (fork() == 0)
		{
			prompt->list_cmd->data->fd_1 = pipex->pipe2[1];
			prompt->list_cmd->data->fd_0 = pipex->pipe[0];
			ret = red(prompt->list_cmd);
			if (ret != -1)
			{
				write(2, "bash: ", 7);
				perror(prompt->list_cmd->data->file[ret]);
				return ;
			}
			close(pipex->pipe2[0]);
			get_cmd_child(pipex, prompt);
		}
		close(pipex->pipe[0]);
		pipex->pipe[0] = pipex->pipe2[0];
		close(pipex->pipe2[1]);
		prompt->list_cmd = prompt->list_cmd->next;
	}
}

void	ft_exec(t_prompt *prompt)
{
	t_pipex	pipex;
	int		ret;

	pipex.envp = prompt->env;
	if (!prompt->list_cmd || !prompt->list_cmd->data || \
			!prompt->list_cmd->data->cmd || !prompt->list_cmd->data->cmd \
					|| prompt->list_cmd->data->cmd[0] == NULL)
		return ;
	if (prompt->list_cmd->next != NULL)
	{
		pipe(pipex.pipe);
		if (fork() == 0)
		{
			prompt->list_cmd->data->fd_1 = pipex.pipe[1];
			ret = red(prompt->list_cmd);
			if (ret != -1)
			{
				write(2, "bash: ", 7);
				perror(prompt->list_cmd->data->file[ret]);
				return ;
			}
			close(pipex.pipe[0]);
			get_cmd_child(&pipex, prompt);
		}
		prompt->list_cmd = prompt->list_cmd->next;
		close(pipex.pipe[1]);
		// if (prompt->list_cmd->next != NULL)
		// 	ft_child_child(&pipex, prompt);
		if (fork() == 0)
		{
			prompt->list_cmd->data->fd_0 = pipex.pipe[0];
			ret = red(prompt->list_cmd);
			if (ret != -1)
			{
				write(2, "bash: ", 7);
				perror(prompt->list_cmd->data->file[ret]);
				return ;
			}
			get_cmd_child(&pipex, prompt);
		}
		close(pipex.pipe[0]);
		while (wait(&prompt->exit_status) != -1)
			;
		prompt->exit_status = prompt->exit_status / 256;
	}
	else
		one_cmd(prompt, &pipex);
}

void	one_cmd(t_prompt *prompt, t_pipex *pipex)
{
	int	ret;

	ret = red(prompt->list_cmd);
	if (ret == -2)
		return ;
	if (ret != -1)
	{
		write(2, "bash: ", 7);
		perror(prompt->list_cmd->data->file[ret]);
		return ;
	}
	if (prompt->list_cmd->data->cmd[0] == NULL)
		return ;
	if (my_strcmp(prompt->list_cmd->data->cmd[0], "exit"))
	{
		printf("exit\n");
		prompt->exit_status = ft_exit(prompt->list_cmd->data->cmd, prompt);
	}
	else if (my_strcmp(prompt->list_cmd->data->cmd[0], "echo"))
		prompt->exit_status = ft_echo(prompt->list_cmd->data->cmd, \
						prompt->list_cmd->data->fd_1);
	else if (my_strcmp(prompt->list_cmd->data->cmd[0], "cd"))
		prompt->exit_status = ft_cd(prompt->list_cmd->data->cmd, prompt);
	else if (my_strcmp(prompt->list_cmd->data->cmd[0], "pwd"))
		prompt->exit_status = ft_pwd();
	else if (my_strcmp(prompt->list_cmd->data->cmd[0], "unset"))
		prompt->exit_status = ft_unset(prompt, prompt->list_cmd->data->cmd);
	else if (my_strcmp(prompt->list_cmd->data->cmd[0], "env"))
		prompt->exit_status = ft_env(prompt);
	else if (my_strcmp(prompt->list_cmd->data->cmd[0], "export"))
		prompt->exit_status = ft_export(prompt);
	else if (fork() == 0)
		get_cmd_child(pipex, prompt);
	else
	{
		wait(&prompt->exit_status);
		prompt->exit_status = prompt->exit_status / 256;
	}
}
