/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 10:37:47 by zlazrak           #+#    #+#             */
/*   Updated: 2023/02/20 15:15:35 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "vector.h"
#include <string.h>
#include <fcntl.h>

typedef struct s_cmd_package
{
	char	**cmd;
	char	**file;	
	char	**rel;	
	char	**buffer;
	int		fd_0;
	int		fd_1;
}	t_cmd_package;

typedef	struct s_list
{
	t_cmd_package	*data;
	struct s_list	*next;
} t_list;


typedef struct s_yassir
{
	t_list	*list_cmd;
	struct s_env *s_env; // add
	char	**env;
	int		exit_status;
}	t_yassir;

typedef struct s_cmd_parse
{
	t_queue	*cmd;
	t_queue	*file;	
	t_queue	*rel;		
	t_queue	*buffer;
}	t_cmd_parse;


typedef	struct s_elem
{
	char	*s;
	int		quote;
	int		dollar;
} t_elem;

typedef struct s_var
{
	t_queue		*queue_answer;
	t_queue		*temp_queue;
	t_vector	vec;
	int			i;
	int			j;
	int			flag;
	char		c;
} t_var;


void	ft_norm_p1_2(char *a, t_var *var);
int		ft_part_3_5(t_queue *q);

t_queue	*ft_part_1(char *a);
t_queue	*ft_part_2(t_queue *q);
t_queue	*ft_part_3(t_queue *queue);
t_queue	*ft_part_4(t_queue *queue, t_yassir *ys);
t_queue	*ft_part_5(t_queue *queue);
char	*ft_substr(char	*a, int s, int e);
void	ft_parse(char *a, t_yassir *ys);


void    ft_putchar_fd(char c, int fd);
void    ft_putstr_fd(char *a, int fd);
int    ft_err_2(char *a, char *b);
int    ft_err_1(char *a);
/****************/

typedef struct s_env
{
	char *variable;
	char *value;
	struct s_env *next;
}t_env;

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	char	**all_paths;
	char	*path;
	char	**cmd;
	char	**envp;
	int		pipe[2];
	int		pipe2[2];
}t_pipex;

// Exec
void	ft_exec(t_yassir *promet);
void	one_cmd(t_yassir *promet, t_pipex *pipex);
void	get_cmd_path(char **paths, char **command);
char	**get_paths(char **envp);
void	get_cmd_child(t_pipex *pipex, t_yassir *promet);

// Utils
size_t	ft_strlen(char *s);
char	*ft_strdup(char *s1);
char	*ft_substr_2(char *s, unsigned int start, size_t len);
int		my_strcmp(char *s1, char *s2);
int		ft_isdigit(char *str);
int		ft_atoi(char *str);
int		ft_strcmp(char *s1, char *s2);
int		ft_isalnum_(char *s);
void	ft_free_all_(char **strs);
int		ft_strchr(char *s, char c);
char	**ft_split(char *s, char c);


// Env
t_env	*ft_env_new(char *str);
void	ft_env_addback(t_env **lst, t_env *new);
t_env	*ft_creat_env(char **envp);
char	*ft_strjoin(char *s1, char *s2);
char	**get_env(t_env *envp);
t_env	*ft_env_last(t_env *lst);
int		ft_env(t_yassir *promet);

// Builting
int		ft_echo(char **args, int fd);
int		ft_exit(char **args, t_yassir *promet);
int		ft_cd(char **args, t_yassir *promet);
int		ft_pwd();
int		ft_unset(t_yassir *promet, char **args);
int		ft_export(t_yassir *promet);

//Red
void	red(t_list	*cmd);int	red_2(t_list	*cmd);


int	is_builting(char *cmd);
void	ft_builting(t_yassir *promet);

#endif
