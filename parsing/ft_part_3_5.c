/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_part_3_5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlazrak <zlazrak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:40:33 by zlazrak           #+#    #+#             */
/*   Updated: 2023/02/25 18:46:46 by zlazrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_2.h"

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
