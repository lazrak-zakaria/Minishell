
#include "../minishell.h"

void	get_cmd_child(t_pipex *pipex, t_yassir *promet)
{
	pipex->cmd = promet->list_cmd->data->cmd;
	if (pipex->cmd[0][0] == '\0')
	{
		write(2, "bash: ", 7);
		write(2, ": command not found\n", 21);
		exit(127);
	}
	if (is_builting(pipex->cmd[0]))
		ft_builting(promet);
	if (ft_strchr(pipex->cmd[0], '/') == -1)
	{
		pipex->all_paths = get_paths(pipex->envp);
		get_cmd_path(pipex->all_paths, pipex->cmd);
		if (pipex->all_paths != NULL)
			ft_free_all_(pipex->all_paths); // command not found
	}
	if (promet->list_cmd->data->fd_0 != 0)
		dup2(promet->list_cmd->data->fd_0, 0);
	if (promet->list_cmd->data->fd_1 != 1)
		dup2(promet->list_cmd->data->fd_1, 1);
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
 
	if (command == NULL || paths == NULL)
		return ;
	tmp = ft_strjoin("/", command[0]);
	while (*paths != NULL)
	{
		path = ft_strjoin(*paths, tmp);
		if (access(path, F_OK | X_OK) == 0)
		{
			free(tmp);
			free(command[0]);
			command[0] = path;
			return ;
		}
		paths++;
		free(path);
	}
	write(2, "bash: ", 7);
	write(2, command[0], ft_strlen(command[0]));
	write(2, ": command not found\n", 21);
	exit(127);
	free(tmp);
	return ;
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

void	ft_builting(t_yassir *promet)
{
	int	ret;

	if (my_strcmp(promet->list_cmd->data->cmd[0], "exit"))
		ret = ft_exit(promet->list_cmd->data->cmd, promet);
	else if (my_strcmp(promet->list_cmd->data->cmd[0], "echo"))
		ret = ft_echo(promet->list_cmd->data->cmd, promet->list_cmd->data->fd_1);
	else if (my_strcmp(promet->list_cmd->data->cmd[0], "cd"))
		ret = ft_cd(promet->list_cmd->data->cmd, promet);
	else if (my_strcmp(promet->list_cmd->data->cmd[0], "pwd"))
		ret = ft_pwd();
	else if (my_strcmp(promet->list_cmd->data->cmd[0], "unset"))
		ret = ft_unset(promet, promet->list_cmd->data->cmd);
	else if (my_strcmp(promet->list_cmd->data->cmd[0], "env"))
		ret = ft_env(promet);
	else if (my_strcmp(promet->list_cmd->data->cmd[0], "export"))
		ret = ft_export(promet);
	exit(ret);
}

// ls | exit : ??? How I can Do this