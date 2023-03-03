/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlazrak <zlazrak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:00:16 by zlazrak           #+#    #+#             */
/*   Updated: 2023/03/03 10:22:29 by zlazrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_2.h"

void	ft_putstr_fd(char *a, int fd)
{
	write (fd, a, ft_strlen(a));
}

void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}

int	_abs(int n)
{
	if (n < 0)
		return (n * (-1));
	return (n);
}

int	int_len(int n)
{
	int	l;

	l = 0;
	if (!n)
		return (1);
	while (n)
	{
		n /= 10;
		l++;
	}
	return (l);
}

char	*ft_itoa(int n)
{
	int		l;
	int		i;
	char	*a;

	l = int_len(n);
	if (n < 0)
		l++;
	a = (char *)malloc(sizeof(char) * (l + 1));
	if (!a)
		return (NULL);
	i = 0;
	if (n < 0)
		a[i++] = '-';
	a[l--] = '\0';
	while (l >= i)
	{
		a[l--] = _abs(n % 10) + '0';
		n /= 10;
	}
	return (a);
}

// int	ft_strlen(char *a)
// {
// 	int	i;

// 	i = 0;
// 	while (a[i])
// 		i++;
// 	return (i);
// }

int	ft_ncmpstr(char *s1, char *s2, size_t n)
{
	size_t			i;
	unsigned char	*a;
	unsigned char	*b;

	i = 0;
	a = (unsigned char *)s1;
	b = (unsigned char *)s2;
	while (a[i] && b[i] && i < n)
	{
		if (a[i] != b[i])
			return (a[i] - b[i]);
		i++;
	}
	if (i == n)
		return (0);
	return (a[i] - b[i]);
}
