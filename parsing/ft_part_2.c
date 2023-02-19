/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_part_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 11:00:21 by zlazrak           #+#    #+#             */
/*   Updated: 2023/02/19 18:05:21 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_norm_p_2(char *a, t_var *var)
{
	while (a[var->i])
	{
		if (a[var->i] == '|')
		{
			if (var->flag)
			{
				ft_push(&var->queue_answer, ft_new_node(var->vec.string));
				memset(&var->vec, 0, sizeof(var->vec));
				var->flag = 0;
			}
			ft_push(&var->queue_answer,
				ft_new_node((ft_substr(a, var->i, var->i + 1))));
			var->i++;
		}
		else
			ft_norm_p1_2(a, var);
	}
}

t_queue	*ft_part_2(t_queue *queue)
{
	t_var	var;
	char	*a;

	var.queue_answer = NULL;
	while (queue)
	{
		memset(&var.vec, 0, sizeof(t_vector));
		var.flag = 0;
		var.i = 0;
		var.temp_queue = ft_pop(&queue);
		a = var.temp_queue->data;
		ft_norm_p_2(a, &var);
	}
	return (var.queue_answer);
}
