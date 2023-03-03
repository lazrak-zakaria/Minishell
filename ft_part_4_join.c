/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_part_4_join.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:16:42 by zlazrak           #+#    #+#             */
/*   Updated: 2023/03/03 10:46:05 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_2.h"

void	ft_cp_env(t_vector **vec, char *a, int j);

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
		if (!ft_ncmpstr(a, ys->env[i], j))
		{
			ft_cp_env(vec, ys->env[i], j);
			break ;
		}
		++i;
	}
}

void	ft_cp_env(t_vector **vec, char *a, int j)
{
	int	f;

	f = 0;
	while (a[j])
	{
		if (a[j] == ' ')
		{
			if (f)
				ft_push_back(*vec, a[j]);
			f = 0;
		}
		else
		{
			ft_push_back(*vec, a[j]);
			f = 1;
		}
		++j;
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
