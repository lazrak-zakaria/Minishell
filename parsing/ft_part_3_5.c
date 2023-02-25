/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_part_3_5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlazrak <zlazrak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:40:33 by zlazrak           #+#    #+#             */
/*   Updated: 2023/02/25 12:55:07 by zlazrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_synerr(char *a, int i, int j);
int		check_err(t_queue *q, char *a, char f);

int	check_enclosed_quotes(char	*a)
{
	int		i;
	int		f;
	char	c;

	i = 0;
	f = 0;
	while (a[i])
	{
		if ((a[i] == '\'' || a[i] == '\"') && !f)
		{
			c = a[i];
			f = 1;
		}
		else if (f && a[i] == c)
			f = 0;
		i++;
	}
	return (f);
}

int	ft_is_token(char *a)
{
	return (a[0] == '>' || a[0] == '<' || a[0] == '|');
}

int	ft_err_1(char *a)
{
	if (a[2] == '>' && a[3] == '<')
	{
		ft_putstr_fd("bash: syntax error near unexpected token `>'", 2);
		ft_putchar_fd('\n', 2);
	}
	else if (strlen(a) == 3)
		ft_synerr(a, 2, -1);
	else if (strlen(a) >= 3)
		ft_synerr(a, 2, 3);
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
	if (strlen(a) >= 2)
	{
		if (a[0] == '>' && a[1] == '<')
		{
			ft_putstr_fd("bash: syntax error near unexpected token `>'", 2);
			ft_putchar_fd('\n', 2);
		}
		else if (strlen(a) >= 2)
			ft_synerr(a, 0, 1);
	}
	else
		ft_synerr(a, 0, -1);
	return (1);
}

int	ft_part_3_5(t_queue *q)
{
	char	*a;
	char	*b;
	char	f;

	f = 0;
	while (q)
	{
		a = q->data;
		if (a[0] == '>' || a[0] == '<' || a[0] == '|')
		{
			if (check_err(q, a, f))
				return (1);
		}
		f = 1;
		q = q->next;
	}
	return (0);
}
