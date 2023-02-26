/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 17:21:35 by yel-mass          #+#    #+#             */
/*   Updated: 2023/02/26 08:04:43 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
