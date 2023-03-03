/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_2.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlazrak <zlazrak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:47:36 by zlazrak           #+#    #+#             */
/*   Updated: 2023/03/03 10:24:38 by zlazrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_2_H
# define MINISHELL_2_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "queue.h"
# include "vector.h"

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

typedef struct s_pr
{
	int		*i;
	int		f;	
}	t_pr;

typedef struct s_cmd_parse
{
	t_queue	*cmd;
	t_queue	*file;	
	t_queue	*rel;		
	t_queue	*buffer;
}	t_cmd_parse;

typedef struct s_elem
{
	char	*s;
	char	*d_s;
	int		quote;
	int		dollar;
}	t_elem;

typedef struct s_var
{
	t_queue		*queue_answer;
	t_queue		*temp_queue;
	t_vector	vec;
	int			i;
	int			j;
	int			flag;
	char		c;
}	t_var;

typedef struct s_var_help
{
	t_queue		*a;
	t_queue		*b;
	char		*string;
	char		*string2;
}	t_var_help;

t_queue	*ft_part_1(char *a);
t_queue	*ft_part_2(t_queue *q);
t_queue	*ft_part_3(t_queue *queue);
t_queue	*ft_part_4(t_queue *queue, t_prompt *ys);
t_queue	*ft_part_5(t_queue *queue);
int		ft_part_3_5(t_queue *q);

void	ft_norm_p1_2(char *a, t_var *var);
char	*ft_substr(char	*a, int s, int e);
int		ft_parse(char *a, t_prompt *ys);

/*         utils 			*/
char	*ft_dupstr(char *a);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *a, int fd);
int		ft_cmpstr(char *a, char *b);
size_t	ft_strlen(char *a);
void	*ft_memset(void *b, int c, size_t len);

int		ft_err_2(char *a, char *b);
int		ft_err_1(char *a);

/*****		free		*****/
void	ft_free_q(t_queue *q);
void	ft_free_qq(t_queue *q);
void	ft_free(t_queue *q);
void	ft_free_part_5(t_queue *q);
/*****************************/

int		ft_dollar_ok(char c);

/*****		part_4		*****/
char	*ft_expand_dollar(char *a, t_prompt *ys);
void	ft_norm_expand(char *a, t_vector *vec, t_prompt *ys, t_pr *pr);
void	ft_join_dollar(t_vector **vec, t_vector *vec_dollar, t_prompt *ys);
char	*ft_itoa(int n);
/*****************************/
int		ft_find(char *a, char c);
int		ft_here_doc(t_queue *queue, t_prompt *ys);

void	ft_memfree(char **a);
void	ft_free_lis(t_list *head);

void	ft_part_norm5(t_elem *e, t_cmd_parse *cmd, t_queue **queue, t_var *var);

t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(void *content);

t_list	*ft_copy_(t_queue *q);

void	ft_handle_out(char *a, t_cmd_parse *cmd, t_queue **queue, t_var *var);
void	ft_handle_in(char *a, t_cmd_parse *cmd, t_queue **queue, t_var *var);
int	ft_ncmpstr(char *s1, char *s2, size_t n);

#endif