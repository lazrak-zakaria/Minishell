/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_part_sub_3_5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlazrak <zlazrak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:42:28 by zlazrak           #+#    #+#             */
/*   Updated: 2023/03/03 15:49:36 by zlazrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_2.h"

int	ft_is_token(char *a);

void	ft_synerr(char *a, int i, int j)
{
	ft_putstr_fd("bash: syntax error near unexpected token `", 2);
	if (i != -1)
		ft_putchar_fd(a[i], 2);
	if (j != -1)
		ft_putchar_fd(a[j], 2);
	ft_putchar_fd('\'', 2);
	ft_putchar_fd('\n', 2);
}

int	check_err(t_queue *q, char *a, char f)
{
	if (a[0] == '|' && !f)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
		return (1);
	}
	if (ft_strlen(a) == 2 && a[0] != a[1])
	{
		ft_synerr(a, 1, -1);
		return (1);
	}
	if (ft_strlen(a) > 2)
		return (ft_err_1(a));
	else if (q->next && ft_is_token(q->next->data))
		return (ft_err_2(q->next->data, a));
	else if (!q->next)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
		return (1);
	}
	return (0);
}

int	ft_err_1(char *a)
{
	if (a[0] == a[1] && !a[3])
			ft_synerr(a, 2, -1);
	else if (a[0] == a[1])
	{
		if (a[2] == a[3])
			ft_synerr(a, 2, 3);
		else if (a[2] != a[3])
			ft_synerr(a, 2, -1);
	}
	else if (a[0] != a[1] && !a[2])
		ft_synerr(a, 1, -1);
	else if (a[0] != a[1])
	{
		if (a[1] == a[2])
			ft_synerr(a, 1, 2);
		else if (a[1] != a[2])
			ft_synerr(a, 1, -1);
	}
	return (1);
}

int	ft_err_2(char *a, char *b)
{
	if (a[0] == '|')
	{
		ft_putstr_fd("bash: syntax error near unexpected token `|'", 2);
		ft_putchar_fd('\n', 2);
		return (1);
	}
	else if (b[0] == '|')
		return (0);
	if (ft_strlen(a) >= 2)
	{
		if (a[0] != a[1])
			ft_synerr(a, 1, -1);
		else
			ft_synerr(a, 0, 1);
	}
	else
		ft_synerr(a, 0, -1);
	return (1);
}
