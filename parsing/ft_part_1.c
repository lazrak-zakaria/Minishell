/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_part_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlazrak <zlazrak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 11:00:06 by zlazrak           #+#    #+#             */
/*   Updated: 2023/02/26 14:15:54 by zlazrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_2.h"

void	ft_norm_p1_2(char *a, t_var *var)
{
	var->flag = 1;
	if (a[var->i] == '\'' || a[var->i] == '\"')
	{
		var->c = a[var->i];
		ft_push_back(&var->vec, a[var->i++]);
		while (a[var->i] && a[var->i] != var->c)
			ft_push_back(&var->vec, a[var->i++]);
		ft_push_back(&var->vec, a[var->i++]);
	}
	else if (a[var->i])
		ft_push_back(&var->vec, a[var->i++]);
	if (!a[var->i])
		ft_push(&var->queue_answer, ft_new_node(var->vec.string));
}

t_queue	*ft_part_1(char *a)
{
	t_var	var;

	ft_memset(&var, 0, sizeof(var));
	while (a[var.i])
	{
		if (a[var.i] == ' ' || a[var.i] == '\t')
		{
			if (var.flag)
			{
				ft_push(&var.queue_answer, ft_new_node(var.vec.string));
				var.flag = 0;
				ft_memset(&var.vec, 0, sizeof(t_vector));
			}
			var.i++;
			continue ;
		}
		else
			ft_norm_p1_2(a, &var);
	}
	return (var.queue_answer);
}

/********part 2********/

void	ft_norm_p_2(char *a, t_var *var)
{
	while (a[var->i])
	{
		if (a[var->i] == '|')
		{
			if (var->flag)
			{
				ft_push(&var->queue_answer, ft_new_node(var->vec.string));
				ft_memset(&var->vec, 0, sizeof(var->vec));
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
		ft_memset(&var.vec, 0, sizeof(t_vector));
		var.flag = 0;
		var.i = 0;
		var.temp_queue = ft_pop(&queue);
		a = var.temp_queue->data;
		ft_norm_p_2(a, &var);
	}
	return (var.queue_answer);
}
