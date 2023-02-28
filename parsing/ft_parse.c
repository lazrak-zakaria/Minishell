/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlazrak <zlazrak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:16:52 by zlazrak           #+#    #+#             */
/*   Updated: 2023/02/28 17:05:45 by zlazrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_2.h"

int		ft_parse_2(t_queue *q, t_prompt *ys);
int		ft_here_doc(t_queue *queue, t_prompt *ys);
int		check_enclosed_quotes(char	*a);
/*************/

char	*ft_substr(char	*a, int s, int e)
{
	char	*answer;
	int		k;

	answer = malloc (sizeof (char) * (e - s + 1));
	k = 0;
	while (s < e && a[s])
		answer[k++] = a[s++];
	answer[k] = '\0';
	return (answer);
}

char	**ft_cp(t_queue *q)
{
	char	**answer;
	int		i;

	answer = malloc (sizeof(char *) * (ft_q_size(q) + 1));
	i = 0;
	while (q)
	{
		answer[i++] = ft_dupstr(q->data);
		q = q->next;
	}
	answer[i] = NULL;
	return (answer);
}

t_list	*ft_copy_(t_queue *q)
{
	t_list			*cmd;
	t_cmd_parse		*from;
	t_cmd_package	*to;

	cmd = NULL;
	while (q)
	{
		to = malloc(sizeof(t_cmd_package));
		from = q->data;
		to->cmd = ft_cp(from->cmd);
		to->file = ft_cp(from->file);
		to->rel = ft_cp(from->rel);
		to->buffer = ft_cp(from->buffer);
		to->fd_0 = 0;
		to->fd_1 = 1;
		ft_lstadd_back(&cmd, ft_lstnew(to));
		q = q->next;
	}
	return (cmd);
}

int	ft_check_q(char *a, t_prompt *ys)
{
	if (check_enclosed_quotes(a))
	{
		ys->exit_status = 258;
		return (1);
	}
	return (0);
}

int	ft_parse(char *a, t_prompt *ys)
{
	t_queue	*q;
	t_queue	*temp;

	if (ft_check_q(a, ys))
		return (1);
	q = ft_part_1(a);
	temp = ft_part_2(q);
	ft_free_q(q);
	q = ft_part_3(temp);
	ft_free_q(temp);
	if (ft_part_3_5(q))
	{
		ft_free_q(q);
		ys->exit_status = 258;
		return (1);
	}
	return (ft_parse_2(q, ys));
}
