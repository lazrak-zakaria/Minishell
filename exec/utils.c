/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:43:47 by yel-mass          #+#    #+#             */
/*   Updated: 2023/02/26 10:50:39 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr_2(char *s, unsigned int start, size_t len)
{
	char			*d;
	size_t			i;
	unsigned int	s_len;

	i = 0;
	if (!s || !len)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len <= start)
		return (ft_strdup(""));
	while (i < len && i + start < s_len)
		i++;
	d = malloc((i + 1) * sizeof(char ));
	if (!d)
		return (NULL);
	i = 0;
	while (i < len && i + start < s_len)
	{
		d[i] = s[start + i];
		i++;
	}
	d[i] = '\0';
	return (d);
}

char	*ft_strdup(char *s1)
{
	int		i;
	char	*str;

	i = 0;
	while (s1 != NULL && s1[i])
		i++;
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[i] = '\0';
	while (--i >= 0)
		str[i] = s1[i];
	return (str);
}

size_t	ft_strlen(char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

int	my_strcmp(char *s1, char *s2)
{
	int	i;

	if (s1 == NULL || s2 == NULL)
		return (0);
	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	if (s1[i] || s2[i])
		return (0);
	return (1);
}

int	ft_isdigit(char *str)
{
	int	i;

	i = -1;
	if (str[0] == '\0')
		return (0);
	while (str[++i])
	{
		if ((str[i] > '9' || str[i] < '0') && str[i] != '-' && str[i] != '+')
			return (0);
		if ((str[i] == '-' || str[i] == '+') && (str[i + 1] > '9' || \
								str[i + 1] < '0'))
			return (0);
	}
	return (1);
}
