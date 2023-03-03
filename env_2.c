/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:20:21 by yel-mass          #+#    #+#             */
/*   Updated: 2023/03/03 10:46:05 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**free_all(char **s, int m);

char	**get_env(t_env *envp)
{
	int		i;
	t_env	*current;
	char	**new_envp;
	char	*tmp;

	new_envp = malloc((ft_count_env(envp) + 1) * sizeof(char *));
	if (new_envp == NULL)
		return (NULL);
	i = 0;
	current = envp;
	while (current)
	{
		if (current->value != NULL)
		{
			tmp = ft_strjoin(current->variable, "=");
			new_envp[i] = ft_strjoin(tmp, current->value);
			free(tmp);
			if (new_envp[i] == NULL)
				return (free_all(new_envp, i));
			i++;
		}
		current = current->next;
	}
	new_envp[i] = NULL;
	return (new_envp);
}
