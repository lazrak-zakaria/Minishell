/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_part_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 11:36:41 by zlazrak           #+#    #+#             */
/*   Updated: 2023/02/19 18:05:25 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_norm_part_3(char *a, t_var *var)
{
	while (a[var->i])
	{
		if (a[var->i] == '<' || a[var->i] == '>')
		{
			if (var->flag)
			{
				ft_push(&var->queue_answer, ft_new_node(var->vec.string));
				memset(&var->vec, 0, sizeof(t_vector));
				var->flag = 0;
			}
			while (a[var->i] == '>' || a[var->i] == '<')
				ft_push_back(&var->vec, a[var->i++]);
			ft_push(&var->queue_answer, ft_new_node(var->vec.string));
			memset(&var->vec, 0, sizeof(t_vector));
		}
		else
			ft_norm_p1_2(a, var);
	}
}

t_queue	*ft_part_3(t_queue *queue)
{
	t_var	var;
	char	*a;

	var.queue_answer = NULL;
	while (queue)
	{
		memset(&var.vec, 0, sizeof(t_vector));
		var.i = 0;
		var.flag = 0;
		var.temp_queue = ft_pop(&queue);
		a = var.temp_queue->data;
		ft_norm_part_3(a, &var);
	}
	return (var.queue_answer);
}
