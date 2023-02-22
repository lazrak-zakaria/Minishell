#include "../minishell.h"

int	check_agrs(char *s)
{
	int i = 0;
	if ((s[0] >= '0' && s[0] <= '9') || s[0] == '\0' || s[0] == '=' || s[0] == '+')
	{
		printf_error("bash: export: `", s, "': not valid identifier\n");
		return (1);
	}
	while (s[i] && s[i] != '=')
	{
		if (s[i] == '+' && s[i + 1] == '=')
			break;
		if (!(s[i] >= 65 && s[i] <= 90) && !(s[i] >= 97 && s[i] <= 122) && !(s[i] >= '0' && s[i] <= '9') && s[i] != '_')
		{
			printf_error("bash: export: `", s, "': not valid identifier\n");
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_print_env(t_prompt *yassir)
{
	t_env *current = yassir->s_env;
	int i = 0;
	t_env	*head = NULL;
	while(current)
	{
		t_env	*new = malloc(sizeof(t_env));
		new->next = NULL;
		new->value = ft_strdup(current->value);
		new->variable = ft_strdup(current->variable);
		ft_env_addback(&head, new);
		current = current->next;
	}
	current = head;
	while (current->next)
	{
		if (ft_strcmp(current->variable, current->next->variable) < 0)
		{
			char *var = current->variable;
			char *val = current->value;
			current->value = current->next->value;
			current->variable = current->next->variable;

			current->next->value = val;
			current->next->variable = var;
			current = head;
		}
		else 
			current = current->next;
	}
	current = head;
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
	current = head;
	while (current)
	{
		free(current->value);
		free(current->variable);
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
	int		flag = 0;
	int		error = 0;
	if (prompt->list_cmd->data->cmd[1] == NULL)
		ft_print_env(prompt);
	else
	{
		int j = 0;
		while(prompt->list_cmd->data->cmd[++j] != NULL)
		{
			if (check_agrs(prompt->list_cmd->data->cmd[j]))
			{
				error = 1;
				continue;
			}
			i = -1;
			while(prompt->list_cmd->data->cmd[j][++i])
				if (prompt->list_cmd->data->cmd[j][i] == '=' || prompt->list_cmd->data->cmd[j][i] == '+')
					break;

			if (prompt->list_cmd->data->cmd[j][i] == '+' && ++i)
				flag = 1;
			if (prompt->list_cmd->data->cmd[j][i] == '=') // there is no =
				value = ft_strdup(&prompt->list_cmd->data->cmd[j][i + 1]);
			else
				value = NULL;
			variable = ft_substr(prompt->list_cmd->data->cmd[j], 0, i - flag);
			curr = prompt->s_env;
			while(curr)
			{
				if (my_strcmp(curr->variable, variable))
				{
					if (value != NULL && flag == 0)
					{
						free(curr->value);
						curr->value = value;
					}
					else if (value != NULL && flag == 1)
					{
						char *tmp = ft_strjoin(curr->value, value);
						free(curr->value);
						curr->value = tmp;
					}
					break;
				}
				curr = curr->next;
			}
			free(variable);
			if (curr != NULL)
				continue;
			free(value);
			ft_env_addback(&prompt->s_env, ft_env_new(prompt->list_cmd->data->cmd[j]));
		}
	}
	return (error);
}

int	ft_export(t_prompt *prompt)
{
	int ret;
	ret = ft_export_2(prompt);
	ft_free_all_(prompt->env);
	prompt->env = get_env(prompt->s_env);
	return (ret);
}