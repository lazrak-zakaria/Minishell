/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:47:55 by yel-mass          #+#    #+#             */
/*   Updated: 2023/03/03 10:46:05 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_wait_main(t_prompt *prompt, pid_t last_cmd);

void	ft_child_norm(t_prompt *prompt, t_pipex *pipex)
{
	int	ret;

	signal(SIGQUIT, SIG_DFL);
	prompt->list_cmd->data->fd_1 = pipex->pipe2[1];
	prompt->list_cmd->data->fd_0 = pipex->pipe[0];
	ret = red(prompt->list_cmd);
	if (ret == -2 || ret != -1)
	{
		prompt->exit_status = 1;
		if (ret != -2)
			perror(prompt->list_cmd->data->file[ret]);
		exit(1);
	}
	close(pipex->pipe2[0]);
	get_cmd_child(pipex, prompt);
}

int	ft_child_child(t_pipex *pipex, t_prompt *prompt)
{
	pid_t	pid;

	while (prompt->list_cmd->next != NULL)
	{
		if (pipe(pipex->pipe2) == -1)
			return (perror("pipe"), -1);
		pid = fork();
		if (pid == -1)
			return (perror("fork"), -1);
		if (pid == 0)
			ft_child_norm(prompt, pipex);
		close(pipex->pipe[0]);
		pipex->pipe[0] = pipex->pipe2[0];
		close(pipex->pipe2[1]);
		prompt->list_cmd = prompt->list_cmd->next;
	}
	return (0);
}

int	first_cmd(t_pipex *pipex, t_prompt *prompt)
{
	int		ret;
	pid_t	pid;

	if (pipe(pipex->pipe) == -1)
		return (perror("pipe"), -1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		prompt->list_cmd->data->fd_1 = pipex->pipe[1];
		ret = red(prompt->list_cmd);
		if (ret == -2 || ret != -1)
		{
			prompt->exit_status = 1;
			if (ret != -2)
				exit(1);
			perror(prompt->list_cmd->data->file[ret]);
			exit(1);
		}
		close(pipex->pipe[0]);
		get_cmd_child(pipex, prompt);
	}
	return (0);
}

int	second_cmd(t_pipex *pipex, t_prompt *prompt)
{
	int		ret;
	pid_t	last_cmd;

	last_cmd = fork();
	if (last_cmd == -1)
		return (perror("fork"), -1);
	if (last_cmd == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		prompt->list_cmd->data->fd_0 = pipex->pipe[0];
		ret = red(prompt->list_cmd);
		if (ret == -2 || ret != -1)
		{
			prompt->exit_status = 1;
			if (ret != -2)
				perror(prompt->list_cmd->data->file[ret]);
			exit(1);
		}
		get_cmd_child(pipex, prompt);
	}
	close(pipex->pipe[0]);
	ft_wait_main(prompt, last_cmd);
	return (0);
}

void	ft_exec(t_prompt *prompt)
{
	t_pipex	pipex;

	pipex.envp = prompt->env;
	if (!prompt->list_cmd || !prompt->list_cmd->data || \
								!prompt->list_cmd->data->cmd)
		return ;
	if (prompt->list_cmd->next != NULL)
	{
		prompt->flag = 1;
		if (first_cmd(&pipex, prompt) == -1)
			return ;
		prompt->list_cmd = prompt->list_cmd->next;
		close(pipex.pipe[1]);
		if (prompt->list_cmd->next != NULL)
			if (ft_child_child(&pipex, prompt) == -1)
				return ;
		if (second_cmd(&pipex, prompt) == -1)
			return ;
	}
	else
		one_cmd(prompt, &pipex);
}
