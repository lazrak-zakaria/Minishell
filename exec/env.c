/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:41:32 by yel-mass          #+#    #+#             */
/*   Updated: 2023/02/22 16:52:16 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_env_new(char *str)
{
	t_env	*new;
	int		i;

	new = malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	i = -1;
	while (str[++i])
		if (str[i] == '=')
			break ;
	if (str[i] == '=')
		new->value = ft_strdup(&str[i + 1]);
	else
		new->value = NULL;
	new->variable = ft_substr(str, 0, i);
	new->next = NULL;
	return (new);
}

t_env	*ft_env_last(t_env *lst)
{
	t_env	*node;

	if (!lst)
		return (0);
	node = lst;
	while (node->next)
		node = node->next;
	return (node);
}

void	ft_env_addback(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_env_last(*lst);
	last->next = new;
}

t_env	*ft_creat_env(char **envp)
{
	t_env	*env;
	int		i;

	env = NULL;
	i = -1;
	while (envp[++i])
		ft_env_addback(&env, ft_env_new(envp[i]));
	return (env);
}

int	ft_count_env(t_env *current)
{
	int	i;

	i = 0;
	while (current)
	{
		if (current->value != NULL)
			i++;
		current = current->next;
	}
	return (i);
}

char	**get_env(t_env *envp)
{
	int		i;
	t_env	*current;
	char	**new_envp;
	char	*tmp;

	new_envp = malloc((ft_count_env(envp) + 1) * sizeof(char *));
	i = 0;
	current = envp;
	while (current)
	{
		if (current->value != NULL)
		{
			tmp = ft_strjoin(current->variable, "=");
			new_envp[i] = ft_strjoin(tmp, current->value);
			free(tmp);
			i++;
		}
		current = current->next;
	}
	new_envp[i] = NULL;
	return (new_envp);
}
