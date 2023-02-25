/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:32:27 by yel-mass          #+#    #+#             */
/*   Updated: 2023/02/25 17:05:59 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <string.h>

char	*search_env(t_env *env, char *str)
{
	while (env)
	{
		if (my_strcmp(env->variable, str))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

t_env	*search_env_2(t_env *env, char *str)
{
	while (env)
	{
		if (my_strcmp(env->variable, str))
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	ft_last_path(t_prompt *prompt)
{
	t_env	*str;

	str = search_env_2(prompt->s_env, "OLDPWD");
	if (str != NULL && str->value != NULL)
	{
		if (chdir(str->value) != 0)
		{
			write(2, "bash: cd: ", 11);
			perror(str->value);
			return (1);
		}
		write(prompt->list_cmd->data->fd_1, str->value, ft_strlen(str->value));
		write(prompt->list_cmd->data->fd_1, "\n", 1);
		return (0);
	}
	write(2, "bash: cd: OLDPWD not set\n", 26);
	return (1);
}

int	ft_home(t_prompt *prompt)
{
	t_env	*str;

	str = search_env_2(prompt->s_env, "HOME");
	if (str != NULL && str->value != NULL)
	{
		if (chdir(str->value) != 0)
		{
			write(2, "bash: cd: ", 11);
			perror(str->value);
			return (1);
		}
		return (0);
	}
	write(2, "bash: cd: HOME not set\n", 24);
	return (1);
}

int	ft_cd_2(char **args, t_prompt *prompt)
{
	if (!args[1] || my_strcmp(args[1], "~"))
	{
		if (ft_home(prompt) == 0)
			return (0);
	}
	else if (my_strcmp(args[1], "-"))
	{
		if (ft_last_path(prompt) == 0)
			return (0);
	}
	else
	{
		if (chdir(args[1]) == 0)
			return (0);
		write(2, "bash: cd: ", 11);
		perror(args[1]);
	}
	return (1);
}
