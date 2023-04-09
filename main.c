/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mass <yel-mass@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:02:54 by yel-mass          #+#    #+#             */
/*   Updated: 2023/04/09 08:07:52 by yel-mass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_prompt	g_prompt;

void	ft_signal_handler(int sg)
{
	if (sg == SIGINT)
	{
		if (g_prompt.flag == 2)
		{
			ft_putchar_fd('\n', 1);
			return ;
		}
		if (g_prompt.flag == 1)
			return ;
		else
			g_prompt.exit_status = 1;
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_signal(void)
{
	signal(SIGINT, ft_signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_minishell(void)
{
	char	*a;
	t_list	*to_free;

	while ("*_*")
	{
		g_prompt.flag = 0;
		g_prompt.list_cmd = NULL;
		a = readline("minishell: ");
		if (a == NULL)
		{
			printf("exit\n");
			exit(g_prompt.exit_status);
		}
		if (a[0])
			add_history(a);
		if (ft_parse(a, &g_prompt))
		{
			free(a);
			continue ;
		}
		free(a);
		to_free = g_prompt.list_cmd;
		ft_exec(&g_prompt);
		ft_free_lis(to_free);
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	g_prompt.flag = 0;
	ft_signal();
	g_prompt.s_env = ft_creat_env(env);
	g_prompt.env = get_env(g_prompt.s_env);
	g_prompt.exit_status = 0;
	g_prompt.list_cmd = NULL;
	ft_minishell();
}
