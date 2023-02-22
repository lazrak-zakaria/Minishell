/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:43:28 by yel-mass          #+#    #+#             */
/*   Updated: 2023/02/22 12:43:29 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exit(char **args, t_prompt *prompt)
{
	if (args[1] == NULL)
		exit(prompt->exit_status);
	if (ft_isdigit(args[1]))
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

/*
bash: exit: %s: numeric argument required && exit => 255 
*/
/*
bash: exit: too many arguments | $? => 1 if the first args numeric and there is more then one args
*/