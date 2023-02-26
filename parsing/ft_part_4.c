/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_part_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlazrak <zlazrak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 11:53:04 by zlazrak           #+#    #+#             */
/*   Updated: 2023/02/26 13:38:56 by zlazrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_2.h"

int	ft_find(char *a, char c)
{
	int	i;

	i = 0;
	while (a[i] && a[i] != c)
		i++;
	return (a[i] != '\0');
}

void	ft_norm_part4(char *a, t_var *var)
{
	while (a[var->i])
	{
		if (a[var->i] == '\'' || a[var->i] == '\"')
		{
			var->c = a[var->i++];
			while (a[var->i] && a[var->i] != var->c)
				ft_push_back(&var->vec, a[var->i++]);
			if (!a[var->i])
				break ;
			++var->i;
		}
		else
			ft_push_back(&var->vec, a[var->i++]);
	}
}

void	ft_var_part4(t_var *var, t_elem *element, char *a)
{
	ft_create_vector(&var->vec, 2);
	var->vec.string[0] = '\0';
	var->i = 0;
	var->flag = 0;
	element->quote = (a[0] == '\'' || a[0] == '\"');
	element->s = NULL;
	element->dollar = 0;
	element->d_s = ft_dupstr(a);
}

t_queue	*ft_part_4(t_queue *queue, t_prompt *ys)
{
	t_var	var;
	t_elem	*element;
	char	*a;

	var.queue_answer = NULL;
	while (queue)
	{
		var.temp_queue = ft_pop(&queue);
		element = malloc (sizeof (t_elem));
		a = var.temp_queue->data;
		ft_var_part4(&var, element, a);
		if (ft_find(a, '$'))
		{
			element->dollar = 1;
			element->s = ft_expand_dollar(a, ys);
			free (var.vec.string);
			ft_push(&var.queue_answer, ft_new_node(element));
			continue ;
		}
		ft_norm_part4(a, &var);
		element->s = var.vec.string;
		ft_push(&var.queue_answer, ft_new_node(element));
	}
	return (var.queue_answer);
}
