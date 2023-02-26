/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:47:55 by yel-mass          #+#    #+#             */
/*   Updated: 2023/02/26 09:19:20 by yel-mass         ###   ########.fr       */
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
		if (ret != -1)
		{
			write(2, "bash: ", 7);
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
	int	ret;

	if (fork() == 0)
	{
		prompt->list_cmd->data->fd_0 = pipex->pipe[0];
		ret = red(prompt->list_cmd);
		if (ret != -1)
		{
			write(2, "bash: ", 7);
			perror(prompt->list_cmd->data->file[ret]);
			exit(1);
		}
		get_cmd_child(pipex, prompt);
	}
	close(pipex->pipe[0]);
	while (wait(&prompt->exit_status) != -1)
		;
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
			!prompt->list_cmd->data->cmd || !prompt->list_cmd->data->cmd)
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
