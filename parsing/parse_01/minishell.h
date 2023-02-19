/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlazrak <zlazrak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 10:37:47 by zlazrak           #+#    #+#             */
/*   Updated: 2023/02/14 15:41:36 by zlazrak          ###   ########.fr       */
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

#endif