/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:43:25 by yel-mass          #+#    #+#             */
/*   Updated: 2023/02/24 14:27:21 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_agrs(char *s)
{
	int	i;

	i = 0;
	if ((s[0] >= '0' && s[0] <= '9') || s[0] == '\0' || \
									s[0] == '=' || s[0] == '+')
	{
		printf_error("bash: export: `", s, "': not valid identifier\n");
		return (1);
	}
	while (s[i] && s[i] != '=')
	{
		if (s[i] == '+' && s[i + 1] == '=')
			break ;
		if (!(s[i] >= 65 && s[i] <= 90) && !(s[i] >= 97 && s[i] <= 122) \
							&& !(s[i] >= '0' && s[i] <= '9') && s[i] != '_')
		{
			printf_error("bash: export: `", s, "': not valid identifier\n");
			return (1);
		}
		i++;
	}
	return (0);
}

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

void	sort_env(t_env *head)
{
	t_env	*current;
	char	*var;
	char	*val;

	current = head;
	while (current->next)
	{
		if (ft_strcmp(current->variable, current->next->variable) < 0)
		{
			var = current->variable;
			val = current->value;
			current->value = current->next->value;
			current->variable = current->next->variable;
			current->next->value = val;
			current->next->variable = var;
			current = head;
		}
		else
			current = current->next;
	}
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
			printf("%s", current->variable);
		if (current->value != NULL)
		{
			write(yassir->list_cmd->data->fd_1, "=\"", 2);
			write(yassir->list_cmd->data->fd_1, current->value, ft_strlen(current->value));
			write(yassir->list_cmd->data->fd_1, "\"", 1);
		}
		write(yassir->list_cmd->data->fd_1, "\n", 2);
		current = current->next;
	}
	ft_free_env(head);
}

int	ft_export_2(t_prompt *prompt)
{
	t_env	*curr;
	char	*variable;
	char	*value;
	int		i;
	int		j;
	int		flag;
	int		error;
	char	*tmp;

	flag = 0;
	error = 0;
	if (prompt->list_cmd->data->cmd[1] == NULL)
		ft_print_env(prompt);
	else
	{
		j = 0;
		while (prompt->list_cmd->data->cmd[++j] != NULL)
		{
			if (check_agrs(prompt->list_cmd->data->cmd[j]))
			{
				error = 1;
				continue ;
			}
			i = -1;
			while (prompt->list_cmd->data->cmd[j][++i])
				if (prompt->list_cmd->data->cmd[j][i] == '=' \
						|| prompt->list_cmd->data->cmd[j][i] == '+')
					break ;
			if (prompt->list_cmd->data->cmd[j][i] == '+' && ++i)
				flag = 1;
			if (prompt->list_cmd->data->cmd[j][i] == '=')
				value = ft_strdup(&prompt->list_cmd->data->cmd[j][i + 1]);
			else
				value = NULL;
			variable = ft_substr(prompt->list_cmd->data->cmd[j], 0, i - flag);
			curr = prompt->s_env;
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
			free(variable);
			if (curr != NULL)
				continue ;
			free(value);
			ft_env_addback(&prompt->s_env, \
					ft_env_new(prompt->list_cmd->data->cmd[j]));
		}
	}
	return (error);
}

int	ft_export(t_prompt *prompt)
{
	int	ret;

	ret = ft_export_2(prompt);
	ft_free_all_(prompt->env);
	prompt->env = get_env(prompt->s_env);
	return (ret);
}