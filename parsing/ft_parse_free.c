/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlazrak <zlazrak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:31:46 by zlazrak           #+#    #+#             */
/*   Updated: 2023/02/26 13:44:51 by zlazrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_2.h"

void	ft_free_q(t_queue *q)
{
	t_queue	*te;

	te = q;
	while (q)
	{
		te = q->next;
		free (q->data);
		free (q);
		q = te;
	}
}

void	ft_free_qq(t_queue *q)
{
	t_queue	*te;
	t_elem	*e;

	te = q;
	while (q)
	{
		te = q->next;
		e = q->data;
		free (e->s);
		free(e->d_s);
		free (e);
		free (q);
		q = te;
	}
}

void	ft_free(t_queue *q)
{
	t_queue	*qq;

	while (q)
	{
		qq = q->next;
		free(q);
		q = qq;
	}
}

void	ft_free_part_5(t_queue *q)
{
	t_cmd_parse	*p;
	t_queue		*qq;

	while (q)
	{
		qq = q->next;
		p = q->data;
		ft_free(p->cmd);
		ft_free_q(p->file);
		ft_free_q(p->rel);
		ft_free_q(p->buffer);
		free(p);
		free(q);
		q = qq;
	}
}
