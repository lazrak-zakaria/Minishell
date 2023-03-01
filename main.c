/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlazrak <zlazrak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:02:54 by yel-mass          #+#    #+#             */
/*   Updated: 2023/03/01 11:59:20 by zlazrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_prompt 	prompt;
void    ft_signal_handler(int sg)
{
	if (sg == SIGINT)
	{
		if (prompt.flag == 2)
		{
			ft_putchar_fd('\n', 1);
			return ;
		}
		if (prompt.flag == 1)
			return ;
		else
			prompt.exit_status = 1;
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void    ft_signal(void)
{
	// struct termios    mini_shell; 

	// tcgetattr(STDIN_FILENO, &mini_shell); 
	// mini_shell.c_lflag &= ~ECHOCTL; 
	// tcsetattr(STDIN_FILENO, TCSANOW, &mini_shell);

	signal(SIGINT, ft_signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	

	//ex_status = &prompt.exit_status;
	prompt.flag = 0;
	ft_signal();
	prompt.s_env = ft_creat_env(env); //		linked list
	prompt.env = get_env(prompt.s_env); // 		char ** alocated
	//prompt.exit_status = 0;
	prompt.list_cmd = NULL;
	while(1)
	{
		//printf("%d_", prompt.exit_status);
		prompt.list_cmd = NULL;
		char *a = readline("minishell: ");
		if (a == NULL)
		{
			printf("exit\n");
			exit(prompt.exit_status);
		}
		if(a[0])
			add_history(a);
		if (ft_parse(a, &prompt))
		{
			free(a);
			continue ;
		}
		free(a);

	/******************************/
		t_list *oo = prompt.list_cmd;
		ft_exec(&prompt);
		ft_free_lis(oo);

	}
}
 