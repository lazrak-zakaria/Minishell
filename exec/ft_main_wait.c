/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main_wait.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:09:24 by yel-mass          #+#    #+#             */
/*   Updated: 2023/03/01 13:12:13 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_wait_main(t_prompt *prompt, pid_t last_cmd)
{
	pid_t	ret_pid;
	int		exit_s;

	while (1)
	{
		ret_pid = wait(&exit_s);
		if (ret_pid == last_cmd)
			prompt->exit_status = exit_s;
		else if (ret_pid == -1)
			break ;
	}
	if (prompt->exit_status == SIGINT)
		prompt->exit_status = 130;
	else if (prompt->exit_status == SIGQUIT)
		prompt->exit_status = 131;
	else
		prompt->exit_status = prompt->exit_status / 256;
	prompt->flag = 0;
}
