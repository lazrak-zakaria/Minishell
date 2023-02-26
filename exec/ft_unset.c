/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:26:02 by yel-mass          #+#    #+#             */
/*   Updated: 2023/02/26 13:19:03 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_unset_error(char *variable_name)
{
	write(2, "bash: unset: `", 15);
	write(2, variable_name, ft_strlen(variable_name));
	write(2, "': not a valid identifier\n", 27);
	return (1);
}

void	free_env_node(t_env *node, t_prompt	*prompt, int a)
{
	if (a == 1)
		prompt->s_env = prompt->s_env->next;
	free(node->value);
	free(node->variable);
	free(node);
}

void	remove_env_variable(t_prompt *prompt, char *variable_name)
{
	t_env	*current;
	t_env	*save;

	current = prompt->s_env;

	while (current->next)
	{
		if (my_strcmp(current->next->variable, variable_name))
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

int	ft_unset_2(t_prompt *prompt, char **args)
{
	int		error;
	t_env	*current;
	t_env	*save;
	int		i;

	error = 0;
	i = 0;
	while (args[++i])
	{
		if (ft_isalnum_(args[i]))
		{
			current = prompt->s_env;
			if (current != NULL)
			{
				if (my_strcmp(current->variable, args[i]))
					free_env_node(current, prompt, 1);
				else
					remove_env_variable(prompt, args[i]);
			}
		}
		else
			error = print_unset_error(args[i]);
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
