/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:43:28 by yel-mass          #+#    #+#             */
/*   Updated: 2023/03/01 12:57:30 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*a;
	unsigned char	*b;

	i = 0;
	a = (unsigned char *)s1;
	b = (unsigned char *)s2;
	while (i < n)
	{
		if (b[i] != a[i] || b[i] == '\0' || a[i] == '\0')
			return (a[i] - b[i]);
		i++;
	}
	return (0);
}

int	check_max(char *str)
{
	if (str[0] == '-')
	{
		if (ft_strlen(str) > ft_strlen("-9223372036854775808"))
			return (0);
		if (ft_strlen(str) < ft_strlen("-9223372036854775808"))
			return (1);
		if (ft_strncmp(str, "-9223372036854775808", 21) > 0)
			return (0);
	}
	else
	{
		if (ft_strlen(str) > ft_strlen("9223372036854775807"))
			return (0);
		if (ft_strlen(str) < ft_strlen("9223372036854775807"))
			return (1);
		if (ft_strncmp(str, "9223372036854775807", 21) > 0)
			return (0);
	}
	return (1);
}

int	ft_exit(char **args, t_prompt *prompt)
{
	if (args[1] == NULL)
		exit(prompt->exit_status);
	if (ft_isdigit(args[1]) && check_max(args[1]))
	{
		if (args[2] != NULL)
		{
			write(2, "exit: too many arguments\n", 26);
			return (1);
		}
		exit((unsigned char )ft_atoi(args[1]));
	}
	printf_error("bash: exit: ", args[1], ": numeric argument required\n");
	exit(255);
}
