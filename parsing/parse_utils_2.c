/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlazrak <zlazrak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 19:53:01 by zlazrak           #+#    #+#             */
/*   Updated: 2023/02/26 14:10:00 by zlazrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_2.h"

// int	ft_strcmp(char *a, char *b)
// {
// 	int	i;

// 	i = 0;
// 	while (a[i] && b[i])
// 	{
// 		if (a[i] != b[i])
// 			break ;
// 		i++;
// 	}
// 	return (a[i] - b[i]);
// }

char	*ft_dupstr(char *s1)
{
	char	*a;
	size_t	i;

	i = ft_strlen(s1);
	a = (char *)malloc(sizeof(char) * (i + 1));
	if (!a)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		a[i] = s1[i];
		i++;
	}
	a[i] = '\0';
	return (a);
}

void	ft_memfree(char **a)
{
	int	i;

	i = 0;
	while (a && a[i])
	{
		free (a[i]);
		i++;
	}
	free (a);
}

void	ft_free_lis(t_list *head)
{
	t_list			*tt;
	t_cmd_package	*p;

	while (head)
	{
		tt = head->next;
		p = head->data;
		ft_memfree(p->cmd);
		ft_memfree(p->file);
		ft_memfree(p->rel);
		ft_memfree(p->buffer);
		free (p);
		free (head);
		head = tt;
	}
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*a;

	i = 0;
	a = (unsigned char *)b;
	while (i < len)
		a[i++] = (unsigned char)c;
	return (b);
}
