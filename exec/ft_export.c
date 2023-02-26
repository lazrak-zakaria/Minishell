/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:43:25 by yel-mass          #+#    #+#             */
/*   Updated: 2023/02/25 20:03:03 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_dupenv(t_env *current)
{
	t_env	*head;
	t_env	*new;

	head = NULL;
	while (current)
	{
		new = malloc(sizeof(t_env));
		new->next = NULL;
		new->value = ft_strdup(current->value);
		new->variable = ft_strdup(current->variable);
		ft_env_addback(&head, new);
		current = current->next;
	}
	return (head);
}

void	ft_free_env(t_env *current)
{
	t_env	*tmp;

	while (current)
	{
		tmp = current->next;
		free(current->value);
		free(current->variable);
		free(current);
		current = tmp;
	}
}

void	ft_print_env(t_prompt *yassir)
{
	t_env	*current;
	t_env	*head;

	head = ft_dupenv(yassir->s_env);
	sort_env(head);
	current = head;
	while (current != NULL)
	{
		write(yassir->list_cmd->data->fd_1, "declare -x ", 12);
		if (current->variable != NULL)
		{
			write(yassir->list_cmd->data->fd_1, current->variable, \
											ft_strlen(current->variable));
		}
		if (current->value != NULL)
		{
			write(yassir->list_cmd->data->fd_1, "=\"", 2);
			write(yassir->list_cmd->data->fd_1, current->value, \
										ft_strlen(current->value));
			write(yassir->list_cmd->data->fd_1, "\"", 1);
		}
		write(yassir->list_cmd->data->fd_1, "\n", 2);
		current = current->next;
	}
	ft_free_env(head);
}

int	ft_extracts_var_val(char **var, char **val, char *cmd)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	while (cmd[++i])
		if (cmd[i] == '=' \
				|| cmd[i] == '+')
			break ;
	if (cmd[i] == '+' && ++i)
		flag = 1;
	if (cmd[i] == '=')
		*val = ft_strdup(&cmd[i + 1]);
	else
		*val = NULL;
	*var = ft_substr(cmd, 0, i - flag);
	return (flag);
}

int	ft_search_and_update(char *variable, char *value, t_env	*curr, int flag)
{
	char	*tmp;

	while (curr)
	{
		if (my_strcmp(curr->variable, variable))
		{
			if (value != NULL && flag == 0)
			{
				free(curr->value);
				curr->value = value;
			}
			else if (value != NULL && flag == 1)
			{
				tmp = ft_strjoin(curr->value, value);
				free(value);
				free(curr->value);
				curr->value = tmp;
			}
			break ;
		}
		curr = curr->next;
	}
	if (curr != NULL)
		return (free(variable), 1);
	return (free(variable), free(value), 0);
}
