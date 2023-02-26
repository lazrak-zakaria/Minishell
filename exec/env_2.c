/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:20:21 by yel-mass          #+#    #+#             */
/*   Updated: 2023/02/25 19:50:00 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
