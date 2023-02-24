/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:32:27 by yel-mass          #+#    #+#             */
/*   Updated: 2023/02/24 17:35:54 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <string.h>

char	*search_env(t_env *env, char *str)
{
	while(env)
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

int	ft_cd_2(char **args, t_prompt *prompt)
{
	t_env	*str;

	if (!args[1] || my_strcmp(args[1], "~"))
	{
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
	}
	else if (my_strcmp(args[1], "-"))
	{
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

int	ft_cd(char **args, t_prompt *prompt)
{
	int		exit_status;
	char	buffer[1024];
	char	*home;
	char	*tmp;
	t_env	*env;

	getcwd(buffer, 1024);
	exit_status = ft_cd_2(args, prompt);
	if (exit_status == 0)
	{
		home = search_env(prompt->s_env, "OLDPWD");
		if (home == NULL)
		{
			tmp = ft_strjoin("OLDPWD=", buffer);
			ft_env_addback(&prompt->s_env, ft_env_new(tmp));
			free(tmp);
		}
		else
		{
			env = prompt->s_env;
			while (env)
			{
				if (my_strcmp(env->variable, "OLDPWD"))
				{
					if (env->value != NULL)
						free(env->value);
					env->value = ft_strdup(buffer);
					break ;
				}
				env = env->next;
			}
		}
	}
	return (exit_status);
}

#include <limits.h>

int	ft_pwd(int fd)
{
	char buf[PATH_MAX + 1];

	getcwd(buf, PATH_MAX);
	write(fd, buf, ft_strlen(buf));
	write(fd, "\n", 1);
	return (0);
}