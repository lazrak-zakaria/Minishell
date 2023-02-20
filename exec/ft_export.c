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
	if (s[i] == '\0')
		return (1);
	return (0);
}

void	ft_print_env(t_yassir *yassir)
{
	t_env *current = yassir->s_env;
	while (current != NULL)
	{
		printf("declare -x ");
		if (current->variable)
			printf("%s", current->variable);
		printf("=");
		if (current->value)
			printf("\"%s\"", current->value);
		printf("\n");
		current = current->next;
	}
}

int	ft_export_2(t_yassir *promet)
{
	t_env	*last;
	t_env	*curr;
	int		i;
	if (promet->list_cmd->data->cmd[1] == NULL)
		ft_print_env(promet);
	else
	{
		int j = 0;
		while(promet->list_cmd->data->cmd[++j] != NULL)
		{
			if (check_agrs(promet->list_cmd->data->cmd[j]))
				continue;
			i = -1;
			while(promet->list_cmd->data->cmd[j][++i])
				if (promet->list_cmd->data->cmd[j][i] == '=')
					break;
			if (promet->list_cmd->data->cmd[j][i] == '\0') // there is no =
				continue;
			char *variable = ft_substr(promet->list_cmd->data->cmd[j], 0, i);
			char *value = ft_strdup(&promet->list_cmd->data->cmd[j][i + 1]);
			curr = promet->s_env;
			while(curr)
			{
				if (my_strcmp(curr->variable, variable))
				{
					free(curr->value);
					free(variable);
					curr->value = value;
					break;
				}
				curr = curr->next;
			}
			if (curr != NULL)
				continue;
			last = ft_env_last(promet->s_env);
			if (last == NULL)
			{
				printf("NOT TODAY\n");
			}
			else
			{
				t_env *new = malloc(sizeof(t_env));
				if (new == NULL)
					continue;
				last->next = new;
				new->variable = variable;
				new->value = value;
				new->next = NULL;
			}
		}
	}
	return (0);
}

int	ft_export(t_yassir *promet)
{
	int ret;
	ret = ft_export_2(promet);
	ft_free_all_(promet->env);
	promet->env = get_env(promet->s_env);
	return (ret);
}