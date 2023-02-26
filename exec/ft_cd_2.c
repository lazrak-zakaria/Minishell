/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:06:23 by yel-mass          #+#    #+#             */
/*   Updated: 2023/02/26 08:04:16 by yel-mass         ###   ########.fr       */
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

int	ft_cd(char **args, t_prompt *prompt, int a, int fd)
{
	char	buffer[PATH_MAX + 1];
	int		exit_status;
	char	*oldpwd;

	oldpwd = search_env(prompt->s_env, "OLDPWD");
	if (a == 1)
	{
		getcwd(buffer, 1024);
		exit_status = ft_cd_2(args, prompt);
		if (exit_status == 0)
			update_oldpwd(prompt, buffer, oldpwd);
		return (exit_status);
	}
	getcwd(buffer, PATH_MAX);
	write(fd, buffer, ft_strlen(buffer));
	write(fd, "\n", 1);
	return (0);
}
