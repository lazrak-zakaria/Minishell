/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc_parse22.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlazrak <zlazrak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:54:27 by zlazrak           #+#    #+#             */
/*   Updated: 2023/02/28 13:56:03 by zlazrak          ###   ########.fr       */
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

int	ft_take(char *a, t_cmd_parse *cmd, t_prompt *ys, char *h)
{
	t_vector	vec;
	char		*s;
	char		*b;
	int			i;
	int			fd[2];

	pipe(fd);
	ft_memset(&vec, 0, sizeof(vec));
	ft_push_back(&vec, '\0');
	vec.i = 0;
	ys->exit_status = 0;
	ys->flag = 2;
	
	int k = fork();
	if (k == 0)
	{
		signal(SIGINT, SIG_DFL);
		close(fd[0]);
		while (a)
		{
			i = 0;
			s = readline(">");
			if (!s || !ft_cmpstr(s, a))
			{
				//ft_push(&cmd->buffer, ft_new_node(ft_dupstr(vec.string)));
				//write (1, "\n", 1);
				write(fd[1], vec.string, ft_strlen(vec.string));
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
		close(fd[1]);
		free(vec.string);
		exit(0);
	}
	else
	{
		close(fd[1]);
		wait(&ys->exit_status);
		ys->flag = 0;
		if (ys->exit_status == SIGINT)
		{
			ys->exit_status = 1;
			free(vec.string);
			return (1);
		}
		else
			ys->exit_status = 0;
		char c;
		
		while (read(fd[0], &c, 1)> 0)
		{
			ft_push_back(&vec, c);
		}
		close(fd[0]);
		ft_push(&cmd->buffer, ft_new_node(ft_dupstr(vec.string)));
		free(vec.string);
	}
	return (0);
}

int	ft_here_doc(t_queue *queue, t_prompt *ys)
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
				if (ft_take(q->data, cmd, ys, var__.string))
					return (1);
			}
		}
	}
	return 0;
}
