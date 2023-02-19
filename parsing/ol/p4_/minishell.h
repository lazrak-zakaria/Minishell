/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlazrak <zlazrak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 10:37:47 by zlazrak           #+#    #+#             */
/*   Updated: 2023/02/19 11:46:26 by zlazrak          ###   ########.fr       */
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

typedef struct s_cmd_package
{
	char	**cmd;
	char	**infile;	 // <  <<
	char	**outfile;	// >> >
	char	**rel_1;	// >> or >
	char	**rel_2;	// << or <
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
	char	**env;
	int		exit_status;
	
}	t_yassir;

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


void	ft_norm_p1_2(char *a, t_var *var);
int	ft_part_3_5(t_queue *q);

t_queue	*ft_part_1(char *a);
t_queue	*ft_part_2(t_queue *q);
t_queue	*ft_part_3(t_queue *queue);
t_queue	*ft_part_4(t_queue *queue, t_yassir *ys);
t_queue	*ft_part_5(t_queue *queue);
char	*ft_substr(char	*a, int s, int e);

#endif
