/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:47:56 by yel-mass          #+#    #+#             */
/*   Updated: 2023/02/25 13:35:20 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_cmd_child(t_pipex *pipex, t_prompt *pt)
{
	if (pt->list_cmd->data->cmd[0] == NULL) // in case of just redirection (<main.c | ls == SEGV)
		return ;
	dup2(pt->list_cmd->data->fd_0, 0);
	dup2(pt->list_cmd->data->fd_1, 1);
	if (pt->list_cmd->data->cmd[0][0] == '\0')
	{
		printf_error("bash: ", "", ": command not found\n");
		exit(127);
	}
	if (is_builting(pt->list_cmd->data->cmd[0]))
		ft_builting(pt);
	if (ft_strchr(pt->list_cmd->data->cmd[0], '/') == -1)
	{
		pipex->all_paths = get_paths(pipex->envp);
		if (pipex->all_paths != NULL)
		{
			if (get_cmd_path(pipex->all_paths, pt->list_cmd->data->cmd) == 0)
				exit(127);
			ft_free_all_(pipex->all_paths);
		}
	}
	execve(pt->list_cmd->data->cmd[0], pt->list_cmd->data->cmd, pipex->envp);
	write(2, "bash: ", 7);
	perror(pt->list_cmd->data->cmd[0]);
	exit(127);
}

int	get_cmd_path(char **paths, char **command)
{
	char	*path;
	char	*tmp;
	char	**tmp2;

	tmp2 = paths;
	if (!(my_strcmp(command[0], "..")) && !(my_strcmp(command[0], ".")))
	{
		tmp = ft_strjoin("/", command[0]);
		while (*paths != NULL)
		{
			path = ft_strjoin(*paths, tmp);
			if (access(path, F_OK | X_OK) == 0)
			{
				free(tmp);
				free(command[0]);
				command[0] = path;
				return (1);
			}
			paths++;
			free(path);
		}
		free(tmp);
	}
	printf_error("bash: ", command[0], ": command not found\n");
	return (ft_free_all_(tmp2), 0);
}

char	**get_paths(char **envp)
{
	int	i;

	i = 0;
	if (envp == NULL)
		return (NULL);
	while (envp[i] != NULL && ft_strcmp(envp[i], "PATH") != 0)
		i++;
	if (envp[i] == NULL)
		return (NULL);
	return (ft_split(envp[i] + 5, ':'));
}

int	is_builting(char *cmd)
{
	if (my_strcmp(cmd, "exit"))
		return (1);
	else if (my_strcmp(cmd, "echo"))
		return (1);
	else if (my_strcmp(cmd, "cd"))
		return (1);
	else if (my_strcmp(cmd, "pwd"))
		return (1);
	else if (my_strcmp(cmd, "unset"))
		return (1);
	else if (my_strcmp(cmd, "env"))
		return (1);
	else if (my_strcmp(cmd, "export"))
		return (1);
	return (0);
}

void	ft_builting(t_prompt *prompt)
{
	int	ret;

	ret = 0;
	if (prompt->list_cmd->data->fd_0 != 0)
		dup2(prompt->list_cmd->data->fd_0, 0);
	if (prompt->list_cmd->data->fd_1 != 1)
		dup2(prompt->list_cmd->data->fd_1, 1);
	if (my_strcmp(prompt->list_cmd->data->cmd[0], "exit"))
		ret = ft_exit(prompt->list_cmd->data->cmd, prompt);
	else if (my_strcmp(prompt->list_cmd->data->cmd[0], "echo"))
		ret = ft_echo(prompt->list_cmd->data->cmd, \
								prompt->list_cmd->data->fd_1);
	else if (my_strcmp(prompt->list_cmd->data->cmd[0], "cd"))
		ret = ft_cd(prompt->list_cmd->data->cmd, prompt);
	else if (my_strcmp(prompt->list_cmd->data->cmd[0], "pwd"))
		ret = ft_pwd(prompt->list_cmd->data->fd_1);
	else if (my_strcmp(prompt->list_cmd->data->cmd[0], "unset"))
		ret = ft_unset(prompt, prompt->list_cmd->data->cmd);
	else if (my_strcmp(prompt->list_cmd->data->cmd[0], "env"))
		ret = ft_env(prompt);
	else if (my_strcmp(prompt->list_cmd->data->cmd[0], "export"))
		ret = ft_export(prompt);
	exit(ret);
}
