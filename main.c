#include "minishell.h"

t_prompt 	prompt;
void    ft_signal_handler(int sg)
{
	// if (wait(NULL) != -1)
	// {
	// 	prompt.flag = 0;
	// 	return ;
	// }

//	printf("%d\n", );
	//wait(&prompt.exit_status);
	if (sg == SIGINT)
	{
		if (prompt.flag == 1)
			return ;
		else
			prompt.exit_status = 1;
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else
	{
		//ft_putchar_fd('\n', 1);
		rl_on_new_line();
		//rl_replace_line("", 0);
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
	signal(SIGQUIT, ft_signal_handler);
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
		char *a = readline("MINISHELL:");
		if (a == NULL)
		{
			printf("exit\n");
			exit(prompt.exit_status);
		}
		if(a[0])
			add_history(a);
		ft_parse(a, &prompt);
		free(a);

	/******************************/
		t_list *oo = prompt.list_cmd;
		ft_exec(&prompt);
		ft_free_lis(oo);

	}
}
 