/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlazrak <zlazrak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:04:51 by zlazrak           #+#    #+#             */
/*   Updated: 2023/03/03 13:27:10 by zlazrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_2.h"

int	ft_parse_2(t_queue *q, t_prompt *ys)
{
	t_queue	*temp;

	temp = ft_part_4(q, ys);
	ft_free_q(q);
	q = ft_part_5(temp);
	if (ft_here_doc(q, ys))
	{
		ft_free_qq(temp);
		ft_free_part_5(q);
		return (1);
	}
	ys->list_cmd = ft_copy_(q);
	ft_free_qq(temp);
	ft_free_part_5(q);
	return (0);
}

/*****part 5      ******/

void	ft_handle_token(char *a, t_cmd_parse *cmd, t_queue **queue, t_var *var)
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

t_queue	*ft_divide(char *a)
{
	t_var	var;

	ft_memset(&var, 0, sizeof(var));
	while (a && a[var.i])
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
		ft_push_back(&var.vec, a[var.i++]);
		var.flag = 1;
		if (!a[var.i])
			ft_push(&var.queue_answer, ft_new_node(var.vec.string));
	}
	return (var.queue_answer);
}

int	ft_bgs_check(char *a)
{
	int	i;
	int	f;

	i = 0;
	f = 0;
	while (a[i] && f < 2)
	{
		if (a[i] == ' ' || a[i] == '\t')
		{
			++i;
			continue ;
		}
		else
		{
			++f;
			while (a[i] && a[i] != ' ' && a[i] != '\t')
				++i;
		}
	}
	return (f >= 2);
}

int	ft_ncmpstr(char *s1, char *s2, size_t n)
{
	size_t			i;
	unsigned char	*a;
	unsigned char	*b;

	i = 0;
	a = (unsigned char *)s1;
	b = (unsigned char *)s2;
	while (a[i] && b[i] && i < n)
	{
		if (a[i] != b[i])
			return (a[i] - b[i]);
		i++;
	}
	if (i == n)
		return (0);
	return (a[i] - b[i]);
}
