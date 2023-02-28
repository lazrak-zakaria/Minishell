/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:47:55 by yel-mass          #+#    #+#             */
/*   Updated: 2023/02/27 14:49:53 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_wait_main(t_prompt *prompt, pid_t last_cmd);

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
		close(pipex->pipe[0]);
		pipex->pipe[0] = pipex->pipe2[0];
		close(pipex->pipe2[1]);
		prompt->list_cmd = prompt->list_cmd->next;
	}
}

void	first_cmd(t_pipex *pipex, t_prompt *prompt)
{
	int	ret;

	prompt->flag = 1;
	pipe(pipex->pipe);
	if (fork() == 0)
	{
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
	prompt->list_cmd = prompt->list_cmd->next;
	close(pipex->pipe[1]);
}

void	second_cmd(t_pipex *pipex, t_prompt *prompt)
{
	int		ret;
	pid_t	last_cmd;

	last_cmd = fork();
	if (last_cmd == 0)
	{
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
}

void	ft_wait_main(t_prompt *prompt, pid_t last_cmd)
{
	pid_t	ret_pid;
	int		exit_s;

	while (1)
	{
		ret_pid = wait(&exit_s);
		if (ret_pid == last_cmd)
			prompt->exit_status = exit_s;
		else if (ret_pid == -1)
			break ;
	}
	if (prompt->exit_status == 2)
		prompt->exit_status = 130;
	else
		prompt->exit_status = prompt->exit_status / 256;
	prompt->flag = 0;
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
		first_cmd(&pipex, prompt);
		if (prompt->list_cmd->next != NULL)
			ft_child_child(&pipex, prompt);
		second_cmd(&pipex, prompt);
	}
	else
		one_cmd(prompt, &pipex);
}
