/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:43:47 by yel-mass          #+#    #+#             */
/*   Updated: 2023/02/22 15:40:29 by yel-mass         ###   ########.fr       */
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

static int	count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			return (count);
		while (s[i] != c && s[i] != '\0')
			i++;
		count++;
	}
	return (count);
}

static char	**free_all(char **s, int m)
{
	m--;
	while (m >= 0)
	{
		free(s[m]);
		m--;
	}
	free(s);
	return (NULL);
}

static void	get_len_word(char const *s, char c, int *index, int *len_word)
{
	while (s[*index] == c)
		*index += 1;
	while (s[*index + *len_word] != c && s[*index + *len_word])
		*len_word += 1;
}

char	**ft_split(char *s, char c)
{
	int		count;
	char	**words;
	int		m;
	int		index;
	int		len_word;

	count = count_words(s, c);
	words = malloc((count + 1) * sizeof(char *));
	index = 0;
	m = 0;
	if (!words)
		return (NULL);
	while (m < count)
	{
		len_word = 0;
		get_len_word(s, c, &index, &len_word);
		words[m] = ft_substr_2(s, index, len_word);
		if (!words[m++])
			return (free_all(words, m));
		index += len_word;
	}
	words[m] = 0;
	return (words);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*new_string;

	i = -1;
	j = -1;
	if (!s2)
		return (s1);
	if (!s1)
		return (s2);
	new_string = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char ));
	if (!new_string)
		return (NULL);
	while (s1[++i])
		new_string[i] = s1[i];
	while ((s2[++j]))
		new_string[i + j] = s2[j];
	new_string[i + j] = '\0';
	return (new_string);
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

int	ft_atoi(char *str)
{
	int					i;
	unsigned long long	number;
	int					signe;

	i = 0;
	signe = 1;
	number = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			signe = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = number * 10 + (str[i] - 48);
		i++;
	}
	return (number * signe);
}

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
