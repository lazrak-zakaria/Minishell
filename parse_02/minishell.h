/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlazrak <zlazrak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 10:37:47 by zlazrak           #+#    #+#             */
/*   Updated: 2023/02/15 06:33:17 by zlazrak          ###   ########.fr       */
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
typedef struct s_cmd_wrapper
{
	char	*cmd;
	t_queue	*args;
	char	*infile;
	char	*outfile;
	char	*limiter;
	char	*append;
	char	*relation;
}	t_cmd_wrapper;

typedef	struct s_list
{
	t_cmd_wrapper	*data;
	struct s_list	*next;
} t_list;

typedef	struct y
{
	char	*s;
	int		quote;
} t_elem;

t_queue	*ft_part_1(char *a);
t_queue	*ft_part_2(t_queue *q);
t_queue	*ft_part_3(t_queue *queue);
t_queue	*ft_part_4(t_queue *queue);

char	*ft_substr(char	*a, int s, int e);

#endif