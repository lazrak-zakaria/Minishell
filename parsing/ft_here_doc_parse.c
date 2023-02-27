/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc_parse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlazrak <zlazrak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:54:27 by zlazrak           #+#    #+#             */
/*   Updated: 2023/02/27 09:42:55 by zlazrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_2.h"

void	ft_sub_take(char *s, int *i, t_prompt *ys, t_vector *vec)
{
	int			j;
	char		*ff;
	char		*tofree;

	if (s[(*i)] == '$')
	{
		j = (*i)++;
		if (s[(*i)] == '?')
			(*i)++;
		else
			while (ft_dollar_ok(s[(*i)]) || s[(*i)] == '$')
			(*i)++;
		tofree = ft_substr(s, j, (*i));
		ff = ft_expand_dollar(tofree, ys);
		free(tofree);
		if (!ff)
			ff = ft_dupstr("");
		j = 0;
		while (ff[j])
			ft_push_back(vec, ff[j++]);
		free(ff);
	}
	if (s[(*i)])
		ft_push_back(vec, s[(*i)++]);
}

void	ft_take(char *a, t_cmd_parse *cmd, t_prompt *ys, char *h)
{
	t_vector	vec;
	char		*s;
	char		*b;
	int			i;

	ft_memset(&vec, 0, sizeof(vec));
	ft_push_back(&vec, '\0');
	vec.i = 0;
	ys->exit_status = 0;
	while (a)
	{
		i = 0;
		s = readline(">");
		if (!s || !ft_cmpstr(s, a))
		{
			ft_push(&cmd->buffer, ft_new_node(ft_dupstr(vec.string)));
			free(s);
			break ;
		}
		if (h[1] == 'E')
			while (s[i])
				ft_sub_take(s, &i, ys, &vec);
		else
		{
			while (s[i])
				ft_push_back(&vec, s[i++]);
		}
		ft_push_back(&vec, '\n');
		free(s);
	}
	free(vec.string);
}

void	ft_here_doc(t_queue *queue, t_prompt *ys)
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
			if (var__.string[1] == 'H')
				ft_take(q->data, cmd, ys, var__.string);
		}
	}
}
