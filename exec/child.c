
#include "../minishell.h"

void	get_cmd_child(t_pipex *pipex, t_yassir *promet)
{
	//is_builting(promet);
	pipex->cmd = promet->list_cmd->data->cmd;
	if (pipex->cmd[0][0] == '\0')
	{
		write(2, "Command Not Found\n", 19); // not related with dup2
		exit(127);
	}
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
	write(1, "Error: ", 8);
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
	write(2, "Command Not Found\n", 19);
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
