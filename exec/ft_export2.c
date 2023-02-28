/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 20:00:37 by yel-mass          #+#    #+#             */
/*   Updated: 2023/02/27 15:33:37 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_export_2(t_prompt *prompt, char **cmd)
{
	char	*variable;
	char	*value;
	int		j;
	int		flag;
	int		error;

	error = 0;
	if (cmd[1] == NULL)
		return (ft_print_env(prompt), error);
	j = 0;
	while (cmd[++j] != NULL)
	{
		if (check_agrs(prompt->list_cmd->data->cmd[j]) && ++error)
			continue ;
		flag = ft_extracts_var_val(&variable, &value, cmd[j]);
		flag = ft_search_and_update(variable, value, prompt->s_env, flag);
		if (flag == 1)
			continue ;
		ft_env_addback(&prompt->s_env, \
				ft_env_new(prompt->list_cmd->data->cmd[j]));
	}
	return (error);
}

int	ft_export(t_prompt *prompt)
{
	int	j;
	int	error;

	j = 0;
	error = ft_export_2(prompt, prompt->list_cmd->data->cmd);
	ft_free_all_(prompt->env);
	prompt->env = get_env(prompt->s_env);
	if (error > 0)
		return (1);
	return (0);
}
