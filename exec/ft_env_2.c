/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:59:54 by yel-mass          #+#    #+#             */
/*   Updated: 2023/02/27 11:00:09 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_prompt *prompt)
{
	t_env	*current;

	current = prompt->s_env;
	while (current != NULL)
	{
		if (current->value != NULL)
		{
			write(prompt->list_cmd->data->fd_1, \
					current->variable, ft_strlen(current->variable));
			write(prompt->list_cmd->data->fd_1, "=", 1);
			write(prompt->list_cmd->data->fd_1, \
						current->value, ft_strlen(current->value));
			write(prompt->list_cmd->data->fd_1, "\n", 1);
		}
		current = current->next;
	}
	return (0);
}
