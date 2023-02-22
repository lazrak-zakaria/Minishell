/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:32:18 by yel-mass          #+#    #+#             */
/*   Updated: 2023/02/22 16:51:08 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(char **args, int fd)
{
	int	i;
	int	j;
	int	flag;

	flag = 0;
	i = 0;
	if (args[1] == NULL)
	{
		write(1, "\n", 1);
		return (0);
	}
	while (args[++i] != NULL && args[i][0] == '-')
	{
		j = 0;
		while (args[i][++j])
		{
			if (args[i][j] != 'n')
				break ;
		}
		if (args[i][j] != '\0')
			break ;
	}
	if (i > 1)
		flag = 1;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
			write(fd, &args[i][j++], 1);
		if (args[i + 1])
			write(fd, " ", 1);
		i++;
	}
	if (flag == 0)
		write(fd, "\n", 1);
	return (0);
}