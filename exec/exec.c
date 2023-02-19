
#include "minishell.h"

void	ft_child_child(t_pipex *pipex, t_yassir *promet)
{

	while (promet->list_cmd->next != NULL)
	{
		pipe(pipex->pipe2);
		if (fork() == 0)
		{
			promet->list_cmd->data->fd_1 = pipex->pipe2[1];
			promet->list_cmd->data->fd_0 = pipex->pipe[0];
			red_2(promet->list_cmd);
			red(promet->list_cmd);
			close(pipex->pipe2[0]);
			get_cmd_child(pipex, promet);
		}
		close(pipex->pipe[0]);
		pipex->pipe[0] = pipex->pipe2[0];
		close(pipex->pipe2[1]);
		promet->list_cmd = promet->list_cmd->next;
	}
}

void	ft_exec(t_yassir *promet)
{
	t_pipex	pipex;
	pipex.envp = promet->env;

	// if (promet->list_cmd == NULL)
	// 	return ;
	// if (promet->list_cmd->data == NULL)
	// 	return ;
	// if (promet->list_cmd->data->cmd == NULL)
	// 	return ;
	if (promet->list_cmd->data->cmd[0] == NULL)
		return ; // if u hit Enter

	if (promet->list_cmd->next != NULL)
	{
		pipe(pipex.pipe);
		if (fork() == 0)
		{
			
			promet->list_cmd->data->fd_1 = pipex.pipe[1];
			red_2(promet->list_cmd);
			red(promet->list_cmd);
			close(pipex.pipe[0]); // you should close this for this test : cat | ls 
			get_cmd_child(&pipex, promet);
		}
		promet->list_cmd = promet->list_cmd->next;
		close(pipex.pipe[1]);
		if (promet->list_cmd->next != NULL)
		 	ft_child_child(&pipex, promet);
		if (fork() == 0)
		{
			promet->list_cmd->data->fd_0 = pipex.pipe[0];
			red_2(promet->list_cmd);
			red(promet->list_cmd);
			get_cmd_child(&pipex, promet);
		}
		close(pipex.pipe[0]);
		while(wait(NULL) != -1)
			;
	}
	else
	 	one_cmd(promet, &pipex);
}

void	one_cmd(t_yassir *promet, t_pipex *pipex)
{
	red_2(promet->list_cmd);
	red(promet->list_cmd);
	if (my_strcmp(promet->list_cmd->data->cmd[0], "exit"))
		promet->exit_status = ft_exit(promet->list_cmd->data->cmd, promet);
	else if (my_strcmp(promet->list_cmd->data->cmd[0], "echo"))
		promet->exit_status = ft_echo(promet->list_cmd->data->cmd, promet->list_cmd->data->fd_1);
	else if (my_strcmp(promet->list_cmd->data->cmd[0], "cd"))
	  	promet->exit_status = ft_cd(promet->list_cmd->data->cmd, promet);
	else if (my_strcmp(promet->list_cmd->data->cmd[0], "pwd"))
	 	promet->exit_status = ft_pwd();
	else if (my_strcmp(promet->list_cmd->data->cmd[0], "unset"))
		ft_unset(promet, promet->list_cmd->data->cmd);
	else if (my_strcmp(promet->list_cmd->data->cmd[0], "env"))
		promet->exit_status = ft_env(promet);
	else if (my_strcmp(promet->list_cmd->data->cmd[0], "export"))
		promet->exit_status = ft_export(promet);
	else if (fork() == 0)
		get_cmd_child(pipex, promet);
	wait(&promet->exit_status);
	promet->exit_status = promet->exit_status / 256;
}