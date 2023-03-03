/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_part_4_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:14:35 by zlazrak           #+#    #+#             */
/*   Updated: 2023/03/03 10:46:05 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_2.h"

int	ft_dollar_ok(char c)
{
	int	f;

	f = ((c == '_') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
			|| (c >= '0' && c <= '9'));
	return (f);
}

void	ft_sub_expand(char *a, t_vector *vec, t_prompt *ys, int *i)
{
	t_pr	pr;

	if (a[(*i)] == '\'')
	{
		(*i)++;
		while (a[(*i)] && a[(*i)] != '\'')
			ft_push_back(vec, a[(*i)++]);
		(*i)++;
	}
	else if (a[(*i)] == '\"')
	{
		(*i)++;
		while (a[(*i)] && a[(*i)] != '\"')
		{
			pr.i = i;
			pr.f = 1;
			ft_norm_expand(a, vec, ys, &pr);
		}
		if (!vec->string)
		{
			ft_push_back(vec, '\0');
			vec->i--;
		}	
		(*i)++;
	}
}

void	ft_sub_norm(char *a, t_vector *vec, int *i, int *flag)
{
	ft_memset(vec, 0, sizeof(t_vector));
	ft_push_back(vec, a[(*i)++]);
	if (a[(*i)] >= '0' && a[*i] <= '9')
		ft_push_back(vec, a[(*i)++]);
	else
	{
		if (a[(*i)] == '?')
			ft_push_back(vec, a[(*i)++]);
		else
			while (ft_dollar_ok(a[(*i)]))
				ft_push_back(vec, a[(*i)++]);
	}
	*flag = 1;
}

void	ft_norm_expand(char *a, t_vector *vec, t_prompt *ys, t_pr *pr)
{
	t_vector	vec_dollar;
	int			flag;

	flag = 0;
	if (a[*(pr->i)] == '$')
		ft_sub_norm(a, &vec_dollar, pr->i, &flag);
	if (flag)
	{
		if (ft_strlen(vec_dollar.string) == 1 && !ft_dollar_ok(a[*(pr->i)])
			&& (pr->f || (a[*(pr->i)] != '"' && a[*(pr->i)] != '\'')))
		{
			ft_push_back(vec, vec_dollar.string[0]);
			free (vec_dollar.string);
		}
		else
			ft_join_dollar(&vec, &vec_dollar, ys);
	}
	else
		ft_push_back(vec, a[(*(pr->i))++]);
}

char	*ft_expand_dollar(char *a, t_prompt *ys)
{
	t_vector	vec;
	int			i;
	t_pr		pr;

	ft_memset(&vec, 0, sizeof(vec));
	i = 0;
	while (a[i])
	{
		if (a[i] == '\'' || a[i] == '\"')
			ft_sub_expand(a, &vec, ys, &i);
		else
		{
			pr.i = &i;
			pr.f = 0;
			ft_norm_expand(a, &vec, ys, &pr);
		}
	}
	return (vec.string);
}
