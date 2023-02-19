/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_part_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 11:00:06 by zlazrak           #+#    #+#             */
/*   Updated: 2023/02/19 15:14:11 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

	memset(&var, 0, sizeof(var));
	while (a[var.i])
	{
		if (a[var.i] == ' ')
		{
			if (var.flag)
			{
				ft_push(&var.queue_answer, ft_new_node(var.vec.string));
				var.flag = 0;
				memset(&var.vec, 0, sizeof(t_vector));
			}
			var.i++;
			continue ;
		}
		else
			ft_norm_p1_2(a, &var);
	}
	return (var.queue_answer);
}
