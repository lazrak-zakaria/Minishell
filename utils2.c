/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:20:29 by yel-mass          #+#    #+#             */
/*   Updated: 2023/03/03 10:46:05 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	if (s1[i] != '\0' && s2[i] != '\0' && s1[i] != s2[i])
		return (s2[i] - s1[i]);
	return (0);
}

int	ft_isalnum_(char *s)
{
	int	i;

	i = -1;
	if ((s[0] >= '0' && s[0] <= '9') || s[0] == '\0')
		return (0);
	while (s[++i])
		if (!(s[i] >= 65 && s[i] <= 90) && !(s[i] >= 97 && s[i] <= 122) \
						&& !(s[i] >= '0' && s[i] <= '9') && s[i] != '_')
			return (0);
	return (1);
}

void	ft_free_all_(char **strs)
{
	int	i;

	i = 0;
	if (strs == NULL)
		return ;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

int	ft_strchr(char *s, char c)
{
	int		i;

	i = -1;
	if (s != NULL)
		while (s[++i])
			if (s[i] == c)
				return (i);
	return (-1);
}

void	printf_error(char *s1, char *s2, char *s3)
{
	if (s1 != NULL)
		write(2, s1, ft_strlen(s1));
	if (s2 != NULL)
		write(2, s2, ft_strlen(s2));
	if (s3 != NULL)
		write(2, s3, ft_strlen(s3));
}
