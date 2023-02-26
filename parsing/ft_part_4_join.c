/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_part_4_join.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlazrak <zlazrak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:16:42 by zlazrak           #+#    #+#             */
/*   Updated: 2023/02/26 13:41:21 by zlazrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_2.h"

void	ft_subjoin_dollar(t_vector **vec, t_vector *vec_dollar, t_prompt *ys)
{
	char	*a;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (vec_dollar->string[1])
		j = 1;
	ft_push_back(vec_dollar, '=');
	a = vec_dollar->string;
	if (j)
		a = vec_dollar->string + 1;
	j = ft_strlen(a);
	i = 0;
	while (ys->env && ys->env[i])
	{
		if (!strncmp(a, ys->env[i], j))
		{
			while (ys->env[i][j])
				ft_push_back(*vec, ys->env[i][j++]);
			break ;
		}
		++i;
	}
}

void	ft_join_dollar(t_vector **vec, t_vector *vec_dollar, t_prompt *ys)
{
	char	*a;
	int		i;
	int		j;

	j = 0;
	if (vec_dollar->string[1] == '?')
	{
		a = ft_itoa(ys->exit_status);
		i = 0;
		while (a && a[i])
			ft_push_back(*vec, a[i++]);
		free (a);
	}
	else
		ft_subjoin_dollar(vec, vec_dollar, ys);
	free (vec_dollar->string);
}
