#include "../minishell.h"

int	ft_unset_2(t_prompt *prompt, char **args)
{
	if (args[1] == NULL)
		return (0);
	for (int i = 1; args[i]; i++)
	{
		if (ft_isalnum_(args[i]))
		{
			t_env *current = prompt->s_env;
			if (my_strcmp(current->variable, args[i]))
			{
				prompt->s_env = prompt->s_env->next;
				free(current->value);
				free(current->variable);
				free(current);
			}
			else
			{
				while(current->next)
				{
					if (my_strcmp(current->next->variable, args[i]))
					{
						t_env *save = current->next;
						current->next = save->next;
						free(save->value);
						free(save->variable);
						free(save);
						break;
					}
					current = current->next;
				}
			}
		}
		else
			printf("unset: %s : not a valid identifier\n", args[i]);
	}
	return (0);
}

int	ft_env(t_prompt *prompt)
{
	t_env *current = prompt->s_env;
	while (current != NULL)
	{
		if (current->variable)
			printf("%s", current->variable);
		printf("=");
		if (current->value)
			printf("%s", current->value);
		printf("\n");
		current = current->next;
	}
	return (0);
}

int	ft_unset(t_prompt *prompt, char **args)
{
	int ret;

	ret = ft_unset_2(prompt, args);
	ft_free_all_(prompt->env);
	prompt->env = get_env(prompt->s_env);
	return (ret);
}