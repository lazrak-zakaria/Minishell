/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc_parse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 11:54:27 by zlazrak           #+#    #+#             */
/*   Updated: 2023/03/03 10:46:05 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_2.h"

int		ft_parent_(int *fd, t_prompt *ys, t_vector *vec, t_cmd_parse *cmd);
void	ft_here_var(t_vector *vec, t_prompt *ys);
void	ft_heredocline(char c, char *s, t_vector *vec, t_prompt *ys);
void	ft_sig_hd(int *fd);

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
	int			fd[2];

	ft_here_var(&vec, ys);
	pipe(fd);
	if (fork() == 0)
	{
		ft_sig_hd(fd);
		while (a)
		{
			s = readline("> ");
			if (!s || !ft_cmpstr(s, a))
			{
				write(fd[1], vec.string, ft_strlen(vec.string));
				free(s);
				break ;
			}
			ft_heredocline(h[1], s, &vec, ys);
		}
		close(fd[1]);
		free(vec.string);
		exit(0);
	}
	return (ft_parent_(fd, ys, &vec, cmd));
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
	return (0);
}
