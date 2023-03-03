/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_part_5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlazrak <zlazrak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:23:58 by zlazrak           #+#    #+#             */
/*   Updated: 2023/03/03 20:35:27 by zlazrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_2.h"

t_queue	*ft_part_5(t_queue *queue)
{
	t_cmd_parse	*cmd;
	t_elem		*elem;
	t_var		var;

	cmd = malloc(sizeof(t_cmd_parse));
	ft_memset(cmd, 0, sizeof(t_cmd_parse));
	var.queue_answer = NULL;
	var.flag = 0;
	while (queue)
	{
		var.temp_queue = ft_pop(&queue);
		elem = var.temp_queue->data;
		if (var.flag)
		{
			cmd = malloc(sizeof(t_cmd_parse));
			ft_memset(cmd, 0, sizeof(*cmd));
			var.flag = 0;
		}
		ft_part_norm5(elem, cmd, &queue, &var);
	}
	ft_push(&var.queue_answer, ft_new_node(cmd));
	return (var.queue_answer);
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
