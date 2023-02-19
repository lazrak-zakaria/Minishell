#include "../minishell.h"

int	ft_export_2(t_yassir *promet)
{
	t_env	*last;
	t_env	*curr;
	int		i;
	if (promet->list_cmd->data->cmd[1] == NULL)
	{
		t_env *current = promet->s_env;
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
	else
	{
		int j = 0;
		while(promet->list_cmd->data->cmd[++j] != NULL)
		{
			i = -1;
			while(promet->list_cmd->data->cmd[j][++i])
				if (promet->list_cmd->data->cmd[j][i] == '=')
					break;
			if (promet->list_cmd->data->cmd[j][i] == '\0') // there is no =
				continue;
			char *variable = ft_substr(promet->list_cmd->data->cmd[j], 0, i);
			if (variable == NULL || ft_isalnum_(variable) == 0)
			{
				printf("Not Valid Variable\n");
				free(variable);
				continue;
			}
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
			t_env *new = malloc(sizeof(t_env));
			printf("%s\n", variable);
			if (new == NULL)
				continue;
			last->next = new;
			new->variable = variable;
			new->value = value;
			new->next = NULL;
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