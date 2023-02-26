/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:22:45 by yel-mass          #+#    #+#             */
/*   Updated: 2023/02/25 20:03:44 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_atoi(char *str)
{
	int					i;
	unsigned long long	number;
	int					signe;

	i = 0;
	signe = 1;
	number = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			signe = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10 + (str[i] - 48);
		i++;
	}
	return (number * signe);
}

int	check_agrs(char *s)
{
	int	i;

	i = 0;
	if ((s[0] >= '0' && s[0] <= '9') || s[0] == '\0' || \
									s[0] == '=' || s[0] == '+')
	{
		printf_error("bash: export: `", s, "': not valid identifier\n");
		return (1);
	}
	while (s[i] && s[i] != '=')
	{
		if (s[i] == '+' && s[i + 1] == '=')
			break ;
		if (!(s[i] >= 65 && s[i] <= 90) && !(s[i] >= 97 && s[i] <= 122) \
							&& !(s[i] >= '0' && s[i] <= '9') && s[i] != '_')
		{
			printf_error("bash: export: `", s, "': not valid identifier\n");
			return (1);
		}
		i++;
	}
	return (0);
}

void	sort_env(t_env *head)
{
	t_env	*current;
	char	*var;
	char	*val;

	current = head;
	while (current->next)
	{
		if (ft_strcmp(current->variable, current->next->variable) < 0)
		{
			var = current->variable;
			val = current->value;
			current->value = current->next->value;
			current->variable = current->next->variable;
			current->next->value = val;
			current->next->variable = var;
			current = head;
		}
		else
			current = current->next;
	}
}
