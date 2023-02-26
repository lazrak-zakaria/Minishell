/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_part_5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlazrak <zlazrak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:23:58 by zlazrak           #+#    #+#             */
/*   Updated: 2023/02/26 13:45:11 by zlazrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_2.h"

t_queue	*ft_part_5(t_queue *queue)
{
	t_cmd_parse	*cmd;
	t_elem		*elem;
	t_var		var;
	char		*a;

	cmd = malloc(sizeof(t_cmd_parse));
	ft_memset(cmd, 0, sizeof(*cmd));
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
