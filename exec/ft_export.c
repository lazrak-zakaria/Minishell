#include "../minishell.h"

int	check_agrs(char *s)
{
	int i = 0;
	if ((s[0] >= '0' && s[0] <= '9') || s[0] == '\0' || s[0] == '=')
	{
		printf("bash: export: `%s': not valid identifier\n", s);
		return (1);
	}
	while (s[i] && s[i] != '=')
	{
		if (!(s[i] >= 65 && s[i] <= 90) && !(s[i] >= 97 && s[i] <= 122) && !(s[i] >= '0' && s[i] <= '9') && s[i] != '_')
		{
			printf("bash: export: `%s': not valid identifier\n", s);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_print_env(t_prompt *yassir)
{
	t_env *current = yassir->s_env;
	while (current != NULL)
	{
		printf("declare -x ");
		if (current->variable != NULL)
			printf("%s", current->variable);
		if (current->value != NULL)
		{
			printf("=");
			printf("\"%s\"", current->value);
		}
			printf("\n");
		current = current->next;
	}
}

int	ft_export_2(t_prompt *prompt)
{
	t_env	*last;
	t_env	*curr;
	char *variable;
	char *value;
	int		i;
	if (prompt->list_cmd->data->cmd[1] == NULL)
		ft_print_env(prompt);
	else
	{
		int j = 0;
		while(prompt->list_cmd->data->cmd[++j] != NULL)
		{
			if (check_agrs(prompt->list_cmd->data->cmd[j]))
				continue;
			i = -1;
			while(prompt->list_cmd->data->cmd[j][++i])
				if (prompt->list_cmd->data->cmd[j][i] == '=')
					break;
			if (prompt->list_cmd->data->cmd[j][i] == '=') // there is no =
				value = ft_strdup(&prompt->list_cmd->data->cmd[j][i + 1]);
			else
				value = NULL;
			variable = ft_substr(prompt->list_cmd->data->cmd[j], 0, i);
			curr = prompt->s_env;
			while(curr)
			{
				if (my_strcmp(curr->variable, variable))
				{
					if (value != NULL)
					{
						free(curr->value);
						curr->value = value;
					}
					break;
				}
				curr = curr->next;
			}
			free(variable);
			if (curr != NULL)
				continue;
			free(value);
			//last = ft_env_last(prompt->s_env);
			//if (last == NULL)
			ft_env_addback(&prompt->s_env, ft_env_new(prompt->list_cmd->data->cmd[j]));
			// else
			// {
			// // 	t_env *new = malloc(sizeof(t_env));
			// // 	if (new == NULL)
			// // 		continue;
			// // 	last->next = new;
			// // 	new->variable = variable;
			// // 	new->value = value;
			// // 	new->next = NULL;
			// }
		}
	}
	return (0);
}

int	ft_export(t_prompt *prompt)
{
	int ret;
	ret = ft_export_2(prompt);
	ft_free_all_(prompt->env);
	prompt->env = get_env(prompt->s_env);
	return (ret);
}