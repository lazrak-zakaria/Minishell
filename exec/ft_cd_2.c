/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:06:23 by yel-mass          #+#    #+#             */
/*   Updated: 2023/03/02 14:49:49 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_oldpwd(t_prompt *prompt, char *cwd, char *oldpwd)
{
	char	*tmp;
	t_env	*env;

	if (oldpwd == NULL)
	{
		tmp = ft_strjoin("OLDPWD=", cwd);
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
				env->value = ft_strdup(cwd);
				break ;
			}
			env = env->next;
		}
	}
}

void	update_pwd(t_prompt *prompt, char *cwd)
{
	char	*tmp;
	t_env	*env;

	if (search_env(prompt->s_env, "PWD") == NULL)
	{
		tmp = ft_strjoin("PWD=", cwd);
		ft_env_addback(&prompt->s_env, ft_env_new(tmp));
		free(tmp);
	}
	else
	{
		env = prompt->s_env;
		while (env)
		{
			if (my_strcmp(env->variable, "PWD"))
			{
				if (env->value != NULL)
					free(env->value);
				env->value = ft_strdup(cwd);
				break ;
			}
			env = env->next;
		}
	}
}

void	ft_cd_norm(t_prompt *prompt, char *buffer, char *oldpwd, char *buffer2);

int	ft_cd(char **args, t_prompt *prompt, int a, int fd)
{
	char	buffer[PATH_MAX];
	char	buffer2[PATH_MAX];
	int		exit_status;
	char	*oldpwd;

	oldpwd = search_env(prompt->s_env, "OLDPWD");
	if (a == 1)
	{
		getcwd(buffer, PATH_MAX);
		exit_status = ft_cd_2(args, prompt);
		getcwd(buffer2, PATH_MAX);
		if (exit_status == 0 && !my_strcmp(buffer, buffer2))
			ft_cd_norm(prompt, buffer, oldpwd, buffer2);
		return (exit_status);
	}
	else
	{
		getcwd(buffer, PATH_MAX);
		write(fd, buffer, ft_strlen(buffer));
		write(fd, "\n", 1);
	}
	return (0);
}

void	ft_cd_norm(t_prompt *prompt, char *buffer, char *oldpwd, char *buffer2)
{
	update_oldpwd(prompt, buffer, oldpwd);
	update_pwd(prompt, buffer2);
	ft_free_all_(prompt->env);
	prompt->env = get_env(prompt->s_env);
}
