#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_yassir 	promet;

	//promet.env = env;
	promet.s_env = ft_creat_env(env); //		linked list
	promet.env = get_env(promet.s_env); // 		char ** alocated
	promet.exit_status = 0;
	promet.list_cmd = NULL;

	while(1)
	{
		char *a = readline(">");
		if (a == NULL)
			exit(0);
		ft_parse(a, &promet);
		free(a);

	/******************************/

		//ft_exec(&promet);
	}
}
