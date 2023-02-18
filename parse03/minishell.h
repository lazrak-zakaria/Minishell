/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlazrak <zlazrak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 10:37:47 by zlazrak           #+#    #+#             */
/*   Updated: 2023/02/18 10:14:32 by zlazrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "vector.h"
#include <string.h>

typedef struct s_cmd_package
{
	char	**cmd;
	char	**infile;	// <  <<
	char	**outfile;	// >> >
	char	**rel_1;	// < or <<
	char	**rel_2;	// >> or >
}	t_cmd_package;

typedef struct s_list
{
	t_cmd_package	*content;
	struct s_list	*next;
}	t_list;








typedef struct s_cmd_parse
{
	t_queue	*cmd;
	t_queue	*infile;	// <  <<
	t_queue	*outfile;	// >> 
	t_queue	*rel_1;		// < or <<
	t_queue	*rel_2;		// >> or >
}	t_cmd_parse;

typedef	struct s_elem
{
	char	*s;
	int		quote;
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

t_queue	*ft_part_1(char *a);
t_queue	*ft_part_2(t_queue *q);
t_queue	*ft_part_3(t_queue *queue);
t_queue	*ft_part_4(t_queue *queue, char **env);

char	*expand_dollar(char **env, char *a);
char	*ft_substr(char	*a, int s, int e);

void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(void *content);
#endif
