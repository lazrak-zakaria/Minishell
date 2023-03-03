/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 10:37:47 by zlazrak           #+#    #+#             */
/*   Updated: 2023/03/03 10:47:43 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "queue.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "vector.h"
# include <string.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <limits.h>
# include <sys/wait.h>
# include <signal.h>

typedef struct s_cmd_package
{
	char	**cmd;
	char	**file;	
	char	**rel;	
	char	**buffer;
	int		fd_0;
	int		fd_1;
}	t_cmd_package;

typedef struct s_list
{
	t_cmd_package	*data;
	struct s_list	*next;
}	t_list;

typedef struct s_prompt
{
	t_list			*list_cmd;
	struct s_env	*s_env;
	char			**env;
	int				exit_status;
	int				flag;
}	t_prompt;

/****************/

typedef struct s_env
{
	char			*variable;
	char			*value;
	struct s_env	*next;
}t_env;

typedef struct s_pipex
{
	char	**all_paths;
	char	*path;
	char	**cmd;
	char	**envp;
	int		pipe[2];
	int		pipe2[2];
}t_pipex;

/*   */
int		ft_parse(char *a, t_prompt *ys);
void	ft_free_lis(t_list *head);
void	ft_putchar_fd(char c, int fd);

/*  */

// Exec
void	ft_exec(t_prompt *prompt);
void	one_cmd(t_prompt *prompt, t_pipex *pipex);
int		get_cmd_path(char **paths, char **command);
char	**get_paths(char **envp);
void	get_cmd_child(t_pipex *pipex, t_prompt *prompt);

// Utils
size_t	ft_strlen(char *s);
char	*ft_strdup(char *s1);
char	*ft_substr_2(char *s, unsigned int start, size_t len);
int		my_strcmp(char *s1, char *s2);
int		ft_isdigit(char *str);
size_t	ft_atoi(char *str);
int		ft_strcmp(char *s1, char *s2);
int		ft_isalnum_(char *s);
void	ft_free_all_(char **strs);
int		ft_strchr(char *s, char c);
char	**ft_split(char *s, char c);
void	printf_error(char *s1, char *s2, char *s3);

// Env
t_env	*ft_env_new(char *str);
void	ft_env_addback(t_env **lst, t_env *new);
t_env	*ft_creat_env(char **envp);
char	*ft_strjoin(char *s1, char *s2);
char	**get_env(t_env *envp);
t_env	*ft_env_last(t_env *lst);
int		ft_env(t_prompt *prompt);

// Builting
int		ft_echo(char **args, int fd);
int		ft_exit(char **args, t_prompt *prompt);
int		ft_cd(char **args, t_prompt *prompt, int a, int fd);
int		ft_pwd(int fd);
int		ft_unset(t_prompt *prompt, char **args);
int		ft_export(t_prompt *prompt);

//Red
int		red(t_list *cmd);
int		red_2(t_list *cmd);

int		ft_count_env(t_env *current);
int		is_builting(char *cmd);
void	ft_builting(t_prompt *prompt);

char	*search_env(t_env *env, char *str);
int		ft_cd_2(char **args, t_prompt *prompt);

int		ft_search_and_update(char *variable, \
						char *value, t_env	*curr, int flag);
int		ft_extracts_var_val(char **var, char **val, char *cmd);

void	ft_print_env(t_prompt *yassir);
void	ft_free_env(t_env *current);

int		check_agrs(char *s);
void	sort_env(t_env *head);

void	ft_wait_main(t_prompt *prompt, pid_t last_cmd);

#endif
