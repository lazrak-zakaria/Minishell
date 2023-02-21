
#include "../minishell.h"
#include <sys/stat.h>

int is_dir(const char *path)
{
	struct stat	statbuf;

	stat(path, &statbuf);
	return (S_ISDIR(statbuf.st_mode));
}

void	get_cmd_child(t_pipex *pipex, t_prompt *prompt)
{
	pipex->cmd = prompt->list_cmd->data->cmd;
	if (pipex->cmd[0][0] == '\0')
	{
		write(2, "bash: ", 7);
		write(2, ": command not found\n", 21);
		exit(127);
	}
	if (is_builting(pipex->cmd[0]))
		ft_builting(prompt);
	if (ft_strchr(pipex->cmd[0], '/') == -1)
	{
		pipex->all_paths = get_paths(pipex->envp);
		get_cmd_path(pipex->all_paths, pipex->cmd);
		if (pipex->all_paths != NULL)
			ft_free_all_(pipex->all_paths);
	}
	else if (is_dir(pipex->cmd[0]))
	{
		write(2, "bash: ", 7);
		write(2, pipex->cmd[0], ft_strlen(pipex->cmd[0]));
		write(2, ": is a directory\n", 18);
		exit(0);
	}
	if (prompt->list_cmd->data->fd_0 != 0)
		dup2(prompt->list_cmd->data->fd_0, 0);
	if (prompt->list_cmd->data->fd_1 != 1)
		dup2(prompt->list_cmd->data->fd_1, 1);
	execve(pipex->cmd[0], pipex->cmd, pipex->envp);
	write(2, "bash: ", 7);
	perror(pipex->cmd[0]);
	exit(127);
} 
// fixed

void	get_cmd_path(char **paths, char **command)
{
	char	*path;
	char	*tmp;
 
	if (command != NULL && paths != NULL)
	{
		tmp = ft_strjoin("/", command[0]);
		while (*paths != NULL)
		{
			path = ft_strjoin(*paths, tmp);
			if (access(path, F_OK | X_OK) == 0 && is_dir(path) == 0)
			{
				free(tmp);
				free(command[0]);
				command[0] = path;
				return ;
			}
			paths++;
			free(path);
		}
	}
	write(2, "bash: ", 7);
	write(2, command[0], ft_strlen(command[0]));
	write(2, ": command not found\n", 21);
	free(tmp);
	exit(127);
}

char	**get_paths(char **envp)
{
	int	i;

	i = 0;
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

	if (my_strcmp(prompt->list_cmd->data->cmd[0], "exit"))
		ret = ft_exit(prompt->list_cmd->data->cmd, prompt);
	else if (my_strcmp(prompt->list_cmd->data->cmd[0], "echo"))
		ret = ft_echo(prompt->list_cmd->data->cmd, prompt->list_cmd->data->fd_1);
	else if (my_strcmp(prompt->list_cmd->data->cmd[0], "cd"))
		ret = ft_cd(prompt->list_cmd->data->cmd, prompt);
	else if (my_strcmp(prompt->list_cmd->data->cmd[0], "pwd"))
		ret = ft_pwd();
	else if (my_strcmp(prompt->list_cmd->data->cmd[0], "unset"))
		ret = ft_unset(prompt, prompt->list_cmd->data->cmd);
	else if (my_strcmp(prompt->list_cmd->data->cmd[0], "env"))
		ret = ft_env(prompt);
	else if (my_strcmp(prompt->list_cmd->data->cmd[0], "export"))
		ret = ft_export(prompt);
	exit(ret);
}

// ls | exit : ??? How I can Do this