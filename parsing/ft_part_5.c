/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_part_5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlazrak <zlazrak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:58:24 by zlazrak           #+#    #+#             */
/*   Updated: 2023/02/23 14:58:18 by zlazrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_part_norm5(t_elem *e, t_cmd_parse *cmd, t_queue **queue, t_var *var);
char	*ft_hq(char *a);

void	ft_handle_out(char *a, t_cmd_parse *cmd, t_queue **queue, t_var *var)
{
	t_elem	*elem;
	char	*b;
	char	*s;

	var->temp_queue = ft_pop(queue);
	elem = var->temp_queue->data;
	b = elem->s;
	if (elem->dollar && !elem->quote)
	{
		s = ft_hq(elem->d_s);
		ft_push(&cmd->rel, ft_new_node(strdup("BIGOUS")));
		ft_push(&cmd->file, ft_new_node(strdup(s)));
		free (s);
		return ;
	}
	else if (a && a[1])
		ft_push(&cmd->rel, ft_new_node(strdup("APPEND")));
	else
		ft_push(&cmd->rel, ft_new_node(strdup("TRUNC")));
	ft_push(&cmd->file, ft_new_node(strdup(b)));
}

void	ft_handle_in_hd(t_elem *elem, t_cmd_parse *cmd, char *b)
{
	char	*s;

	s = ft_hq(elem->d_s);
	if (elem->dollar && elem->quote)
		ft_push(&cmd->file, ft_new_node(strdup(s)));
	else
	{
		if (!b)
			ft_push(&cmd->file, ft_new_node(strdup(elem->d_s)));
		else
			ft_push(&cmd->file, ft_new_node(strdup(b)));
	}
	ft_push(&cmd->rel, ft_new_node(strdup("HERE_DOC")));
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
		if (elem->dollar && !elem->quote && !b)
		{
			s = ft_hq(elem->d_s);
			ft_push(&cmd->rel, ft_new_node(strdup("BIGOUS")));
			ft_push(&cmd->file, ft_new_node(strdup(s)));
			free(s);
			return ;
		}
		else
			ft_push(&cmd->rel, ft_new_node(strdup("INPUT")));
		ft_push(&cmd->file, ft_new_node(strdup(b)));
	}
}

t_queue	*ft_part_5(t_queue *queue)
{
	t_cmd_parse	*cmd;
	t_elem		*elem;
	t_var		var;
	char		*a;

	cmd = malloc(sizeof(t_cmd_parse));
	memset(cmd, 0, sizeof(*cmd));
	var.queue_answer = NULL;
	var.flag = 0;
	while (queue)
	{
		var.temp_queue = ft_pop(&queue);
		elem = var.temp_queue->data;
		if (var.flag)
		{
			cmd = malloc(sizeof(t_cmd_parse));
			memset(cmd, 0, sizeof(*cmd));
			var.flag = 0;
		}
		ft_part_norm5(elem, cmd, &queue, &var);
	}
	ft_push(&var.queue_answer, ft_new_node(cmd));
	return (var.queue_answer);
}

void	ft_part_norm5(t_elem *e, t_cmd_parse *cmd, t_queue **queue, t_var *var)
{
	char	*a;

	a = e->s;
	if (a && (a[0] == '>' || a[0] == '<' || a[0] == '|') && !e->quote)
	{
		if (a[0] == '>')
			ft_handle_out(a, cmd, queue, var);
		else if (a[0] == '<')
			ft_handle_in(a, cmd, queue, var);
		else
		{
			ft_push(&var->queue_answer, ft_new_node(cmd));
			var->flag = 1;
		}
	}
	else
		if (a)
			ft_push(&cmd->cmd, ft_new_node(a));
}

char	*ft_hq(char *a)
{
	char		*b;
	t_vector	vec;
	char		c;
	int			i;

	memset(&vec, 0, sizeof (vec));
	i = 0;
	while (a[i])
	{
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
