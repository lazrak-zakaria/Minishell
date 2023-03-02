/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hsub_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlazrak <zlazrak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 17:03:18 by zlazrak           #+#    #+#             */
/*   Updated: 2023/03/02 18:24:39 by zlazrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_2.h"

void	ft_sub_take(char *s, int *i, t_prompt *ys, t_vector *vec);

void	ft_heredocline(char c, char *s, t_vector *vec, t_prompt *ys)
{
	int	i;

	i = 0;
	if (c == 'E')
		while (s[i])
		{
			ft_sub_take(s, &i, ys, vec);
		}
	else
	{
		while (s[i])
			ft_push_back(vec, s[i++]);
	}
	ft_push_back(vec, '\n');
	free(s);
}

void	ft_here_var(t_vector *vec, t_prompt *ys)
{
	ft_memset(vec, 0, sizeof(t_vector));
	ft_push_back(vec, '\0');
	vec->i = 0;
	ys->exit_status = 0;
	ys->flag = 2;
}

void	ft_sig_hd(int *fd)
{
	signal(SIGINT, SIG_DFL);
	close(fd[0]);
}

int	ft_parent_(int *fd, t_prompt *ys, t_vector *vec, t_cmd_parse *cmd)
{
	char	c;

	close(fd[1]);
	wait(&ys->exit_status);
	ys->flag = 0;
	if (ys->exit_status == SIGINT)
	{
		ys->exit_status = 1;
		free(vec->string);
		return (1);
	}
	else
		ys->exit_status = 0;
	while (read(fd[0], &c, 1) > 0)
	{
		ft_push_back(vec, c);
	}
	close(fd[0]);
	ft_push(&cmd->buffer, ft_new_node(ft_dupstr(vec->string)));
	free(vec->string);
	return (0);
}
