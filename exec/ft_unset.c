/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:26:02 by yel-mass          #+#    #+#             */
/*   Updated: 2023/02/24 14:30:56 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset_2(t_prompt *prompt, char **args)
{
	int		error;
	t_env	*current;
	t_env	*save;
	int		i;

	error = 0;
	if (args[1] == NULL)
		return (0);
	i = 0;
	while (args[++i])
	{
		if (ft_isalnum_(args[i]))
		{
			current = prompt->s_env;
			if (current != NULL)
			{
				if (my_strcmp(current->variable, args[i]))
				{
					prompt->s_env = prompt->s_env->next;
					free(current->value);
					free(current->variable);
					free(current);
				}
				else
				{
					while (current->next)
					{
						if (my_strcmp(current->next->variable, args[i]))
						{
							save = current->next;
							current->next = save->next;
							free(save->value);
							free(save->variable);
							free(save);
							break ;
						}
						current = current->next;
					}
				}
			}
		}
		else
		{
			write(2, "bash: unset: `", 15);
			write(2, args[i], ft_strlen(args[i]));
			write(2, "': not a valid identifier\n", 27);
			error = 1;
		}
	}
	return (error);
}

int	ft_env(t_prompt *prompt)
{
	t_env	*current;

	current = prompt->s_env;
	while (current != NULL)
	{
		if (current->value != NULL)
		{
			write(prompt->list_cmd->data->fd_1, current->variable, ft_strlen(current->variable));
			write(prompt->list_cmd->data->fd_1, "=", 1);
			write(prompt->list_cmd->data->fd_1, current->value, ft_strlen(current->value));
			write(prompt->list_cmd->data->fd_1, "\n", 1);
		}
		current = current->next;
	}
	return (0);
}

int	ft_unset(t_prompt *prompt, char **args)
{
	int	ret;

	if (prompt->env == NULL)
		return (0);
	ret = ft_unset_2(prompt, args);
	ft_free_all_(prompt->env);
	prompt->env = get_env(prompt->s_env);
	return (ret);
}