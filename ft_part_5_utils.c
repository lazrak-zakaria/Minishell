/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_part_5_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlazrak <zlazrak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:58:24 by zlazrak           #+#    #+#             */
/*   Updated: 2023/03/03 20:32:45 by zlazrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_2.h"

t_queue	*ft_divide(char *a);
void	ft_handle_token(char *a, t_cmd_parse *cmd, t_queue **queue, t_var *var);
int		ft_bgs_check(char *a);

char	*ft_hq(char *a)
{
	t_vector	vec;
	char		c;
	int			i;

	ft_memset(&vec, 0, sizeof (vec));
	i = 0;
	while (a[i])
	{
		if (a[i] == '$' && (a[i + 1] == '\'' || a[i + 1] == '"'))
		{
			i++;
			continue ;
		}
		if (a[i] == '\'' || a[i] == '"')
		{
			c = a[i++];
			while (a[i] && a[i] != c)
				ft_push_back(&vec, a[i++]);
			i++;
		}
		else if (a[i])
			ft_push_back(&vec, a[i++]);
	}
	return (vec.string);
}

void	ft_handle_out(char *a, t_cmd_parse *cmd, t_queue **queue, t_var *var)
{
	t_elem	*elem;
	char	*b;
	char	*s;

	var->temp_queue = ft_pop(queue);
	elem = var->temp_queue->data;
	b = elem->s;
	if ((elem->dollar && !elem->quote && !b)
		|| (elem->dollar && b && ft_bgs_check(b)))
	{
		s = ft_hq(elem->d_s);
		ft_push(&cmd->rel, ft_new_node(ft_dupstr("BIGOUS")));
		ft_push(&cmd->file, ft_new_node(ft_dupstr(s)));
		free (s);
		return ;
	}
	else if (a && a[1])
		ft_push(&cmd->rel, ft_new_node(ft_dupstr("APPEND")));
	else
		ft_push(&cmd->rel, ft_new_node(ft_dupstr("TRUNC")));
	ft_push(&cmd->file, ft_new_node(ft_dupstr(b)));
}

void	ft_handle_in_hd(t_elem *elem, t_cmd_parse *cmd, char *b)
{
	char	*s;
	int		flag;
	int		i;

	i = 0;
	flag = 0;
	while (elem->d_s[i] && !flag)
	{
		if (elem->d_s[i] == '\'' || elem->d_s[i] == '"')
			flag = 1;
		i++;
	}
	s = ft_hq(elem->d_s);
	if ((elem->dollar || !b) && s)
		ft_push(&cmd->file, ft_new_node(ft_dupstr(s)));
	else
		ft_push(&cmd->file, ft_new_node(ft_dupstr(b)));
	if (elem->quote || flag)
		ft_push(&cmd->rel, ft_new_node(ft_dupstr("HQRE_DOC")));
	else
		ft_push(&cmd->rel, ft_new_node(ft_dupstr("HERE_DOC")));
	free (s);
}

void	ft_handle_in(char *a, t_cmd_parse *cmd, t_queue **queue, t_var *var)
{
	t_elem	*elem;
	char	*b;
	char	*s;

	var->temp_queue = ft_pop(queue);
	elem = var->temp_queue->data;
	b = elem->s;
	if (a && a[1])
		ft_handle_in_hd(elem, cmd, b);
	else
	{
		if ((elem->dollar && !elem->quote && !b)
			|| (elem->dollar && b && ft_bgs_check(b)))
		{
			s = ft_hq(elem->d_s);
			ft_push(&cmd->rel, ft_new_node(ft_dupstr("BIGOUS")));
			ft_push(&cmd->file, ft_new_node(ft_dupstr(s)));
			free(s);
			return ;
		}
		else
			ft_push(&cmd->rel, ft_new_node(ft_dupstr("INPUT")));
		ft_push(&cmd->file, ft_new_node(ft_dupstr(b)));
	}
}

void	ft_part_norm5(t_elem *e, t_cmd_parse *cmd, t_queue **queue, t_var *var)
{
	char	*a;
	t_var	v;

	a = e->s;
	if (a && (a[0] == '>' || a[0] == '<' || a[0] == '|') && !e->quote)
		ft_handle_token(a, cmd, queue, var);
	else
	{
		if (e->dollar && a && !e->quote)
		{
			v.queue_answer = ft_divide(a);
			v.temp_queue = v.queue_answer;
			while (v.temp_queue)
			{
				ft_push(&cmd->cmd, ft_new_node(((v.temp_queue)->data)));
				v.temp_queue = v.temp_queue->next;
			}
			ft_free(v.queue_answer);
		}
		else if (a)
			ft_push(&cmd->cmd, ft_new_node(ft_dupstr(a)));
	}
}
