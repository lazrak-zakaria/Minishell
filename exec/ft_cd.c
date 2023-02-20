#include "../minishell.h"
#include <errno.h>
#include <string.h>

char *search_env(t_env *env, char *str)
{
	while(env)
	{
		if (my_strcmp(env->variable, str))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

t_env *search_env_2(t_env *env, char *str)
{
	while(env)
	{
		if (my_strcmp(env->variable, str))
			return (env);
		env = env->next;
	}
	return (NULL);
}


int	ft_cd_2(char **args, t_prompt *prompt)
{
	t_env *str;

	if (!args[1] || my_strcmp(args[1], "~"))
	{
		str = search_env_2(prompt->s_env, "HOME");
		if (str != NULL && str->value != NULL)
		{
			chdir(str->value);
			return (0);
		}
		if (str == NULL)
			printf("cd: HOME not set\n");
	}
	else if (my_strcmp(args[1], "-"))
	{
		str = search_env_2(prompt->s_env, "OLDPWD");
		if (str != NULL && str->value != NULL)
		{
			chdir(str->value);
			printf("%s\n", str->value);
			return (0);
		}
		if (str == NULL)
			printf("cd: OLDPWD not set\n");
	}
	else
	{
		if (chdir(args[1]) == 0)
			return (0);
		printf("No Such File Or Dir\n");
	}
	return (1);
}

int	ft_cd(char **args, t_prompt *prompt)
{
	int exit_status;
	char buffer[1024];
	getcwd(buffer, 1024);
	exit_status = ft_cd_2(args, prompt);
	if (exit_status == 0)
	{
		char *home = search_env(prompt->s_env, "");
		if (home == NULL)
		{

		}
		else
		{
			t_env *env = prompt->s_env;
			while(env)
			{
				if (ft_strcmp(env->variable, "OLDPWD"))
				{
					free(env->value);
					char *value = ft_strdup(buffer);
					env->value = value;
					break;
				}
				env = env->next;
			}
			if (env == NULL)
			{
				char *variable = "OLDPWD";
				char *value = ft_strdup(buffer);
				env = ft_env_last(prompt->s_env);
				env->next = malloc(sizeof(t_env));
				if (env->next == NULL)
					return (1);
				env->next->value = value;
				env->variable = variable;
			}
		}
	}
	printf("%d\n", exit_status);
	return (0);
}

int	ft_pwd()
{
	char buf[1024];
	getcwd(buf, 1024);
	printf("%s\n", buf);
	return (0);
}