/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:57:11 by zlazrak           #+#    #+#             */
/*   Updated: 2023/03/03 10:46:21 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"

t_queue	*ft_new_node(void *data)
{
	t_queue	*q;

	q = malloc(sizeof(t_queue));
	q->data = data;
	q->next = NULL;
	return (q);
}

void	ft_push(t_queue **top, t_queue *q)
{
	t_queue	*temp;

	temp = *top;
	if (!(*top))
	{
		*top = q;
		return ;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = q;
}

t_queue	*ft_pop(t_queue **top)
{
	t_queue	*answer;

	answer = *top;
	*top = (*top)->next;
	return (answer);
}

int	ft_q_size(t_queue *top)
{
	int	i;

	i = 0;
	while (top)
	{
		top = top->next;
		i++;
	}
	return (i);
}
