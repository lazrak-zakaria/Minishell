/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_part_sub_3_5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlazrak <zlazrak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:42:28 by zlazrak           #+#    #+#             */
/*   Updated: 2023/02/19 16:47:28 by zlazrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_token(char *a);

void	ft_putstr_fd(char *a, int fd)
{
	write (fd, a, strlen(a));
}

void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}

int	check_err(t_queue *q, char *a, char f)
{
	if (a[0] == '|' && !f)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
		return (1);
	}
	if (strlen(a) > 2)
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
