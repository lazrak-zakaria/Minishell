/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 15:41:32 by yel-mass          #+#    #+#             */
/*   Updated: 2023/03/03 10:46:05 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_env_new(char *str)
{
	t_env	*new;
	int		i;
	int		flag;

	flag = 0;
	new = malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	i = -1;
	while (str[++i])
		if (str[i] == '=' || str[i] == '+')
			break ;
	if (str[i] == '+')
		flag = 1;
	if (str[i + flag] == '=')
		new->value = ft_strdup(&str[i + flag + 1]);
	else
		new->value = NULL;
	new->variable = ft_substr_2(str, 0, (i));
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
