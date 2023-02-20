/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc_parse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlazrak <zlazrak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:54:27 by zlazrak           #+#    #+#             */
/*   Updated: 2023/02/20 17:25:00 by zlazrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
char	*ft_expand_dollar(char *a, t_yassir *ys);
int		ft_find(char *a, char c);
int		ft_dollar_ok(char c);
typedef	struct s_var_help
{
	t_queue		*a;
	t_queue		*b;
	char		*string;
	char		*string2;
} t_var_help;

void	ft_take(char *a, t_cmd_parse *cmd, t_yassir *ys)
{
	t_vector	vec;
	char		*s;
	char		*b;
	int			i;
	t_vector	vecb;


	memset(&vec, 0, sizeof(vec));
	ft_push_back(&vec, '\0');
	vec.i = 0;
	while (a)
	{
		i = 0;
		s = readline(">");
		if (!s || !strcmp(s, a))
		{
			ft_push(&cmd->buffer, ft_new_node(vec.string));
			free(s);
			break ;
		}
		while (s[i])
		{	
			if (s[i] == '$')
			{
				memset(&vecb, 0, sizeof(vecb));
				int j = i++;
				while (ft_dollar_ok(s[i]))
					i++;
				char	*ff = ft_expand_dollar(ft_substr(s, j, i), ys);
				if (!ff)
					ff = strdup("");
				j = 0;
				while (ff[j])
					ft_push_back(&vec, ff[j++]);
			}
			if (s[i])
				ft_push_back(&vec, s[i++]);
		}	
		ft_push_back(&vec, '\n');		
	}
}

void	ft_here(t_queue *queue, t_yassir *ys)
{
	t_cmd_parse	*cmd;
	t_var		var;
	t_var_help	var__;
	t_queue		*q;

	while (queue)
	{
		cmd = ft_pop(&queue)->data;
		var.i = 0;
		var__.a = cmd->file;
		var__.b = cmd->rel;
		while (var__.a)
		{
			q = ft_pop(&var__.a);
			var.temp_queue = ft_pop(&var__.b);
			var__.string = var.temp_queue->data;
			if (var__.string[0] == 'H')
			{
				ft_take(q->data, cmd, ys);
			}
		}
	}
}
